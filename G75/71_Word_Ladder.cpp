class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        queue<string> todo;
        todo.push(beginWord);
        int result = 1;
        while (!todo.empty()) {
            int size = todo.size();
            for (int i = 0; i < size; i++) {
                string word = todo.front();
                todo.pop();
                if (word == endWord) {
                    return result;
                }
                dict.erase(word);
                for (int j = 0; j < word.size(); j++) {
                    char c = word[j];
                    for (int k = 0; k < 26; k++) {
                        word[j] = 'a' + k;
                        if (dict.find(word) != dict.end()) {
                            todo.push(word);
                        }
                    }
                    word[j] = c;
                }
            }
            result++;
        }
        return 0;
        
    }
};