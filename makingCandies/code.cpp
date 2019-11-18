#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

vector<string> split_string(string);

bool check (ll m, ll w, ll p, ll n, ll passes) {
    ll current = 0;
    while (current < n && passes > 0) {
        // passes--;
        ll pass = (n - current + m * w - 1) / (m * w);
        if (pass <= passes) {
            return true;
        }
        if (current < p) {
            ll pass = (p - current + m * w - 1) / (m * w);
            passes -= pass;
            if (passes < 1) {
                return false;
            }
            current += pass * w * m;
        }
        current -= p;
        if (m < w) {
            m++;
        } else {
            w++;
        }
    }
    if (current < n) {
        return false;
    }
    return true;
}

// Complete the minimumPasses function below.
ll minimumPasses(ll m, ll w, ll p, ll n) {
    ll low = 1, high = 1000000000000L;
    while (low <= high) {
        ll mid = low + (high - low) / 2;
        cout << "Mid = " << mid << endl;
        if (check (m, w, p, n, mid)) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return low;
}

int main()
{
    // ofstream fout(getenv("OUTPUT_PATH"));
    ofstream fout ("out.txt");

    string mwpn_temp;
    getline(cin, mwpn_temp);

    vector<string> mwpn = split_string(mwpn_temp);

    ll m = stol(mwpn[0]);

    ll w = stol(mwpn[1]);

    ll p = stol(mwpn[2]);

    ll n = stol(mwpn[3]);

    ll result = minimumPasses(m, w, p, n);

    fout << result << "\n";

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

