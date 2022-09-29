#include<bits/stdc++.h>

using namespace std;


// the 8 ways to traverse from a node to it's neighbor 
int dx8[] = {1, 1, 0, -1, -1, -1, 0, 1};
int dy8[] = {0, 1, 1, 1, 0, -1, -1, -1};


// the height and the width of the grid 
const int n = 3, m = 4;

#define alphabet_size  26
#define MAX 50



// Trie Structure begins here 
struct node {
    bool isTerminal;
    node *nxt[alphabet_size];
    string word;
    node () {
        this->word = "";
        this->isTerminal = false;
        for (int i = 0; i < alphabet_size; i ++ ) {
            this->nxt[i] = nullptr;
        }
    }

}*root = new node();

void insertTrie(string &word) {
    node *curr = root;
    for (auto ch : word) {
        int idx = ch - 'A';
        if (!curr->nxt[idx]) {
            curr->nxt[idx] = new node();
        }
        curr = curr->nxt[idx];
    }
    curr->isTerminal = true;
    curr->word = word;
}
bool findTrie(string &word) {
    node *curr = root;
    for (auto ch : word) {
        int idx = ch - 'A';
        if (!curr->nxt[idx]) return false;
        curr = curr->nxt[idx];
    }
    return true;

}

// Trie ends here 



unordered_set<string> output;
// input for example
string words[] = {"SNAKE", "FOR", "QUEZ",
                  "SNACK", "SNACKS",
                  "GO","TUNES", "CAT"};


// the game board 
char board[3][4] = {
        {'S', 'E', 'R', 'T'},
        {'U', 'N', 'K', 'S'},
        {'T', 'C', 'A', 'T'},

};

// visited array to keep track of the subsequences
bool vis[MAX][MAX];


// checking if the given indexes from the dfs calls are valid
bool isValid(int x, int y) {
    return x >= 0 && y >= 0 && x < n && y < m;
}

// 8-way dfs for exploring the grid guided search by the trie structure
void dfs(int x, int y, node* currNode) {
    int idx = board[x][y] - 'A';

    // base case
    // if we didn't find the current char in the curr level
    // then the word isn't inserted in the trie
    if (currNode->nxt[idx] == nullptr)
        return;


    // mark the node visited for now
    vis[x][y] = true;
    currNode = currNode->nxt[idx];


    // checking if we reached a word
    if (currNode->isTerminal) {
        output.insert(currNode->word);
    }

    // 8-way dfs
    for (int i = 0; i < 8; i ++ ){
        int new_x = x + dx8[i];
        int new_y = y + dy8[i];

        if (isValid(new_x, new_y) && !vis[new_x][new_y]) {
            dfs(new_x, new_y,currNode);
        }
    }
    // backtrack step
    // marking the node not visited for generating all subsequences from the grid
    vis[x][y] = false;

}



int32_t main() {

    // inserting all our input words to the trie to guide the search 
    for (auto word : words){
        insertTrie(word);
    }


    // 8-way dfs from every cell
    for (int i = 0; i < n; i ++ ){
        for (int j = 0; j < m; j ++ ) {
            dfs(i, j, root);

            // reset the visited array after each call (while backtracking)
            // using backtrack to get subsequences

        }
    }

    // print the output
    for (auto &word : output){
        cout << word << endl;
    }
    system("pause");
}