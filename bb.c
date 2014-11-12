#include "bb.h"


/*vérifie si l'ensemble V\S est vide ou pas*/
/*
int sub_vide (int * sub, int n)
{
  int res = 0;
  int i=0;

  while(i<n && !res){
    res|=sub[i];
    i++;
      }
  return !res;
  }*/


/*Algorithme de Prim pour trouver le poids de l'arbre min couvrant V\S*/
/*
sub - l'ensemble de sommets (si sub[i] = 1 -> appartient à V\S)
n - taille de sub
G - matrice de couts
nbr - nombre de sommets de V\S
*/
double Prim(int* sub, int n, double** G, int nbr){


  /*int nbr = 0;
  for(int i=0; i<n; i++)
    
    if(sub[i]){
      nbr++;
      }*/

 
  int* nv = malloc(n*sizeof(int)); /*le tableau pour indiquer les sommets non visités*/
  double* cout_min = malloc(n*sizeof(double));/* le cout min pour aller de chaque sommet non-visité à un des sommets visités*/

  /*initialistaion*/
  for(int i=0; i<n;i++){
    nv[i]=1;
    cout_min[i] = DBL_MAX;
  }

  int i=0;
  double res=0;

  /*on cherche le premier sommet dans V\S*/
  while(sub[i]==0)
    i++;

 
  nv[i]=0;
  int prec = i; /*le dernier sommet visité*/
  double min;
  int ind_min;
  nbr--;

  while(nbr!=0){ /*jusqu'à on n'a pas de sommets non-visités*/
    min =  DBL_MAX; /*la distance min*/
    ind_min = -1;/*son indice, le sommet qui va passer en visité*/
 
    for (int j=0; j<n; j++){ /*parcours de tous les sommets*/
      if(nv[j] && sub[j]){ /*si non-visité et dans V\S*/
	cout_min[j] = fmin(cout_min[j],G[prec][j]);/*on met à jour le cout min comme il y a le sommet prec qui est passé en visité*/
	
	if(min>cout_min[j]){
	ind_min = j;/*sommet qui va passer en visité*/
	min = cout_min[j];
	}

      }
    }

    prec = ind_min;
    res += min;/*la mise à jour de résultat*/
    nv[prec] = 0;/*le sommet ind_min est non plus dans non-visité*/
    nbr--;
  }

  free(nv);
  free(cout_min);
  return res;
}

/*Algo de branch & bound*/
/*
cout_tr - le cout min atteint pour le moment
cout_cour - le cout de chemin qu'on est en train de construire
res - le chemin qu'on construit
res_final - le résultat optimal pour le moment
sub - V\S
n - taille de graphe
G - matrice des couts
last - b de l'énoncé
nbr - nombre de sommets dans V\S
*/
void rec (double* cout_tr, double cout_cour, int* res, int* res_final, int* sub, int n, double ** G, int last, int nbr){

  //if(sub_vide(sub,n)){
  if(!nbr){
    /*on a trouvé la solution mais c'est le chemin donc on ajoute la dernière arrete*/
    cout_cour += G[last][0];
    
    /*si mieux par rapport ce qu'on a trouvé pour l'instant*/
    if(*cout_tr>cout_cour){
    /*ce tour remplace le tour trouvé précedemment*/
    *cout_tr = cout_cour;
    for(int i=0;i<n;i++)
      res_final[i] = res[i];

    res_final[last] = 0;
    }
  }
    else{
      
      double min_a = DBL_MAX; /*distance min de a à V\S*/
   

      for(int j=0; j<n; j++){
	if(min_a > G[0][j] && sub[j]){
	  min_a = G[0][j];
	}
      }
              
      double min_b = DBL_MAX; /*distance min de b à V\S*/
 
      for(int j=0; j<n; j++){
	if(min_b > G[last][j] && sub[j]){
	  min_b = G[last][j];
	}
      }

      double min_arbre_couvr = Prim(sub, n,  G, nbr);
      
      /*on construit le lower bound d'après l'énoncé*/
      double lb = min_arbre_couvr + min_a +min_b;
      
      if (lb<*cout_tr){ /*on va développer l'arbre si c'est possible d'améliorer la solution locale courante*/
	 for(int j=0; j<n; j++){
	   if(sub[j] != 0){/*pour tous les x dans V\S*/
	     res[last] = j;/*on rajoute x dans S*/
	     sub[j] = 0;
	     rec (cout_tr, cout_cour+G[last][j], res, res_final, sub, n, G, j, nbr-1);/*on relance la branche*/	     	     
	     sub[j] = 1;/*on remet à jour les valeurs*/
	     res[last] = -1;
	 
	   }
	 }
	 }

   
    }


}

/*l'initialisation pour la récurrence*/
double bb (double ** G, int * res, int n){

  int* sub = malloc (n*sizeof(int));
  int* res_loc = malloc (n*sizeof(int));
  
  for(int i=0; i<n; i++){
    sub [i] = 1;
    res_loc[i] = -1;
  }
  
sub[0]=0;
double cout_tr = DBL_MAX;

rec (&cout_tr, 0, res_loc, res, sub, n, G, 0,n-1);

free(sub);
free(res_loc);

return cout_tr;

}

