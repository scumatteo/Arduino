package fsm;

import event.AutoState;
import event.Event;
import event.Humidity;
import event.ManualState;
import event.IrrigationOn;
import event.Tick;
import file.HumidityManager;
import file.IrrigationManager;
import file.SegnalationManager;
import file.StateManager;
import event.ObservableTimer;
import serial.MessageManager;
import service.DataService;
import state.*;

public class FinalStateMachine extends EventLoopControllerWithHandlers{
	
	private static final int MIN = 30;
	private static final int MED = 60;
	private static final int MAX = 90;
	private DataService server;
	private MessageManager message;
	private MyState currentState;
	private ObservableTimer timer;
	
	
	public FinalStateMachine(DataService server, MessageManager message) {
		this.server = server;
		this.message = message;
		this.timer = new ObservableTimer();
		this.startObserving(this.server);
		this.startObserving(this.message);
		this.startObserving(this.timer);
	}

	@Override
	protected void setupHandlers() {
		addHandler(Humidity.class, (Event ev) -> {			
			try {
				HumidityManager.writeHumidity(((Humidity) ev).getHumidity());
				if(!this.currentState.equals(MyState.MANUAL)) {
					if(((Humidity) ev).getHumidity() < 30 && ((Humidity) ev).getHumidity() > 20) {
						this.message.sendMassage(Integer.toString(MIN));
						IrrigationManager.writeIrrigation(MIN);
						timer.start(6500);
						this.currentState = MyState.ON;
						
					}
					else if(((Humidity) ev).getHumidity() < 20 && ((Humidity) ev).getHumidity() > 10) {
						this.message.sendMassage(Integer.toString(MED));
						IrrigationManager.writeIrrigation(MED);
						timer.start(6500);
						this.currentState = MyState.ON;
						
					}
					else if(((Humidity) ev).getHumidity() < 10) {
						this.message.sendMassage(Integer.toString(MAX));
						IrrigationManager.writeIrrigation(MAX);
						timer.start(6500);
						this.currentState = MyState.ON;
					}
					else if(((Humidity) ev).getHumidity() > 35 && this.currentState.equals(MyState.ON)) {
						timer.stop();
					}
				}	
				else {
					this.message.sendMassage(Integer.toString(((Humidity) ev).getHumidity()));
				}
			}
			catch (Exception ex) {}
		}).addHandler(Tick.class, (Event ev) -> {
			try {
				SegnalationManager.writeSegnalation();
			}
			catch (Exception ex) {}
		}).addHandler(IrrigationOn.class, (Event ev) -> {
			if(this.currentState.equals(MyState.MANUAL)){
				IrrigationManager.writeIrrigation(Integer.parseInt(((IrrigationOn) ev).getIrrigation()));
				timer.start(6500);
			}
			
		}).addHandler(ManualState.class, (Event ev) -> {
			this.currentState = MyState.MANUAL;
			StateManager.writeState("manual");
		}).addHandler(AutoState.class, (Event ev) -> {
			this.currentState = MyState.OFF; 
			StateManager.writeState("auto");
		});
		
	}

}
