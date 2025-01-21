# Jane Street Puzzles - January 2025: Somewhat Square Sudoku

## Description:

<img title="squares" src="https://www.janestreet.com/puzzles/20250101_sudoku.png">

Fill the empty cells in the grid above with digits such that each row, column,
and outlined 3-by-3 box contains the same set of nine unique digits\*, and such
that the nine 9-digit numbers\*\* formed by the rows of the grid has the
highest-possible GCD over any such grid.

Some of the cells have already been filled in. The answer to this puzzle is the
9-digit number formed by the middle row in the completed grid.

\* that is, you’ll be using nine of the ten digits (0-9) in completing this grid

\*\* possibly with a leading 0

# Approach:

The first approach taken was to try to brute-force potential valid solutions to the starting grid (an O(9^81) approach) and check to see whether or not the rows have a common GCD. This was a Bad approach; generally generating all possible solutions in the space is not in the spirit of these problems.

The next try was to first choose a GCD, then try to construct rows of the grid recursively (filling in the cells of each column in the row before moving onto the next) and backtrack based on whether or not they fit the row requirements of the starting grid and are divisible by the prospective GCD. If there's no possible solution, use the next lowest GCD and try again. This was again not constraining enough on the solution set and the runtime of a program to find such a GCD would have taken a long time.

Finally, the successful approach taken was to continue constraining the GCD, but not to try to construct a potential sudoku board. The objective here was to find GCDs which could plausibly have multiples that would fill the rows of the sudoku board. The heuristic is as follows: for a given GCD, find all multiples between `[0]10000000` and `100000000`, so that the multiples are in the correct range to occupy all cells.
Next, understanding that we need to leave one digit in `[0, 9]` out of the solution, we loop through the possible digits to leave out `(1, 3, 4, 6, 7, 8, 9)` and see if we can construct **any** multiples with nine unique digits (referred to as uniques from here on). We store these uniques into a `vector<vector<int>>`, with the top level vector indexed by the digit left out, and the inner vector being the one containing all corresponding uniques with the digit left out.
Next, we take this vector and for each of the digits left out, generate "buckets," a structure represented by another `vector<vector<int>>`, where each inner vector's index corresponds to the row that the constituent integers can feasibly occupy given the starting board. The thought here was that there would exist starting GCDs whose buckets would contain more than one number per row, so it would be necessary to then feed these potential rows into a recursive solver which would construct a board given the rows, backtracking if a completed grid violated the rules of sudoku. **However**, in generating the largest possible GCD who had at least nine uniques which could feasibly occupy the rows, it happened to be the solution, as those potential rows did not violate the rules of sudoku.

This number was `[0]12345679`, whose multiples and potential rows (from top to bottom) were: `395061728, [0]61728395, 728395061, 950617283, 283950617, 617283950, 839506172, 506172839, 172839506`

Therefore, the answer to this problem was `283950617`, the 9-digit number occupying the middle row.

## Learnings:

- Do not attempt to brute-force a solution to these puzzles.
- If you need to use computation, try to reduce the set of possible solutions as much as you can before doing so. For example, the first step was to start computing from the largest possible GCD for numbers between `[10^7, 10^8]`, which was `98765431`. Then, it narrowed it down to the largest GCD s.t. nine uniques could be found, `013428567`. Then, narrowed it down to the largest GCD s.t. all 9 buckets were occupied, `012345679`. This happened to be the solution, but the set of numbers to check for was reduced by ≈ 98.75%.
