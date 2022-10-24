// store all letters of magazine into map
// which stores frequency of characters
// iterate through the note, ensuring the character is in the map
// decrement char frequency along the way..
// if either no character, or < 0 characters, then return false


class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        unordered_map<char, int> map;
        for (int i = 0; i < magazine.size(); i++) {
            map[magazine[i]]++;
        }
        for (int i = 0; i < ransomNote.size(); i++) {
            if (map.find(ransomNote[i]) == map.end() || --map[ransomNote[i]] < 0) return false;
        }
        return true;
    }
};