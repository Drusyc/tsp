#include "generateur_connexe.h"


double double_rand(int bornes)
{
  double res =  ((double)rand()/(double)(RAND_MAX));
  if(!bornes){
    while(res==0 || res == 1)
	res = ((double)rand()/(double)(RAND_MAX));
    }

  return res;
}

void affiche_connect(connect* m, int n)
{
for(int i = 0;i < n;i++)
{
   printf("%d %d %d ", i, m[i].comp, m[i].next);
    printf("\n");
}

}

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

connect* tab = (connect*) malloc(n*sizeof(connect));

while (cmp!=1){

	//printf ("p = %f\n\n",p);

 for(int i = 0;i < n;i++)
   for(int j = 0;j < 2;j++)
      points[i][j] = double_rand(1);




for(int i=0; i<n; i++)
{
    tab[i].comp = i;
    tab[i].next = i;
}

cmp=n;

for(int i = 0;i < n;i++){

   for(int j = i+1;j < n;j++){
     double p2 = double_rand(0);

     if(cmp>1 && p2<p)
        calcul_connect(tab, i, j, &cmp);

     couts[i][j] = (p2<p)?sqrt(pow(points[j][2]-points[i][2],2)+pow(points[j][1]-points[i][1],2)):(-1);
     couts[j][i] = couts[i][j];
     }
     couts[i][i] = 0;
}

//printf("nombre de composants %d\n\n",cmp);

	}

//affiche_connect(tab,n);

}
