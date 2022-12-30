/**
 * Author: Olivia Pitcl
 * Phys 426
 * Code to produce random walks for 1D, 2D, and 3D
 *
 * Timeout is set to 20 minutes
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

int rightLeft(double pRight, double pLeft) {
	// Generate random float between 0 and 1, 3 decimal places of precision
	double r = rand() % 1000 / 1000.0;
	// printf("%.3f ", r);
	// If less than pRight, return 0
	if (r < pRight) {
		return 1;
	}

	// If less than 1 - pRight, return 1
	return -1;
}

int randomWalk_1D(int border, double pRight, double pLeft) {
	// Original position is at the origin
	int cur = 0;

	// Count for total number of steps (return value)
	int count = 1;
	
	// Take the first step
	int step = rightLeft(pRight, pLeft);
	cur += step;

	while (cur != 0 && abs(cur) < border) {
		step = rightLeft(pRight, pLeft);
		cur += step;
		count += 1;
	}
	if (abs(cur) > border) {
		return -1;
	}

	return count;
}

/**
 * Our 2D random walk displacement will be governed by randomness,
 * generating a random angle from 0 to 2pi and then incrementing our
 * x- and y- coordinates in that fashion.
 */
void radius_2D_HARD(int* coords) {
	// Some random number between 0 and 2 pi
	int ra = rand();

	// To 5 sig figs
	int pi = (int) M_PI * 1000000;
	double r = ra % pi / 1000000;

	coords[0] = cos(r);
	coords[1] = sin(r);
}

/**
 * Our 2D random walk displacement will be governed by randomness,
 * generating a random angle from 0 to 2pi and then incrementing our
 * x- and y- coordinates by pos/neg 1.
 */
void radius_2D_EASY(int* coords) {
	// Some random number between 0 and 2 pi
	double ra_x = rand() % 1000 / 1000.0;
	double ra_y = rand() % 1000 / 1000.0;
	
	// Shift
	ra_x -= 0.5;
	ra_y -= 0.5;

	// printf("%.2f, %.2f\n", ra_x, ra_y);
	// Use unit vector
	if (ra_x < 0.0) {
		coords[0] = -1;
	} else {
		coords[0] = 1;
	}
	if (ra_y < 0.0) {
		coords[1] = -1;
	} else {
		coords[1] = 1;
	}
}

/**
 * Our 3D random walk displacement will be governed by randomness,
 * generating a random angle float between -0.5 and 0.5 and incrementing
 * x, y, and z by -1 or 1 respectively
 */
void radius_3D(int* coords) {
	// Some random number between 0 and 2 pi
	double ra_x = rand() % 1000 / 1000.0;
	double ra_y = rand() % 1000 / 1000.0;
	double ra_z = rand() % 1000 / 1000.0;

	// Shift
	ra_x -= 0.5;
	ra_y -= 0.5;
	ra_z -= 0.5;

	// printf("%.2f, %.2f\n", ra_x, ra_y);
	// Use unit vector
	if (ra_x < 0.0) {
		coords[0] = -1;
	} else {
		coords[0] = 1;
	}
	if (ra_y < 0.0) {
		coords[1] = -1;
	} else {
		coords[1] = 1;
	}
	if (ra_z < 0) {
		coords[2] = -1;
	} else {
		coords[2] = 1;
	}
}

double getRadius(int x, int y) {
	double toReturn = pow(x, 2.0) + pow(y, 2.0);
	toReturn = pow(toReturn, 0.5);
	return toReturn;
}

double getRadius_3D(int x, int y, int z) {
	double toReturn = pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0);
	toReturn = pow(toReturn, 0.5);
	return toReturn;
}
/**
 * Random walk for a particle in 2D
 * If one walk exceeds 30s, the function will return
 */
int randomWalk_2D(int border, double timeout) {
	clock_t start_t, end_t;

	// Original position is at the origin
	int cur_x = 0;
	int cur_y = 0;

	// Count for total number of steps (return value)
	int count = 1;
	
	// Take the first step
	int* steps = calloc(2, sizeof(int));
	radius_2D_EASY(steps);
	cur_x += steps[0];
	cur_y += steps[1];
	

	double radius = getRadius(cur_x, cur_y);
	border = (double) border / pow(2.0, 0.5);
	
	start_t = clock();
	while ((radius > 0.0) && (radius < border)) {
		radius_2D_EASY(steps);
		cur_x += steps[0];
		cur_y += steps[1];
		count += 1;
		radius = getRadius(cur_x, cur_y);

		// Return if we've travelled for too long
		end_t = clock();
		double change = (end_t - start_t) / CLOCKS_PER_SEC;

		// Break, do not return (memory)
		if (change > timeout) {
			printf("Timeout\n");
			count = -1;
			break;
		}
	}
	free(steps);

	if (radius > border) {
		return -1;
	}

	return count;
}


