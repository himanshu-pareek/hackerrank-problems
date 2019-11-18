#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);
typedef long long ll;
const int mod = 1e9;

void add_self (int & a, int b) {
    a += b;
    if (a >= mod) {
        a -= mod;
    }
}

int mul (int a, int b) {
    long long c = (long long) a * b;
    c %= mod;
    return (int) c;
}

struct Matrix {
    vector < vector < int > > t;
    Matrix (int m, int n) {
        t.resize (m, vector < int > (n));
    }
    Matrix operator * (const Matrix & b) {
        // const int m = b.t.size();
        // const int n = b.t[0].size();
        Matrix c = Matrix (t.size(), b.t[0].size());
        for (int i = 0; i < t.size(); i++) {
            for (int j = 0; j < b.t[0].size(); j++) {
                for (int k = 0; k < t[0].size(); k++) {
                    add_self (c.t[i][j], mul (t[i][k], b.t[k][j]));
                }
            }
        }
        return c;
    }
};

Matrix power (Matrix & mat, ll k) {
    Matrix answer = Matrix (mat.t.size(), mat.t.size());
    for (int i = 0; i < answer.t.size(); i++) {
        answer.t[i][i] = 1;
    }
    while (k >= 1) {
        if (k % 2) {
            answer = answer * mat;
        }
        mat = mat * mat;
        k /= 2;
    }
    return answer;
}

int power (int a, int n) {
    if (n == 0) return 0;
    int x = power (a, n / 2);
    x = mul (x, x);
    if (n % 2) {
        x = mul (x, a);
    }
    return x;
}

int inverse (int a) {
    return power (a, mod - 2);
}

template < typename T >
void printMatrix (const vector < vector < T > > & mat) {
    for (const vector < T > vec : mat) {
        for (const T t : vec) {
            cout << t << " ";
        }
        cout << endl;
    }
}

// Complete the solve function below.
vector<int> solve(int a, int b, int c, int d, int e, int f, int g, int h, ll n) {
    vector < int > ans;
    Matrix mat = Matrix (24, 24);
    mat.t[0][a - 1]++;
    mat.t[0][10 + b - 1]++;
    mat.t[0][10 + c - 1]++;

    mat.t[10][10 + e - 1]++;
    mat.t[10][f - 1]++;
    mat.t[10][g - 1]++;

    for (int i = 1; i < 10; i++) {
        mat.t[i][i - 1] = 1;
        mat.t[10 + i][10 + i - 1] = 1;
    }

    mat.t[0][20] = mat.t[10][22] = 1;
    mat.t[20][20] = d; mat.t[20][21] = d; mat.t[21][21] = d;
    mat.t[22][22] = mat.t[22][23] = mat.t[23][23] = h;

    Matrix F = Matrix (24, 1);
    for (int i = 0; i < F.t.size(); i++) {
        F.t[i][0] = 1;
    }
    F.t[20][0] = F.t[22][0] = 0;
    F.t[21][0] = F.t[23][0] = 1;

    printMatrix(mat.t);
    printMatrix(F.t);

    Matrix result = power (mat, n + 1);
    Matrix answer = result * F;

    // printMatrix (answer.t);

    ans.push_back(answer.t[0][0]); ans.push_back(answer.t[10][0]);
    
    return ans;
}

int main()
{
    ofstream fout("out1");

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string abcdefghn_temp;
        getline(cin, abcdefghn_temp);

        vector<string> abcdefghn = split_string(abcdefghn_temp);

        int a = stoi(abcdefghn[0]);

        int b = stoi(abcdefghn[1]);

        int c = stoi(abcdefghn[2]);

        int d = stoi(abcdefghn[3]);

        int e = stoi(abcdefghn[4]);

        int f = stoi(abcdefghn[5]);

        int g = stoi(abcdefghn[6]);

        int h = stoi(abcdefghn[7]);

        ll n = stol(abcdefghn[8]);

        vector<int> result = solve(a, b, c, d, e, f, g, h, n);

        for (int i = 0; i < result.size(); i++) {
            fout << result[i];

            if (i != result.size() - 1) {
                fout << " ";
            }
        }

        fout << "\n";
    }

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
