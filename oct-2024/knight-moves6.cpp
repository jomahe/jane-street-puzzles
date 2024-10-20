#include <iostream>
#include <map>
#include <vector>

using namespace std;

vector<vector<char>> board{
                           {'a', 'b', 'b', 'c', 'c', 'c'},   // 6
                           {'a', 'b', 'b', 'c', 'c', 'c'},   // 5
                           {'a', 'a', 'b', 'b', 'c', 'c'},   // 4
                           {'a', 'a', 'b', 'b', 'c', 'c'},   // 3
                           {'a', 'a', 'a', 'b', 'b', 'c'},   // 2
                           {'a', 'a', 'a', 'b', 'b', 'c'}    // 1
};  //                       A    B    C    D    E    F

vector<pair<int, int>> knight_moves = {
    {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
    {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
};

inline bool validMove(int col, int row, bool (&visited)[6][6]) {
  return (row >= 0 && row <= 5 && col >= 0 && col <= 5 && !visited[row][col]);
}

void dfs(pair<int,int> start, pair<int,int> end, string& curr_path,
         vector<string>& all_paths, bool (&visited)[6][6]) {
  int x = start.second, y = start.first;
  curr_path += board[y][x];
  visited[y][x] = true;

  if (start == end) {
    all_paths.push_back(curr_path);
    return;
  }

  for (const pair<int,int>& move : knight_moves) {
    int new_x = move.second + x, new_y = move.first + y;
    if (!validMove(new_x, new_y, visited)) continue;

    dfs({new_y, new_x}, end, curr_path, all_paths, visited);

    curr_path.pop_back();
    visited[new_y][new_x] = false;
  }
}

void aggregatePaths() {

  // Generate potential paths from A1 to F6
  bool visited[6][6] = {false};
  string curr_path;
  vector<string> trip1_paths;
  dfs({5, 0}, {0, 5}, curr_path, trip1_paths, visited);

  // Generate potential paths from A6 to F1
  memset(visited, 0, sizeof(visited));
  vector<string> trip2_paths;
  dfs({0, 0}, {5, 5}, curr_path, trip2_paths, visited);

  for (const string& path : trip1_paths) {
    cout << path << '\n' << "====" << endl;
  }
  for (const string& path : trip2_paths) {
    cout << path << '\n' << "====" << endl;
  }
}

int main() {
  aggregatePaths();
  return 0;
}