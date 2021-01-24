typedef struct
{
	int dd;int mm;int yyyy;

}date;

struct employee{
	char name[20];
	char passwd[20];
	float age;
	float exp;
	float cl; //available to use for the year only
	float ml; //available to use for the year only
	float el; //
};

int isleap(int year);

int isValidDate(date *validDate);

int datedifference(date *d1, date *d2);

int check(struct employee e[],char a[], char *pa, int j);

void apply(struct employee *e,date *d1,date *d2);

void disp(struct employee *e);

void menu(struct employee *e,date *d1,date *d2);
