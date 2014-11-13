#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "generateur_connexe.h" 
#include "FloydWarshall.h"

/*
double couts[5][5] = 	{{0, 1, 2, 2, 5}, 
			 {1, 0, 1, 2, 2}, 
			 {2, 1, 0, 9, 2}, 
			 {2, 2, 9, 0, 5}, 
			 {5, 2, 2, 5, 0}};

double couts[4][4] = 	{{0, 1, 2, 5}, 
			 {1, 0, 1, 2}, 
			 {2, 1, 0, 3}, 
			 {5, 2, 3, 0}};
	
*/



