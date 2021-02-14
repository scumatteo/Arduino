package file;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

import org.json.JSONArray;
import org.json.JSONObject;

public class SegnalationManager {
	
	public static void writeSegnalation() {
		DateFormat df = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss");
		Date time = new Date(System.currentTimeMillis());
		JSONObject obj = new JSONObject();
		obj.put("time", df.format(time));
		JSONObject jobj = new JSONObject(FileManager.readFile("src/file/history.json"));
		JSONArray jarr = jobj.getJSONArray("notification");
		jarr.put(obj);
		jobj.put("notification", jarr);
		FileManager.writeFile(jobj, "src/file/history.json");
	}

}
