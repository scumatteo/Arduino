package application;

import gui.View;
import javafx.application.Platform;
import message.MessageManager;

public class Loop extends Thread{

	private View v;
	private MessageManager m;
	
	public Loop(View v, MessageManager m) {
		this.v = v;
		this.m = m;
	}
	
	@Override
	public void run() {
		while(true) {
			try {
				m.manageMessage();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			Platform.runLater(new Runnable() {
				
				@Override
				public void run() {
					v.updateView();					
				}
			});
			try {
				Thread.sleep(20);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
	}
}
