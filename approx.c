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

void sort(arc * ar, int l, int h){
  int i, j
  arc wsp, m;
  
 i=l; 
 j=h;
 m=ar[(int)(double_rand(1)*(h-l)+l)]; 

     do
      while (ar[i].cout < m.cout) i++;    
      while (ar[j].cout > m.cout) j--;    
        if (i<=j){
          wsp=ar[i];
	  ar[i]=ar[j];
	  ar[j]=wsp;
          i++;
	  j--;
	}
     while (i <= j);
     
      if (i<h)
	sort(ar, i, h);
      if (l<j)
	sort(ar, l, j);
  
}
 
void qsort(arc* ar, int n){
 srand (time(NULL));
 sort(ar, 0, n-1);
}


