package vmap.model;

import java.util.Arrays;

public class FieldMap
{
	private static final Cell[] CMAP = new Cell[128];
	
	static
	{
		CMAP['R'] = Cell.ROBOT;
		CMAP['#'] = Cell.WALL;
		CMAP['*'] = Cell.ROCK;
		CMAP['\\'] = Cell.LAMBDA;
		CMAP['L'] = Cell.CLOSED_LIFT;
		CMAP['O'] = Cell.OPEN_LIFT;
		CMAP['.'] = Cell.EARTH;
		CMAP['W'] = Cell.BEARD;
		CMAP['!'] = Cell.RAZOR;
		CMAP[' '] = Cell.EMPTY;
	}
	
	private int width;
	private int height;
	private Cell[][] cells;
	private int waterHeight;
	private int waterProof;
	private int[][] trampolines = new int[9][];
	private int[][] targets = new int[9][];
	
	public FieldMap(int width, int height)
	{
		this.width = width;
		this.height = height;
		
		cells = new Cell[width][height];
		for (int ix = 0; ix < width; ix++) Arrays.fill(cells[ix], Cell.EMPTY);
	}
	
	public int getWidth()
	{
		return width;
	}
	
	public int getHeight()
	{
		return height;
	}
	
	public Cell getCell(int ix, int iy)
	{
		return cells[ix][iy];
	}
	
	public void setCell(int ix, int iy, Cell c)
	{
		cells[ix][iy] = c;
	}
	
	public int getWaterHeight()
	{
		return waterHeight;
	}
	
	public void setWaterHeight(int h)
	{
		waterHeight = h;
	}
	
	public int getWaterProof()
	{
		return waterProof;
	}
	
	public void setWaterProof(int value)
	{
		waterProof = value;
	}
	
	public int[] getTrampoline(char c)
	{
		return trampolines[c - 'A'];
	}
	
	public int[] getTarget(int i)
	{
		return targets[i - 1];
	}
	
	public static FieldMap fromString(String s)
	{
		String[] lines = s.split("\\n");
		
		if (lines.length == 0)
		{
			return null;
		}
		
		int nx = lines[0].length(), ny = lines.length;
		FieldMap m = new FieldMap(nx, ny);
		for (int iy = 0; iy < ny; iy++)
		{
			for (int ix = 0; ix < nx; ix++)
			{
				char c = lines[iy].charAt(ix);
				if ('A' <= c && c <= 'I')
				{
					m.trampolines[c - 'A'] = new int[] { ix, iy };
					m.setCell(ix, iy, Cell.TRAMPOLINE);
				}
				else if ('1' <= c && c <= '9')
				{
					m.targets[c - '1'] = new int[] { ix, iy };
					m.setCell(ix, iy, Cell.TARGET);
				}
				else
				{
					m.setCell(ix, iy, CMAP[c]);
				}
			}
		}
		return m;
	}
}
