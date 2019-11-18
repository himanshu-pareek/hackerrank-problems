#include <iostream>
#include <queue>
#define MAXS 500    //sum of the length of all patterns
#define MAXC 26     //as 26 letters in alphabet
using namespace std;

int output[MAXS];
int fail[MAXS];
int gotoMat[MAXS][MAXC];

int buildTree(string array[], int size) {
   for(int i = 0; i<MAXS; i++)
      output[i] = 0;    //all element of output is 0

   for(int i = 0; i<MAXS; i++)
      fail[i] = -1;    //all element of failure array is -1

   for(int i = 0; i<MAXS; i++)
      for(int j = 0; j<MAXC; j++)
         gotoMat[i][j] = -1;    //all element of goto matrix is -1

   int state = 1;    //there is only one state

   for (int i = 0; i < size; i++) {    //make trie structure for all pattern in array
      //const string &word = array[i];
      string word = array[i];
      int presentState = 0;

      for (int j = 0; j < word.size(); ++j) {    //all pattern is added
         int ch = word[j] - 'a';
         if (gotoMat[presentState][ch] == -1)    //ic ch is not present make new node
            gotoMat[presentState][ch] = state++;    //increase state
            presentState = gotoMat[presentState][ch];
      }
      output[presentState] |= (1 << i); //current word added in the output
   }

   for (int ch = 0; ch < MAXC; ++ch)   //if ch is not directly connected to root
      if (gotoMat[0][ch] == -1)
         gotoMat[0][ch] = 0;

         queue<int> q;

   for (int ch = 0; ch < MAXC; ++ch) {    //node goes to previous state when fails
      if (gotoMat[0][ch] != 0) {
         fail[gotoMat[0][ch]] = 0;
         q.push(gotoMat[0][ch]);
      }
   }

   while (q.size()) {
      int state = q.front();    //remove front node
      q.pop();

      for (int ch = 0; ch <= MAXC; ++ch) {
         if (gotoMat[state][ch] != -1) {    //if goto state is present
            int failure = fail[state];
            while (gotoMat[failure][ch] == -1)    //find deepest node with proper suffix
               failure = fail[failure];
            failure = gotoMat[failure][ch];
            fail[gotoMat[state][ch]] = failure;
            output[gotoMat[state][ch]] |= output[failure];   // Merge output values
            q.push(gotoMat[state][ch]);    //add next level node to the queue
         }
      }
   }
   return state;
}

int getNextState(int presentState, char nextChar) {
   int answer = presentState;
   int ch = nextChar - 'a'; //subtract ascii of 'a'

   while (gotoMat[answer][ch] == -1) //if go to is not found, use fail function
      answer = fail[answer];
   return gotoMat[answer][ch];
}

void patternSearch(string arr[], int size, string text) {
   buildTree(arr, size);    //make the trie structure
   int presentState = 0;    //make current state as 0

   for (int i = 0; i < text.size(); i++) {    //find all occurances of pattern
      presentState = getNextState(presentState, text[i]);
      if (output[presentState] == 0)    //if no match continue;
      for (int j = 0; j < size; ++j) {   //matching found and print words
         if (output[presentState] & (1 << j)) {
            cout << "Word " << arr[j] << " location: " << i - arr[j].size() + 1 << endl;
         }
      }
   }
}

int main() {
   string arr[] = {"their", "there", "answer", "any", "bye"};
   string text = "isthereanyanswerokgoodbye";
   int k = sizeof(arr)/sizeof(arr[0]);
   patternSearch(arr, k, text);
   return 0;
}