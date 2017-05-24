#include "metropolis.h"

/* Metrópolis debería hacerse más de L**2 veces en la red. 
Ojo que 1_kt es NEGATIVO!! Sino explota todo. */

/* Esta función implementa el algoritmo propiamente dicho de 
Metrópolis - Montecarlo. Toma como parámetros a la red, el tamaño
nxn de la red, a kt, al campo magnético (magfield) y al número
de vecinos que se están teniendo en cuenta (num_vec), que por
ahora sólo pueden ser 1 o 2. */

void metropolis(int **red, int n, double kt, float magfield, int num_vec) 
		{
		/* Elijo dos índices aleatorios de la red */
		int a = rand() % n;
		int b = rand() % n;
		
		double probab;
		double rand_compare;
		
		/* Programa a ejecutarse en el caso de sólo primeros vecinos. */
		if(num_vec == 1)
		{
		 float en_pas = energia1(red, magfield);
		/* Flippeo el spin, y recalculo la energía de la red */
		 red[a][b] = -red[a][b];
		 float en_nueva = energia1(red, magfield);
		
		/* Evalúo el cambio de spin en la red. */
		
		 if(en_nueva > en_pas)
			 {
			 /*Le pido que evalúe la exponencial y la compare con un número 
			 aleatorio. */
			 double delta_e = en_nueva - en_pas;
			 probab = exp(kt * delta_e );
			 rand_compare = (double)rand() / (double)RAND_MAX;
			 /* Al spin le falta la prueba del traje de baño. */
			 /* Si no la pasa, volvemos al estado anterior. */
			 if(probab < rand_compare)
				 {
				 red[a][b] = -red[a][b]; 
				 /* printf("No se cumplió la condición\n"); */
				 }
				 /* else printf("Se cumplió la condición, con %e \n", kt); */
			 }
		}
		
		/* A continuación, los pasos a seguir si tengo en cuenta segundos 
		vecinos son casi iguales. Sólo cambio la función energia1 por energia2. */
		else if(num_vec == 2)
			{
		 	float en_pas = energia2(red, magfield);
		 
			/* Flippeo el spin, y recalculo la energía de la red */
		
		 	red[a][b] = -red[a][b];
		 	float en_nueva = energia2(red, magfield);
		
			/* Evalúo el cambio de spin en la red. */
		
		 	if(en_nueva > en_pas)
			 	{
				/*Le pido que evalúe la exponencial y la compare con un número aleatorio. */
			 	double delta_e = en_nueva - en_pas;
			 	probab = exp(kt * delta_e );
			 	rand_compare = (double)rand() / (double)RAND_MAX;
				/* Al spin le falta la prueba del traje de baño. */
				/* Si no la pasa, volvemos al estado anterior. */
			 	if(probab < rand_compare)
				 	{
				 	red[a][b] = -red[a][b];
				 	}
			 	}
			}
			
		else printf("Error. El número de vecinos debe ser 1 ó 2!!\n");
		
		}
