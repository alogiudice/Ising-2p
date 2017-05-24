/* Implementación del modelo de Ising mediante el algoritmo de Metrópolis
	 Montecarlo.
	 Hecho por A.Lo Giudice 
	 (agostina.logiudice@gmail.com)
	 
	 Compilar este programa usando el standard 	C99 y el linkeo manual con la
	 librería math de C:
	 
	 $ gcc -std=c99 -Wall -O2 -lm ising.c lattice.c energia.c metropolis.c 
	 montecarlo.c magnet.c
 
*/

/*
	 Se implementa el algoritmo de Metrópolis-Montecarlo para calcular la 
	 energía media y la magnetización de una red de spines aleatorios a 
	 diferentes temperaturas.
	 Estos resultados son devueltos en el archivo Resultados.DAT, junto 
	 con la temperatura correspondiente. En "definitions.h" se encuentran
	 definidos los macros tales como el tamaño de la red, la constante
	 de intercambio, el campo magnético aplicado, el número de promedios
	 a tomar, etc.
	  
*/


#include <stdlib.h>
#include <time.h>

#include "energia.h"
#include "lattice.h"
#include "definitions.h"
#include "metropolis.h"
#include "magnet.h"

  		 
int main(int argc, char **argv) 
		{
		srand(time(NULL));
		
		FILE *F = fopen("Resultados.DAT", "w");

		if(F == NULL)
			{
			printf("Error: %m\n");
			return (1); 
			}
			
		fprintf(F, "T U M\n");
		
		/* Inicializo la red, y otras variables a usar. */
		int n = N ;
  	int **red;
  	float u, m;
  	float magfield = B;
  	
  	/* Hago un calloc para la red y la lleno. */
  	
  	red = (int **)calloc(n, sizeof(int*)); 
		for(int i = 0; i < n; i++) 
   		 red[i] = (int *)calloc(n, sizeof(int));
   		 
   	fill_lattice(red, n);
   	
  	/* Acá arranca la corrida para distintos T. */
  	
		for(int t = 1; t < T_MAX; ++t)
			 {
			 double kt = (-1) / ((double)K * (double) t);
			 
			 /* Termalizo la red para que llegue al estado con esa T lo mejor 
			 posible. Se puede cambiar NUM_TERMAL en definitions.h. */
			 
  		 for(int termal = 0; termal < NUM_TERMAL ; ++termal)
  		 		{
  		 		metropolis(red, n, kt, magfield, 1);
  		 		}
  		 
  		 /* Y ahora, lo vuelvo a hacer. Tomamos PROMEDIOS * L **2 */
  		 
  		 u = 0.0;
  		 m = 0.0;
  		 
  		 for(int cont = 0; cont < PROMEDIOS; ++cont)
  		 		{
  		 		for(int pasadas = 0; pasadas < n*n ; ++pasadas)
  		 			 {
  		 			 metropolis(red, n, kt, magfield, 1);
  		 			 }
  		 		u += energia1(red, magfield);
  		 		m += magnet(red, n);
  		 		
  		 		}
  		 /* Normalizo por la cantidad de promedios tomados y el tamaño de la red. */
  		 
  		 u /= (float) PROMEDIOS * (n*n);
  		 m /= (float) PROMEDIOS * (n*n);
			 fprintf(F, "%d %f %f\n", t, u, m);

  		 }
  		 
	free(red);
	fclose(F);
  
  return 0;
}
