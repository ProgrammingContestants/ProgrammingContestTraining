package vmap.gui;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.WindowConstants;

import vmap.Env;

public class ConsoleWindow extends JFrame
{
	private ColoredLinePrinter printer;
	private Color colorCmdFore;
	private Color colorCmdBack;
	private Color colorOutFore;
	private Color colorOutBack;
	private Color colorErrFore;
	private Color colorErrBack;
	private Color colorInpFore;
	private Color colorInpBack;
	
	public ConsoleWindow()
	{
		setTitle("Console");
		setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);
		
		printer = new ColoredLinePrinter();
		printer.setPreferredSize(new Dimension(400, 300));
		add(new JScrollPane(printer), BorderLayout.CENTER);
		
		JButton buttonClear = new JButton("Clear");
		buttonClear.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				printer.setText("");
			}
		});
		add(buttonClear, BorderLayout.SOUTH);
		
		pack();
		
		initColors();
	}
	
	private void initColors()
	{
		Env env = Env.getEnv();
		colorCmdFore = getColor(env.get("color_cmd_fore"), Color.WHITE);
		colorCmdBack = getColor(env.get("color_cmd_back"), Color.BLUE);
		colorOutFore = getColor(env.get("color_out_fore"), Color.WHITE);
		colorOutBack = getColor(env.get("color_out_back"), Color.BLACK);
		colorErrFore = getColor(env.get("color_err_fore"), Color.GRAY);
		colorErrBack = getColor(env.get("color_err_back"), Color.BLACK);
		colorInpFore = getColor(env.get("color_inp_fore"), Color.YELLOW);
		colorInpBack = getColor(env.get("color_inp_back"), Color.BLACK);
	}
	
	private static Color getColor(String s, Color def)
	{
		Color c;
		try
		{
			c = !s.isEmpty() ? Color.decode(s) : def;
		}
		catch (NumberFormatException e)
		{
			c = def;
		}
		return c;
	}
	
	public void printCommand(String s)
	{
		printer.appendLine(s, colorCmdFore, colorCmdBack);
	}
	
	public void printStandardInput(String s)
	{
		printer.appendLine(s, colorInpFore, colorInpBack);
	}
	
	public void printStandardOutput(String s)
	{
		printer.appendLine(s, colorOutFore, colorOutBack);
	}
	
	public void printStandardError(String s)
	{
		printer.appendLine(s, colorErrFore, colorErrBack);
	}
	
	private static final long serialVersionUID = 1L;
}
