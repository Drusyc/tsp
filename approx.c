#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#include "approx.h"
#include "generateur_connexe.h" 
#include "FloydWarshall.h"


double **couts;

//const int n = 4;
/*
double couts[5][5] = 	{{0, 1, 2, 2, 5}, 
			 {1, 0, 1, 2, 2}, 
			 {2, 1, 0, 9, 2}, 
			 {2, 2, 9, 0, 5}, 
			 {5, 2, 2, 5, 0}};
double couts[5][5] = 	{{0, 1, 4, 5, 1}, 
			 {1, 0, 1, 5, 4}, 
			 {4, 1, 0, 2, 8}, 
			 {5, 5, 2, 0, 1}, 
			 {1, 4, 8, 1, 0}};
*/

/*
double couts[4][4] = 	{{0, 1, 2, 5},
			 {1, 0, 1, 2}, 
			 {2, 1, 0, 3}, 
			 {5, 2, 3, 0}};
*/

int * node_seen;
int ak; /* indice pour tableau aretes */
int nseen_i; /* indice pour tableau node_seen */

/*
 * Algo de sort pour le QuickSort
 */

void sort(struct arc * ar, int l, int h){
        int i, j;
        struct arc wsp, m;

        i=l; 
        j=h;
        m=ar[(int)(double_rand(1)*(h-l)+l)]; 

        do
        {
                while (ar[i].cout < m.cout) i++;     
                while (ar[j].cout > m.cout) j--;     
		if (i<=j){
			wsp=ar[i];
			ar[i]=ar[j];
			ar[j]=wsp;
			i++;
			j--;
		}//fi
        } while (i <= j);

        if (i<h) sort(ar, i, h);
        if (l<j) sort(ar, l, j);
}//sort
 
/*
 * Algo d'initialisation pour le Qsort
 */
void my_qsort(struct arc* ar, int n){
        srand (time(NULL));
        sort(ar, 0, n-1);
}//qsort

/* 
 * Affiche un tableau en 2D de taille nxn
 */
void printf_tab(double ** m, int n){
        printf("\n\n");
        for(int i = 0;i < n;i++){ 
                for(int j = 0;j < n;j++)
                        printf("[%0.3f] \t ", m[i][j]);
                printf("\n");
        }//for
        printf("\n\n");
}//printf_tab


/*
 * Affiche un tableau d'arc de taille size
 */
void printf_tab_arc (struct arc* aretes, uint32_t size) {
        for (uint32_t i = 0; i < size; i++) {
                printf("aretes[%i] : %i->%i : %f\n",i,aretes[i].p1,
                                                      aretes[i].p2,
                                                      aretes[i].cout);
        }//for i

}//printf_tab_arc()

/*
 * Algo de création d'un tableau d'arc selon la matrice de coût du graphe complet 
 * Crée un tableau d'arc et met les arcs les uns après les autres 
 */
void create_tab_arc (struct arc* aretes, int n) {
        struct arc * to_add = malloc(sizeof(struct arc));
        uint32_t k = 0;
        for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                        if (couts[i][j] != 0) {
                                to_add->cout = couts[i][j];
                                to_add->p1 = i;
                                to_add->p2 = j;
                                aretes[k++] = *to_add;
                        }//fi
                }//for j
        }//for i
        free(to_add);
}//create_tab_arc()

/*
 * Renvoie true sur l'élément "a" est présent dans le tableau tab de taille size
 */
bool approx_is_seen (int * tab, int a, int size) {
        
        for (int i = 0; i < size; i++) {
             if (tab[i] == a) {
                return true;
             }//fi
        }//for
        return false;
}//

/*
 * Renvoie true si tous les éléments [0..n-1] sont dans le tableau node_seen
 */
bool approx_all_seen (int n) {
        bool seen;
        for (uint8_t i = 0; i < n; i++) {
                seen = false;
                seen = approx_is_seen(node_seen,i, n);
                if (seen == false) {
                        return false;
                }//fi
        }//for()
        return true;
}//all_seen()

/*
 * Algo de calcul de l'arbre couvrant de poid minimum selon un tableau d'arc trié
 * Le tableau finale sera l'argument aretes de taille size_arc
 */

void set_abr_pmin (struct arc * aretes, unsigned size_arc,  double ** mat, int n) {

        for (int i = 0; i < n; i++) {
                node_seen[i] = -1;
        }//for

        bool is_p1, is_p2;
        int k = 0;
	
	unsigned i=0;

        while(i<size_arc && k!=n){
	        // printf("**%d\n", k);
                is_p1 = approx_is_seen(node_seen,aretes[i].p1,n);
                is_p2 = approx_is_seen(node_seen,aretes[i].p2,n);
                if ((!is_p1 || !is_p2) &&(!(!is_p1 && !is_p2) || k==0)) {
                        if (!is_p1) {
                                node_seen[k++] = aretes[i].p1;
                        }//fi
                        if (!is_p2) {
                                node_seen[k++] = aretes[i].p2;
                        }//fi

                        /* 2 pour simuler le doublement des arêtes
                         * nécessaire pour la suite de l'algo*/
                        mat[aretes[i].p1][aretes[i].p2] = 2;
                        mat[aretes[i].p2][aretes[i].p1] = 2;
			i=0;    
                }//fi
        	i++;	
        }//for
}//set_abr_pmin()

