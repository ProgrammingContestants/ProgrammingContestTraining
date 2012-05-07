import java.util.Arrays;
import java.util.Scanner;

//Verbal Arithmetic
public class Verbal_Arithmetic {

	static int ans;
	static int[] assign;
	static char[][] s;
	static int n;
	static boolean[] used;
	
	static void dfs(int k, int m, int sum){
		if(k==s[n-1].length){	//最後までいったら
			if(sum==0){		//繰り上がりがあったら不適
				boolean f = true;
				for(int i=0;i<n;i++){
					if(assign[s[i][0]-'A']==0&&s[i].length > 1){	//最上位の桁が0かつ数字が1桁より多かったらfalse
						f = false;
						break;
					}
				}
				if(f)ans++;
			}
			return;
		}
		int pos = s[m].length-1-k;
		if(pos < 0){	//該当する桁を持っていなかったら次へ
			dfs(k,m+1,sum);
			return;
		}
		int ch = s[m][pos]-'A';
		if(m==n-1){ 	//出力の文字だったら
			if(assign[ch]!=-1){		//既に出た文字だったら
				if(assign[ch]==sum%10){
					dfs(k+1, 0, sum/10);
				}
			}
			else{	//まだ出ていない文字だったら
				int mod = sum%10;	//繰り上がりを考慮して新たに数値を決める
				if(!used[mod]){		//まだ割り当てていなかったら		
					if(mod==0&&pos==0&&s[m].length!=1)return;	//数字が1桁以外で最上位の桁が0だった場合、return
					used[mod] = true;	//割り当てる
					assign[ch] = mod;	//割り当てる
					dfs(k+1, 0, sum/10);	//次の桁を探索する。繰り上がりがあればsumを+1する。
					used[mod] = false;
					assign[ch] = -1;
				}
			}
			return;
		}
		if(assign[ch]!=-1){		//既にアルファベットに数値が割り当てられていたら
			dfs(k, m+1, sum+assign[ch]);	//sumにその数値を足して次へ
			return;
		}
		//新たに数値を割り当てる
		for(int i=0;i<10;i++){
			if(!used[i]){
				if(i==0&&pos==0&&s[m].length!=1)continue;	//数字が1桁以外で最上位の桁が0だった場合、continue
				used[i] = true;		//割り当てる
				assign[ch] = i;		//割り当てる
				dfs(k, m+1, sum+i);
				used[i] = false;	//失敗したので割り当て解除
				assign[ch] = -1;	//失敗したので割り当て解除
			}
		}
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		while(true){
			n = sc.nextInt();
			if(n==0)break;
			s = new char[n][];
			int upmax = 0;
			for(int i=0;i<n;i++){
				s[i]=sc.next().toCharArray();
				if(i<n-1)	//入力のみ（出力以外）を選択　
					upmax = Math.max(upmax, s[i].length);
			}
			/* 明らかにありえない
			 * 例えば、出力3桁　< 入力MAX4桁　=>　ありえない */
			if(s[n-1].length < upmax){
				System.out.println(0);
				continue;
			}
			ans = 0;
			assign = new int[26];
			Arrays.fill(assign, -1);
			used = new boolean[10];
			dfs(0,0,0);
			System.out.println(ans);
		}
	}
}