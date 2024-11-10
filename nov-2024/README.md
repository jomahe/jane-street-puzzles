# Jane Street Puzzles - October 2024: Knight Moves 6

## Description:

<img title="squares" src="https://www.janestreet.com/puzzles/november-2024.png">

Two random points, one red and one blue, are chosen uniformly and independently from the interior of a square. To ten decimal places1, what is the probability that there exists a point on the side of the square closest to the blue point that is equidistant to both the blue point and the red point?

## Approach:

Going to generate random numbers `x, y` $\in$ [0,1] for both the red and blue
points. Next, find the closest side to the blue point. Then, for every point
(maybe a binary search instead for runtime purposes?) you attempt to find a
point on the wall equidistant from the two points. Rerun this simulation many
many times until your running average converges within 10 decimal points.

### Notes:

Originally, the approach I was going to take to find the point equidistant was
an optimization one where you try to minimize the difference of the distances of
the two points and perform a sort of binary search on the points of the line, or
to try to solve for the optimal point using derivatives.

On a morning walk, though, pondering the question on 11/10, I thought about what
would arise if I took the line segment between the two points, found the
midpoint there, and then used a line perpendicular to that segment, intersecting
with the midpoint. If the closest side of the square's line segment was a true
line (ran forever in both directions), we'd be guaranteed to find an intersection
unless they shared the exact same x or y coordinate. However, since the sides do
not extend forever, there is a probabilistic elemtn to it. If the perpendicular
line intersects with the side of the square, we can add one to the count and
continue with the simulation.
