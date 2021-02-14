package event;

import java.util.LinkedList;

public class ObservableImpl implements Observable {
	
	private LinkedList<Observer> observers;
	
	protected ObservableImpl(){
		observers = new LinkedList<Observer>();
	}

	@Override
	public void notifyEvent(Event ev) {
		synchronized (observers){
			for (Observer obs: observers){
				obs.notifyEvent(ev);
			}
		}
	}

	@Override
	public void addObserver(Observer obs) {
		synchronized (observers){
			observers.add(obs);
		}
		
	}

	@Override
	public void removeObserver(Observer obs) {
		synchronized (observers){
			observers.remove(obs);
		}
		
	}

}
