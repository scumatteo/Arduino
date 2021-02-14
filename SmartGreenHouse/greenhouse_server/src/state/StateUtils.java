package state;

public class StateUtils {
	
	private static MyState currentState;
	
	public static void setState(MyState state) {
		currentState = state;
	}
	
	public static MyState getState() {
		return currentState;
	}

}
