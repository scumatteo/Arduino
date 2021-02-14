package event;

public class IrrigationOn implements Event {
	
	private String irrigation;
	
	public IrrigationOn(String irrigation){
		this.irrigation = irrigation;
	}
	
	public String getIrrigation(){
		return this.irrigation;
	}

}
