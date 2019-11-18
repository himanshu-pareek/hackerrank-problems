#include <bits/stdc++.h>

using namespace std;

struct vertex {
    vertex () {
        children.clear();
        flag = false;
        parent = -1;
        suffixLink = -1;
        wordId.resize (0);
        endWordLink = -1;
    }

    unordered_map < char, int > children;
    bool flag;
    int parent;
    char parentChar;
    int suffixLink;
    int endWordLink;
    vector < int > wordId;

    void print () {
        cout << flag << " - " << parent << " - " << parentChar << " - " << suffixLink << " - " << endWordLink << endl;
        for (int id : wordId) {
            cout << id << " ";
        }
        cout << endl;
    }
};

struct Aho {
    vector < vertex* > trie;
    vector < int > wordsLength;
    int size = 0;
    int root = 0;

    Aho () {
        trie.resize (0);
        wordsLength.resize (0);
        init();
    }

    void init() {
        trie.push_back (new vertex());
        size++;
    }

    void addString(string s, int wordId) {
        int currentVertex = root;
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            if ((trie[currentVertex] -> children).find(c) == 
                (trie[currentVertex] -> children).end()) {
                trie.push_back (new vertex());
                trie[size] -> suffixLink = -1;
                trie[size] -> parent = currentVertex;
                (trie[currentVertex] -> children)[c] = size;
                size++;
            }
            currentVertex = (trie[currentVertex] -> children)[c];
        }
        trie[currentVertex] -> flag = true;
        (trie[currentVertex] -> wordId).push_back (wordId);
        wordsLength.push_back (s.size());
    }

    void prepareAho () {
        queue < int > vertexQueue;
        vertexQueue.push (root);
        while (!vertexQueue.empty()) {
            int currentVertex = vertexQueue.front(); vertexQueue.pop();
            calculateSuffixLink (currentVertex);

            for (auto it = (trie[currentVertex] -> children).begin();
            it != (trie[currentVertex] -> children).end(); it++) {
                vertexQueue.push (it -> second);
            }
        }
    }

    void calculateSuffixLink (int vertex) {
        if (vertex == root) {
            trie[vertex] -> suffixLink = root;
            trie[vertex] -> endWordLink = root;
            return;
        }

        if (trie[vertex] -> parent == root) {
            trie[vertex] -> suffixLink = root;
            if (trie[vertex] -> flag)
                trie[vertex] -> endWordLink = vertex;
            else 
                trie[vertex] -> endWordLink = trie[trie[vertex] -> suffixLink] -> endWordLink;
            return;
        }
        int currentBetterVertex = trie[trie[vertex] -> parent] -> suffixLink;
        char vertexChar = trie[vertex] -> parentChar;

        while (true) {
            if ((trie[currentBetterVertex] -> children).find (vertexChar) != (trie[currentBetterVertex] -> children).end()) {
                trie[vertex] -> suffixLink = (trie[currentBetterVertex] -> children)[vertexChar];
                break;
            }
            if (currentBetterVertex == root) {
                trie[vertex] -> suffixLink = root;
                break;
            }

            currentBetterVertex = trie[currentBetterVertex] -> suffixLink;
        }

        if (trie[vertex] -> flag) {
            trie[vertex] -> endWordLink = vertex;
        } else {
            trie[vertex] -> endWordLink = trie[trie[vertex] -> suffixLink] -> endWordLink;
        }

    }

    int processString (vector < int > &counts, string text) {
        
        int currentState = root;
        int result = 0;
        for (int j = 0; j < text.size(); j++) {
            while (true) {
                if ((trie[currentState] -> children).find (text[j]) != (trie[currentState] -> children).end ()) {
                    currentState = (trie[currentState] -> children)[text[j]];
                    break;
                }
                if (currentState == root) {
                    break;
                }
                currentState = trie[currentState] -> suffixLink;
            }
            int checkState = currentState;
            while (true) {
                checkState = trie[checkState] -> endWordLink;
                if (checkState == root) break;

                result++;
                int indexOfMatch = j + 1 - wordsLength[(trie[checkState] -> wordId)[0]];
                // cout << indexOfMatch << ", " << (trie[checkState] -> wordId) << endl;
                for (int index : (trie[checkState] -> wordId)) {
                    // cout << index << " -> " << indexOfMatch << endl;
                    counts[index]++;
                }
                j = indexOfMatch;
                checkState = trie[checkState] -> suffixLink;
            }
        }
        return result;
    }
};

int main() {
    int N, S;
    string d;
    cin >> N;
    vector < string > genes (N);
    vector < int > health (N);
    for (int i = 0; i < N; i++) {
        cin >> genes[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> health[i];
    }
    Aho* ahoAlg = new Aho();
    for (int i = 0; i < genes.size(); i++) {
        ahoAlg -> addString(genes[i], i);
    }
    ahoAlg -> prepareAho();

    // for (vertex* v : ahoAlg -> trie) {
    //     v -> print();
    // }

    cin >> S;
    int first, last;
    int minimum = INT_MAX, maximum = INT_MIN;
    vector < int > counts (N);
    while (S--) {
        cin >> first >> last >> d;
        for (int i = 0; i < N; i++) {
            counts[i] = 0;
        }
        // counts.resize (N, 0);
        int countOfMatches = ahoAlg -> processString (counts, d);
        int hel = 0;
        for (int i = first; i <= last; i++) {
            cout << genes[i] << " => " << counts[i] << endl;
            hel += counts[i] * health[i];
            
        }

        cout << "health = " << hel << endl;
        minimum = min (minimum, hel);
        maximum = max (maximum, hel);
        
    }
    cout << minimum << " " << maximum << endl;
    return 0;
}
