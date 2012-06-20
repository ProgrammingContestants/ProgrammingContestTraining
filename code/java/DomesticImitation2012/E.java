import java.util.*;
import java.math.*;

class E {
    public static int N;
    public static int[] powers;
    public static int[][] neighbors;
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while (true) {
            N = sc.nextInt();
            if (N==0) break;

            powers = new int[N];
            neighbors = new int[N][];

            String[] names = new String[N];
            String[][] neighborNames = new String[N][];
            Map<String,Integer> map = new HashMap<String,Integer>();

            for (int i=0; i<N; i++) {
                names[i] = sc.next();
                powers[i] = sc.nextInt();
                map.put(names[i], i);
                int c = sc.nextInt();
                neighborNames[i] = new String[c];
                for (int j=0; j<c; j++) neighborNames[i][j] = sc.next();
            }

            for (int i=0; i<N; i++) {
                String name = names[i];
                int index = 0;
                neighbors[i] = new int[neighborNames[i].length];
                for (String neighbor : neighborNames[i]) {
                    neighbors[i][index] = map.get(neighbor);
                    index++;
                }
            }

            System.out.println(dfs());
            System.out.println(counter);
        }
    }

    public static int counter = 0;
    public static int[] using;
    public static int dfs() {
        using = new int[N];
        using[0] = 1;
        for (int id : neighbors[0]) {
            using[id] += 1;
        }
        return runDfs(1) + powers[0];
    }

    public static int runDfs(int from) {
        counter++;
        int max = 0;
        for (int i=from; i<N; i++) {
            if (using[i]!=0) continue;
            
            using[i] += 1;
            for (int id : neighbors[i]) {
                using[id] += 1;
            }
            max = Math.max(max, runDfs(i+1) + powers[i]);
            using[i] -= 1;
            for (int id : neighbors[i]) {
                using[id] -= 1;
            }
        }
        return max;
    }

}

