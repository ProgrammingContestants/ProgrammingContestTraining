package vmap.gui;

import java.awt.BorderLayout;
import java.awt.Dialog.ModalityType;
import java.awt.Dimension;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSlider;
import javax.swing.JTextField;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import vmap.Env;
import vmap.connection.Runner;
import vmap.connection.event.PrintLineListener;
import vmap.connection.event.ProcessFinishListener;
import vmap.model.FieldMap;
import vmap.model.TrampolineMappings;

/**
 * Mediator
 */
public class MainFrame extends JFrame
{
	private String previousInput;
	
	private FieldPanel fieldPanel;
	private JScrollPane scrollPane;
	
	private JButton buttonInitialize;
	private JButton buttonKill;
	private JButton buttonRestart;
	private JCheckBox checkSuppressStdErr;
	private JSlider sliderChipSize;
	private JLabel labelScore;
	private JTextField sentCommands;
	private Runner runner;
	private int nLines;
	private int turn;
	
	private ConsoleWindow console;
	
	public MainFrame()
	{
		setTitle("Lambda Lifting");
		
		fieldPanel = new FieldPanel();
		fieldPanel.setFocusable(true);
		fieldPanel.addKeyListener(new InputHandler());
		
		scrollPane = new JScrollPane(fieldPanel);
		scrollPane.setPreferredSize(new Dimension(400, 300));
		scrollPane.getViewport().addMouseListener(new MouseListener()
		{
			public void mouseReleased(MouseEvent e)
			{
			}
			
			public void mousePressed(MouseEvent e)
			{
				System.out.println("pressed");
			}
			
			public void mouseExited(MouseEvent e)
			{
			}
			
			public void mouseEntered(MouseEvent e)
			{
			}
			
			public void mouseClicked(MouseEvent e)
			{
			}
		});
		add(scrollPane);
		
		buttonInitialize = new JButton("Init");
		buttonInitialize.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				initialize();
			}
		});
		buttonKill = new JButton("Kill");
		buttonKill.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				killProcess();
			}
		});
		buttonKill.setEnabled(false);
		
		buttonRestart = new JButton("Restart");
		buttonRestart.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				restartSimulation();
			}
		});
		buttonRestart.setEnabled(false);
		
		checkSuppressStdErr = new JCheckBox("Suppress error output");
		
		labelScore = new JLabel("");
		
		sliderChipSize = new JSlider(1, 100, 32);
		sliderChipSize.addChangeListener(new ChangeListener()
		{
			public void stateChanged(ChangeEvent e)
			{
				fieldPanel.setChipSize(sliderChipSize.getValue());
				fieldPanel.repaint();
				fieldPanel.revalidate();
			}
		});
		
		JPanel toolPanel = new JPanel();
		toolPanel.add(buttonInitialize);
		toolPanel.add(buttonKill);
		toolPanel.add(buttonRestart);
		toolPanel.add(checkSuppressStdErr);
		toolPanel.add(sliderChipSize);
		add(toolPanel, BorderLayout.NORTH);
		
		sentCommands = new JTextField(30);
		sentCommands.setEditable(false);
		
		JPanel infoPanel = new JPanel();
		infoPanel.add(labelScore);
		infoPanel.add(sentCommands);
		add(infoPanel, BorderLayout.SOUTH);
		
		addWindowListener(new WindowAdapter()
		{
			public void windowClosed(WindowEvent e)
			{
				if (runner != null)
				{
					runner.exit();
				}
			}
		});
		
		console = new ConsoleWindow();
		console.setVisible(true);
	}
	
	public void setGameModel(FieldMap m)
	{
		fieldPanel.setFieldMap(m);
	}
	
	private String getFieldText(String inputString)
	{
		String[] lines = inputString.split("\n");
		String s = "";
		for (int i = 0; i < lines.length && !lines[i].isEmpty(); i++)
		{
			if (i != 0) s += "\n";
			s += lines[i];
		}
		return s;
	}
	
	private int calcHeight(String mapString)
	{
		String[] lines = mapString.split("\n");
		return lines.length;
	}
	
	private boolean createProcess(String initialInput)
	{
		if (runner != null) killProcess();
		
		String command = Env.getEnv().get("simulator");
		console.printCommand(command);
		
		Runner r = new Runner(command);
		r.setErrorListener(new PrintLineListener()
		{
			public void printLine(String line)
			{
				if (!checkSuppressStdErr.isSelected())
				{
					console.printStandardError(line);
				}
			}
		});
		r.setFinishListener(new ProcessFinishListener()
		{
			public void finished(int exitCode)
			{
				console.printStandardError("-- Exit Code = " + exitCode);
				buttonKill.setEnabled(false);
			}
		});
		
		boolean ret = r.start();
		if (ret)
		{
			runner = r;
			
			console.printStandardInput(initialInput);
			runner.sendString(initialInput);
			
			console.printStandardInput("END-OF-INPUT");
			runner.sendString("END-OF-INPUT");
		}
		else
		{
			JOptionPane.showMessageDialog(this,
				"Failed to execute: " + command + "\n" +
				"Check the simulator file name and/or the value of the key 'simulator' in env.txt",
				"Fatal Error",
				JOptionPane.ERROR_MESSAGE);
		}
		return ret;
	}
	
	private void killProcess()
	{
		if (runner == null) return;
		
		console.printStandardError("-- Kill");
		
		runner.exit();
		runner = null;
		
		buttonKill.setEnabled(false);
	}
	
	private void startSimulation(String input)
	{
		turn = 0;
		
		String fieldText = getFieldText(input);
		nLines = calcHeight(fieldText);
		
		if (createProcess(input))
		{
			previousInput = input;
			buttonRestart.setEnabled(true);
			
			// TODO: until supported by the simulator
			//fieldPanel.setTrampolineMapping(readTrampolineMappings());
			
			FieldMap m = FieldMap.fromString(fieldText);
			setGameModel(m);
			buttonKill.setEnabled(true);
		}
	}
	
	private void restartSimulation()
	{
		if (previousInput != null)
		{
			startSimulation(previousInput);
		}
	}
	
	private void initialize()
	{
		InitializeDialog dialog = new InitializeDialog();
		dialog.setModalityType(ModalityType.APPLICATION_MODAL);
		dialog.setVisible(true);
		if (dialog.isApproved())
		{
			startSimulation(dialog.getInputText());
		}
	}
	
	private TrampolineMappings readTrampolineMappings()
	{
		TrampolineMappings tmap = new TrampolineMappings();
		
		int n = Integer.parseInt(runner.readString(1));
		for (int i = 0; i < n; i++)
		{
			String[] pair = runner.readString(1).split(" ");
			if (pair.length == 2)
			{
				tmap.set(pair[0].charAt(0), pair[1].charAt(0) - '0');
			}
		}
		
		return tmap;
	}
	
	private void doCommand(String command)
	{
		console.printStandardInput(command);
		runner.sendString(command);
		
		String lines = runner.readString(nLines);
		console.printStandardOutput(lines);
		
		String score = runner.readString(1);
		console.printStandardOutput(score);
		
		String waterH = runner.readString(1);
		console.printStandardOutput(waterH);
		
		String currentProof = runner.readString(1);
		console.printStandardOutput(currentProof);
		
		String direction = runner.readString(1);
		console.printStandardOutput(direction);
		
		labelScore.setText("Turn: "
		
			+turn+++
		
		" Score: " + score);
		
		FieldMap m = FieldMap.fromString(lines);
		m.setWaterHeight(Integer.parseInt(waterH));
		m.setWaterProof(Integer.parseInt(currentProof));
		setGameModel(m);
		
		if (direction.equals("end"))
		{
			runner.exit();
			runner = null;
			buttonKill.setEnabled(false);
		}
	}
	
	private boolean processInput(int code)
	{
		boolean processed = true;
		
		String command = "";
		switch (code)
		{
		case KeyEvent.VK_LEFT:  command = "L"; break;
		case KeyEvent.VK_RIGHT: command = "R"; break;
		case KeyEvent.VK_UP:    command = "U"; break;
		case KeyEvent.VK_DOWN:  command = "D"; break;
		case KeyEvent.VK_S:     command = "S"; break;
		case KeyEvent.VK_W:     command = "W"; break;
		case KeyEvent.VK_A:     command = "A"; break;
		default:
			processed = false;
			break;
		}
		if (processed)
		{
			sentCommands.setText(sentCommands.getText() + command);
			doCommand(command);
		}
		return processed;
	}
	
	private class InputHandler extends KeyAdapter
	{
		public void keyPressed(KeyEvent e)
		{
			if (runner == null) return;
			if (processInput(e.getKeyCode())) e.consume();
		}
	}
	
	private static final long serialVersionUID = 1L;
}
