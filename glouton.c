#include "glouton.h"
#include <float.h>
#include <stdio.h>


/*on retourne le cout total et on remplie le tableau res qui décrit l'ordre de parcoiurs*/

double glouton (double ** G, int * res, int n){
  
  double c = 0; //cout de tour hamiltonien

  int s = 0; //sommet par lequel on commence

  int p; //sommet prochain à explorer - le resultat

  double min;

  for(int i=0; i<n-1; i++){ //compteur pour trouver un cycle
    
    min =  DBL_MAX;
    for(int j=0; j<n; j++){
      if(s!=j && min>G[s][j] && res[j] == -1) {
	min = G[s][j];
	p = j;
      }
    }
    
    //printf("min %0.2f \n", min);
    c += min;
    res[s] = p;
    s = p;
    

 }

  res[p] = 0;
  c+= G[0][p];

  return c;

}
