package Domestic2010Practice;

import java.io.InputStream;
import java.util.Scanner;

public class ProblemC {
	public static void main(String[] args) {
		new ProblemC().solve(System.in);
	}

	private void solve(InputStream in) {
		Scanner sc = new Scanner(in);

		while (true) {
			int N = sc.nextInt();
			int M = sc.nextInt();
			if (N == 0 && M == 0) {
				break;
			}

			int[] book = new int[M];
			for (int i = 0; i < M; i++) {
				book[i] = sc.nextInt();
			}
			int[] input = new int[N];
			for (int i = 0; i < N; i++) {
				input[i] = sc.nextInt();
			}

			int[] dp = new int[256];
			for (int i = 0; i < dp.length; i++) {
				dp[i] = Integer.MAX_VALUE;
			}
			dp[128] = 0;

			for (int code : input) {
				int[] newdp = new int[256];
				for (int i = 0; i < newdp.length; i++) {
					newdp[i] = Integer.MAX_VALUE;
				}
				for (int lastCode = 0; lastCode < dp.length; lastCode++) {
					if (dp[lastCode] >= Integer.MAX_VALUE) {
						continue;
					}
					for (int j = 0; j < book.length; j++) {
						int nextCode = Math.min(
								Math.max(lastCode + book[j], 0), 255);
						int candidate = dp[lastCode] + (code - nextCode)
								* (code - nextCode);
						newdp[nextCode] = Math.min(candidate, newdp[nextCode]);
					}
				}
				dp = newdp;
			}

			int ans = Integer.MAX_VALUE;
			for (int value : dp) {
				ans = Math.min(ans, value);
			}
			System.out.println(ans);
		}
	}
}
