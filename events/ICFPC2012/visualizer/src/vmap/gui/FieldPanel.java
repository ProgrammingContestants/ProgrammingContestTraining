package vmap.gui;

import java.awt.AlphaComposite;
import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Composite;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Point;
import java.awt.Stroke;
import java.awt.Transparency;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.JPanel;

import vmap.Env;
import vmap.model.Cell;
import vmap.model.FieldMap;
import vmap.model.TrampolineMappings;

public class FieldPanel extends JPanel
{
	private static final Stroke STROKE_ARROW = new BasicStroke(3.0F);
	private static final int FADE_COUNT = 20;
	
	private Image img;
	private Image prevImage;
	private BufferedImage drawingImage;
	private int fadeCount;
	private int chipSize = 32;
	
	private TrampolineMappings tmap;
	private FieldMap fieldMap;
	
	public FieldPanel()
	{
		try
		{
			String fileName = "mc.png";
			Env env = Env.getEnv();
			if (env.isSet("cell_image_file"))
			{
				fileName = env.get("cell_image_file");
			}
			img = ImageIO.read(new File(fileName));
		}
		catch (IOException e)
		{
			img = new BufferedImage(384, 48, Transparency.OPAQUE);
		}
		
		addMouseListener(new MouseAdapter()
		{
			public void mousePressed(MouseEvent e)
			{
				requestFocus();
			}
		});
		addFocusListener(new FocusListener()
		{
			public void focusLost(FocusEvent e)
			{
				repaint();
			}
			
			public void focusGained(FocusEvent e)
			{
				repaint();
			}
		});
		
		Thread animThread = new AnimationThread();
		animThread.setDaemon(true);
		animThread.start();
	}
	
	public void setChipSize(int size)
	{
		chipSize = size;
		recalcPreferredSize();
		repaint();
		revalidate();
	}
	
	public void setTrampolineMapping(TrampolineMappings tm)
	{
		tmap = tm;
	}
	
	public void setFieldMap(FieldMap m)
	{
		fieldMap = m;
		prevImage = drawingImage;
		fadeCount = 0;
		
		Dimension size = getActualFieldSize();
		drawingImage = new BufferedImage(size.width, size.height, Transparency.TRANSLUCENT);
		
		recalcPreferredSize();
		repaint();
		revalidate();
	}
	
	public FieldMap getFieldMap()
	{
		return fieldMap;
	}
	
	protected void paintComponent(Graphics g)
	{
		g.setColor(Color.BLACK);
		g.fillRect(0, 0, getWidth(), getHeight());
		
		Point o = getOrigin();
		g.translate(o.x, o.y);
		
		if (fieldMap != null)
		{
			Graphics gBuf = drawingImage.getGraphics();
			drawField(gBuf);
			gBuf.dispose();
			
			if (prevImage == null || fadeCount >= FADE_COUNT)
			{
				g.drawImage(drawingImage, 0, 0, null);
			}
			else
			{
				drawImageInterpol((Graphics2D)g, prevImage, drawingImage, (float)fadeCount / FADE_COUNT);
			}
		}
		
		if (tmap != null)
		{
			drawTrampoline(g);
		}
		
		g.translate(-o.x, -o.y);
		
		if (isFocusOwner())
		{
			g.setColor(Color.RED);
			g.drawString("READY", 20, 20);
		}
	}
	
	private void drawField(Graphics g)
	{
		for (int iy = 0; iy < fieldMap.getHeight(); iy++)
		{
			for (int ix = 0; ix < fieldMap.getWidth(); ix++)
			{
				Point p = toView(ix, iy);
				Cell cell = fieldMap.getCell(ix, iy);
				drawImagePart(g, p.x, p.y, cell.ordinal());
				if (cell == Cell.ROBOT)
				{
					Color color = g.getColor();
					g.setColor(Color.RED);
					g.drawString(Integer.toString(fieldMap.getWaterProof()), p.x, p.y);
					g.setColor(color);
				}
			}
		}
		
		int wh = fieldMap.getWaterHeight();
		if (wh > 0)
		{
			Point p0 = toView(0, fieldMap.getHeight() - wh);
			Point p1 = toView(fieldMap.getWidth() - 1, fieldMap.getHeight() - 1);
			p1.translate(chipSize, chipSize);
			g.setColor(new Color(0, 0, 255, 80));
			g.fillRect(p0.x, p0.y, p1.x - p0.x, p1.y - p0.y);
		}
	}
	
	private void drawTrampoline(Graphics g)
	{
		for (char c = 'A'; c <= 'I'; c++)
		{
			int target = tmap.get(c);
			if (target == -1) continue;
			int[] i0 = fieldMap.getTrampoline(c);
			int[] i1 = fieldMap.getTarget(target);
			if (i0 == null || i1 == null) continue;
			Point p0 = toView(i0[0], i0[1]);
			Point p1 = toView(i1[0], i1[1]);
			p0.translate(chipSize / 2, chipSize / 2);
			p1.translate(chipSize / 2, chipSize / 2);
			drawArrowEdge((Graphics2D)g, p0, p1);
		}
	}
	
	private static void drawArrowEdge(Graphics2D g, Point p0, Point p1)
	{
		g.setColor(new Color(255, 128, 0, 128));
		g.setStroke(STROKE_ARROW);
		
		double a = Math.atan2(p1.y - p0.y, p1.x - p0.x);
		g.drawLine(p0.x, p0.y, p1.x, p1.y);
		
		double l = 8, b = Math.toRadians(30);
		g.drawLine(p1.x, p1.y, (int)(p1.x - l * Math.cos(a + b)), (int)(p1.y - l * Math.sin(a + b)));
		g.drawLine(p1.x, p1.y, (int)(p1.x - l * Math.cos(a - b)), (int)(p1.y - l * Math.sin(a - b)));
	}
	
	private static void drawImageInterpol(Graphics2D g, Image img0, Image img1, float t)
	{
		Composite compSave = g.getComposite();
		
		g.drawImage(img0, 0, 0, null);
		
		g.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_OVER, t));
		g.drawImage(img1, 0, 0, null);
		
		g.setComposite(compSave);
	}
	
	private void recalcPreferredSize()
	{
		Dimension size = getActualFieldSize();
		size.width += 2 * 20;
		size.height += 2 * 20;
		setPreferredSize(size);
	}
	
	private Point toView(int ix, int iy)
	{
		return new Point(chipSize * ix, chipSize * iy);
	}
	
	private Dimension getActualFieldSize()
	{
		if (fieldMap == null) return new Dimension();
		return new Dimension(chipSize * fieldMap.getWidth(), chipSize * fieldMap.getHeight());
	}
	
	private Point getOrigin()
	{
		Dimension size = getActualFieldSize();
		return new Point((getWidth() - size.width) / 2, (getHeight() - size.height) / 2);
	}
	
	private void drawImagePart(Graphics g, int x, int y, int index)
	{
		int sx = index * 48;
		g.drawImage(img, x, y, x + chipSize, y + chipSize, sx, 0, sx + 48, 48, null);
	}
	
	private class AnimationThread extends Thread
	{
		public void run()
		{
			try
			{
				while (true)
				{
					if (fadeCount < FADE_COUNT) fadeCount++;
					repaint();
					Thread.sleep(20);
				}
			}
			catch (InterruptedException e)
			{
			}
		}
	}
	
	private static final long serialVersionUID = 1L;
}
