#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'cutTheTree' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY data
 *  2. 2D_INTEGER_ARRAY edges
 */

struct node {
    int data;
    vector < node* > children;

    node (int d) {
        data = d;
    }
};

bool compareEdges (const vector < int > &edge1, const vector < int > &edge2) {
    if (edge1[0] == edge2[0])
        return edge1[1] == edge2[1];
    return edge1[0] < edge2[0];
}

pair < int, int > search (vector<vector<int>> &edges, int index) {
    pair < int, int > p;
    int low = 0, high = edges.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (edges[mid][0] >= index) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    p.first = low;
    low = 0, high = edges.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (edges[mid][0] <= index) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    p.second = high;
    return p;
}

node* dfs (vector < bool > &visited, vector<vector<int>> &edges, int index, vector < int > &data, int sum, int &diff) {
    visited[index] = true;
    node* root = new node (data[index]);
    pair < int, int > p = search (edges, index);
    int totalData = 0, count = 0;
    
    for (int i = p.first; i <= p.second; i++) {
        if (!visited[edges[i][1]]) {
            root -> children.push_back(dfs (visited, edges, edges[i][1], data, sum, diff));
            totalData += (root -> children)[count] -> data;
            count++;
            // cout << edges[i][1] << ", ";
        }
    }
    
    cout << index << ", " << (root -> data) << " -> [ ";
    for (node* temp : root -> children) {
    	cout << (temp -> data) << ", ";
    }
    cout << " ]\n";
    
    root -> data += totalData;
    diff = min (diff, abs (sum - 2 * (root -> data)));
    return root;
}

int cutTheTree(vector<int> data, vector<vector<int>> edges) {
    
    const int n = data.size();
    for (int i = 0; i < n - 1; i++) {
        edges[i][0]--; edges[i][1]--;
        edges.push_back ({edges[i][1], edges[i][0]});
    }
    sort (edges.begin(), edges.end(), compareEdges);
    vector < bool > visited (n, false);
    int sum = 0;
    for (int d : data) sum += d;
    int diff = sum;
    dfs (visited, edges, 0, data, sum, diff);
    return diff;
}

int main()
{
    // ofstream fout(getenv("OUTPUT_PATH"));
    ofstream fout("out.txt");

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string data_temp_temp;
    getline(cin, data_temp_temp);

    vector<string> data_temp = split(rtrim(data_temp_temp));

    vector<int> data(n);

    for (int i = 0; i < n; i++) {
        int data_item = stoi(data_temp[i]);

        data[i] = data_item;
    }

    vector<vector<int>> edges(n - 1);

    for (int i = 0; i < n - 1; i++) {
        edges[i].resize(2);

        string edges_row_temp_temp;
        getline(cin, edges_row_temp_temp);

        vector<string> edges_row_temp = split(rtrim(edges_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int edges_row_item = stoi(edges_row_temp[j]);

            edges[i][j] = edges_row_item;
        }
    }

    int result = cutTheTree(data, edges);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}

