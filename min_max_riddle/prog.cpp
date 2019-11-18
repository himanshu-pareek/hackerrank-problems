#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the riddle function below.
vector<long> riddle(vector<long> arr) {
    int n = arr.size();
    vector < int > left(n), right(n);
    stack < int > s;
    for (int i = 0; i < n; i++) {
        while (!s.empty() && arr[s.top()] >= arr[i]) {
            s.pop();
        }
        left[i] = s.empty() ? -1 : s.top();
        s.push(i);
    }
    while (!s.empty()) s.pop();
    for (int i = n - 1; i >= 0; i--) {
        while (!s.empty() && arr[s.top()] >= arr[i]) {
            s.pop();
        }
        right[i] = s.empty() ? n - 1 : s.top() - 1;
        s.push(i);
    }
    
    map < long, int > maxWindowSize;
    for (int i = 0; i < n; i++){
        if (maxWindowSize.find(arr[i]) == maxWindowSize.end()) {
            maxWindowSize[arr[i]] = right[i] - left[i];
        } else {
            maxWindowSize[arr[i]] = max (maxWindowSize[arr[i]], right[i] - left[i]);
        }
    }
    vector < long > maxElement(n, -1);
    for (map < long, int > :: iterator it = maxWindowSize.begin(); it != maxWindowSize.end(); it++) {
        maxElement[(it -> second) - 1] = max (maxElement[(it -> second) - 1], it -> first);
    }
    for (int i = n - 1; i >= 0; i--) {
        if (maxElement[i] == -1) {
            maxElement[i] = maxElement[i + 1];
        }
    }
    return maxElement;
}

int main()
{
    ofstream fout("my_out.txt");

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<long> arr(n);

    for (int i = 0; i < n; i++) {
        long arr_item = stol(arr_temp[i]);

        arr[i] = arr_item;
    }

    vector<long> res = riddle(arr);

    for (int i = 0; i < res.size(); i++) {
        fout << res[i];

        if (i != res.size() - 1) {
            fout << " ";
        }
    }

    fout << "\n";

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

