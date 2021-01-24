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



int isleap(int year)
{
	//to check if the year is leap or not
	return (((year %4 == 0)&&(year %100!=0)) || (year %400 == 0));
}
int isValidDate(date *validDate)
{
	//Date, month, year validation with all cases
	if (validDate->yyyy > max_yr || validDate->yyyy < min_yr)
		return 0;
	if (validDate->mm <1 ||validDate->mm > 12)
		return 0;
	if (validDate->dd < 1 || validDate->dd > 31)
		return 0;
	if (validDate->mm ==2)
	{
		if(isleap(validDate->yyyy))
			return (validDate->dd <=29);
		else 
			return (validDate->dd <=28);
	}
	if (validDate->mm == 4 || validDate->mm ==6 || validDate->mm ==9 || validDate->mm == 11)
		return (validDate->dd <=30);
	return 1;
}



int datedifference(date *d1, date *d2)
{
	//Finding the number of days between the two given dates 
	int count = 1; 
	char startdate[20],enddate[20];

	date startDate = *d1, endDate = *d2; 
	while ( !(startDate.dd == endDate.dd && startDate.mm == endDate.mm && startDate.yyyy == endDate.yyyy))
	{
		switch(startDate.mm)
		{
			case 1:				//For months with 31 days excluding December
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			{
				count ++;
				if (startDate.dd == 31)
				{
					startDate.dd =1;
					startDate.mm++;
				}
				else
				{
					startDate.dd++;
				}
			}
			break;
			case 4:				//For months with 30 days 
			case 6:
			case 9:
			case 11:
			{
				count++;
				if(startDate.dd == 30)
				{
					startDate.dd = 1;
					startDate.mm++;
				}
				else
				{
					startDate.dd++;
				}
				break;
			}
			case 12:
			{					//For December
				count++;
				if (startDate.dd == 31)
				{
					startDate.dd = 1;
					startDate.mm = 1;
					startDate.yyyy++;
				}
				else
				{
					startDate.dd++;
				}
				break;
			}
			case 2:
			{					//For February considering the year to be 1.leap 2.not leap
				if (isleap(startDate.yyyy))
				{
					count++;
					if (startDate.dd == 29){
						startDate.dd =1;
						startDate.mm++;
					}
					else
						startDate.dd++;
				}
				else {
				count++;
				if (startDate.dd ==28){
						startDate.dd=1;
						startDate.mm++;
					}
					else
						startDate.dd++;
					
				}
				break;
			}
		}
	}
	return count;
	
}

int check(struct employee e[],char nam[], char *password, int j)
{
	//Validating the employee details(username and password)
	int statusy=0,ret;
	for (int i=0;i<j;i++)
 	{
  		if(strcmp(nam,e[i].name)==0 && strcmp(password,e[i].passwd)==0)
   		{
      			statusy++;
   			ret=i;
   	  		break;
   		}	 
  	}
	if(statusy==1)
  		return ret;
  	else
		return -1;
}

void apply(struct employee *e,date *d1,date *d2);

void disp(struct employee *e)
{
	//displaying the details of the employee
	float total;
	total = e->cl + e->ml + e->el;
	printf("\t\ttName : %s \n\n",e->name);
	printf("\t\tCasual leaves available : %f \n\n",e->cl);
	printf("\t\tMedical leaves available : %f \n\n",e->ml);
	printf("\t\tEarned leaves available : %f \n\n",e->el);
	printf("\t\tTotal leaves available : %f \n\n",total);
}

