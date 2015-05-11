import java.util.*;

class Solution {
    public static void main(String agrs[]) throws Exception {
        Scanner in = new Scanner(System.in);
        int T = in.nextInt();
        while(T-- > 0) {
            char str[] = in.next().toCharArray();
            int m = in.nextInt();
            int cnt[] = new int[26];
            for(char c : str)
                cnt[c - 'a']++;

            while(m-- > 0) {
                int op = in.nextInt();
                if(op == 1) {
                    int p = in.nextInt();
                    cnt[str[p] - 'a']--;
                    str[p] = in.next().charAt(0);
                    cnt[str[p] - 'a']++;
                } else {
                    System.out.println(cnt[in.next().charAt(0) - 'a']);
                }
            }
        }
    };
};
