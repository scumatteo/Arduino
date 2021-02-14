package serial;

import event.AutoState;
import event.IrrigationOn;
import event.ManualState;
import event.ObservableImpl;

public class MessageManager extends ObservableImpl{
	
	private SerialCommChannel channel;
	
	public MessageManager(SerialCommChannel channel) {
		this.channel = channel;
	}
	
	public synchronized void manageMessage() throws InterruptedException {
		if(channel.isMsgAvailable()) {
			String msg = channel.receiveMsg();
			if(msg.equals("m")) {
				this.notifyEvent(new ManualState());
			}
			else if(msg.equals("a")) {
				this.notifyEvent(new AutoState());
			}
			else {
				this.notifyEvent(new IrrigationOn(msg));
			}
		}	
	}
	
	public synchronized void sendMassage(String msg) {
		this.channel.sendMsg(msg);
	}	

}