/**
 * Random walk for a particle in 3D
 * If one walk exceeds 10s, the function will return
 */
int randomWalk_3D(int border, double timeout) {
	clock_t start_t, end_t;

	// Original position is at the origin
	int cur_x = 0;
	int cur_y = 0;
	int cur_z = 0;

	// Count for total number of steps (return value)
	int count = 1;
	
	// Take the first step
	int* steps = calloc(3, sizeof(int));
	radius_3D(steps);
	cur_x += steps[0];
	cur_y += steps[1];
	cur_z += steps[2];

	double radius = getRadius_3D(cur_x, cur_y, cur_z);
	border = (double) border / pow(2.0, 0.5);
	
	start_t = clock();
	while ((radius > 0.0) && (radius < border)) {
		radius_3D(steps);
		cur_x += steps[0];
		cur_y += steps[1];
		cur_z += steps[2];

		count += 1;
		radius = getRadius_3D(cur_x, cur_y, cur_z);

		// Return if we've travelled for too long
		end_t = clock();
		double change = (end_t - start_t) / CLOCKS_PER_SEC;

		// Break, do not return (memory)
		if (change > timeout) {
			printf("Timeout\n");
			count = -1;
			break;
		}
	}
	free(steps);

	if (radius > border) {
		return -1;
	}

	return count;
}


int main(int argv, char** argc) {
	// The borders for these problems will be 100 steps away on either side of the origin,
	// specified by command line arguments
	int border = 0;
	int num = 0;
	double timeout = 10;
	int dimension = 0;

	// Example of how to run (order must be maintained)
	// random-walk -b 1000 -n 2000 -d 3
	// This will run the program with a border 1000 spaces from the origin
	// and 2000 runs per walk in dimension 3
	for (int i = 1; i < argv; i++) {
		if (strcmp(argc[i], "-b") == 0) {
			char* ch = argc[i+1];
			printf("%s\n", ch);
			border = atoi(ch);
		}
		
		if (strcmp(argc[i], "-n") == 0) {
			char* ch1 = argc[i+1];
			printf("%s\n", ch1);
			num = atoi(ch1);
		}
		
		if (strcmp(argc[i], "-d") == 0) {
			char* ch2 = argc[i+1];
			printf("%s\n", ch2);
			dimension = atoi(ch2);
		}
	}
	
	//-------------- 1D -----------------------------------
	// Random walk, 1D, border determines radius
	// Run 1D walk about num times to get an even spread of data, writing each of these
	// results to a csv file
	if (dimension == 0 || dimension == 1) {
		FILE *file = fopen("random-walk-1D.csv", "w");


		// Note the parameters of the run
		fprintf(file, "Number of iter: %d\n", num);
		fprintf(file, "Length of border: %d\n", border);
		fprintf(file, "Dimension: %d\n", dimension);

		for (int i = 0; i < num; i++) {
			int result = randomWalk_1D(border, 0.5, 0.5);
			fprintf(file, "%d ", result);
		}
		printf("Not getting stuck on 1D\n");
		fclose(file);
	}

	//-------------- 2D -----------------------------------
	if (dimension == 0 || dimension == 2) {
		FILE *file1 = fopen("random-walk-2D.csv", "w");

		// Note the parameters of the run
		fprintf(file1, "Number of iter: %d\n", num);
		fprintf(file1, "Length of border: %d\n", border);
		fprintf(file1, "Dimension: %d\n", dimension);

		// Random walk, 2D, still using border for radius
		// Run num times
		for (int i = 0; i < num; i++) {
			// Even probability of travelling in any direction
			int result = randomWalk_2D(border, timeout);
			printf("Finished iteration %d\n", i);
			fprintf(file1, "%d ", result);
		}
		fclose(file1);
	}


	//-------------- 3D -----------------------------------
	if (dimension == 0 || dimension == 3) {
		FILE *file2 = fopen("random-walk-3D.csv", "w");
		
		// Note the parameters of the run
		fprintf(file2, "Number of iter: %d\n", num);
		fprintf(file2, "Length of border: %d\n", border);
		fprintf(file2, "Dimension: %d\n", dimension);

		// Random walk, 3D, still using border for radius
		// Run num times
		for (int i = 0; i < num; i++) {
			// Even probability of travelling in any direction
			int result = randomWalk_3D(border, timeout);
			printf("Finished iteration %d\n", i);
			fprintf(file2, "%d ", result);
		}
		fclose(file2);
	}
}	
