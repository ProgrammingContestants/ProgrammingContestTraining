package vmap.gui;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Insets;
import java.awt.Point;
import java.awt.Polygon;
import java.awt.RenderingHints;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Map;
import java.util.Queue;
import java.util.Set;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.WindowConstants;

import vmap.model.TreeNode;

public class TreeDrawPanel extends JPanel
{
	private static final int NODE_R = 8;
	private static final int PADDING = 100;
	
	private int nodeR = NODE_R;
	private int padding = PADDING;
	
	private Set<TreeNode> nodeSet = new HashSet<TreeNode>();
	private TreeNode root;
	
	public TreeDrawPanel()
	{
		setPreferredSize(new Dimension(300, 300));
	}
	
	public void setNodeSet(Set<TreeNode> set)
	{
		nodeSet = set;
	}
	
	public void setTreeRoot(TreeNode r)
	{
		if (!nodeSet.contains(r))
			throw new RuntimeException("The root node must be contained the node set.");
		
		root = r;
		
		setPreferredSize(calcPreferredSize());
		revalidate();
		repaint();
	}
	
	protected void paintComponent(Graphics g)
	{
		g.setColor(Color.WHITE);
		g.fillRect(0, 0, getWidth(), getHeight());
		
		Graphics2D g2 = (Graphics2D)g;
		g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		
		Point o = getOrigin();
		g.translate(o.x, o.y);
		
		drawTree(g2);
		
		g.translate(-o.x, -o.y);
	}
	
	private void drawTree(Graphics2D g)
	{
		Set<TreeNode> visited = new HashSet<TreeNode>();
		Queue<TreeNode> queue = new LinkedList<TreeNode>();
		Map<TreeNode, int[]> pos = new HashMap<TreeNode, int[]>();
		Map<TreeNode, Point> locations = new HashMap<TreeNode, Point>();
		
		queue.add(root);
		pos.put(root, new int[] { 0, 0 });
		
		while (!queue.isEmpty())
		{
			TreeNode node = queue.poll();
			if (visited.contains(node)) continue;
			visited.add(node);
			
			int[] p = pos.get(node);
			locations.put(node, new Point(p[0] * padding, p[1] * padding));
			
			int i = 0;
			for (Map.Entry<TreeNode, String> entry : node.getChildren())
			{
				TreeNode n = entry.getKey();
				if (!visited.contains(n))
				{
					queue.add(n);
					pos.put(n, new int[] { p[0] + 1, i });
					i++;
				}
			}
		}
		
		// draw edges
		g.setColor(Color.BLACK);
		visited.clear();
		for (TreeNode n0 : nodeSet)
		{
			visited.add(n0);
			Point p0 = locations.get(n0);
			if (p0 == null) continue;
			for (Map.Entry<TreeNode, String> ent : n0.getChildren())
			{
				TreeNode n1 = ent.getKey();
				Point p1 = locations.get(n1);
				if (p1 == null) continue;
				drawArrowEdge(g, p0, p1, ent.getValue());
				if (!visited.contains(n1)) visited.add(n1);
			}
		}
		
		// draw nodes
		for (Map.Entry<TreeNode, Point> ent : locations.entrySet())
		{
			TreeNode node = ent.getKey();
			Point pt = ent.getValue();
			g.setColor(Color.WHITE);
			g.fillOval(pt.x - nodeR, pt.y - nodeR, 2 * nodeR, 2 * nodeR);
			g.setColor(Color.BLACK);
			g.drawOval(pt.x - nodeR, pt.y - nodeR, 2 * nodeR, 2 * nodeR);
			g.drawString(Integer.toString(node.getID()), pt.x, pt.y - 10);
		}
	}
	
	private Dimension calcPreferredSize()
	{
		Dimension dim = calcTreeSize();
		Insets pad = getPadding();
		dim.width += pad.left + pad.right;
		dim.height += pad.top + pad.bottom;
		return dim;
	}
	
