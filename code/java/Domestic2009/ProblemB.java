import java.util.Scanner;


public class ProblemB {

	static int wx;
	static int hy;
	static boolean[][] sfield;
	
	public static void main(String[] args){
		
		Scanner sc = new Scanner(System.in);
		
		while(true){
			
			wx = hy = 0;
			
			int w = sc.nextInt();
			int h = sc.nextInt();
			
			wx = w;
			hy = h;
			
			boolean[][] field = new boolean[w][h];
			sfield = field;
			String line;
			int count = 0;
			line = sc.nextLine();
			for(int i = 0; i < h; i++){
				line = sc.nextLine();
				line = line.replaceAll(" ", "");
				for(int j = 0; j < w; j++){
					if(line.charAt(j) == '0'){
						sfield[j][i] = false;	
					}else if(line.charAt(j) == '1'){
						sfield[j][i] = true;
					}
				}
			}
			for(int i = 0; i < h; i++){
				for(int j = 0; j < w; j++){
					if(sfield[j][i]){
						System.out.println(j + " " + i);
						sfield[j][i] = false;
						count++;
						searchIsland(j, i);
					}
				}
			}
			System.out.println(count);
			
		}
	}

	private static void searchIsland(int x, int y) {
		if( x != wx - 1 && sfield[x + 1][y]){
			sfield[x + 1][y] = false;
			searchIsland(x + 1, y);
		}
		
		if( x != wx - 1  && y != hy - 1  &&sfield[x + 1][y + 1]){
			sfield[x + 1][y + 1] = false;
			searchIsland(x + 1, y + 1);
		}
		
		if(y != hy - 1 &&sfield[x][y + 1]){
			sfield[x][y + 1] = false;
			searchIsland(x, y + 1);
		}
		
		if(y != hy - 1 && x != 0 && sfield[x - 1][y + 1]){
			sfield[x - 1][y + 1] = false;
			searchIsland(x - 1, y + 1);
		}
		
		if(x != 0 && sfield[x - 1][y]){
			sfield[x - 1][y] = false;
			searchIsland(x - 1, y);
		}
		
		if(x != 0 && y != 0 && sfield[x - 1][y - 1]){
			sfield[x - 1][y - 1] = false;
			searchIsland(x - 1, y - 1);
		}

		if(y != 0 && sfield[x][y - 1]){
			sfield[x][y - 1] = false;
			searchIsland(x, y - 1);
		}
		
		if(y != 0 &&  x != wx - 1 && sfield[x + 1][y - 1]){
			sfield[x + 1][y - 1] = false;
			searchIsland(x + 1, y - 1);
		}
	}

}
