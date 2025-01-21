#include <iostream>
#include <vector>
#include <unistd.h>

using namespace std;

constexpr int kDigitsLeftOut[7] = {1, 3, 4, 6, 7, 8, 9};

// Find the smallest possible GCD which has at least nine multiples with unique
// digits
int NextLowestGcd(int initial_gcd) {
  int next_gcd = initial_gcd - 2;
  while (next_gcd % 5 == 0 && next_gcd > 0) {
    next_gcd -= 2;
  }
  return next_gcd;
}

bool HasUniqueDigits(int num, int digit_left_out) {
  bool seen[10] = {false};
  seen[0] = (num / 100000000 < 1);
  int last_digit;
  while (num > 0) {
    last_digit = num % 10;
    if (digit_left_out != -1 && last_digit == digit_left_out) {
      return false;
    }
    if (seen[last_digit] == true) {
      return false;
    }
    seen[last_digit] = true;
    num /= 10;
  }
  return true;
}

vector<vector<int>> GenerateUniqueMultiples(int gcd) {
  int digits_left_out[7] = {1,3,4,6,7,8,9};
  vector<vector<int>> multiples(10);
  int multiple = gcd;
  while (multiple / 10000000 < 1) {
    multiple *= 10;
  }
  while (multiple < 1000000000) {
    for (const int& digit : digits_left_out) {
      if (HasUniqueDigits(multiple, digit)) {
        // There's only one possible missing digit for each prospective row. Can
        // break if we find it.
        multiples[digit].push_back(multiple);
        break;
      }
    }
    multiple += gcd;
  }
  return multiples;
}

int LowestGcdWithNineUniqueMultiples() {
  int gcd = 36984127;
  vector<vector<int>> multiples = GenerateUniqueMultiples(gcd);
  while (multiples.size() < 9 && gcd > 0) {
    gcd = NextLowestGcd(gcd);
    multiples = GenerateUniqueMultiples(gcd);
  }
  return gcd;
}

bool RowZeroConstraint(vector<int>& row) {
  // Row 0 must have 2 at index 7, no 2 at index 4, no zeros at idx 2, 4, and
  // no five at index 6, 8.
  return !(row[7] != 2 || row[4] == 2 || row[2] == 0 ||
           row[4] == 0 || row[6] == 5 || row[8] == 5);
}

bool RowOneConstraint(vector<int>& row) {
  // Row 1: must have a 2 at idx 4, 5 at index 8, no 0s at idx 2, 4, no 2s at
  return !(row[4] != 2 || row[8] != 5 || row[2] == 0 || row[4] == 0);
}

bool RowTwoConstraint(vector<int>& row) {
  // Row 2: must have 2 at idx 1, no 0 at idx 2, 4, no 5 at idx 6, 8
  return !(row[1] != 2 || row[2] == 0 || row[4] == 0 ||
           row[6] == 5 || row[8] == 5);
}

bool RowThreeConstraint(vector<int>& row) {
  // Row 3: must have 0 at idx 2, no 2 at idx 1, 3, 5, 7, no 5 at idc 6, 8
  return !(row[2] != 0 || row[1] == 2 || row[3] == 2 ||
           row[4] == 2 || row[5] == 2 || row[6] == 5 ||
           row[7] == 2 || row[8] == 5);
}

bool RowFourConstraint(vector<int>& row) {
  // Row 4 has no givens but cannot have 2 at idxs 1, 3, 4, 5, 7, no 0s at idxs 2, 4, and no 5s at idxs 6, 8
  return !(row[1] == 2 || row[3] == 2 || row[4] == 2 ||
           row[5] == 2 || row[7] == 2 || row[2] == 0 ||
           row[4] == 0 || row[6] == 5 || row[8] == 5);
}

bool RowFiveConstraint(vector<int>& row) {
  // Row 5 has 2 at idx 3, no 0 at idxs 2, 4, no 5s at idx 6, 8.
  return !(row[3] != 2 || row[4] == 2 || row[6] == 5 || row[8] == 5);
}

