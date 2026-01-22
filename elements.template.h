#define ELEMENTS 118

struct
data_t
{
	unsigned char first;
	
	unsigned char symbol;
	unsigned char number;
	unsigned char name;
	unsigned char mass;
	unsigned char density;
	unsigned char type;
	unsigned char phase;
	unsigned char melting;
	unsigned char boiling;
	unsigned char ionization;
	unsigned char electronegativity;
	unsigned char electron_configuration;
};

struct
element_t
{
  	char *symbol;
	unsigned char number;
	char *name;
	float mass;
	float density;
	char *type;
	char *phase;
	float melting;
	float boiling;
	float ionization;
	float electronegativity;
	char *electron_configuration;
};

void print_header(struct data_t data);
void print_element(int element, struct data_t data);

/* Intentionally last, because generated. */
static struct element_t elements[ELEMENTS] =
