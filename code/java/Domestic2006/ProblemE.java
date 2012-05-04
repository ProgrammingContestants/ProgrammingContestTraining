
import java.util.Scanner;

abstract class Node
{
	private int extLength = -1;
	protected abstract int calcExtendLength();
	public int getExtendLength()
	{
		if (extLength == -1)
		{
			extLength = calcExtendLength();
		}
		return Math.min(extLength, 1000001);
	}
	public abstract char getCharAt(int i);
}

class StrNode extends Node
{
	public final String s;
	
	public StrNode(String s)
	{
		this.s = s;
	}
	
	protected int calcExtendLength()
	{
		return s.length();
	}
	
	public char getCharAt(int i)
	{
		return i < getExtendLength() ? s.charAt(i) : '0';
	}
}

class RepNode extends Node
{
	public final int n;
	public final Node node;
	
	public RepNode(int n, Node node)
	{
		this.n = n;
		this.node = node;
	}
	
	protected int calcExtendLength()
	{
		return n * node.getExtendLength();
	}
	
	public char getCharAt(int i)
	{
		if (i < getExtendLength())
		{
			return node.getCharAt((int)(i % node.getExtendLength()));
		}
		else
		{
			return '0';
		}
	}
}

class SeqNode extends Node
{
	public final Node fst;
	public final Node snd;
	
	public SeqNode(Node fst, Node snd)
	{
		this.fst = fst;
		this.snd = snd;
	}
	
	protected int calcExtendLength()
	{
		return fst.getExtendLength() + snd.getExtendLength();
	}
	
	public char getCharAt(int i)
	{
		if (i < fst.getExtendLength())
		{
			return fst.getCharAt(i);
		}
		else if (i < getExtendLength())
		{
			return snd.getCharAt((int)(i - fst.getExtendLength()));
		}
		else
		{
			return '0';
		}
	}
}

public class ProblemE
{
	private static String src;
	private static int p;
	
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		for(;;)
		{
			String pattern = sc.next();
			int i = sc.nextInt();
			
			if (pattern.equals("0") && i == 0) break;
			
			System.out.println(getCharAt(pattern, i));
		}
	}
	
	private static char getCharAt(String pattern, int i)
	{
		src = pattern;
		p = 0;
		Node root = patternSeq();
		return root.getCharAt(i);
	}
	
	//
	// <<PatternSeq>> ::= <<Pattern>> { <<Pattern>> }
	//
	private static Node patternSeq()
	{
		Node node = pattern();
		while (p < src.length() && src.charAt(p) != ')')
		{
			node = new SeqNode(node, pattern());
		}
		return node;
	}
	
	//
	// <<Pattern>> ::= <D> ( "(" <<PatternSeq>> ")" | <C> )
	//               | <C> { <C> }
	//
	private static Node pattern()
	{
		char c = src.charAt(p);
		if (Character.isDigit(c))
		{
			int n = 0;
			while (p < src.length() && Character.isDigit(c = src.charAt(p)))
			{
				n = 10 * n + (c - '0');
				p++;
			}
			Node node;
			if (c == '(')
			{
				p++;
				node = patternSeq();
				c = src.charAt(p);
				if (c == ')') p++;
			}
			else
			{
				p++;
				node = new StrNode(Character.toString(c));
			}
			return new RepNode(n, node);
		}
		else
		{
			String s = "";
			while (p < src.length() && Character.isLetter(c = src.charAt(p)))
			{
				s += c;
				p++;
			}
			return new StrNode(s);
		}
	}
}
/*
ABC 3
ABC 0
2(4(AB)3(XY))10C 30
1000(1000(1000(1000(1000(1000(NM)))))) 999999
0 0
*/
