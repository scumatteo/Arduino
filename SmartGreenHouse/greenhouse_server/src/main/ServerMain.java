package main;

import fsm.FinalStateMachine;
import io.vertx.core.Vertx;
import serial.MessageManager;
import serial.SerialCommChannel;
import service.DataService;
import state.*;

public class ServerMain {
	
	public static void main(String[] args) throws Exception {
		
		StateUtils.setState(MyState.OFF);
		Vertx vertx = Vertx.vertx();
		DataService service = new DataService(8080);
		vertx.deployVerticle(service);
		SerialCommChannel serial = new SerialCommChannel("COM5", 9600);
		MessageManager message = new MessageManager(serial);
		new FinalStateMachine(service, message).start();
		
	}
	
}
