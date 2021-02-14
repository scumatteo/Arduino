package file;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;

import org.json.JSONObject;

public class FileManager {
	
	private static BufferedWriter bw;
	private static BufferedReader br;
	
	public static String readFile(String filename) {
	    String result = "";
	    try {
	        br = new BufferedReader(new FileReader(filename));
	        StringBuilder sb = new StringBuilder();
	        String line = br.readLine();
	        while (line != null) {
	            sb.append(line);
	            line = br.readLine();
	        }
	        br.close();
	        result = sb.toString();
	    } catch(Exception e) {
	        e.printStackTrace();
	    }
	    return result;
	}
	
	
	
	public static void writeFile(JSONObject obj, String filename) {
	    try {
	        bw = new BufferedWriter(new FileWriter(filename));
	        bw.write(obj.toString());
	        bw.close();
	    } catch(Exception e) {
	        e.printStackTrace();
	    }
	}

}
