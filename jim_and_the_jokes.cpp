#include <bits/stdc++.h>

using namespace std;

// Complete the solve function below.
long solve(vector<vector<int>> dates) {
    map < int, int > mp;
    long ans = 0;
    for (const vector < int > md : dates) {
        int m = md[0], d = md[1];
        bool valid = true;
        int sum = 0, p = 1;
        if (m <= 1) {
            continue;
        }
        while (d) {
            int digit = d % 10;
            if (digit >= m) {
                valid = false;
                break;
            }
            sum = p * digit + sum;
            p *= m;
            d /= 10;
        }
        if (valid) {
            ans += mp[sum];
            mp[sum]++;
        }
    }
    return ans;
}

int main()
{
    // ofstream fout(getenv("OUTPUT_PATH"));
    ofstream fout ("out1");

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<int>> dates(n);
    for (int dates_row_itr = 0; dates_row_itr < n; dates_row_itr++) {
        dates[dates_row_itr].resize(2);

        for (int dates_column_itr = 0; dates_column_itr < 2; dates_column_itr++) {
            cin >> dates[dates_row_itr][dates_column_itr];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    long result = solve(dates);

    fout << result << "\n";

    fout.close();

    return 0;
}
