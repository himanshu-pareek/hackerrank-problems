#include <bits/stdc++.h>

using namespace std;

// Complete the candies function below.
long candies(int n, vector<int> arr) {
    map < int, vector < int > > ratings;
    for (int i = 0; i < n; i++) {
        ratings[arr[i]].push_back(i);
    }
    vector < int > candies(n, 0);
    int numCandies = 0;
    for (map < int, vector < int > > :: iterator it = ratings.begin(); it != ratings.end(); it++) {
        int rating = it -> first;
        for (int pos : it -> second) {
            int leftCandies, rightCandies;
            if (pos == 0 || rating == arr[pos - 1]) {
                leftCandies = 0;
            } else {
                leftCandies = candies[pos - 1];
            }
            if (pos == n - 1 || rating == arr[pos + 1]) {
                rightCandies = 0;
            } else {
                rightCandies = candies[pos + 1];
            }
            candies[pos] = max (leftCandies, rightCandies) + 1;
        }
    }
    for (int i = 0; i < n; i++) {
        numCandies += candies[i];
    }
    return numCandies;
}

int main()
{
    ofstream fout("my_out.txt");

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item;
        cin >> arr_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        arr[i] = arr_item;
    }

    long result = candies(n, arr);

    fout << result << "\n";

    fout.close();

    return 0;
}

