#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

vector < pair < int, int > > toAdd;

bool isValid (int m, int n, int i, int j) {
    return i >= 0 && j >= 0 && i < m && j < n;
}


pair < bool, int > dfs (vector < string > &matrix, int m, int n, int i, int j, vector < vector < bool > > &visited) {
    visited[i][j] = true;
    if (matrix[i][j] == '*') {
        return {true, 0};
    }
    int choices = 0;
    cout << "size of toAdd: " << toAdd.size() << endl;
    for (pair < int, int > p : toAdd) {
        int x = i + p.first;
        int y = j + p.second;
        
        if (isValid(m, n, x, y) && !visited[x][y]) {
        	cout << "x = " << x << ", y = " << y << " " << isValid (m, n, x, y) << " " << visited[x][y] << " " << matrix[x][y] << endl;
            if (matrix[x][y] != 'X') {
                choices++;
            }
        }
    }
    cout << i << ", " << j << ", " << choices << endl;
    for (pair < int, int > p : toAdd) {
        int x = i + p.first;
        int y = j + p.second;
        if (isValid(m, n, x, y) && matrix[x][y] != 'X' && !visited[x][y]) {
            pair < bool, int > rt = dfs (matrix, m, n, x, y, visited);
            if (rt.first) {
                return {true, rt.second + (choices > 1)};
            }
        }
    }
    return {false, 0};
}

// Complete the countLuck function below.
string countLuck(vector<string> matrix, int k) {
    
    int m = matrix.size();
    int n = matrix[0].size();
    int startR = -1, startCol = -1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 'M') {
                startR = i; startCol = j;
                break;
            }
        }
        if (startR != -1) {
            break;
        }
    }
    // cout << startR << startCol << endl;
    vector < vector < bool > > visited (m, vector < bool > (n, false));
    pair < bool, int > ans = dfs (matrix, m, n, startR, startCol, visited);
    if (ans.second == k) {
        return "Impressed";
    } else {
        return "Opps!";
    }
}

int main()
{
    // ofstream fout(getenv("OUTPUT_PATH"));
    ofstream fout ("out.txt");

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    toAdd.push_back ({-1, 0});
    toAdd.push_back ({0, -1});
    toAdd.push_back ({1, 0});
    toAdd.push_back ({0, 1});

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string nm_temp;
        getline(cin, nm_temp);

        vector<string> nm = split_string(nm_temp);

        int n = stoi(nm[0]);

        int m = stoi(nm[1]);

        vector<string> matrix(n);

        for (int i = 0; i < n; i++) {
            string matrix_item;
            getline(cin, matrix_item);

            matrix[i] = matrix_item;
        }

        int k;
        cin >> k;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string result = countLuck(matrix, k);

        fout << result << "\n";
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

