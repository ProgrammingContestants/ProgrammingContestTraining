package vmap.gui;

import java.awt.BorderLayout;
import java.awt.Font;
import java.awt.Dialog.ModalityType;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSlider;
import javax.swing.JTextArea;
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
	
	private JButton buttonInitialize;
	private JButton buttonKill;
	private JButton buttonRestart;
	private JCheckBox checkSuppressStdErr;
	private JSlider sliderChipSize;
	
	private JTextArea inputMoves;
	private JButton buttonCommitMoves;
	
	private JLabel labelScore;
	private JTextField sentCommands;
	private Runner runner;
	private int nLines;
	private int turn;
	
	private ConsoleWindow console;
	
	private boolean commiting;
	private Thread commitingThread;
	
	public MainFrame()
	{
		setTitle("Lambda Lifting");
		
		fieldPanel = new FieldPanel();
		fieldPanel.setFocusable(true);
		fieldPanel.addKeyListener(new InputHandler());
		
		JScrollPane sp = new JScrollPane(fieldPanel);
		sp.setPreferredSize(new Dimension(400, 300));
		add(sp);
		
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
		toolPanel.setLayout(new BoxLayout(toolPanel, BoxLayout.Y_AXIS));
		
		JPanel panel0 = new JPanel();
		panel0.add(buttonInitialize);
		panel0.add(buttonKill);
		panel0.add(buttonRestart);
		panel0.add(checkSuppressStdErr);
		panel0.add(sliderChipSize);
		
		inputMoves = new JTextArea();
		inputMoves.setFont(new Font(Font.DIALOG_INPUT, Font.PLAIN, 12));
		buttonCommitMoves = new JButton("Commit");
		buttonCommitMoves.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				startCommits();
			}
		});
		
		JPanel panel1 = new JPanel(new BorderLayout());
		panel1.add(new JLabel("Input Moves:"), BorderLayout.WEST);
		panel1.add(new JScrollPane(inputMoves), BorderLayout.CENTER);
		panel1.add(buttonCommitMoves, BorderLayout.EAST);
		panel1.setPreferredSize(new Dimension(100, 60));
		
		toolPanel.add(panel0);
		toolPanel.add(panel1);
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
		endCommits();
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
			
			fieldPanel.setTrampolineMapping(makeTrampolineMappings(input));
			
			FieldMap m = FieldMap.fromString(fieldText);
			setGameModel(m);
			buttonKill.setEnabled(true);
			sentCommands.setText("");
			fieldPanel.requestFocus();
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
	
	private void startCommits()
	{
		if (commiting) return;
		
		commiting = true;
		buttonCommitMoves.setEnabled(false);
		inputMoves.setEditable(false);
		
		commitingThread = new Thread()
		{
			public void run()
			{
				try
				{
					while (commiting)
					{
						commitOneMove();
						Thread.sleep(500);
					}
				}
				catch (InterruptedException e)
				{
				}
			}
		};
		commitingThread.setDaemon(true);
		commitingThread.start();
	}
	
	private void endCommits()
	{
		if (!commiting) return;
		
		buttonCommitMoves.setEnabled(true);
		inputMoves.setEditable(true);
		commiting = false;
	}
	
	private void commitOneMove()
	{
		if (runner == null) return;
		
		String moves = inputMoves.getText();
		
		if (moves.isEmpty()) return;
		
		while (!moves.isEmpty())
		{
			char c = Character.toUpperCase(moves.charAt(0));
			moves = moves.substring(1);
			if ("LRUDSWA".indexOf(c) != -1)
			{
				String cmd = Character.toString(c);
				sentCommands.setText(sentCommands.getText() + cmd);
				doCommand(cmd);
				break;
			}
		}
		
		inputMoves.setText(moves);
		if (moves.isEmpty())
		{
			endCommits();
		}
		
		inputMoves.setCaretPosition(0);
	}
	
	// simple parser
	private TrampolineMappings makeTrampolineMappings(String input)
	{
		TrampolineMappings tm = new TrampolineMappings();
		String[] lines = input.split("\n");
		for (int i = 0; i < lines.length; i++)
		{
			String s = lines[i];
			if (!s.startsWith("Trampoline")) continue;
			String[] r = s.split(" "); // Trampoline $0 targets $1
			if (r.length == 4)
			{
				tm.set(r[1].charAt(0), r[3].charAt(0) - '0');
			}
		}
		return tm;
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
			endCommits();
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
			if (runner == null || commiting) return;
			if (processInput(e.getKeyCode())) e.consume();
		}
	}
	
	private static final long serialVersionUID = 1L;
}
