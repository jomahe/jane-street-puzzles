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
