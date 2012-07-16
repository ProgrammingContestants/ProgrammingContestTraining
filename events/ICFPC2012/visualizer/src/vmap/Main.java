package vmap;

import javax.swing.UIManager;
import javax.swing.WindowConstants;

import vmap.gui.MainFrame;

public class Main
{
	public static void main(String[] args)
	{
		try
		{
			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		}
		catch (Exception e)
		{
			e.printStackTrace();
		}
		
		MainFrame f = new MainFrame();
		f.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		f.pack();
		f.setLocationRelativeTo(null);
		f.setVisible(true);
	}
}
/*
###############
#***...R......#
#***... ...*..#
#\\\... ..\\\.#
#...... ...*..#
#..     .. ...#
#.... .... ...#
#.... .... ...#
#.. .       ..#
#..*. .. .....#
#.... .. .....#
#.\.. .......*#
#.............#
#.........   .#
#############L#

##L###########
#!!!.WR#.**..#
#.*A.WW#..1..#
#.*....#.  \.#
#.\\\..#@@.\.#
#2.....**B...#
##############

Water 0
Flooding 10
Waterproof 5
Trampoline A targets 1
Trampoline B targets 2
Growth 25
Razors 1

##L###########
#!!!.WR#D**..#
#.*A.WW#..1..#
#C*....#.  \.#
#.\\\.3#@@.\.#
#2.....**B..E#
##############

*/
