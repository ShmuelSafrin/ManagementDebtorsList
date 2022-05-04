#define _CRT_SECURE_NO_WARNINGS
#include "MainHeader.h"

void print(Debtor* head, int flag)
{
	if (!flag)
		printf("\nSummary debtors debts of the file. Sorted in ascending order by debt(Anyone with a credit balance is not shown)\n");
	else
		printf("\nDebtors that match your query\n");
	printf("----------------------------------------------------------------------------------------------------\n");
	printf("|First Name:\t\Last Name:\t Id:\t\t Phone Number:\t Total Debt:   Earliest Date Debt: |\n");
	printf("----------------------------------------------------------------------------------------------------\n");

	while (head != NULL)
	{
		if (head->TotalDebt < 0 && !flag)
		{
			head = head->next;
			continue;
		}
		else
		{
			printf("|%-15s %-15s %-15s %-15s %-15.2f %-15s   |\n", head->FirstName, head->LastName,
				head->ID, head->TelphonNumber, head->TotalDebt, head->FirstDebtsDate);
			printf("----------------------------------------------------------------------------------------------------\n");
			head = head->next;
		}
	}
}

void QueriesSetPrint(FILE* fptr, Debtor* head, int* countLines)
{
	char temp[8], ch; //ch for case that user didn't enter select/set/print/quit. So we will use getchar(), to clean the rest line
	printf("\n       --QUERIES-- ||  --SET-- || --PRINT--\n\n");
	printf("(1. For queries, first type \"select\" and then type the query."
		"\n(2. For set old/new debtors, first type \"set\" and then type the debtor you want to add the file."
		"\n*Note For a new debt type positive number and for a debt payment type negative number"
		"\n(3. For print the exist update debtors in the file, type \"print\".\n"
		"\n*Note: in any time, you can type \"quit\" to exit from the Qureies/Set/Print"
		"\n*Note: spell the fields names in the \"query\" and \"set\", exactly as"
		"\nthe fields are spelled in the table as shown below"
		"\n------------------------------------------------------------"
		"\n| first name | last name | id | phone number | debt | date |"
		"\n------------------------------------------------------------"
		"\n*Note: You must put a space between words in a query"
		"\n*Note: in all fielde you can select one of these options to the query: \"=\" , \"!=\" , \"<\" , \">\" , \"<=\" , \">=\""
		"\nA query's example: select date >= 05/05/2005  (*Note: the format data is _ _/_ _/_ _ _ _)"
		"\nA set's example: set first name = Moshe, last name = Burditzov, id = 987654321, phone number = 0000000000, debt = -1000, date = 01/01/1999\n\n-->");

	scanf("%s", &temp);
	while (strcmp(temp, "quit"))
	{
		if (!strcmp(temp, "select"))
			queries(head);
		else if (!strcmp(temp, "set"))
		{
			buildNodeUser(fptr, &head, countLines);
		}
		else if (!strcmp(temp, "print"))
		{
			if (!checkUnnecessaryInputAtQueryEnd())
				goto input;
			print(head, 0);
		}
		else
		{
			printf("\nError. Neither \"select\" nor \"set\" nor \"print\" nor \"quit\" are at the beginning of your input."
				"\nPlease re-enter your choice either \"select\" or \"set\" or \"print\" or \"quit\".");
			while ((ch = getchar()) != '\n');
		}
	input:
		printf("\n\n-->");
		scanf("%s", &temp);
	}
	if (!checkUnnecessaryInputAtQueryEnd())
		goto input;
}