	private Insets getPadding()
	{
		return new Insets(40, 40, 40, 40);
	}
	
	private Point getOrigin()
	{
		Insets pad = getPadding();
		return new Point(pad.left, pad.top);
	}
	
	private Dimension calcTreeSize()
	{
		int[] bd = calcMaxBreadthAndMaxDepth();
		return new Dimension(2 * nodeR + bd[1] * padding, 2 * nodeR + (bd[0] - 1) * padding);
	}
	
	private int[] calcMaxBreadthAndMaxDepth()
	{
		int maxB = 0, maxD = 0;
		
		Set<TreeNode> visited = new HashSet<TreeNode>();
		Queue<TreeNode> queue = new LinkedList<TreeNode>();
		Map<TreeNode, Integer> depthMap = new HashMap<TreeNode, Integer>();
		depthMap.put(root, 0);
		queue.add(root);
		while (!queue.isEmpty())
		{
			TreeNode node = queue.poll();
			if (visited.contains(node)) continue;
			visited.add(node);
			
			int depth = depthMap.get(node);
			depthMap.remove(node);
			maxD = Math.max(maxD, depth);
			
			depth++;
			
			int i = 0;
			for (Map.Entry<TreeNode, String> entry : node.getChildren())
			{
				TreeNode n = entry.getKey();
				if (!visited.contains(n))
				{
					queue.add(n);
					depthMap.put(n, depth);
					i++;
				}
			}
			maxB = Math.max(maxB, i);
		}
		return new int[] { maxB, maxD };
	}
	
	private static void drawArrowEdge(Graphics2D g, Point p0, Point p1, String label)
	{
		g.setColor(Color.BLACK);
		
		double a = Math.atan2(p1.y - p0.y, p1.x - p0.x);
		double cosA = Math.cos(a), sinA = Math.sin(a);
		double x0 = p0.x + NODE_R * cosA, y0 = p0.y + NODE_R * sinA;
		double x1 = p1.x - NODE_R * cosA, y1 = p1.y - NODE_R * sinA;
		g.drawLine((int)Math.round(x0), (int)Math.round(y0), (int)Math.round(x1), (int)Math.round(y1));
		
		double l = 10, b = Math.toRadians(30);
		Polygon triangle = new Polygon();
		triangle.addPoint((int)Math.round(x1), (int)Math.round(y1));
		triangle.addPoint((int)Math.round(x1 - l * Math.cos(a + b)), (int)Math.round(y1 - l * Math.sin(a + b)));
		triangle.addPoint((int)Math.round(x1 - l * Math.cos(a - b)), (int)Math.round(y1 - l * Math.sin(a - b)));
		g.fill(triangle);
		
		FontMetrics fm = g.getFontMetrics();
		int w = fm.stringWidth(label);
		g.setColor(Color.BLUE);
		g.drawString(label, (p0.x + p1.x - w) / 2, (p0.y + p1.y) / 2);
	}
	
	private static final long serialVersionUID = 1L;
	
	public static void main(String[] args)
	{
		final int V = 20, E = 30;
		
		TreeNode[] nodes = new TreeNode[V];
		for (int i = 0; i < V; i++) nodes[i] = new TreeNode(i);
		
		for (int i = 0; i < E; i++)
		{
			int a = (int)(Math.random() * V);
			int b = (int)(Math.random() * V);
			if (a != b) TreeNode.addEdge(nodes[a], nodes[b], "");
		}
		
		TreeDrawPanel p = new TreeDrawPanel();
		
		p.setNodeSet(new HashSet<TreeNode>(Arrays.asList(nodes)));
		p.setTreeRoot(nodes[0]);
		
		JFrame f = new JFrame("Tree test");
		f.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		f.add(new JScrollPane(p));
		f.pack();
		f.setLocationRelativeTo(null);
		f.setVisible(true);
	}
}
