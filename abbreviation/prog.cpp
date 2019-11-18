#include <bits/stdc++.h>

using namespace std;

// Complete the abbreviation function below.
string abbreviation(string a, string b) {
    int countUpperInA = 0;
    int na = a.length();
    int nb = b.length();
    for (int i = 0; i < na; i++) {
        if (a[i] >= 'A' && a[i] <= 'Z')
            countUpperInA++;
    }
    cout << "countUpperInA = " << countUpperInA << endl;
    int lcs[na + 1][nb + 1];
    for (int i = 0; i <= na; i++) {
        lcs[i][0] = 0;
    }
    for (int i = 0; i <= nb; i++) {
        lcs[0][i] = 0;
    }
    for (int i = 1; i <= na; i++) {
        for (int j = 1; j <= nb; j++) {
            if (a[i - 1] == b[j - 1]) {
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
            } else {
                lcs[i][j] = max (lcs[i][j - 1], lcs[i - 1][j]);
            }
        }
    }
    if (lcs[na][nb] != countUpperInA) {
        return "NO";
    }
    // int lcs[na + 1][nb + 1];
    for (int i = 0; i <= na; i++) {
        lcs[i][0] = 0;
    }
    for (int i = 0; i <= nb; i++) {
        lcs[0][i] = 0;
    }
    for (int i = 1; i <= na; i++) {
        for (int j = 1; j <= nb; j++) {
            if (a[i - 1] == b[j - 1] || (a[i - 1] >= 'a' && a[i - 1] <= 'z' && a[i - 1] - 'a' + 'A' == b[j - 1])) {
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
            } else {
                lcs[i][j] = max (lcs[i][j - 1], lcs[i - 1][j]);
            }
        }
    }
    if (lcs[na][nb] == nb) return "YES";
    return "NO";
}

int main()
{
    ofstream fout("myout.txt");

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string a;
        getline(cin, a);

        string b;
        getline(cin, b);

        string result = abbreviation(a, b);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

