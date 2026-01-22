#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <errno.h>
#include <getopt.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "pt.g.h"
#include "pt.l.h"

#include "elements.h"
#include "pt.h"
#include "table.h"

struct data_t
parse_data_options()
{
	struct data_t data;

	
	data.symbol = args.symbol_given || args.all_given;
	if (data.symbol && !data.first)
		data.first = 1;
	data.number = args.number_given || args.all_given;
	if (data.number && !data.first)
		data.first = 2;
	data.name = args.name_given || args.all_given;
	if (data.name && !data.first)
		data.first = 3;
	data.mass = args.mass_given || args.all_given;
	if (data.mass && !data.first)
		data.first = 4;
	data.density = args.density_given || args.all_given;
	if (data.density && !data.first)
		data.first = 5;
	data.type = args.type_given || args.all_given;
	if (data.type && !data.first)
		data.first = 6;
	data.phase = args.phase_given || args.all_given;
	if (data.phase && !data.first)
		data.first = 7;
	data.melting = args.melting_point_given || args.all_given;
	if (data.melting && !data.first)
		data.first = 8;
	data.boiling = args.boiling_point_given || args.all_given;
	if (data.boiling && !data.first)
		data.first = 9;
	data.ionization = args.ionization_given || args.all_given;
	if (data.ionization && !data.first)
		data.first = 10;
	data.electronegativity = args.electronegativity_given || args.all_given;
	if (data.electronegativity && !data.first)
		data.first = 11;
	data.electron_configuration = args.electron_configuration_given || args.all_given;
	if (data.electron_configuration && !data.first)
		data.first = 12;

	if (!(data.symbol || data.number || data.name || data.mass || data.density || data.type || data.phase || data.melting || data.boiling || data.ionization || data.electronegativity || data.electron_configuration))
	{
		data.first = 1;
		data.symbol = 1;
		data.number = 1;
		data.mass = 1;
	}
		
	return data;
}

int
parse_element(int token, char *text)
{
	int len;
	long element;
	char *endptr;

	switch (token)
	{
		case 0:
			errno = 0;
			element = strtol(text, &endptr, 10);
			if ((*endptr != '\0' || errno) || ((element < 1) || (element > ELEMENTS)))
			{
				if (!args.silent_given)
					fprintf(stderr, "%s: %s: Bad argument\n", progname, text);	
				element = -1;
			}
			break;
		case 1:
			for (element=0; element < ELEMENTS; element++)
			{
				if (!strcasecmp(elements[element].symbol, text))
					break;
			}
			if (element == ELEMENTS)
			{
				if (!args.silent_given)
					fprintf(stderr, "%s: %s: Bad argument\n", progname, text);
			}
			break;
		case 2:
			for (element=0; element < ELEMENTS; element++)
			{
				if (!strcasecmp(elements[element].name, text))
					break;
			}
			if (element == ELEMENTS)
			{
				if (!args.silent_given)
					fprintf(stderr, "%s: %s: Bad argument\n", progname, text);
			}
			break;
	}
	return (int) element == ELEMENTS ? -1 : element;
}

void
read_stdin(struct data_t data)
{
	int element, t;
	     
	while ((t = yylex()) != -1)
	{
		if ((element = parse_element(t, yytext)) >= 0)
			print_element(element, data);
		else
			status = 1;
	}

	return;
}

void
read_args(int argc, char *argv[], struct data_t data)
{
	int element, i, j, t;

	for (i=0; i<argc; i++)
	{
		t = 0;
		for (j=0; j<strlen(argv[i]); j++)
		{
			if (!isdigit(argv[i][j]))
			{
				t = 1;
				break;
			}
		}
		if (t)
			t = strlen(argv[i])>2 ? 2 : 1;
		if ((element = parse_element(t, argv[i])) >= 0)
			print_element(element, data);
		else
			status = 1;
	}
	return;
}

int
main(int argc, char *argv[])
{
	struct data_t data;

	progname = basename(argv[0]);

	if (ggo(argc, argv, &args))
		return 1;

	if (args.help_given)
	{
		ggo_print_help();
		return 0;
	}
	if (args.version_given)
	{
		ggo_print_version();
		return 0;
	}

	if (!args.inputs_num)
	{
		print_table();
	}
	else
	{
		data = parse_data_options();
		if (!args.no_header_given)
			print_header(data);
		if (!strcmp(args.inputs[0], "-"))
			read_stdin(data);
		else
			read_args(args.inputs_num, args.inputs, data);
	}

	return args.loose_exit_status_given ? 0 : status;
}
