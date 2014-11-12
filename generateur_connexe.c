#include "generateur_connexe.h"

/*génère un double dans l'interv ]0;1[ si bornes = false, [0;1] sinon*/
double double_rand(int bornes)
{
  double res =  ((double)rand()/(double)(RAND_MAX));
  if(!bornes){
    while(res==0 || res == 1)
	res = ((double)rand()/(double)(RAND_MAX));
    }

  return res;
}

/*affiche le tableau de structures: la composante du chaque sommet et son sommet suivant*/
void affiche_connect(connect* m, int n){
for(int i = 0;i < n;i++){
   printf("%d %d %d ", i, m[i].comp, m[i].next);
    printf("\n");
}

}

/*changer la composante pour ind+1 et sa suite en composante de ind*/
void changer_comp(connect* tab, int ind){
  int i = ind+1;
 
  while(tab[i].next!=ind+1){
    tab[i].comp = tab[ind].comp;
    i = tab[i].next;
  }
    tab[i].comp = tab[ind].comp;
}

/*pour mettre à jour le tableau des composantes*/
void calcul_connect(connect* tab, int i, int j, int* cmp)
{
if(tab[i].next==i && tab[j].next==j)
     {
         tab[i].next=j;
         tab[j].next=i;
         tab[j].comp=tab[i].comp;
         (*cmp)--;
     }

     else
        if(tab[i].next==i || tab[j].next==j)
        {
         int libre = (tab[i].next==i)? i:j;
         int lie = (tab[i].next==i)? j:i;

         int l = tab[lie].next;
         tab[lie].next=libre;
         tab[libre].next=l;
         tab[libre].comp=tab[lie].comp;
         (*cmp)--;
        }
        else
            if(tab[i].comp!=tab[j].comp)
            {
                int l = tab[i].next;
                tab[i].next=tab[j].next;
                tab[j].next=l;

                int p = j;
                while(tab[p].next!=j)
                {
                    tab[p].comp = tab[i].comp;
                    p=tab[p].next;
                }
                tab[p].comp = tab[i].comp;
                (*cmp)--;
            }

}

void graphe_connexe(double** couts, double** points, int n, double p)
{
    int cmp = n;
    
/*tableau utile pour calculer les composantes connexes du graphe*/
connect* tab = (connect*) malloc(n*sizeof(connect));


//printf ("p = %f\n\n",p);

/*génération des points*/
 for(int i = 0;i < n;i++)
   for(int j = 0;j < 2;j++)
      points[i][j] = double_rand(1);


 /* au début de parcours il n'y a pas d'aretes, donc n composantes*/
for(int i=0; i<n; i++)
{
    tab[i].comp = i;
    tab[i].next = i;
}

cmp=n;

for(int i = 0;i < n;i++){
   for(int j = i+1;j < n;j++){
     
     double p2 = double_rand(0); /*probabilité pour que le sommet appartient au graphe*/

     /*on remplit la matrice des couts et en meme temps on calcule la connectivité*/
     if(cmp>1 && p2<p) /*s'il y une arrete connectivité peut changer*/
        calcul_connect(tab, i, j, &cmp);

     couts[i][j] = (p2<p)?sqrt(pow(points[j][2]-points[i][2],2)+pow(points[j][1]-points[i][1],2)):(-1);/*si proba est plus petit on a cette arrete, sinon pas atteint -> -1 (une sorte d'infinité)*/
     couts[j][i] = couts[i][j];/*car graphe non-orienté*/
     }
     couts[i][i] = 0;
}


 int i = 0;

 /*si le graphe obtenu n'est pas connexe*/

 while(cmp!=1){
   while(i<n-1){ 
     if(tab[i].comp!=tab[i+1].comp){ /*si les composantes de 2 sommets voisins sont differentes, on les relie forcement*/
       changer_comp(tab, i);
       couts[i][i+1] = sqrt(pow(points[i+1][2]-points[i+1][2],2)+pow(points[i+1][1]-points[i][1],2));
       couts[i+1][i] = couts[i][i+1];
       cmp--;
       }
     i++;
   }
 }
	


 free(tab);
}
