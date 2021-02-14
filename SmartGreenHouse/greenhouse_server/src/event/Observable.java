package event;

public interface Observable {
	
	void notifyEvent(Event ev);

	void addObserver(Observer obs);

	void removeObserver(Observer obs);

}
