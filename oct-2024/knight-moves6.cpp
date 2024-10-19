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

vector<string> findPaths(pair<int,int> start, pair<int,int> end) {
  vector<string> paths;

}

void aggregatePaths() {
  vector<string> trip1_paths = findPaths({5, 0}, {0, 5});
  vector<string> trip2_paths = findPaths({0, 0}, {5, 5});
  map<pair<int, int>, bool> visited;

  // Generate paths from a1


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