/*
 * Algo récursif pour calculer un tour eulérien d'un arbre couvrant minimum 
 * où tous les arcs ont été doublés
 */
void recur_find_eul (double ** mat, struct arc * arc, int n, int node) {

        for (int i = 0; i < n; i++) {         
                
                if (mat[node][i] != 0 && !approx_is_seen(node_seen,i,n)) {
                        //printf("for :%i -> %i\n", node, i);

                        arc[ak].p1 = node;
                        arc[ak].p2 = i;
                        arc[ak].cout = couts[node][i];
                        ak++;
                        
                        node_seen[nseen_i++] = i;

                        mat[node][i]--;
                        mat[i][node]--;
                        
                        recur_find_eul(mat,arc,n,i);
                }//fi
        }//for

        if (node == 0) 
                return;

        int i = 0;
        while (i<n && mat[node][i] == 0 ) i++;
                
        if(i == 0 && mat[node][i] != 0 && approx_all_seen(n)) {
                //printf("while: %i -> %i\n", node, i);
                arc[ak].p1 = node;
                arc[ak].p2 = i;
                arc[ak].cout = couts[node][i];
                return;
        }//fi

        if (i<n) {
                //printf("while: %i -> %i\n", node, i);
                arc[ak].p1 = node;
                arc[ak].p2 = i;
                arc[ak].cout = couts[node][i];
                ak++;

                mat[node][i]--;
                mat[i][node]--;
                
                recur_find_eul(mat,arc,n,i);
        }//i


        return;
}//recur_find_eul()

/*
 * Algo de création du chemin hamiltonien à partir du chemin eulérien précédement crée
 * Renvoie la solution hamiltonienne dans res et le coût associé dans res_cout
 *
 */
void crea_hamil (struct arc * arc, uint32_t size_arc,  int * res, double * res_cout, int n) {

        ak = 0;
        nseen_i = 1;
        uint32_t i = 0;
        while (i < size_arc) {

                if (!approx_is_seen(node_seen,arc[i].p2,n)) {
                        //printf("for: -> %i\n", i);
                        res[ak++] = arc[i].p2;
                        node_seen[nseen_i] = arc[i].p2;

			//printf("**for: %i->%i\n", node_seen[nseen_i -1], node_seen[nseen_i]);
			//printf("**cout: %f\n", couts[node_seen[nseen_i -1]][node_seen[nseen_i]]);
			(*res_cout) += couts[node_seen[nseen_i - 1]][node_seen[nseen_i]];
			nseen_i++;
                        
                } else if (i >= (size_arc - 1)) {
                        res[ak] = 0;
                        return;                        
                } else {
                        while(i < size_arc && approx_is_seen(node_seen,arc[i].p2,n)) i++;
                        if (i >= (size_arc)) {
                                res[ak] = 0;
                                return; 
                        }//fi
                        //printf("while: -> %i\n", i);

	
                        res[ak++] = arc[i].p2;
                        node_seen[nseen_i] = arc[i].p2;
			
			(*res_cout) += couts[node_seen[nseen_i - 1]][node_seen[nseen_i]];
			nseen_i++;
                }//fi
                i++;
        }//while

        return;
}//crea_hamil()


/*
 * Fonction principale 
 *
 */

void algo_approx (double ** graph, int * res, double * res_cout, int n) {
        
        uint32_t nb_arc = n*(n-1);
        struct arc * aretes = malloc((nb_arc) * sizeof(struct arc));

	couts = graph;
	(*res_cout) = 0;

        create_tab_arc(aretes, n);
        //printf_tab_arc(aretes, nb_arc);

        my_qsort(aretes, nb_arc);

        double ** mat_mabr  = (double **)malloc( n * sizeof(double*));
        for(int i = 0;i < n;i++){
                mat_mabr[i] =  malloc( n * sizeof(double));
        }//for

        for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) {
                        mat_mabr[i][j] = 0;
                }//for
        }//for

        node_seen = malloc (n * sizeof(int));
        set_abr_pmin (aretes, nb_arc, mat_mabr, n);

        //printf_tab(mat_mabr,n);

        /***** INIT RECUR ******/

        for (int i = 0; i < n; i++) {
                node_seen[i] = -1;
        }//for()
        node_seen[0] = 0;



        nb_arc = 2*(n-1);
        aretes = realloc(aretes,nb_arc * sizeof(struct arc));
        ak = 0; //indice pour aretes..
        nseen_i = 1; //indice pour node_seen..

        recur_find_eul(mat_mabr, aretes, n, 0);

        //printf_tab_arc(aretes, nb_arc);



        /**** CREATION HAMILTONIEN *****/

        
        for (int i = 0; i < n; i++) {
                res[i] = -1;
                node_seen[i] = -1;
        }//for()
        res[0]=0;
        node_seen[0] = 0;

        crea_hamil (aretes, nb_arc, res, res_cout, n);

	(*res_cout) += couts[node_seen[n - 1]][0];
        //printf("\n\n");
	/*
        for(int i = 0; i < (n-1); i++) {
                printf("%i->",res[i]);
        }//for()
        printf("0\n");
	*/

        /************ FREE ************/
        for(int i = 0;i < n;i++){
                free(mat_mabr[i]);
        }//for

        free(aretes);
        free(mat_mabr);
        free(node_seen);
        return ;
}//for
