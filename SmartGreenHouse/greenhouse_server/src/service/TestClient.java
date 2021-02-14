package service;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.Vertx;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.client.WebClient;

public class TestClient extends AbstractVerticle {
	
	public static void main(String[] args) {		
	
		Vertx vertx = Vertx.vertx();
		WebClient webClient = WebClient.create(vertx);
		
		JsonObject item = new JsonObject().put("value", 24);
		
		webClient.post(8082, "localhost", "/api/data")
		  .sendJsonObject(item, ar->{
			  if(ar.succeeded()) {
				  System.out.println("Dati inviati");
			  }
		  });
	}
	
}
