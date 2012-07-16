package vmap.gui;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

public class InitializeDialog extends JDialog
{
	private JTextArea input;
	private JButton buttonOK;
	private JButton buttonCancel;
	private boolean approved;
	
	public InitializeDialog()
	{
		setTitle("Initialize");
		
		JLabel label = new JLabel("Input field map string.");
		label.setOpaque(true);
		label.setBackground(Color.WHITE);
		label.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));
		add(label, BorderLayout.NORTH);
		
		input = new JTextArea();
		input.setFont(new Font(Font.DIALOG_INPUT, Font.PLAIN, 12));
		JScrollPane jsp = new JScrollPane(input);
		jsp.setPreferredSize(new Dimension(300, 300));
		add(jsp, BorderLayout.CENTER);
		
		buttonOK = new JButton("OK");
		buttonOK.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				okPushed();
			}
		});
		
		buttonCancel = new JButton("Cancel");
		buttonCancel.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				cancelPushed();
			}
		});
		
		JButton buttonOpen = new JButton("From file");
		buttonOpen.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				openFile();
			}
		});
		
		JPanel buttonPanel = new JPanel();
		buttonPanel.add(buttonOK);
		buttonPanel.add(buttonCancel);
		buttonPanel.add(buttonOpen);
		add(buttonPanel, BorderLayout.SOUTH);
		
		pack();
		setLocationRelativeTo(null);
	}
	
	public String getInputText()
	{
		return input.getText();
	}
	
	public boolean isApproved()
	{
		return approved;
	}
	
	private void openFile()
	{
		JFileChooser chooser = new JFileChooser(".");
		int ret = chooser.showOpenDialog(this);
		if (ret == JFileChooser.APPROVE_OPTION)
		{
			String text = readFromFile(chooser.getSelectedFile());
			input.setText(text);
		}
	}
	
	private static String readFromFile(File file)
	{
		StringBuilder buf = new StringBuilder();
		try
		{
			BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(file)));
			String line;
			boolean flag = false;
			while ((line = reader.readLine()) != null)
			{
				if (flag) buf.append("\n");
				buf.append(line);
				flag = true;
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
		return buf.toString();
	}
	
	private void okPushed()
	{
		approved = true;
		dispose();
	}
	
	private void cancelPushed()
	{
		dispose();
	}
	
	private static final long serialVersionUID = 1L;
}