void menu(struct employee *e,date *d1,date *d2)
{
	//Menu 
	char yn[5];int choice;int reason; float n;
	option:
	{
		printf("\t\tPress 1.Check balance 2.Apply for leave 3.Exit \n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
			{	//Check balance
				disp(e);
				menu(e,d1,d2);
				break;
			}
			case 2:
			{	//Apply for leave
				apply(e,d1,d2);
				break;
			}
			case 3:			
			{	//Exit
				break;
			}
			default:
			{	//input validation
				printf("\t\tChoose any of the given options only\n");
				printf("\t\tTry again \n");
				goto option;
			}
		}	
	}
}
void apply(struct employee *e,date *d1,date *d2)
{	
	//Applying for leave, after successfull login
	int status1 = 0, status2 = 0, dif, mm=0, dd=0, yyyy=0; 
	if (e->exp < 2.0)
	{	
		//Experience of the employee lesser than 2 years
		float n; int choice;
		again:
		{
			//Leave based on experience
			printf("\t\t **You can only use casual leaves** \n");
			printf("\t\t Enter the start day leave date as dd/mm/yyyy \n");
			scanf("%d/%d/%d",&d1->dd,&d1->mm,&d1->yyyy);
			status1 = isValidDate(d1);
			if (status1 != 1)
			{	
				//Validation of Start date
				printf("\t\tDate is invalid \n");
				printf("\t\t1.Try again 2.Menu \n");
				scanf("%d",&choice);
				switch (choice)
				{
					case 1:
						goto again;
					case 2:
						break;
				}
			}
			else
			{
				printf("\t\tEnter the last day leave date as dd/mm/yyyy \n");
				scanf("%d/%d/%d",&d2->dd,&d2->mm,&d2->yyyy);
				status2 = isValidDate(d2);
				if (status2 != 1)
				{
					//Validation of End date
					printf("\t\tDate is invalid \n");
					printf("\t\t1.Try again 2.Menu \n");
					scanf("%d",&choice);
					switch (choice)
					{
						case 1:
							goto again;
						case 2:
							break;
					}
				}
				else 
				{
					// Calculating the number of days between start date and end date
					dif = datedifference(d1,d2);	
					if (dif>=0 && dif <=3)
					{
						e->cl = e->cl - dif;
						//Leave granted
						printf("\t\t Leave granted for your application \n");
						printf("You have %.2f casual leaves available to use \n",e->cl);
					}
					else
					{
						//Rejection and reason
						printf("\t\tAplication rejected \n");
						printf("\t\tCasual leaves cannot be permitted for more than three days at a time \n");
						printf("\t\t1.Try again 2.Menu \n");
						scanf("%d",&choice);
						switch (choice)
						{
							case 1:
								goto again;
							case 2:
								break;
						}
					}
				}
			}
		}
		menu(e,d1,d2);
	}
	else
	{	
		//Experience greater 2 complete years
		def:
		{
			float n; int choice;
			//Options in leave based on experience
			printf("Choose 1.Workshop\t 2.Casual Leave\t 3.Medical Leave\t 4.Earned Leave\t 5.Menu\t 6.Exit \n");
			scanf("%d",&choice);
			switch(choice)
			{
				case 1:
				{
					//No changes in number of leaves for workshop or conference
					printf("\tYou are permitted to attend the workshop \n\tNo change in the number of leaves available \n");
					menu(e,d1,d2);
					break;
				}
				case 2:
				{
					//Casual leave
					int choice;
					casual:
					{
						printf("Enter the start date of leave as dd/mm/yyyy \n");
						scanf("%d/%d/%d",&d1->dd,&d1->mm,&d1->yyyy);
						status1 = isValidDate(d1);
						if (status1 != 1)
						{
							//Validation of Start date
							printf("Date is invalid \n");
							printf("\t\t1.Try again 2.Menu \n");
							scanf("%d",&choice);
							switch (choice)
							{
								case 1:
									goto casual;
								case 2:
									break;
							}
						}
						else
						{
							printf("Enter the last day leave date as dd/mm/yyyy \n");
							scanf("%d/%d/%d",&d2->dd,&d2->mm,&d2->yyyy);
							status2 = isValidDate(d2);
							if (status2 != 1)
							{
								//Validation of End date
								printf("Date is invalid \n");
								printf("\t\t1.Try again 2.Menu \n");
								scanf("%d",&choice);
								switch (choice)
								{
									case 1:
										goto casual;
									case 2:
										break;
								}
							}
							else 
							{
								//Number of days between Start date and End date
								dif = datedifference(d1,d2);	
								if (dif>=0 && dif <=3)
								{
									e->cl = e->cl - dif;
									//Leave granted
									printf("\t\t Leave granted for your application \n");
									printf("You have %.2f casual leaves available to use \n",e->cl);
								}
								else
								{
									//Leave rejection and reason
									printf("\t\tAplication rejected \n");
									//Restriction on casual leaves
									printf("\t\tCasual leaves cannot be permitted for more than three days at a time \n");
									printf("\t\t1.Try again 2.Menu \n");
									scanf("%d",&choice);
									switch (choice)
									{
										case 1:
											goto casual;
										case 2:
											break;
									}
								}
							}
						}
					}
					menu(e,d1,d2);
					break;
				}
				case 3:
				{
					//Medical leave
					int choice;
					medical:
					{
						printf("Enter the start date of leave as dd/mm/yyyy \n");
						scanf("%d/%d/%d",&d1->dd,&d1->mm,&d1->yyyy);
						status1 = isValidDate(d1);
						//date validation
						if (status1 != 1)
						{
							printf("Date is invalid \n");
							printf("\t\t1.Try again 2.Menu \n");
							scanf("%d",&choice);
							switch (choice)
							{
								case 1:
									goto medical;
								case 2:
									break;
							}
						}
						else
						{
							printf("Enter the last day leave date as dd/mm/yyyy \n");
							scanf("%d/%d/%d",&d2->dd,&d2->mm,&d2->yyyy);
							status2 = isValidDate(d2);
							if (status2 != 1)
							{
								printf("Date is invalid \n");
								printf("\t\t1.Try again 2.Menu \n");
								scanf("%d",&choice);
								switch (choice)
								{
									case 1:
										goto medical;
									case 2:
										break;
								}
							}
							else 
							{
								dif = datedifference(d1,d2);	
								if (dif>=0 && dif <=3)
								{
									e->ml = e->ml - dif;
									//Grant and display leaves available
									printf("\t\t Leave granted for your application \n");
									printf("You have %.2f medical leaves available to use \n",e->ml);
								}
								else
								{
									//Rejection and reason
									printf("\t\tAplication rejected \n");
									//Restriction on medical leaves
									printf("\t\tMedical leaves cannot be permitted for more than three days at a time \n");
									printf("\t\t1.Try again 2.Menu \n");
									scanf("%d",&choice);
									switch (choice)
									{
										case 1:
											goto again;
										case 2:
											break;
									}
								}
							}
						}
					}
					menu(e,d1,d2);
					break;
				}
				case 4:
				{
					//Earned leave
					int choice;
					earned:
					{
						printf("Enter the start date of leave as dd/mm/yyyy \n");
						scanf("%d/%d/%d",&d1->dd,&d1->mm,&d1->yyyy);
						status1 = isValidDate(d1);
						if (status1 != 1)
						{
							//Date Validation
							printf("Date is invalid \n");
							printf("\t\t1.Try again 2.Menu \n");
							scanf("%d",&choice);
							switch (choice)
							{
								case 1:
									goto earned;
								case 2:
									break;
							}
						}
						else
						{
							printf("Enter the last day leave date as dd/mm/yyyy \n");
							scanf("%d/%d/%d",&d2->dd,&d2->mm,&d2->yyyy);
							status2 = isValidDate(d2);
							if (status2 != 1)
							{
								printf("Date is invalid \n");
								printf("\t\t1.Try again 2.Menu \n");
								scanf("%d",&choice);
								switch (choice)
								{
									case 1:
										goto earned;
									case 2:
										break;
								}
							}
							else 
							{
								dif = datedifference(d1,d2);	
								if (dif < e->el)
								{
									e->el = e->el - dif;
									//Grant and display leaves available
									printf("\t\t Leave granted for your application \n");
									printf("You have %.2f Earned leaves available to use \n",e->el);
								}
								else
								{
									//Rejection and reason
									printf("\t\tAplication rejected \n");
									printf("\t\tRequired number of leaves are more than earned leaves available for use\n");
									printf("\t\t1.Try again 2.Menu \n");
									scanf("%d",&choice);
									switch (choice)
									{
										case 1:
											goto again;
										case 2:
											break;
									}
								}
							}
						}
					}
					menu(e,d1,d2);
					break;
				}
				case 5:
				{
					menu(e,d1,d2);
					break;
				}
				case 6:
				{
					break;
				}
				default :
				{
					//Input validation
					printf("\t Choose any one FROM the options given \n");
					goto def;
				}
			}
		}
	}
}

