package event;

public class Humidity implements Event {
	
	private int humidity;
	
	public Humidity(int humidity) {
		this.humidity = humidity;
	}
	
	public int getHumidity() {
		return this.humidity;
	}

}
