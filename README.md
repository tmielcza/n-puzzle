# N-puzzle
A N-Puzzle solver for OS X.

## What's good about it
It's fast ? I think.

## How to
```
make
./npuzzle [<file>] [-s <size>] [-h <heuristic_name>] [-b]
```
`size` is the length of the square's edge.

`heuristic_name` is one of: `zero manhattan misplacedtiles linearconflict linearconflictplus`.  
The default is `manhattan`.

`-b` is for bidirectionnal search.

File format:
```
# size
4
# lines
1 2 3 4
12 13 14 5
11 0 15 6
10 9 8 7
```
