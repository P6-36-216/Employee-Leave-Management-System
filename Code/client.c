
#include<stdio.h>
#include"server.h"
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<stdio.h>
#include<time.h>
#define max_yr 9999
#define min_yr 1900


int main()
{
	char un[20];
	int i=0;int flag = 0;
	int temp; // i for iteration ; temp is the temporary variable
	struct employee e[30];
	char nam[20]; 
	char *password;
	FILE *fp; date d1,d2;
	time_t t;
	time(&t);
	fp=fopen("emp.txt","r");
	while(fscanf(fp,"%s %s %f %f %f %f %f\n",e[i].name,e[i].passwd,&e[i].age,&e[i].exp,&e[i].cl,&e[i].ml,&e[i].el)!=EOF)
  	{
		i++;
	}
	fclose(fp);
	printf("\t\t\t******EMPLOYEE LEAVE MANAGEMENT SYSTEM*******\n");
	printf("\t\tCurrent date and time is : %s",ctime(&t));
	here:
	{	
		//Login as an employee
		printf("Enter employee name : \n");
		scanf("%s",nam);
		password = getpass("Enter password : \n"); //Input taken but not displayed for security reasons
		int x=check(e,nam,password,i);
		if (x != -1)
		{
			printf("\t\t LOGIN SUCCESSFULL! \n\n");
			menu(&e[x],&d1,&d2);
		}
		else 
		{
			//Input validation
			printf("Invalid username or password \n \n");
			try:
			{
				printf(" Press 1.Try again 2.Exit \n ");
				scanf("%d",&temp);
				switch(temp)
				{
					case 1:
					{
						goto here;
					}
					case 2:
					{
						break;			
					}
					default:
					{
						printf("Choose option 1 or 2 \n");
						goto try;	
					}
				}	
			}	
		}
	}
	return 0;
}
