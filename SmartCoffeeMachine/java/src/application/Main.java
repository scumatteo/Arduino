package application;

import gui.View;
import javafx.application.Application;
import javafx.stage.Stage;
import message.MessageManager;
import message.SerialCommChannel;

public class Main extends Application{
	
	public static void main(String[] args) {
		launch(args);
	}

	@Override
	public void start(Stage primaryStage) throws Exception {
		SerialCommChannel channel = new SerialCommChannel("COM3", 9600);
		System.out.println("Waiting for arduino rebooting...");
		Thread.sleep(4000);		
		View v = new View(primaryStage);
		MessageManager m = new MessageManager(channel, v);
		v.init(m);
		Loop l= new Loop(v, m);
		new Thread(l).start();
		
		
		
		
		
	}

	
	
}
