package fsm;

import event.Event;

public interface Handler {
	void handle(Event ev);
}
