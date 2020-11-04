# tsp_ai

Programming assignment 1 of AI

## What works
The savings algorithm alone has been applied to generate tours. This alone passes all test cases with decent scores.

## What needs some fixing
The commented part of the code has 2-OPT (needs correction).

Currently the code doesn't check if the switch is generating a valid tour or not. If you apply that condition as well, your tours will be much more optimised.

## How to run
### Ubuntu/Linux:
> g++ code.cpp -o tsp\
> ./tsp < _input_file_ > _output_file_

### Windows:
> g++ code.cpp -o tsp\
> tsp < _input_file_ > _output_file_
