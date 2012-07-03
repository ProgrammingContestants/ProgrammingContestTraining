import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
 
public class ProblemD {
     
    static final long INF = 100000000000L;
     
    public static void main(String[] args) throws IOException {
        BufferedReader s = new BufferedReader(new InputStreamReader(System.in));
         
        while (true) {
            String[] line = s.readLine().split(" ");
            int N = Integer.valueOf(line[0]);
            int M = Integer.valueOf(line[1]);
            if (N == 0 && M == 0) {
                break;
            }
             
            // 大きな数で初期化
            long[][] landpath = new long[N][N];
            long[][] seapath = new long[N][N];
            for (int i = 0 ; i < N ; i++) {
                Arrays.fill(landpath[i], INF);
                Arrays.fill(seapath[i], INF);
            }
             
            // 道の情報を読む
            for (int i = 0 ; i < M ; i++) {
                String[] loaddata = s.readLine().split(" ");
                int from = Integer.valueOf(loaddata[0]) - 1;
                int to = Integer.valueOf(loaddata[1]) - 1;
                long time = Long.valueOf(loaddata[2]);
                if ("L".equals(loaddata[3])) {
                    landpath[from][to] = Math.min(landpath[from][to], time);
                    landpath[to][from] = Math.min(landpath[to][from], time);
                } else {
                    seapath[from][to] = Math.min(seapath[from][to], time);
                    seapath[to][from] = Math.min(seapath[to][from], time);              
                }
            }
            for (int k = 0 ; k < N ; k++) {
                landpath[k][k] = 0;
                seapath[k][k] = 0;
            }
             
            // ワーシャルフロイド法で最短路を求める
            for (int k = 0 ; k < N ; k++) {
                for (int i = 0 ; i < N ; i++) {
                    for (int j = 0 ; j < N ; j++) {
                        landpath[i][j] = Math.min(landpath[i][j], landpath[i][k] + landpath[k][j]);
                        seapath[i][j] = Math.min(seapath[i][j], seapath[i][k] + seapath[k][j]);
                    }
                }
            }
             
             
            // 集配先の情報を読む
            int R = Integer.valueOf(s.readLine());
            int[] go = new int[R];
            String[] dst = s.readLine().split(" ");
            for (int i = 0 ; i < R ; i++) {
                go[i] = Integer.valueOf(dst[i]) - 1;
            }
             
            // DP
            long[][] dp = new long[R+1][N];
            for (int i = 0 ; i < R+1 ; i++) {
                Arrays.fill(dp[i], INF);
            }
            dp[1][go[0]] = 0;
            for (int i = 1 ; i < R ; i++) {
                int from = go[i-1];
                int to = go[i];
                for (int j = 0 ; j < N ; j++) {
                    if (dp[i][j] >= INF) {
                        continue;
                    }
                    for (int k = 0 ; k < N ; k++) {
                        dp[i+1][k] = Math.min(dp[i+1][k], dp[i][j] + landpath[from][j] + seapath[j][k] + landpath[k][to]);
                    }
                    dp[i+1][j] = Math.min(dp[i+1][j], dp[i][j] + landpath[from][to]);
                }
            }
             
            long ans = INF;
            for (int i = 0 ; i < N ; i++) {
                ans = Math.min(ans, dp[R][i]);
            }
            System.out.println(ans);
        }
    }
}

