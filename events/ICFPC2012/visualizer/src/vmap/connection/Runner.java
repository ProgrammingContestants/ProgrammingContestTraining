package vmap.connection;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;

import vmap.connection.event.PrintLineListener;

public class Runner
{
	private ProcessBuilder pb;
	private Process p;
	private PrintWriter writer;
	private BufferedReader reader;
	private PrintLineListener errListener;
	
	public Runner(String cmd)
	{
		pb = new ProcessBuilder(cmd);
	}
	
	public void setErrorListener(PrintLineListener l)
	{
		errListener = l;
	}
	
	public boolean start()
	{
		boolean ret = false;
		try
		{
			p = pb.start();
			
			final BufferedReader errReader = new BufferedReader(new InputStreamReader(p.getErrorStream()));
			new Thread()
			{
				public void run()
				{
					try
					{
						String line;
						while ((line = errReader.readLine()) != null)
						{
							if (errListener != null) errListener.printLine(line);
						}
					}
					catch (IOException e)
					{
					}
				}
			}.start();
			
			reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
			writer = new PrintWriter(p.getOutputStream());
			ret = true;
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
		return ret;
	}
	
	public void exit()
	{
		if (p == null)
			throw new RuntimeException("Process is null.");
		
		p.destroy();
		try
		{
			p.getInputStream().close();
			p.getOutputStream().close();
			p.getErrorStream().close();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}
	
	public void sendString(String s)
	{
		writer.print(s + "\n");
		writer.flush();
	}
	
	public String readString(int nLines)
	{
		String s = "";
		try
		{
			for (int i = 0; i < nLines; i++)
			{
				if (i != 0) s += "\n";
				s += reader.readLine();
			}
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
		return s;
	}
}
