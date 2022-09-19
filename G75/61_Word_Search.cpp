class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (board[i][j] == word[0] && dfs(board, word, i, j, 0)) return true;
            }
        }
        return false;  
    }
    bool dfs(vector<vector<char>>& board, string word, int i, int j, int idx) {
        if (idx == word.size()) return true;
        if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size() || board[i][j] != word[idx]) return false;
        bool found = false;
        char temp = board[i][j];
        board[i][j] = ' ';
        idx++;
        found = dfs(board, word, i+1, j, idx) ||
            dfs(board, word, i-1, j, idx) ||
            dfs(board, word, i, j+1, idx) ||
            dfs(board, word, i, j-1, idx);
        board[i][j] = temp;
        return found;
    }
};