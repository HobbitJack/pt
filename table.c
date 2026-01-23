#define _POSIX_C_SOURCE 200809L

#include <stdio.h>

#include "pt.g.h"

#include "elements.h"
#include "fmt.h"
#include "pt.h"
#include "table.h"

int
print_period(int element, int period, int cutout, int header)
{
	int group;

	if (header)
		printf("%d ", period);
	
	for (group=1; group<=18; group++)
	{
		if (((period == 1) && (group == 1 || group == 18)) || ((period == 2 || period == 3) && (group <= 2 || group >= 13)) || (period > 3))
		{
			if (group == 3)
			{
				if (cutout)
					element += 14;
				printf(" %c%-2s", cutout ? 41+cutout : ' ', elements[element++].symbol);
			}
			else
			{
				if (!header && (group == 1))
					printf("%-2s", elements[element++].symbol);
				else
					printf("  %-2s", elements[element++].symbol);
			}
		}
		else
		{
			fputs("    ", stdout);
		}
	}
	putchar('\n');
	return element;
}

void
print_table(int header)
{
	int i, j;
	int group, element, period;

	if (header)
	{
		fputs("  ", stdout);
		for (group = 1; group<=18; group++)
			if (group) printf("  %-2d", group);
		putchar('\n');
	}

	element = 0;

	for (period=1; period<=7; period++)
	  element = print_period(element, period, period>=6 ? period-5 : 0, header);

	i = 56;
	j = 0;
	while (i<102)
	{
		if (header)
			fputs("    ", stdout);
		fputs("      ", stdout);
		for (element = i; element <= i+13; element++)
			printf(" %c%-2s", element==i ? '*'+(j++) : ' ', elements[element].symbol);
		putchar('\n');
		i += 32;
	}

	return;
}
