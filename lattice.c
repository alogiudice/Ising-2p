#include "lattice.h"


/* Esta función llena el array con 1 y -1 (los spines)
Toma como parámetros a la red en sí y a su tamaño (nxn) */
void fill_lattice(int **red, int n) 
		{	
		for(int i = 0; i < n; ++i)
			 {
	   	 for(int j = 0; j < n; ++j)
	   	   	{
	   	   	double a = ((double) rand() / (double) (RAND_MAX));
					if(a < 0.5)
						{
						red[i][j] = -1;
						}
					else red[i][j] = 1; 
	
	   	  	}
			 }
		}

/* Esta función printea el contenido de la red en pantalla. */
void print_lattice(int **red, int n)
	{
	printf("La red es: \n");
	for(int i = 0; i < n; ++i)
		{
		printf("\n");
		
	   for(int j = 0; j < n; ++j)
	    	{
	    	printf("%d ", red[i][j]);
	     	}
	   }	
		printf("\n");
	}
