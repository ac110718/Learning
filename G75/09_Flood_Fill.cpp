class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        if (image[sr][sc] == color) return image;
        int target = image[sr][sc];
        image[sr][sc] = color;
        int delta[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        queue<pair<int, int>> q;
        q.push(make_pair(sr, sc));
        while (!q.empty()) {
            int row = q.front().first;
            int col = q.front().second;
            q.pop();
            for (int k = 0; k < 4; k++) {
                int x = row + delta[k][0];
                int y = col + delta[k][1];
                if (x >= 0 && y >= 0 && x < image.size() && y < image[0].size() && image[x][y] == target) {
                    image[x][y] = color;
                    q.push(make_pair(x, y));
                }
            }
        }
        return image;
    }
};