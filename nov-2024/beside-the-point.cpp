#include <iostream>
#include <iomanip>
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
void ApplyTransform(pair<double,double>& blue, pair<double,double>& red,
                    char& closest) {
  double blue_x_raw = blue.first, blue_y_raw = blue.second;
  double red_x_raw = red.first, red_y_raw = red.second;

  switch(closest) {
    case ('r'):
      blue = {blue_y_raw, 1.0 - blue_x_raw};
      red = {red_y_raw, 1.0 - red_x_raw};
      break;
    case ('t'):
      blue = {1.0 - blue_x_raw, 1.0 - blue_y_raw};
      red = {1.0 - red_x_raw, 1.0 - red_y_raw};
      break;
    case ('l'):
      blue = {1.0 - blue_y_raw, blue_x_raw};
      red = {1.0 - red_y_raw, red_x_raw};
      break;
    case ('b'):
      // No transformation needed!
      break;
    default:
      // If closest isn't one of these chars, fucked up.
      break;
  }
}

// Function to find the line intersecting the two points, find the midpoint of
// the line, and to follow the line perpendicular (and intersecting the
// midpoint) to the endpoints of the line (0,0) and (1,0). We can simply check
// the endpoints and see if either of the checks evaluate to <= 0. If so, then
// the line must intersect with the bottom of the square.
bool FoundEquidistantPointOnSegment(
    pair<double,double>& blue, pair<double,double>& red) {
  // Find the line intersecting the two points, the midpoint of
  double connecting_slope =
    (blue.second - red.second) / (blue.first - red.first);
  auto starting_point = blue.first <= red.first ? blue : red;
  auto midpoint = pair<double,double>(
    (blue.first + red.first) / 2.0,
    starting_point.second +
      connecting_slope * ((blue.first + red.first) / 2.0 - starting_point.first)
  );

  double perpendicular_slope = -1.0 / connecting_slope;

  // Check the endpoints of the perpendicular line
  return (connecting_slope * (1 - midpoint.first) + midpoint.second <= 0 ||
          connecting_slope * (0 - midpoint.first) + midpoint.second <= 0);
}

bool FoundEquidistantPoint() {
  // Generate blue and red points
  pair<double, double> blue = GenerateRandPoint();
  pair<double, double> red = GenerateRandPoint();

  // Determine which side is closest to blue; use the perpendicular distance to
  // each side since that's the shortest path.
  double blue_x = blue.first, blue_y = blue.second;
  double top_dist, bottom_dist, left_dist, right_dist;

  top_dist = 1 - blue_y, bottom_dist = blue_y;
  right_dist = 1 - blue_x, left_dist = blue_x;

  char closest = ' ';

  if (right_dist <= min(min(top_dist, bottom_dist), left_dist)) {
    closest = 'r';
  } else if (top_dist <= min(min(right_dist, bottom_dist), left_dist)) {
    closest = 't';
  } else if (bottom_dist <= min(min(top_dist, right_dist), left_dist)) {
    closest = 'b';
  } else {
    closest = 'l';
  }
  ApplyTransform(blue, red, closest);
  return FoundEquidistantPointOnSegment(blue, red);
}

int main(void) {
  int num_equidistant = 0, total_count = 0;
  while (true) {
    ++total_count;
    num_equidistant += FoundEquidistantPoint();
    cout << "Total runs: " << total_count << ". Current probability: "
         << setprecision(10) << (double) num_equidistant / (double) total_count << endl;
  }

  return 0;
}