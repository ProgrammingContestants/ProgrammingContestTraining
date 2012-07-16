package vmap.model;

import java.util.Arrays;

public class TrampolineMappings
{
	private int[] map = new int[9];
	
	public TrampolineMappings()
	{
		clear();
	}
	
	public void clear()
	{
		Arrays.fill(map, -1);
	}
	
	public void set(char c, int target)
	{
		check(c);
		map[c - 'A'] = target;
	}
	
	public int get(char c)
	{
		check(c);
		return map[c - 'A'];
	}
	
	private void check(char c)
	{
		if (c < 'A' || 'I' < c)
			throw new RuntimeException("Invalid trampoline: " + c);
	}
}
