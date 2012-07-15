package vmap;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Map;

public class Env
{
	private static final File ENV_FILE = new File("./env.txt");
	private static Env env;
	
	private Map<String, String> vars = new HashMap<String, String>();
	
	public Env()
	{
		try
		{
			BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(ENV_FILE)));
			
			String line;
			while ((line = reader.readLine()) != null)
			{
				int i = line.indexOf('#');
				if (i != -1) line = line.substring(0, i);
				
				String[] pair = line.split("\\s+=\\s+");
				
				if (pair.length != 2) continue;
				pair[0] = pair[0].trim();
				pair[1] = pair[1].trim();
				if (pair[0].isEmpty() || pair[1].isEmpty()) continue;
				vars.put(pair[0], pair[1]);
			}
		}
		catch (FileNotFoundException e)
		{
			e.printStackTrace();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}
	
	public String get(String k)
	{
		String v = vars.get(k);
		return v != null ? v : "";
	}
	
	public boolean isSet(String k)
	{
		return vars.containsKey(k);
	}
	
	public static Env getEnv()
	{
		if (env == null)
		{
			env = new Env();
		}
		return env;
	}
}
