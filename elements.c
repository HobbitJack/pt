#define _POSIX_C_SOURCE 200809L

#include <stdio.h>

#include "elements.h"
#include "fmt.h"
#include "pt.h"

void
print_header(struct data_t data)
{
	if (data.symbol)
		printf("Symbol");

	if (data.number)
	{
		if (data.first != 2)
			putchar('\t');
		printf("Number");
	}

	if (data.name)
	{
		if (data.first != 3)
			putchar('\t');
		printf("Name");
	}

	if (data.mass)
	{
		if (data.first != 4)
			putchar('\t');
		printf("Mass");
	}

	if (data.density)
	{
		if (data.first != 5)
			putchar('\t');
		printf("Density");
	}

	if (data.type)
	{
		if (data.first != 6)
			putchar('\t');
		printf("Type");
	}

	if (data.phase)
	{
		if (data.first != 7)
			putchar('\t');
		printf("Phase");
	}

	if (data.melting)
	{
		if (data.first != 8)
			putchar('\t');
		printf("Melting Point");
	}

	if (data.boiling)
	{
		if (data.first != 9)
			putchar('\t');
		printf("Boiling Point");
	}

	if (data.ionization)
	{
		if (data.first != 10)
			putchar('\t');
		printf("First Ionization Energy");
	}

	if (data.electronegativity)
	{
		if (data.first != 11)
			putchar('\t');
		printf("Electronegativity");
	}

	if (data.electron_configuration)
	{
		if (data.first != 12)
			putchar('\t');
		printf("Electron Configuration");
	}
	putchar('\n');
	return;
}

void
print_element(int element, struct data_t data)
{
	int sig;

	if (data.symbol)
		printf("%s", elements[element].symbol);

	if (data.number)
	{
		if (data.first != 2)
			putchar('\t');
		printf("%d", elements[element].number);
	}

	if (data.name)
	{
		if (data.first != 3)
			putchar('\t');
		printf("%s", elements[element].name);
	}

	if (data.mass)
	{
		if (data.first != 4)
			putchar('\t');

		sig = fmtsigf(elements[element].mass);
		if (sig)
			printf("%.*f", sig, elements[element].mass);
		else
			printf("(%.0f)", sig, elements[element].mass);
			
	}

	if (data.density)
	{
		if (data.first != 5)
			putchar('\t');
		if (elements[element].density == -1)
			printf("N/A");
		else
			printf("%.*fkg/m^3", fmtsigf(elements[element].density), elements[element].density);
	}

	if (data.type)
	{
		if (data.first != 6)
			putchar('\t');
		printf("%s", elements[element].type);
	}

	if (data.phase)
	{
		if (data.first != 7)
			putchar('\t');
		printf("%s", elements[element].phase);
	}

	if (data.melting)
	{
		if (data.first != 8)
			putchar('\t');
		printf("%.*fK", fmtsigf(elements[element].melting), elements[element].melting);
	}

	if (data.boiling)
	{
		if (data.first != 9)
			putchar('\t');
		printf("%.*fK", fmtsigf(elements[element].boiling), elements[element].boiling);
	}

	if (data.ionization)
	{
		if (data.first != 10)
			putchar('\t');
		printf("%.*fkJ/mol", fmtsigf(elements[element].ionization), elements[element].ionization);
	}

	if (data.electronegativity)
	{
		if (data.first != 11)
			putchar('\t');
		printf("%.*f", fmtsigf(elements[element].electronegativity), elements[element].electronegativity);
	}

	if (data.electron_configuration)
	{
		if (data.first != 12)
			putchar('\t');
		printf("%s", elements[element].electron_configuration);
	}

	putchar('\n');
	return;
}
