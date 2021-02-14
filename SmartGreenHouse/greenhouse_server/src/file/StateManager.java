package file;

import org.json.JSONObject;

public class StateManager {
	
	public static void writeState(String state) {
		JSONObject jobj = new JSONObject(FileManager.readFile("src/file/history.json"));;
		jobj.put("status", state);
		FileManager.writeFile(jobj, "src/file/history.json");
	}

}
