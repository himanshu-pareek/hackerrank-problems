#include <bits/stdc++.h>

using namespace std;

struct suffix {
    int index;
    int rank[2];

    bool operator < (const suffix & s) {
        if (rank[0] == s.rank[0]) return rank[1] < s.rank[1];
        return rank[0] < s.rank[0];
    }
};

vector < int > computeSuffixArray (const string & s) {
    const int n = s.size();
    vector < suffix > suff (n);
    for (int i = 0; i + 1 < n; i++) {
        suff[i].index = i;
        suff[i].rank[0] = s[i] - 'A';
        suff[i].rank[1] = s[i + 1] - 'A';
    }
    suff[n - 1].index = n - 1;
    suff[n - 1].rank[0] = s[n - 1] - 'A';
    suff[n - 1].rank[1] = -1;
    sort (suff.begin(), suff.end());
    vector < int > ind (n);
    for (int k = 4; k < 2 * n; k <<= 1) {
        int rank = 0;
        int prev_rank = suff[0].rank[0];
        suff[0].rank[0] = rank;
        ind[suff[0].index] = 0;
        for (int i = 1; i < n; i++) {
            if (suff[i].rank[0] != prev_rank || suff[i].rank[1] != suff[i - 1].rank[1]) rank++;
            prev_rank = suff[i].rank[0];
            suff[i].rank[0] = rank;
            ind[suff[i].index] = i;
        }
        for (int i = 0; i < n; i++) {
            int nextIndex = suff[i].index + (k >> 1);
            suff[i].rank[1] = (nextIndex < n) ? suff[ind[nextIndex]].rank[0] : -1;
        }
        sort (suff.begin(), suff.end());
    }
    vector < int > suffixArray (n);
    for (int i = 0; i < n; i++) {
        suffixArray[i] = suff[i].index;
    }
    return suffixArray;
}

// Complete the morganAndString function below.
string morganAndString(string a, string b) {
    string c = a + 'z' + b + 'z';
    const int na = a.size();
    const int nb = b.size();
    const int n = c.size();
    vector < int > suff = computeSuffixArray (c);
    vector < int > position (n);
    for (int i = 0; i < n; i++) {
        position[suff[i]] = i;
    }
    string s;
    int i = 0, j = na + 1;
    while (i < na && j < n - 1) {
        if (position[i] < position[j]) {
            s += c[i++];
        } else {
            s += c[j++];
        }
    }
    while (i < na) {
        s += c[i++];
    }
    while (j < n - 1) {
        s += c[j++];
    }
    return s;
}

int main()
{
    // ofstream fout(getenv("OUTPUT_PATH"));
    ofstream fout ("out1");

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string a;
        getline(cin, a);

        string b;
        getline(cin, b);

        string result = morganAndString(a, b);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

