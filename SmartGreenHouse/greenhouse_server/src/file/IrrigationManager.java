package file;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

import org.json.JSONArray;
import org.json.JSONObject;

public class IrrigationManager {
	
	public static void writeIrrigation(int value) {
		DateFormat df = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss");	
	    //int value = 20; //valore di prova
		Date time = new Date(System.currentTimeMillis());
		JSONObject obj = new JSONObject();
		obj.put("time", df.format(time));
		obj.put("value", value);
		JSONObject jobj = new JSONObject(FileManager.readFile("src/file/history.json"));
		JSONArray jarr = jobj.getJSONArray("irrigation");
		jarr.put(obj);
		jobj.put("irrigation", jarr);
		FileManager.writeFile(jobj, "src/file/history.json");
	}

}
