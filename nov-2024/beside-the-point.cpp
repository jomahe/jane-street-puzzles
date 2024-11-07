#include <iostream>
#include <random>

using namespace std;


// Helper method to generate pseudorandom numbers in [0, 1]
double GenerateRandNum() {
  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<> dist(0.0, 1.0);

  return dist(gen);
}

pair<double, double> GenerateRandPoint() {
  return {GenerateRandNum(), GenerateRandNum()};
}

// Apply a transformation to the points and sweep from the "bottom" side of
// the square
pair<pair<double,double>, pair<double,double>> ApplyTransform(
    pair<double,double> blue, pair<double,double> red, char& closest) {
  pair<double,double> blue_prime;
  pair<double,double> red_prime;

  switch(closest) {
    case ('r'):
      blue_prime = {blue.second, 1.0 - blue.first};
      red_prime = {red.second, 1.0 - red.first};
    case ('t'):
      blue_prime = {1.0 - blue.first, 1.0 - blue.second};
      red_prime = {1.0 - red.first, 1.0 - red.second};
    case ('l'):
      blue_prime = {1.0 - blue.second, blue.first};
      red_prime = {1.0 - red.second, red.first};
    case ('b'):
      blue_prime = blue;
      red_prime = red;
    default:
      // If closest isn't one of these chars, fucked up.
  }
  return {blue_prime, red_prime};
}

bool FoundEquidistantPoint() {
  // Generate blue and red points
  pair<double, double> blue_raw = GenerateRandPoint();
  pair<double, double> red_raw = GenerateRandPoint();

  // Determine which side is closest to blue; use the perpendicular distance to
  // each side since that's the shortest path.
  double blue_x = blue_raw.first, blue_y = blue_raw.second;
  double top_dist, bottom_dist, left_dist, right_dist;

  top_dist = 1 - blue_y, bottom_dist = blue_y;
  right_dist = 1 - blue_x, left_dist = blue_x;

  char closest = ' ';

  if (right_dist <= min(top_dist, bottom_dist, left_dist)) {
    closest = 'r';
  } else if (top_dist <= min(right_dist, bottom_dist, left_dist)) {
    closest = 't';
  } else if (bottom_dist <= min(top_dist, right_dist, left_dist)) {
    closest = 'b';
  } else {
    closest = 'l';
  }

  auto [blue, red] = ApplyTransform(blue_raw, red_raw, closest);

  // Implement a binary search to look for a point equidistant from both points

}

int main(void) {

  int num_equidistant = 0, total_count = 0;
  while (true) {
    ++total_count;
    num_equidistant += FoundEquidistantPoint();
    cout << (double) num_equidistant / (double) total_count << endl;
  }

  return 0;
}