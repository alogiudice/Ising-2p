
#include "energia.h"
#include "definitions.h"

/* Estas funciones devuelven la energía de la red, según la cantidad de vecinos que
considere (energia1 ó energia2). Recibe el campo magnético aplicado al sistema.
La constante de intercambio está definida en "definitions.h"
Se tiene en cuenta el hamiltoniano dado por:

H = sum(-J1 * (s_i s_j)) + sum(-J2 * (s_i * s_j)) - B*sum(s_i)
La suma sobre J1 se hace sobre los primeros vecinos del spin en si, y la de 
J2, sobre sus segundos vecinos.

la función energia1 sólo tiene en cuenta a los 1eros vecinos; energia2, 
en cambio, tiene en cuenta al H en su totalidad.
Ambas tienen en cuenta cdc periódicas. En los extremos de la 
red, se encargan de recalcular los índices para satisfacerlas. */


float energia1(int **red, float magfield)
		{
		int a,b,c,d;
		int dum1, dum2, dum3, dum4, dum5, dum6;
		float energia = 0.0;
		float totspin = 0.0;
		
		/*
		Me armo un sistema de etiquetas dummy que servirán para representar a 
		los siguientes índices de la red:
		dum1 = i+1
		dum2 = i-1
		dum3 = j+1
		dum4 = j-1
		dum5 = i
		dum6 = j 
		*/

		for(int i = 0; i < N; ++i)
			 {
			 for(int j = 0; j < N; ++j)
			 		{
			 		/*Arreglo las etiquetas para forzar periodicidad. */
			 		switch(i)
			 					{
			 					case 0 :
			 					dum2 = N-1;
			 					dum1 = 1;
			 					dum5 = 0;
			 					break;
			 					
			 					case N-1 :
			 					dum1 = 0;
			 					dum2 = N-2;
			 					dum5 = N-1;
			 					break;
			 					
			 					default : 
			 					dum1 = i+1;
			 					dum2 = i-1;
			 					dum5 = i;
			 					}
			 		
			 		switch(j)
			 					{
			 					case 0 :
			 					dum3 = 1;
			 					dum4 = N-1;
			 					dum6 = 0;
			 					break;
			 					
			 					case N-1 :
			 					dum3 = 0;
			 					dum4 = N-2;
			 					dum6 = N-1;
			 					break;
			 					
			 					default : 
			 					dum3 = j+1;
			 					dum4 = j-1;
			 					dum6 = j;
			 					}
					 
					a = red[dum2][dum6];
					b = red[dum1][dum6];
					c = red[dum5][dum3];
					d = red[dum5][dum4];
			 					
			 		energia += red[i][j] * (a + b + c + d);
			 		totspin += red[i][j];
			 		}
			 }
		
		energia =  - ( (float) J1 * energia) - (magfield * totspin);
	
		return energia;
		}

/* Esta es la función que tiene en cuenta los segundos vecinos. Es casi 
idéntica a la anterior. */

float energia2(int **red, float magfield)
		{
		int dum1, dum2, dum3, dum4, dum5, dum6;
		int a, b, c, d, f, g, h, k;
		float energia1 = 0.0;
		float energia2 = 0.0;
		float energia = 0.0;
		float totspin = 0.0;
		
		for(int i = 0; i < N; ++i)
			 {
			 for(int j = 0; j < N; ++j)
			 		{
			 		/*Arreglo los índices para forzar periodicidad. */
			 		switch(i)
			 					{
			 					case 0 :
			 					dum2 = N-1;
			 					dum1 = 1;
			 					dum5 = 0;
			 					break;
			 					
			 					case N-1 :
			 					dum1 = 0;
			 					dum2 = N-2;
			 					dum5 = N-1;
			 					break;
			 					
			 					default : 
			 					dum1 = i+1;
			 					dum2 = i-1;
			 					dum5 = i;
			 					}
			 		
			 		switch(j)
			 					{
			 					case 0 :
			 					dum3 = 1;
			 					dum4 = N-1;
			 					dum6 = 0;
			 					break;
			 					
			 					case N-1 :
			 					dum3 = 0;
			 					dum4 = N-2;
			 					dum6 = N-1;
			 					break;
			 					
			 					default : 
			 					dum3 = j+1;
			 					dum4 = j-1;
			 					dum6 = j;
			 					}
					 
					a = red[dum2][dum6];
					b = red[dum1][dum6];
					c = red[dum5][dum3];
					d = red[dum5][dum4];
					
					f = red[dum2][dum3];
					g = red[dum1][dum3];
					h = red[dum1][dum4];
					k = red[dum2][dum4];
					
			 		energia1 += red[i][j] * (a + b + c + d);
			 		energia2 += red[i][j] * (f + g + h + k);
			 		
			 		totspin += red[i][j];
			 		}
			 }
		
		energia =  - ( (float) J1 * energia1) - ( (float) J2 * energia2) - (magfield * totspin);
	
		return energia;
		}

