
#include "magnet.h"

/* Esta función devuelve la magnetización de la red. */

int magnet(int **red, int n)
		{
		int a = 0;
		for(int i = 0; i < n; ++i)
			 {
			 for(int j = 0; j < n; ++j)
			 	  {
			 	  a += red[i][j];
			 	  }
			 } 
		return a;
		}

