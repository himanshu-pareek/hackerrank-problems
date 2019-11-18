#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

int median (int a[], int d, int n) {
    int count = d / 2;
    if (d % 2) {
        // d is odd
        int i = 0;
        while (count > 0) {
            count -= a[i];
            i++;
        }
        if (count < 0) return 2*(i - 1);
        while (i <= n) {
            if (a[i] > 0) return 2*i;
            i++;
        }
    } else {
        count--;
        int i = 0;
        while (count > 0) {
            count -= a[i++];
        }
        int first, second;
        if (count < -1) {
            first = i - 1, second = i - 1;
        } else {
            bool changed = false;
            int ci = -1;
            if (count < 0) {
                first = i - 1;
            } else {
                while (i <= n) {
                    if (a[i] > 0) {
                        first = i;
                        a[i]--;
                        changed = true;
                        ci = i;
                        break;
                    }
                    i++;
                }
            }
            while (i <= n) {
                if (a[i] > 0) {
                    second = i;
                    break;
                }
                i++;
            }
            if (changed) {
                a[ci]++;
            }
        }
        return (first + second);
    }
    return 0;
}

// Complete the activityNotifications function below.
int activityNotifications(vector<int> e, int d) {
    int a[201] = {0};
    int n = e.size();
    int i;
    for (i = 0; i < d; i++) {
        a[e[i]]++;
    }
    int count = 0;
    // for (int i = 0; i < 201; i++) {
    //     if (a[i] != 0) {
    //         cout << i << " => " << a[i] << endl;
    //     }
    // }
    for (;i < n; i++) {
        // cout << "########################" << endl;
        // for (int j = 0; j < 201; j++) {
        //     if (a[j] != 0)
        //         cout << j << " => " << a[j] << endl;
        // }
        int med = median (a, d, 200);
        // cout << med << "'" << endl;
        if (e[i] >= med) {
            count++;
        }
        a[e[i - d]]--;
        a[e[i]]++;
    }
    return count;
}

int main()
{
    ofstream fout("output01.txt");

    string nd_temp;
    getline(cin, nd_temp);

    vector<string> nd = split_string(nd_temp);

    int n = stoi(nd[0]);

    int d = stoi(nd[1]);

    string expenditure_temp_temp;
    getline(cin, expenditure_temp_temp);

    vector<string> expenditure_temp = split_string(expenditure_temp_temp);

    vector<int> expenditure(n);

    for (int i = 0; i < n; i++) {
        int expenditure_item = stoi(expenditure_temp[i]);

        expenditure[i] = expenditure_item;
    }

    int result = activityNotifications(expenditure, d);

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

