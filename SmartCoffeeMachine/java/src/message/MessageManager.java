package message;

import gui.View;

public class MessageManager {
	
	private SerialCommChannel channel;
	private View v;
	
	public MessageManager(SerialCommChannel channel, View v) {
		this.channel = channel;
		this.v = v;
	}
	
	public void manageMessage() throws InterruptedException {
		if(channel.isMsgAvailable()) {
			String msg = channel.receiveMsg();
			if(msg.equals("0") || msg.equals("1") || msg.equals("2")
					|| msg.equals("3")) {
				v.setSugar(Integer.parseInt(msg));
			}
			else if(msg.equals("m")) {
				v.setMaintenanceOn();
			}
			else{
				v.setMessage(msg);
			}
		}	
	}
	
	public void sendMassage(String msg) {
		this.channel.sendMsg(msg);
	}
	
	

}
