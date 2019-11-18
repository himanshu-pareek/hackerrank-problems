#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

int move (int rod, int disc, int state) {
	disc *= 2;
	state &= ~(3 << disc);
	state |= (rod << disc);
	return state;
}

int get_rod_top (int rod, int state, int N) {
	for (int i = 0; i < N; i++) {
		int st = state & 3;
		if (st == rod) {
			return i;
		}
		state >>= 2;
	}
	return N;
}

int steps_hanoi (vector < int > &tower, int N) {
	int steps = 0, state = 0, win = 0;
	for (int i = 0; i < N; i++) {
		state = move (tower[i] - 1, i, state);
	}
	if (state == win) return steps;
	
	queue < int > q;
	unordered_map < int, int > m;
	vector < int > d (4);
	
	q.push (state);
	m[state] = 0;
	
	while (true) {
		state = q.front(); q.pop();
		steps = m[state];
		
		int tempState = state;
		
		for (int i = 0; i < 4; i++) {
			d[i] = get_rod_top (i, state, N);
		}
		
		for (int from = 0; from < 4; from++) {
			if (d[from] == N) {
				continue;
			}
			
			for (int to = 0; to < 4; to++) {
				if (d[to] > d[from]) {
					state = tempState;
					state = move (to, d[from], state);
					if (state == win) {
						return steps + 1;
					}
					if (m.find (state) == m.end()) {
						m[state] = steps + 1;
						q.push (state);
					}
				}
			}
		}
	}
	
	return m[0];
}

int main()
{
    int N;
    cin >> N;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string a_temp_temp;
    getline(cin, a_temp_temp);

    vector<string> a_temp = split_string(a_temp_temp);

    vector<int> a(N);

    for (int i = 0; i < N; i++) {
        int a_item = stoi(a_temp[i]);

        a[i] = a_item;
    }

    int result = steps_hanoi (a, N);
    cout << result << endl;

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