void queries(Debtor* head)
{
	int flag = 1;
	char temp[7];
	char field[20];
	char operator[20];
	char word[20];
	Debtor* headQuery = NULL, * tailQuery = NULL, * current = head;
	scanf("%s", &field);
	if (!strcmp(field, "first") || !strcmp(field, "last"))
	{
		scanf("%s", &temp);
		if (!strcmp(temp, "name"))
		{
			scanf("%s", &operator);
			if (!strcmp(operator, "=") || !strcmp(operator, "!=") || !strcmp(operator, "<") || !strcmp(operator, ">") || !strcmp(operator, "<=") || !strcmp(operator, ">="))
			{
				scanf("%s", &word);
				if (checkAlphabet(word))
				{
					if (!checkUnnecessaryInputAtQueryEnd())
						goto Return;
					strcpy(word,stringToLower(word));
					/*Build linked list for first name query*/
					if (!strcmp(field, "first"))
					{/*Check the operator query*/
						if (!strcmp(operator, "="))
						{
							while (current != NULL)
							{
								if (!strcmp(strcpy(current->FirstName, stringToLower(current->FirstName)), word))/*if 0. i.e they are equal*/
									buildNodeQuery(&headQuery, &tailQuery, current);
								current = current->next;
							}
							if (headQuery == NULL)
							{
								printf("\nDebtors with such a first name were not found");
								flag = 0;
							}
						}
						else if (!strcmp(operator, "!="))
						{
							while (current != NULL)
							{
								if (strcmp(strcpy(current->FirstName, stringToLower(current->FirstName)), word))/*if not 0. i.e they are not equal*/
									buildNodeQuery(&headQuery, &tailQuery, current);
								current = current->next;
							}
							if (headQuery == NULL)
							{
								printf("\nDetors with a different first name(from the first name you gave) were not found.");
								flag = 0;
							}
						}
						else if (!strcmp(operator, "<"))
						{
							while (current != NULL)
							{
								if (!strcmp(strcpy(current->FirstName, stringToLower(current->FirstName)), word) == -1)/*if return -1. So current->FirstName < word*/
									buildNodeQuery(&headQuery, &tailQuery, current);
								current = current->next;
							}
							if (headQuery == NULL)
							{
								printf("\nDetors with a smaller first name(from the first name you gave) were not found.");
								flag = 0;
							}
						}
						else if (!strcmp(operator, ">"))
						{
							while (current != NULL)
							{
								if (strcmp(strcpy(current->FirstName, stringToLower(current->FirstName)), word) == 1)/*if return 1. So current->FirstName > word*/
									buildNodeQuery(&headQuery, &tailQuery, current);
								current = current->next;
							}
							if (headQuery == NULL)
							{
								printf("\nDetors with a bigger first name(from the first name you gave) were not found.");
								flag = 0;
							}
						}
						else if (!strcmp(operator, "<="))
						{
							while (current != NULL)
							{
								if (!strcmp(strcpy(current->FirstName, stringToLower(current->FirstName)), word) || strcmp(strcpy(current->FirstName, stringToLower(current->FirstName)), word) == -1)/*if return 0 So current->FirstName = word. And if return -1. So current->FirstName < word*/
									buildNodeQuery(&headQuery, &tailQuery, current);
								current = current->next;
							}
							if (headQuery == NULL)
							{
								printf("\nDetors with an equal first name or a smaller one(from the first name you gave) were not found.");
								flag = 0;
							}
						}
						else if (!strcmp(operator, ">="))
						{
							while (current != NULL)
							{
								if (!strcmp(strcpy(current->FirstName, stringToLower(current->FirstName)), word) || strcmp(strcpy(current->FirstName, stringToLower(current->FirstName)), word) == 1)/*if return 0 So current->FirstName = word. And if return 1. So current->FirstName > word*/
									buildNodeQuery(&headQuery, &tailQuery, current);
								current = current->next;
							}
							if (headQuery == NULL)
							{
								printf("\nDetors with an equal first name or a bigger one(from the first name you gave) were not found.");
								flag = 0;
							}
						}
					}
					/*Build linked list for last name query*/
					if (!strcmp(field, "last"))
					{/*Check the operator query*/
						if (!strcmp(operator, "="))
						{
							while (current != NULL)
							{
								if (!strcmp(strcpy(current->LastName, stringToLower(current->LastName)), word))/*if 0. i.e they are equal*/
									buildNodeQuery(&headQuery, &tailQuery, current);
								current = current->next;
							}
							if (headQuery == NULL)
							{
								printf("\nDebtors with such a last name were not found");
								flag = 0;
							}
						}
						else if (!strcmp(operator, "!="))
						{
							while (current != NULL)
							{
								if (strcmp(strcpy(current->LastName, stringToLower(current->LastName)), word))/*if not 0. i.e they are not equal*/
									buildNodeQuery(&headQuery, &tailQuery, current);
								current = current->next;
							}
							if (headQuery == NULL)
							{
								printf("\nDetors with a different last name(from the last name you gave) were not found.");
								flag = 0;
							}
						}
						else if (!strcmp(operator, "<"))
						{
							while (current != NULL)
							{
								if (strcmp(strcpy(current->LastName, stringToLower(current->LastName)), word) == -1)/*if return -1. So current->FirstName < word*/
									buildNodeQuery(&headQuery, &tailQuery, current);
								current = current->next;
							}
							if (headQuery == NULL)
							{
								printf("\nDetors with a smaller last name(from the last name you gave) were not found.");
								flag = 0;
							}
						}
						else if (!strcmp(operator, ">"))
						{
							while (current != NULL)
							{
								if (strcmp(strcpy(current->LastName, stringToLower(current->LastName)), word) == 1)/*if return 1. So current->FirstName > word*/
									buildNodeQuery(&headQuery, &tailQuery, current);
								current = current->next;
							}
							if (headQuery == NULL)
							{
								printf("\nDetors with a bigger last name(from the last name you gave) were not found.");
								flag = 0;
							}
						}
						else if (!strcmp(operator, "<="))
						{
							while (current != NULL)
							{
								if (!strcmp(strcpy(current->LastName, stringToLower(current->LastName)), word) || strcmp(strcpy(current->LastName, stringToLower(current->LastName)), word) == -1)/*if return 0 So current->FirstName = word. And if return -1. So current->FirstName < word*/
									buildNodeQuery(&headQuery, &tailQuery, current);
								current = current->next;
							}
							if (headQuery == NULL)
							{
								printf("\nDetors with an equal last name or a smaller one(from the last name you gave) were not found.");
								flag = 0;
							}
						}
						else if (!strcmp(operator, ">="))
						{
							while (current != NULL)
							{
								if (!strcmp(strcpy(current->LastName, stringToLower(current->LastName)), word) || strcmp(strcpy(current->LastName, stringToLower(current->LastName)==1), word))/*if return 0 So current->FirstName = word. And if return 1. So current->FirstName > word*/
									buildNodeQuery(&headQuery, &tailQuery, current);
								current = current->next;
							}
							if (headQuery == NULL)
							{
								printf("\nDetors with an equal last name or a bigger one(from the last name you gave) were not found.");
								flag = 0;
							}
						}
					}
				}
				else
				{
					printf("Error!. The word %s is not a name"
						"\nPlease enter query again.", word);
					goto Return;
				}

			}
			else
			{
				printf("Error!. The word %s is not an operator"
					"\nPlease enter query again.", operator);
				goto Return;
			}
		}
		else
		{
			printf("Error!. The word %s is not a field"
				"\nPlease enter query again.", temp);
			goto Return;
		}
	}
	else if (!strcmp(field, "id") || !strcmp(field, "debt") || !strcmp(field, "date"))
	{
		scanf("%s", &operator);
		if (!strcmp(operator, "=") || !strcmp(operator, "!=") || !strcmp(operator, "<") || !strcmp(operator, ">") || !strcmp(operator, "<=") || !strcmp(operator, ">="))
		{
			scanf("%s", &word);
			if (!checkUnnecessaryInputAtQueryEnd())
				goto Return;
			if (!strcmp(field, "id"))
			{
				if (checkSizeAndDigits(field, 9))
				{
					/*Check the operator query for the Id*/
					if (!strcmp(operator, "="))
					{
						while (current != NULL)
						{
							if (!strcmp(current->ID, word))/*if 0. i.e they are equal*/
								buildNodeQuery(&headQuery, &tailQuery, current);
							current = current->next;
						}
						if (headQuery == NULL)
						{
							printf("\nDebtors with such an Id were not found");
							flag = 0;
						}
					}
					else if (!strcmp(operator, "!="))
					{
						while (current != NULL)
						{
							if (strcmp(current->ID, word))/*if not 0. i.e they are not equal*/
								buildNodeQuery(&headQuery, &tailQuery, current);
							current = current->next;
						}
						if (headQuery == NULL)
						{
							printf("\nDetors with a different Id(from the Id you gave) were not found.");
							flag = 0;
						}
					}
					else if (!strcmp(operator, "<"))
					{
						while (current != NULL)
						{
							if (strcmp(current->ID, word) == -1)/*if return -1. So current->FirstName < word*/
								buildNodeQuery(&headQuery, &tailQuery, current);
							current = current->next;
						}
						if (headQuery == NULL)
						{
							printf("\nDetors with a smaller Id(from the Id you gave) were not found.");
							flag = 0;
						}
					}
					else if (!strcmp(operator, ">"))
					{
						while (current != NULL)
						{
							if (strcmp(current->ID, word) == 1)/*if return 1. So current->FirstName > word*/
								buildNodeQuery(&headQuery, &tailQuery, current);
							current = current->next;
						}
						if (headQuery == NULL)
						{
							printf("\nDetors with a bigger ID(from the Id you gave) were not found.");
							flag = 0;
						}
					}
					else if (!strcmp(operator, "<="))
					{
						while (current != NULL)
						{
							if (!strcmp(current->ID, word) || strcmp(current->ID, word) == -1)/*if return 0 So current->FirstName = word. And if return -1. So current->FirstName < word*/
								buildNodeQuery(&headQuery, &tailQuery, current);
							current = current->next;
						}
						if (headQuery == NULL)
						{
							printf("\nDetors with an equal Id or a smaller Id(from the Id you gave) were not found.");
							flag = 0;
						}
					}
					else if (!strcmp(operator, ">="))
					{
						while (current != NULL)
						{
							if (!strcmp(current->ID, word) || strcmp(current->ID, word) == 1)/*if return 0 So current->FirstName = word. And if return 1. So current->FirstName > word*/
								buildNodeQuery(&headQuery, &tailQuery, current);
							current = current->next;
						}
						if (headQuery == NULL)
						{
							printf("\nDetors with an equal Id or a bigger Id(from the Id you gave) were not found.");
							flag = 0;
						}
					}
				}
				else
				{
					printf("Error!. Invalid Id"
						"\nPlease enter query again.");
					goto Return;
				}
			}
			else if (!strcmp(field, "debt"))
			{
				if (isCorrectAmount(word))
				{
					/*Check the operator query for the debt*/
					if (!strcmp(operator, "="))
					{
						while (current != NULL)
						{
							if (current->TotalDebt == atof(word))
								buildNodeQuery(&headQuery, &tailQuery, current);
							current = current->next;
						}
						if (headQuery == NULL)
						{
							printf("\nDebtors with such a debt were not found");
							flag = 0;
						}
					}
					else if (!strcmp(operator, "!="))
					{
						while (current != NULL)
						{
							if (current->TotalDebt != atof(word))
								buildNodeQuery(&headQuery, &tailQuery, current);
							current = current->next;
						}
						if (headQuery == NULL)
						{
							printf("\nDetors with a different debt(from the debt you gave) were not found.");
							flag = 0;
						}
					}
					else if (!strcmp(operator, "<"))
					{
						while (current != NULL)
						{
							if (current->TotalDebt < atof(word))
								buildNodeQuery(&headQuery, &tailQuery, current);
							current = current->next;
						}
						if (headQuery == NULL)
						{
							printf("\nDetors with a different debt(from the debt you gave) were not found.");
							flag = 0;
						}
					}
					else if (!strcmp(operator, ">"))
					{
						while (current != NULL)
						{
							if (current->TotalDebt > atof(word))/*if return 1. So current->FirstName > word*/
								buildNodeQuery(&headQuery, &tailQuery, current);
							current = current->next;
						}
						if (headQuery == NULL)
						{
							printf("\nDetors with a different debt(from the debt you gave) were not found.");
							flag = 0;
						}
					}
					else if (!strcmp(operator, "<="))
					{
						while (current != NULL)
						{
							if ((current->TotalDebt <= atof(word)))
								buildNodeQuery(&headQuery, &tailQuery, current);
							current = current->next;
						}
						if (headQuery == NULL)
						{
							printf("\nDetors with an equal debt or a smaller debt(from the debt you gave) were not found.");
							flag = 0;
						}
					}
					else if (!strcmp(operator, ">="))
					{
						while (current != NULL)
						{
							if ((current->TotalDebt >= atof(word)))
								buildNodeQuery(&headQuery, &tailQuery, current);
							current = current->next;
						}
						if (headQuery == NULL)
						{
							printf("\nDetors with an equal debt or a bigger debt(from the debt you gave) were not found.");
							flag = 0;
						}
					}
				}
				else
				{
					printf("Error!. Invalid debt"
						"\nPlease enter query again.");
					goto Return;
				}
			}
			else if (!strcmp(field, "date"))
			{
				if (checkDateValidation(word))
				{
					/*Check the operator query for the Date*/
					if (!strcmp(operator, "="))
					{
						while (current != NULL)
						{
							if (!strcmp(current->FirstDebtsDate, word))/*if 0. i.e they are equal*/
								buildNodeQuery(&headQuery, &tailQuery, current);
							current = current->next;
						}
						if (headQuery == NULL)
						{
							printf("\nDebtors with such a date were not found");
							flag = 0;
						}
					}
					else if (!strcmp(operator, "!="))
					{
						while (current != NULL)
						{
							if (strcmp(current->FirstDebtsDate, word))/*if not 0. i.e they are not equal*/
								buildNodeQuery(&headQuery, &tailQuery, current);
							current = current->next;
						}
						if (headQuery == NULL)
						{
							printf("\nDetors with a different date(from the date you gave) were not found.");
							flag = 0;
						}
					}
					else if (!strcmp(operator, "<"))
					{
						while (current != NULL)
						{
							if (strcmp(current->FirstDebtsDate, word) == -1)/*if return -1. So current->FirstName < word*/
								buildNodeQuery(&headQuery, &tailQuery, current);
							current = current->next;
						}
						if (headQuery == NULL)
						{
							printf("\nDetors with a smaller date(from the date you gave) were not found.");
							flag = 0;
						}
					}
					else if (!strcmp(operator, ">"))
					{
						while (current != NULL)
						{
							if (strcmp(current->FirstDebtsDate, word)==1)/*if return 1. So current->FirstName > word*/
								buildNodeQuery(&headQuery, &tailQuery, current);
							current = current->next;
						}
						if (headQuery == NULL)
						{
							printf("\nDetors with a bigger date(from the date you gave) were not found.");
							flag = 0;
						}
					}
					else if (!strcmp(operator, "<="))
					{
						while (current != NULL)
						{
							if (!strcmp(current->FirstDebtsDate, word) || strcmp(current->FirstDebtsDate, word) == -1)/*if return 0 So current->FirstName = word. And if return -1. So current->FirstName < word*/
								buildNodeQuery(&headQuery, &tailQuery, current);
							current = current->next;
						}
						if (headQuery == NULL)
						{
							printf("\nDetors with an equal date or a smaller date(from the date you gave) were not found.");
							flag = 0;
						}
					}
					else if (!strcmp(operator, ">="))
					{
						while (current != NULL)
						{
							if (!strcmp(current->FirstDebtsDate, word) || strcmp(current->FirstDebtsDate, word)==1)/*if return 0 So current->FirstName = word. And if return 1. So current->FirstName > word*/
								buildNodeQuery(&headQuery, &tailQuery, current);
							current = current->next;
						}
						if (headQuery == NULL)
						{
							printf("\nDetors with an equal date or a bigger date(from the date you gave) were not found.");
							flag = 0;
						}
					}
				}
				else
				{
					printf("Error!. Invalid date"
						"\nPlease enter query again.");
					goto Return;
				}
			}
		}
		else
		{
			printf("Error!. The word %s is not an operator"
				"\nPlease enter query again.", operator);
			goto Return;
		}
	}
	else if (!strcmp(field, "phone"))
	{
		scanf("%s", &temp);
		if (!strcmp(temp, "number"))
		{
			scanf("%s", &operator);
			if (!strcmp(operator, "=") || !strcmp(operator, "!=") || !strcmp(operator, "<") || !strcmp(operator, ">") || !strcmp(operator, "<=") || !strcmp(operator, ">="))
			{
				scanf("%s", &word);
				if (checkSizeAndDigits(word, 10))
				{
					if (!checkUnnecessaryInputAtQueryEnd())
						goto Return;
					/*Check the operator query for the Fhone Number*/
					if (!strcmp(operator, "="))
					{
						while (current != NULL)
						{
							if (!strcmp(current->TelphonNumber, word))/*if 0. i.e they are equal*/
								buildNodeQuery(&headQuery, &tailQuery, current);
							current = current->next;
						}
						if (headQuery == NULL)
						{
							printf("\nDebtors with such a phone number were not found");
							flag = 0;
						}
					}
					else if (!strcmp(operator, "!="))
					{
						while (current != NULL)
						{
							if (strcmp(current->TelphonNumber, word))/*if not 0. i.e they are not equal*/
								buildNodeQuery(&headQuery, &tailQuery, current);
							current = current->next;
						}
						if (headQuery == NULL)
						{
							printf("\nDetors with a different phone number(from the phone number you gave) were not found.");
							flag = 0;
						}
					}
					else if (!strcmp(operator, "<"))
					{
						while (current != NULL)
						{
							if (strcmp(current->TelphonNumber, word) == -1)/*if return -1. So current->FirstName < word*/
								buildNodeQuery(&headQuery, &tailQuery, current);
							current = current->next;
						}
						if (headQuery == NULL)
						{
							printf("\nDetors with a smaller phone number(from the phone number you gave) were not found.\n\n");
							flag = 0;
						}
					}
					else if (!strcmp(operator, ">"))
					{
						while (current != NULL)
						{
							if (strcmp(current->TelphonNumber, word)==1)/*if return 1. So current->FirstName > word*/
								buildNodeQuery(&headQuery, &tailQuery, current);
							current = current->next;
						}
						if (headQuery == NULL)
						{
							printf("\nDetors with a bigger phone number(from the phone number you gave) were not found.\n\n");
							flag = 0;
						}
					}
					else if (!strcmp(operator, "<="))
					{
						while (current != NULL)
						{
							if (!strcmp(current->TelphonNumber, word) || strcmp(current->TelphonNumber, word) == -1)/*if return 0 So current->FirstName = word. And if return -1. So current->FirstName < word*/
								buildNodeQuery(&headQuery, &tailQuery, current);
							current = current->next;
						}
						if (headQuery == NULL)
						{
							printf("\nDetors with an equal phone number or a smaller phone number(from the phone number you gave) were not found.\n\n");
							flag = 0;
						}
					}
					else if (!strcmp(operator, ">="))
					{
						while (current != NULL)
						{
							if (!strcmp(current->TelphonNumber, word) || strcmp(current->TelphonNumber, word)==1)/*if return 0 So current->FirstName = word. And if return 1. So current->FirstName > word*/
								buildNodeQuery(&headQuery, &tailQuery, current);
							current = current->next;
						}
						if (headQuery == NULL)
						{
							printf("\nDetors with an equal phone number or a bigger phone number(from the phone number you gave) were not found.\n\n");
							flag = 0;
						}
					}
				}
				else
				{
					printf("Error!. Invalid phone number"
						"\nPlease enter query again");
					goto Return;
				}
			}
			else
			{
				printf("Error!. The word %s is not an operator"
					"\nPlease enter query again", operator);
				goto Return;
			}
		}
		else
		{
			printf("Error!. The word %s is not a field"
				"\nPlease enter query again", temp);
			goto Return;
		}
	}
	else
	{
		printf("Error!. The word %s is not a field"
			"\nPlease enter query again", field);
		goto Return;
	}
	if (flag)
	{
		//we don't need to sort because in the creation of the query list
		//we link each node from the tail
		print(headQuery, 1);
		freeAllDebtors(headQuery);
	}
Return:
	return;
}