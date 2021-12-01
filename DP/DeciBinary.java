import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.stream.IntStream;

class Result {

    /*
     * Complete the 'decibinaryNumbers' function below.
     *
     * The function is expected to return a LONG_INTEGER.
     * The function accepts LONG_INTEGER x as parameter.
     */

    // public static long decibinaryNumbers(long x) {
    // Write your code here

    // }

}

public class DeciBinary {

    private static final int M = 300001;
    private static final int D = 25;

    private static long dp[][];
    private static long F[];

    private static long f(int s, int d) {

        if (d == -1) {
            return s == 0 ? 1 : 0;
        }
        if (dp[s][d] == -1) {
            dp[s][d] = 0l;
            for (int digit = 0; digit < 10 && digit * (1 << d) <= s; digit++) {
                dp[s][d] += f(s - ((1 << d) * digit), d - 1);
            }
        }
        return dp[s][d];
    }

    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new OutputStreamWriter(System.out));

        dp = new long[M][D];
        F = new long[M];
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < D; j++) {
                dp[i][j] = -1;
            }
        }
        for (int i = 0; i < M; i++) {
            dp[i][D - 1] = f(i, D - 1);
            F[i] = dp[i][D - 1];
        }
        for (int i = 1; i < M; i++) {
            F[i] += F[i - 1];
        }

        // for (int i = 0; i < 15; i++) {
        //     System.out.println(i + " => " + F[i]);
        // }

        int q = Integer.parseInt(bufferedReader.readLine().trim());

        IntStream.range(0, q).forEach(qItr -> {
            try {
                long x = Long.parseLong(bufferedReader.readLine().trim());

                long result = decibinaryNumbers(x);

                bufferedWriter.write(String.valueOf(result));
                bufferedWriter.newLine();
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        });

        bufferedReader.close();
        bufferedWriter.close();
    }

    private static long decibinaryNumbers(long x) {
        if (x == 1) return 0;
        int left = 0, right = M - 1;
        int ind = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (F[mid] >= x) {
                ind = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        // System.out.println(x + " " + ind);
        // return 0;
        long y = x - F[ind - 1];
        int s = ind;

        int lmDigit = -1;
        while (f(s, lmDigit) < y) lmDigit++;

        long ans = 0l;

        while (lmDigit >= 0) {
            for (int digit = 0; digit < 10; digit++) {
                int tmp = s - digit * (1 << lmDigit);
                if (y <= f(tmp, lmDigit - 1)) {
                    ans *= 10;
                    ans += digit;
                    s = tmp;
                    break;
                }
                y -= f(tmp, lmDigit - 1);
            }
            --lmDigit;
        }
        

        return ans;
    }
}
