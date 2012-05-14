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
		if(k==s[n-1].length){	//�Ō�܂ł�������
			if(sum==0){		//�J��オ�肪��������s�K
				boolean f = true;
				for(int i=0;i<n;i++){
					if(assign[s[i][0]-'A']==0&&s[i].length > 1){	//�ŏ�ʂ̌���0��������1����葽��������false
						f = false;
						break;
					}
				}
				if(f)ans++;
			}
			return;
		}
		int pos = s[m].length-1-k;
		if(pos < 0){	//�Y�����錅�������Ă��Ȃ������玟��
			dfs(k,m+1,sum);
			return;
		}
		int ch = s[m][pos]-'A';
		if(m==n-1){ 	//�o�͂̕�����������
			if(assign[ch]!=-1){		//���ɏo��������������
				if(assign[ch]==sum%10){
					dfs(k+1, 0, sum/10);
				}
			}
			else{	//�܂��o�Ă��Ȃ�������������
				int mod = sum%10;	//�J��オ����l�����ĐV���ɐ��l�����߂�
				if(!used[mod]){		//�܂����蓖�ĂĂ��Ȃ�������		
					if(mod==0&&pos==0&&s[m].length!=1)return;	//������1���ȊO�ōŏ�ʂ̌���0�������ꍇ�Areturn
					used[mod] = true;	//���蓖�Ă�
					assign[ch] = mod;	//���蓖�Ă�
					dfs(k+1, 0, sum/10);	//���̌���T������B�J��オ�肪�����sum��+1����B
					used[mod] = false;
					assign[ch] = -1;
				}
			}
			return;
		}
		if(assign[ch]!=-1){		//���ɃA���t�@�x�b�g�ɐ��l�����蓖�Ă��Ă�����
			dfs(k, m+1, sum+assign[ch]);	//sum�ɂ��̐��l�𑫂��Ď���
			return;
		}
		//�V���ɐ��l�����蓖�Ă�
		for(int i=0;i<10;i++){
			if(!used[i]){
				if(i==0&&pos==0&&s[m].length!=1)continue;	//������1���ȊO�ōŏ�ʂ̌���0�������ꍇ�Acontinue
				used[i] = true;		//���蓖�Ă�
				assign[ch] = i;		//���蓖�Ă�
				dfs(k, m+1, sum+i);
				used[i] = false;	//���s�����̂Ŋ��蓖�ĉ���
				assign[ch] = -1;	//���s�����̂Ŋ��蓖�ĉ���
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
				if(i<n-1)	//���͂̂݁i�o�͈ȊO�j��I���@
					upmax = Math.max(upmax, s[i].length);
			}
			/* ���炩�ɂ��肦�Ȃ�
			 * �Ⴆ�΁A�o��3���@< ����MAX4���@=>�@���肦�Ȃ� */
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