// If color already same as target, return original image
// Grab continuity target (original cell color) and place into target variable
// Change the color of the pointed cell
// Prepare a "shift" array to iterate through
// Load a processing queue starting with candidates to change color
// for each "shift" candidate (up, down, left, right)....
// Update the x and y coordinate according to which of four pairs you're on
// Test boundary conditions + continuity color condition of updated "neighbor" cell
// Change the color.. Add another processing cell to the queue
// When no more to fill (i.e. boundaries extinguished).. return image

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