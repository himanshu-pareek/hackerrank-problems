#include <bits/stdc++.h>

using namespace std;

// Complete the biggerIsGreater function below.
string biggerIsGreater(string w) {
    int n = w.length();
    int index = -1;
    for (int i = n - 1; i > 0; i--) {
        if (w[i] > w[i - 1]) {
            index = i - 1;
            break;
        }
    }
    if (index == -1) {
        return "no answer";
    }
    int index2 = index + 1;
    for (int i = index + 1; i < n; i++) {
        if (w[i] <= w[index]) {
            break;
        }
        index2 = i;
    }
    swap (w[index], w[index2]);
    int left = index + 1, right = n - 1;
    while (left < right) {
        swap (w[left], w[right]);
        left++;
        right--;
    }
    return w;
}

int main()
{
    ofstream fout("my_out.txt");

    int T;
    cin >> T;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int T_itr = 0; T_itr < T; T_itr++) {
        string w;
        getline(cin, w);

        string result = biggerIsGreater(w);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