bool RowSixConstraint(vector<int>& row) {
  // Row 6 has 0 at idx 4, no 2 at idx 1, 3, 4, 5, 7, no 5 at idx 6, 8
  return !(row[4] != 0 || row[1] == 2 || row[3] == 2 ||
           row[4] == 2 || row[5] == 2 || row[7] == 2 ||
           row[6] == 5 || row[8] == 5);
}

bool RowSevenConstraint(vector<int>& row) {
  // Row 7 has 2 at idx 5, no 0 at idxs 2, 4, no 5s at idxs 6, 8
  return !(row[5] != 2 || row[2] == 0 || row[4] == 0 ||
           row[6] == 5 || row[8] == 5);
}

bool RowEightConstraint(vector<int>& row) {
  // Row 8 has 5 at idx 6, no 2s at idxs 1, 3, 4, 5, 7, no 0s at idxs 2, 4
  return !(row[6] != 5 || row[1] == 2 || row[3] == 2 ||
           row[4] == 2 || row[5] == 2 || row[7] == 2 ||
           row[2] == 0 || row[4] == 0);
}

vector<int> IntToArray(int num) {
  vector<int> vec(9);
  if (num < 100000000) {
    vec[0] = 0;
  }
  for (size_t i = 0; i < 9; ++i) {
    vec[8 - i] = num % 10;
    num /= 10;
    if (num == 0) {
      break;
    }
  }
  return vec;
}

void AssignRow(vector<vector<int>>& buckets, int row) {
  vector<int> row_array = IntToArray(row);
  if (RowZeroConstraint(row_array)) {
    buckets[0].push_back(row);
  } else if (RowOneConstraint(row_array)) {
    buckets[1].push_back(row);
  } else if (RowTwoConstraint(row_array)) {
    buckets[2].push_back(row);
  } else if (RowThreeConstraint(row_array)) {
    buckets[3].push_back(row);
  } else if (RowFourConstraint(row_array)) {
    buckets[4].push_back(row);
  } else if (RowFiveConstraint(row_array)) {
    buckets[5].push_back(row);
  } else if (RowSixConstraint(row_array)) {
    buckets[6].push_back(row);
  } else if (RowSevenConstraint(row_array)) {
    buckets[7].push_back(row);
  } else if (RowEightConstraint(row_array)) {
    buckets[8].push_back(row);
  }
}

vector<vector<int>> GenerateBuckets(vector<int>& rows) {
  vector<vector<int>> buckets(9);
  for (const int& row : rows) {
    AssignRow(buckets, row);
  }
  return buckets;
}


int main(void) {
  /**
   * Highest number such that we can generate 9 numbers with 9 unique digits
   * each, with a digit left out (9).
   * FIRST GCD WITH 9 UNIQUE MULTIPLES WITH A DIGIT LEFT OUT: 013428567
   * MULTIPLES:
   * 013428567 026857134 053714268 067142835 107428536 134285670 268571340
   * 537142680 671428350
   */
  // int gcd = 13428567;

  /**
   * Highest number such that there are at least nine unique numbers which
   * satisfy the row requirements for a sudoku board given the starting board
   */
  int gcd = 12345679;
  while (gcd > 0) {
    cout << "checking: " << gcd << endl;
    vector<vector<int>> unique_multiples = GenerateUniqueMultiples(gcd);
    for (const int& digit : kDigitsLeftOut) {
      if (unique_multiples[digit].size() >= 9) {
        // Generate the buckets: each entry holds a vector of ints, each are
        // compatible with the row in a sudoku board corresponding to its index.
        vector<vector<int>> buckets = GenerateBuckets(unique_multiples[digit]);
        bool success = true;
        for (const auto& bucket : buckets) {
          if (bucket.size() < 1) {
            success = false;
            break;
          }
        }
        if (success) {
          cout << "GCD WHERE THERE ARE 9 OCCUPIED BUCKETS: " << gcd
               << " WITH DIGIT LEFT OUT: " << digit << endl;
          int row = 0;
          for (const auto& bucket : buckets) {
            cout << "Potential nums for row: " << row << endl;
            for (const int& num : bucket) {
              cout << num << " ";
            }
            cout << endl;
            ++row;
          }
          sleep(6);
        }
      }
    }
    gcd = NextLowestGcd(gcd);
  }
}
