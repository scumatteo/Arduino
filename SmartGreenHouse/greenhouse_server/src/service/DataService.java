package service;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.handler.BodyHandler;
import java.util.LinkedList;

import org.json.JSONObject;

import event.Event;
import event.Humidity;
import event.Observable;
import event.Observer;
import file.FileManager;


/**
 * Classe per riceve i dati in post dal client(espruino) e scriverli su json.
 */
public class DataService extends AbstractVerticle implements Observable{

	private LinkedList<Observer> observers;
	private int port;
	
	public DataService(int port) {	
		this.port = port;
		observers = new LinkedList<Observer>();
	}

	@Override
	public void start() {		
		Router router = Router.router(vertx);
		router.route().handler(BodyHandler.create());
		router.post("/api/data").handler(this::handleAddNewData);
		router.get("/api/data").handler(this::handleGetData);
		vertx.createHttpServer().requestHandler(router).listen(port);
		log("Server ready.");
	}
	
	private synchronized void handleAddNewData(RoutingContext routingContext) {
		HttpServerResponse response = routingContext.response();
		JsonObject res = routingContext.getBodyAsJson();
		if (res == null) {
			sendError(400, response);
		} else {
			int value = res.getInteger("value");
			this.notifyEvent(new Humidity(value));	
		    //int value = 20; //valore di prova
			response.setStatusCode(200).end();
		}
	}
	
	private synchronized void handleGetData(RoutingContext routingContext) {
		JSONObject jobj = new JSONObject(FileManager.readFile("src/file/history.json"));
		routingContext.response().putHeader("content-type", "application/json")
		.end(jobj.toString());
	}
	
	private void sendError(int statusCode, HttpServerResponse response) {
		response.setStatusCode(statusCode).end();
	}

	private void log(String msg) {
		System.out.println("[GREENHOUSE SERVER] "+msg);
	}

	@Override
	public void notifyEvent(Event ev) {
		synchronized (observers){
			for (Observer obs: observers){
				obs.notifyEvent(ev);
			}
		}
	}

	@Override
	public void addObserver(Observer obs) {
		synchronized (observers){
			observers.add(obs);
		}
		
	}

	@Override
	public void removeObserver(Observer obs) {
		synchronized (observers){
			observers.remove(obs);
		}
		
	}
}