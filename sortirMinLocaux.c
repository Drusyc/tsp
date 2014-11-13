#include <stdio.h>
#include <stdlib.h>
#include "sortirMinLocaux.h"
#include <time.h>
#include <math.h>

int g(int it){
	return 1/it;
}

void transform1(int * m, int n){
  int* t = malloc(n*sizeof(int));
  for(int i = 0;i < n;i++) 
    t[i] = m[i];

  int j = 0;

  for(int i = 0;i < n;i++){
    m[i] = j;
    j = t[j];
  }
 
 
  free(t);
}

void sortirMinLocaux(double** G, int* res, double* cout, int n){

        transform1(res,n);
	int ameliore = 1;
	int temp = 0;
	srand(time(NULL));
	double p = (double)rand()/(double)(RAND_MAX/1.0);
	int it=0;
	while(ameliore){
		ameliore = 0;
		it++;
		//Cas i=0
		for(int j=2; j<(n-1); ++j){
			//On regarde s'il existe un plus court chemin
			if(G[res[0]][res[1]] + G[res[j]][res[j+1]] > G[res[0]][res[j]] + G[res[1]][res[j+1]]){
				//Echange 
				temp = res[1];
				res[1]=res[j];
				res[j]=temp;
				ameliore = 1;
			}else{
				//Recuit-simulé
				if (p<exp(-(G[res[0]][res[j]] + G[res[1]][res[j+1]] - G[res[0]][res[1]] - G[res[j]][res[j+1]])/g(it))){
					//Echange
					temp = res[1];
					res[1]=res[j];
					res[j]=temp;
					ameliore = 1;
				}
			}
		}

		//Cas i=n-1
		for(int j=1; j<(n-2); ++j){
			if(G[res[n-1]][res[0]] + G[res[j]][res[j+1]] > G[res[n-1]][res[j]] + G[res[0]][res[j+1]]){
				//Echange
				temp = res[0];
				res[0]=res[j];
				res[j]=temp;
				ameliore = 1;
			}else{
				//Recuit-simulé
				if (p<exp(-(G[res[n-1]][res[j]] + G[res[0]][res[j+1]] - G[res[n-1]][res[0]] - G[res[j]][res[j+1]])/g(it))){
					//Echange
					temp = res[0];
					res[0]=res[j];
					res[j]=temp;
					ameliore = 1;
				}
			}
		}

		//Cas général
		for(int i=1; i<(n-1); ++i){
			for(int j=0; j<(n-1); ++j){
				//Conditions  de couplage
				if(j != i && j!=(i-1) && j!=(i+1)){
					//Sous cas j=n-1
					if(j==(n-1)){
						if(G[res[i]][res[i+1]] + G[res[n-1]][res[0]] > G[res[i]][res[n-1]] + G[res[i+1]][res[0]]){
							//Echange
							temp = res[i+1];
							res[i+1]=res[n-1];
							res[n-1]=temp;
							ameliore = 1;
						}else{
							//Recuit-simulé
							if (p<exp(-(G[res[i]][res[n-1]] + G[res[i+1]][res[0]] - G[res[i]][res[i+1]] - G[res[n-1]][res[0]])/g(it))){
								//Echange
								temp = res[i+1];
								res[i+1]=res[j];
								res[j]=temp;
								ameliore = 1;
							}
						}
					}
					if(G[res[i]][res[i+1]] + G[res[j]][res[j+1]] > G[res[i]][res[j]] + G[res[i+1]][res[j+1]]){
						//Echange
						temp = res[i+1];
						res[i+1]=res[j];
						res[j]=temp;
						ameliore = 1;
					}else{
						//Recuit-simulé
						if (p<exp(-(G[res[i]][res[j]] + G[res[i+1]][res[j+1]] - G[res[i]][res[i+1]] - G[res[j]][res[j+1]])/g(it))){
							//Echange
							temp = res[i+1];
							res[i+1]=res[j];
							res[j]=temp;
							ameliore = 1;
						}
					}
				}
			}
		}
	}

	//Calcul du nouveau coût
	cout[0] = 0.0;
	for(int k=0; k<(n-1); ++k){
		cout[0] = cout[0] + G[res[k]][res[k+1]];
	}
	//On "ferme" le cycle
	cout[0] = cout[0] + G[res[n-1]][res[0]];
}
