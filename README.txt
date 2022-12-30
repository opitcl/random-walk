Author: Olivia Pitcl
Random Walk in 3, 3, and 1 dimensions

To run:
	- compile
	So long as the makefile is in your current directory, type 'make' on
	the command line to compile the current c file.

	- run
	In addition to typing the name of the executable file, a few command line
	arguments will need to be specified in order to run.

	'-n' specify number of iterations:
	Example:
	random-walk -n 1000
	Runs random walk for each dimension for 100 iterations (but will not run anything since
	the border width is not specified)

	'-b' specify border width:
	Example
	random-walk -n 100 -b 5
	Runs the random walk problem for 100 iterations with a radius of 5 for each
	dimension

	'-d' specify number of dimensions:
	Example
	random-walk -n 100 -b 5 -d 2
	Runs the random walk problem for the 2nd dimension for 100 iterations
	over a circular area with a radius of 5
	If nothing is specified, all dimensions will be run

	If no number is presented next to an option, an error will be thrown.

Final example:
If is want to run the program in the 3rd dimension for 1000 iterations over a border of
1000 steps, I'd run:
make
random-walk -n 1000 -b 1000 -d 3
