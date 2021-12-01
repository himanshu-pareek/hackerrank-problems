import java.io.*;
import java.math.*;
import java.security.*;
import java.text.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.regex.*;

public class MinMaxRiddle {

    // Complete the riddle function below.
    static long[] riddle(long[] arr) {
        // complete this function

        final int n = arr.length;
        long[] result = new long[n];

        int[] leftIndex = new int[n];
        int[] rightIndex = new int[n];

        Stack<Integer> s = new Stack<>();
        for (int i = 0; i < n; i++) {
            while(!s.isEmpty() && arr[s.peek()] >= arr[i]) {
                s.pop();
            }
            if (s.isEmpty()) leftIndex[i] = -1;
            else leftIndex[i] = s.peek();
            s.push(i);
        }

        s.clear();
        for (int i = n - 1; i >= 0; i--) {
            while(!s.isEmpty() && arr[s.peek()] >= arr[i]) {
                s.pop();
            }
            if (s.isEmpty()) rightIndex[i] = n;
            else rightIndex[i] = s.peek();
            s.push(i);
        }

        for (int i = 0; i < n; i++) {
            int index = rightIndex[i] - leftIndex[i] - 2;
            result[index] = Math.max(result[index], arr[i]);
            // System.out.println(i + " " + leftIndex[i] + " " + rightIndex[i] + " " + arr[i]);
        }

        for (int i = n - 1; i > 0; i--) {
            result[i - 1] = Math.max(result[i - 1], result[i]);
        }

        return result;

    }

    private static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) throws IOException {
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter("out"));

        int n = scanner.nextInt();
        scanner.skip("(\r\n|[\n\r\u2028\u2029\u0085])?");

        long[] arr = new long[n];

        String[] arrItems = scanner.nextLine().split(" ");
        scanner.skip("(\r\n|[\n\r\u2028\u2029\u0085])?");

        for (int i = 0; i < n; i++) {
            long arrItem = Long.parseLong(arrItems[i]);
            arr[i] = arrItem;
        }

        long[] res = riddle(arr);

        for (int i = 0; i < res.length; i++) {
            bufferedWriter.write(String.valueOf(res[i]));

            if (i != res.length - 1) {
                bufferedWriter.write(" ");
            }
        }

        bufferedWriter.newLine();

        bufferedWriter.close();

        scanner.close();
    }
}
