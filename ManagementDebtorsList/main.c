#define _CRT_SECURE_NO_WARNINGS

#include "MainHeader.h"

int main()
{
	Debtor* head = NULL;
	FILE* file_ptr;
	
	/*If we encountered in error or warninig to notify user.
	so the notification will included in which line it is*/
	int countLines = 0;
	/*We oprn for readinig and for writing*/
	file_ptr = fopen(FileName,"a+");
	if(file_ptr == NULL)
		//If Debtors == NULL the program will notify and will exit
		Error_Msg("File not found");
	fromFileToList(file_ptr,&head,&countLines);
	MergeSort(&head);
	print(head,0);
	QueriesSetPrint(file_ptr,head,&countLines);
	freeAllDebtors(head);
	fclose(file_ptr);
	printf("\nBye bye. Thank you for using my app...%c%c%c\n", 1, 1, 1);
	printf("(The program created by Shmuel Safrin)\n\n");
	return 0;
}