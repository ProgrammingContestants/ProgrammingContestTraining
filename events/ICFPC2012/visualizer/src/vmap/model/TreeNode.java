package vmap.model;

import java.util.HashMap;
import java.util.Map;

public class TreeNode
{
	private int id;
	private Map<TreeNode, String> children = new HashMap<TreeNode, String>();
	
	public TreeNode(int id)
	{
		this.id = id;
	}
	
	public int getID()
	{
		return id;
	}
	
	public boolean isLeaf()
	{
		return children.isEmpty();
	}
	
	public int countChildren()
	{
		return children.size();
	}
	
	public Iterable<Map.Entry<TreeNode, String>> getChildren()
	{
		return children.entrySet();
	}
	
	public int hashCode()
	{
		return id;
	}
	
	public boolean equals(Object o)
	{
		return o == this
			|| o instanceof TreeNode && ((TreeNode)o).id == id;
	}
	
	public static void addEdge(TreeNode from, TreeNode to, String label)
	{
		from.children.put(to, label);
	}
}
