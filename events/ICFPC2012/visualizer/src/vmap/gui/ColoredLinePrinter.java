package vmap.gui;

import java.awt.Color;
import java.awt.Font;

import javax.swing.JTextPane;
import javax.swing.text.BadLocationException;
import javax.swing.text.Document;
import javax.swing.text.Element;
import javax.swing.text.SimpleAttributeSet;
import javax.swing.text.StyleConstants;

public class ColoredLinePrinter extends JTextPane
{
	public ColoredLinePrinter()
	{
		setFont(new Font(Font.DIALOG_INPUT, Font.PLAIN, 12));
		setForeground(Color.WHITE);
		setBackground(Color.BLACK);
	}
	
	public void appendLine(String line)
	{
		appendLine(line, getForeground());
	}
	
	public void appendLine(String line, Color fg)
	{
		appendLine(line, fg, getBackground());
	}
	
	public void appendLine(String line, Color fg, Color bg)
	{
		SimpleAttributeSet a = new SimpleAttributeSet();
		StyleConstants.setForeground(a, fg);
		StyleConstants.setBackground(a, bg);
		
		Document doc = getDocument();
		try
		{
			doc.insertString(doc.getLength(), line + "\n", a);
		}
		catch (BadLocationException e)
		{
			e.printStackTrace();
		}
		
        Element elem = doc.getDefaultRootElement();
        int offset = elem.getElement(elem.getElementCount() - 1).getStartOffset();
        setCaretPosition(offset - 1);
	}
	
	private static final long serialVersionUID = 1L;
}
