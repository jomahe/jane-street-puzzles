# Jane Street Puzzles - October 2024: Knight Moves 6

## Description:

<img title="board" src="october.png">
Pick distinct positive integers A, B, and C, and place them in the grid above.
Your goal is to create two corner-to-corner trips — one from a1 to f6, and the
other from a6 to f1 — both of which score exactly 2024 points.

A “trip” consists of knight’s moves. Squares may not be revisited within a trip.

The “score” for a trip is calculated as follows:

- Start with A points.
- Every time you make a move:
  - if your move is between two different integers, multiply your score by the
    value you are moving to;
  - otherwise, increment your score by the value you are moving to. Can you
    find positive integers A, B, and C, as well as a pair of trips, that satisfy
    the criteria above? How low can you get A + B + C?

Please format your entry by concatenating your values for A, B, and C, followed
by your a1-to-f6 tour, followed by your a6-to-f1 tour. For example,
“1,2,253,a1,b3,c5,d3,f4,d5,f6,a6,c5,a4,b2,c4,d2,f1” would be a properly
formatted entry.

To qualify for the leaderboard your value for A + B + C must be less than 50.

Full page [here](https://www.janestreet.com/puzzles/current-puzzle/)

## Approach:

First, I am going to generate all possible paths from A1 to F6 and brute-force
my way to find the solution that generates a score of 2024 by formulating a
integer program that will find integers satisfying the rules. It's likely that
many solutions will not work, so I will likely have to create a new IP for each
potential path. Because of the first sub-rule, this will be a convex
optimization problem (multiplying the score by the different integer value). I
can probably do this with scipy.
