
PROBLEM STATEMENT:

Develop a mini employee leave management system

ABOUT THE PROGRAM:

The program folder contains client.c, server.c file, server.h file, makefile.mk file. All are executable through the makefile
The input taken as password is not displayed while being taken

INSTRUCTION ON PROGRAM EXECUTION:

Command to compile : make -f makefile.mk

Command to run the program : ./a.out

BUGS AND ISSUES KNOWN : 

->When employee uses a leave, the leave count available for further use is decreased. But the updated leave count is restricted to the program i.e., the leave count couldn't be updated in the txt file.
->It could be solved, but the trials invloved errors in every function (Issue is suspected to be in accessing the file in multiple functions).
->Tried using the file in w+, r+ mode separately.
->Not an issue in function call or arguement passing

ASSUMPTIONS :

1. Employee considers sunday date not be taken as leave
2. Employee applies leave for days in the future i.e., days before the present day aren't applied
	while the same day can applied a leave
3. Leave need not be a whole day. A half day leave can be taken.

CONDITIONS UNDER WHICH CODE WORKS PROPERLY:

1.Year be between 1900 and 9999 (Out of the limit is an invalid case)
2.Employee login success (positive and negative cases work)
3.Valid date input (positive and negative cases work)
4.Number of days of leave within limit (positive and negative cases work)
5.Employee considers dates for leave in the near future
