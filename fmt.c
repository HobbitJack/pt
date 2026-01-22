#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fmt.h"

unsigned int
sigs(char *num)
{
	int i, len, trail, sig;
	
	len = strlen(num);
	
	sig = -1;
	trail = 0;

	for (i=0; i<len; i++)
	{
		if (num[i] == '.')
			sig = 0;

		if (sig >= 0 && isdigit(num[i]))
		{
			if (num[i] == '0')
			{
				trail++;
			}
			else
			{
				if (trail)
				{
					sig += trail;
					trail = 0;
				}
				sig++;
			}
		}
	}

	return (unsigned int)sig;
}


unsigned int
fmtsigf(float num)
{
	unsigned int len, sig;
	char *buf;

	len = 12;
	buf = malloc((len+1) * sizeof(char));

	if ((len = snprintf(buf, len, "%.5f", num)) > strlen(buf))
	{
		free(buf);
		buf = malloc((len+1) * sizeof(char));
		snprintf(buf, len, "%.5f", num);
	}

	sig = sigs(buf);
	return sig > 5 ? 5 : sig;
}
