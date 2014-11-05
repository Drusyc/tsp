#include <stdio.h>
#include <stdint.h>
#include "FloydWarshall.h"

int** FloydWarshall(int** G, int n){
	for (int k=0; k<n; k++){
		for (int i=0; i<n; i++){
			for (int j=0; j<n; j++){
                // On regarde s'il existe un plus court chemin
                // on élimine les cas i=j (diagonale)
				if (G[i][j] > G[i][k] + G[k][j] && i!=j){ 
					if(G[i][k] + G[k][j] > 0){
						G[i][j]=G[i][k] + G[k][j];
					}
				}
                // Pas d'arête existante entre i et j
				if (G[i][j] == -1){
                    // On vérifie qu'il existe un chemin
                    // positif entre i et j par k
					if(G[i][k] + G[k][j] > 0){
						G[i][j]=G[i][k] + G[k][j];
					}
				}
			}
		}
	}
	return G;
}
