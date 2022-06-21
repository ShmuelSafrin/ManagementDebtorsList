#define _CRT_SECURE_NO_WARNINGS
#include "MainHeader.h"

void checkAndSetFirstLastNameExistField(int flag, char** debtorField, char* token, int* lineNumber)
{
	if (!checkAlphabet(token))
	{
		char field[6];
		if (!flag)
			strcpy(field,"First");
		else
			strcpy(field,"Last");
		printf("\n(Warning in line %d) --> The %s Name is Unknown Characters.\n",*lineNumber,field);
		*debtorField = (char*)malloc(13);
		strcpy(*debtorField, "UnknownChars");
	}
	else
	{
		*debtorField = (char*)malloc(strlen(token) + 1);
		strcpy(*debtorField, token);
	}
}

int checkAndSetIdExistField(char* debtorField, char* token, int* lineNumber)
{
	if (!checkSizeAndDigits(token, 9))
	{
		printf("\n(Error in line %d) --> The Id should be exactly 9 digits.\nThe line was not accepted in the program.\n", *lineNumber);
		return 0;
	}
	strcpy(debtorField, token);
	return 1;
}

void checkAndSetPhoneNumberExistField(char* debtorField, char* token, int* lineNumber)
{
	if (*token != '0')
	{
		printf("\n(Warning in line % d) --> The phone number should start with digit 0.\n", *lineNumber);
		strcpy(debtorField, "Invalid");
	}
	else if (!checkSizeAndDigits(token, 10))
	{
		printf("\n(Warning in line %d) --> The phone number should be exactly 10 digits.\n", *lineNumber);
		strcpy(debtorField, "Invalid");
	}
	else
		strcpy(debtorField, token);
}

int checkAndSetDebtExistField(float *debtorField, char* field, int* lineNumber)
{
	if (!(isCorrectAmount(field)))
	{
		printf("\n(Error in line %d) --> The debt is invalid.\nThe line was not accepted in the program.\n", *lineNumber);
		freeOneDebtor(field);
		return 0;
	}
	*debtorField = atof(field);
	return 1;
}

int checkAndSetDateExistField(char* debtorField, char* field, int* lineNumber)
{
	if (strstr(field, " ") || strstr(field, "\t"))
	{
		int i = 0;
		char check[MIDDLE_SIZE];
		strcpy(check, field);
		field = strtok(field, " \t");
		while (check[i] != ' ' && check[i] != '\t')
			i++;
		while (check[i] == ' ' || check[i] == '\t')
			i++;
		if (check[i] != '\0')
		{
			printf("\n(Error in line %d) --> Irrelevant words at the line end.\nThe line was not accepted in the program.\n", *lineNumber);
			return 0;
		}
	}
	char copy[MIDDLE_SIZE];
	strcpy(copy, field);
	if (!checkDateValidation(copy))
	{
		printf("\n(Warning Invalid Date in line %d) --> The Date should be in this format  _ _/_ _/_ _ _ _,\nAnd with days from 01 to 12 and month from 01 to 31.\n", *lineNumber);
		strcpy(debtorField, "Invalid");
	}
	else
		strcpy(debtorField, field);
	return 1;
}

int handleMissingField(Debtor* temp, int* i, int* lineNumber)
{
	switch (*i)
	{
			
		case 0://First name
			printf("\n(Warning in line %d) --> The First Name is missing.\n", *lineNumber);
			temp->FirstName = (char*)malloc(8);
			strcpy(temp->FirstName, "Missing");
			break;
		case 1://Last name
			printf("\n(Warning in line %d) --> The Last Name is missing.\n", *lineNumber);
			temp->LastName = (char*)malloc(8);
			strcpy(temp->LastName, "Missing");
			break;
		case 2://Id
			printf("\n(Erorr in line %d) --> The Id is missing.\nThe line was not accepted in the program.\n", *lineNumber);
			freeOneDebtor(temp);
			return 0;
		case 3://Phone
			printf("\n(Warning in line %d) --> The phone number is missing.\n", *lineNumber);
			strcpy(temp->PhoneNumber, "Missing");
			break;
		case 4://Debt
			printf("\n(Erorr in line %d) --> The debt amount is missing.\nThe line was not accepted in the program.\n", *lineNumber);
			freeOneDebtor(temp);
			return 0;
		case 5://Date
			printf("\n(Warning in line %d) --> The date debt is missing.\n",*lineNumber);
			strcpy(temp->Date, "Missing");
	}
}

int handleExistingField(Debtor* temp,char *field, int* i, int* lineNumber)
{
	switch (*i)
	{

	case 0://First name
		checkAndSetFirstLastNameExistField(0, &(temp->FirstName), field, lineNumber);
		break;
	case 1://Last name
		checkAndSetFirstLastNameExistField(1, &(temp->LastName),field, lineNumber);
		break;
	case 2://Id
		if (!checkAndSetIdExistField(temp->ID,field, lineNumber))
		{
			freeOneDebtor(temp);
			return 0;
		}
		return 1;
	case 3://Phone
		checkAndSetPhoneNumberExistField(temp->PhoneNumber, field, lineNumber);
		break;
	case 4://Debt
		if (!checkAndSetDebtExistField(&(temp->Debt), field, lineNumber))
		{
			freeOneDebtor(temp);
			return 0;
		}
		return 1;
	case 5://Date
		if (!checkAndSetDateExistField(temp->Date, field, lineNumber))
		{
			freeOneDebtor(temp);
			return 0;
		}
		return 1;
	}
}

void buildNodeFile(FILE* file_ptr, Debtor** head, int* countLines)
{
	int length, i, flag = 0;
	char date[11];
	char line[MAX_LINE];
	char copyline[MAX_LINE];
	char delimiter[2] = ",";
	char* column = NULL, * delim;
	Debtor* temp;

	unsigned char column_index = 0;
	//char* column_p[MAX_COLUMN];
	//char line[] = "john,doe,123456789,-100";
getNewLine:
	i = 0;
	while (fgets(line, MAX_LINE, file_ptr) != NULL)
	{
		line[strlen(line) - 1] = '\0';
		strcpy(copyline, line);
		(*countLines)++;

		if (!checkFormatLine(line, countLines))
			goto getNewLine;
		temp = (Debtor*)malloc(sizeof(Debtor));
		if (temp == NULL)//check if the allocation failed
		{
			Error_Msg("Memmory allocation failed!!. (Try closing other programs that are currently running.\nIf you are still having a problem try restarting your computer.)\n");
		}
		/*--------------Here we start to split each line to fields by it commas------------------ */
		delim = copyline;
		column = strtok(line, ",");
		do
		{
			while (*delim == ',')
			{
				if (!handleMissingField(temp, &i, countLines))
					goto getNewLine;
				delim++;
				i++;
			}
			if (!handleExistingField(temp, column, &i, countLines))
				goto getNewLine;
			delim = strchr(delim, ',');
			delim++;
			column = strtok(NULL,",");
			i++;
		}while (column);
		//---------------------------------------------------
		/*Now we linking the new Debtor to the link list*/
		//---------------------------------------------------
		addNodeFileToList(head, temp, countLines);
		i = 0;
	}
}

void addNodeFileToList(Debtor** head, Debtor* node, int* lineNumber)
{
	Debtor* current;
	if (*head == NULL)//If it's the first DetorList
	{
		node->next = NULL;
		*head = node;
	}
	else//There are alredy Detors in the linked list
	{
		current = *head;
		while (current != NULL)
		{
			if (strcmp(current->ID, node->ID) == 0)//check by comparing Ids if The this Debtor is alredy exsits  
				break;
			current = current->next;
		}
		if (current == NULL)//i.e not exists Detor in the link list with the same Id. 
		{
			node->next = *head;
			*head = node;
		}
		else//This Detor is alredy in the linked list
		{
			//checks matching between the names of an exsist DetorList with the same Id.
			/*If node->FirstName != Missing and current->FirstName = Missing*/
			if ((strcmp(node->FirstName, "Missing")) && !(strcmp(current->FirstName, "Missing")))
			{
				strcpy(current->FirstName, node->FirstName);
			}
			/*If node->FirstName != Missing, and current->FirstName != Missing, and their names are diffrent*/
			else if (strcmp(node->FirstName, "Missing") && strcmp(current->FirstName, "Missing") && strcmp(node->FirstName, current->FirstName))
			{
				printf("\nError, The first name does not match the name that is already exists in the file with the same ID.\n");
				goto free;
			}

			if ((strcmp(node->LastName, "Missing")) && !(strcmp(current->LastName, "Missing")))
			{
				strcpy(current->LastName, node->LastName);
			}
			/*If node->FirstName != Missing, and current->FirstName != Missing, and their names are diffrent*/
			else if (strcmp(node->LastName, "Missing") && strcmp(current->LastName, "Missing") && strcmp(node->LastName, current->LastName))
			{
				printf("\nError, The last name does not match the name that is already exists in the file with the same ID.\n");
				goto free;
			}
			else//The names are matchinig.
			{//so we update the TotalSum.
			//and update firstDetsDate to the oldest date.
			//as well we free all the temp inculding all is dynamic fields
				strcpy(current->PhoneNumber, node->PhoneNumber);
				current->Debt += node->Debt;
				/*If in one user line ther's a missinig date
				so we update his node with missing
				if it's not missing but invalid so
				we update the node with invalid
				and if it's not invalid but it is
				valid date so we update the earliest date
				The function earlierDate return
				the int who's date is eariler*/
				if (!strcmp(node->Date, "Missing"))
					strcpy(current->Date, "Missing");
				else if (!strcmp(node->Date, "Invalid") && strcmp(current->Date, "Missing"))
					strcpy(current->Date, "Invalid");
				/*In this case node->FirstDebtsDate = valid date. So we check if current->FirstDebtsDate = valid as well because otherwise it's not posible to check the earlier date*/
				else if (strcmp(current->Date, "Missing") && strcmp(current->Date, "Invalid"))
				{
					if (checkEarlierDate(node->Date, current->Date) == -1)
						strcpy(current->Date, node->Date);
				}
				free:
				freeOneDebtor(node);
			}
		}
	}
}

void buildNodeQuery(Debtor** headQuery, Debtor** tailQuery, Debtor* current)
{
	(*current->FirstName) = toupper(*current->FirstName);
	(*current->LastName) = toupper(*current->LastName);
	Debtor* temp;
	temp = (Debtor*)malloc(sizeof(Debtor));
	if (temp == NULL)//check if the allocation failed
	{
		Error_Msg("Memmory allocation failed!!. (Try closing other programs that are currently running.\nIf you are still having a problem try restarting your computer.)\n");
	}
	temp->FirstName = (char*)malloc(strlen(current->FirstName) + 1);
	strcpy(temp->FirstName, current->FirstName);
	temp->LastName = (char*)malloc(strlen(current->LastName) + 1);
	strcpy(temp->LastName, current->LastName);
	strcpy(temp->ID, current->ID);
	strcpy(temp->PhoneNumber, current->PhoneNumber);
	temp->Debt = current->Debt;
	strcpy(temp->Date, current->Date);
	addNodeQueryToList(headQuery, tailQuery, temp);
}

void addNodeQueryToList(Debtor** headQuery, Debtor** tailQuery, Debtor* node)
{
	//DebtorList* current;
	if (*headQuery == NULL)//If it's the first DetorList
	{
		node->next = NULL;
		*headQuery = node;
		*tailQuery = node;
	}
	else//There are alredy Detors in the linked list
	{
		//current = *headQuery;
		node->next = NULL;
		(*tailQuery)->next = node;
		*tailQuery = node;
	}
}

void buildNodeUser(FILE* fptr, Debtor** head, int* countLines)
{
	int flag = 1,fromDate = 0;
	char delimiters[4] = " \t=";
	char copy[MAX_LINE];
	char line[MAX_LINE];
	char* token = NULL;
	Debtor* temp = NULL;
	fgets(line, MAX_LINE, stdin);
	if (!strcmp(line,"\n"))
	{
		printf("An empty line\n");
		return;
	}
	line[strlen(line) - 1] = '\0';
	
	/*allocation of new node*/
	temp = (Debtor*)calloc(1,sizeof(Debtor));
	if (temp == NULL)//check if the allocation failed
	{
		Error_Msg("Memmory allocation failed!!. (Try closing other programs that are currently running.\nIf you are still having a problem try restarting your computer.)\n");
	}
	token = strtok(line, delimiters);
	while (token != NULL)
	{
		if (flag)
			flag = 0;
		else
		{
			token = strtok(NULL, delimiters);
			if (token == NULL)
				break;
		}
		/*for the First Name*/
		if (!strcmp(token, "first"))
		{
			token = strtok(NULL, delimiters);
			if (!strcmp(token, "name"))
				token = strtok(NULL, " \t,=");
			else
				goto Irrelevant;

			if (!checkAlphabet(token))
			{
				printf("\nWarning, The First Name is Unknown Characters.\n");
				temp->FirstName = (char*)malloc(13);
				strcpy(temp->FirstName, "UnknownChars");
			}
			else
			{
				temp->FirstName = (char*)malloc(strlen(token) + 1);
				strcpy(temp->FirstName, token);
			}
		}
		/*for the Last Name*/
		else if (!strcmp(token, "last"))
		{
			token = strtok(NULL, delimiters);
			if (!strcmp(token, "name"))
				token = strtok(NULL, " \t,=");
			else
				goto Irrelevant;
			if (!checkAlphabet(token))
			{
				printf("\nWarning, The Last Name is Unknown Characters.\n");
				temp->LastName = (char*)malloc(13);
				strcpy(temp->LastName, "UnknownChars");
			}
			else
			{
				temp->LastName = (char*)malloc(strlen(token) + 1);
				strcpy(temp->LastName, token);
			}
		}

		/*for the ID*/
		else if (strstr(token, "id"))
		{
			token = strtok(NULL, " \t,=");
			if (!checkSizeAndDigits(token, 9))
			{
				printf("\nError, The Id should be exactly 9 digits\n");
				freeOneDebtor(temp);
				return;
			}
			else
			{
				strcpy(temp->ID, token);
			}
		}
		/*for the TelphonNumber*/
		else if (strstr(token, "phone number"))
		{
			token = strtok(NULL, " \t,=");
			if (*token != '0')
			{
				printf("\nWarning, The phone number should start with digit \"0\"\n");
				strcpy(temp->PhoneNumber, "Invalid");
			}
			else if (!checkSizeAndDigits(token, 10))
			{
				printf("\Warning, The phone number should be exactly 9 digits\n");
				strcpy(temp->PhoneNumber, "Invalid");
			}
			else
			{
				strcpy(temp->PhoneNumber, token);
			}
		}
		/*for the amountDebt*/
		else if (strstr(token, "debt"))
		{
			token = strtok(NULL, " \t,=");
			if (!(isCorrectAmount(token)))
			{
				printf("\n(Error, The amount debt is incorrect.\n");
				freeOneDebtor(temp);
				return;
			}
			temp->Debt = atof(token);
		}

		/*for the dateDebt*/
		else if (strstr(token, "date"))
		{
			token = strtok(NULL, " \t,=");
			strcpy(copy, token);
			if (!checkDateValidation(copy))
			{
				printf("\nWarning, Invalid Date."
					"\nThe Date should be in this format _ _/_ _/_ _ _ _,"
					"\nAnd with days from 01 to 12. Month from 01 to 31\n\n.");
				strcpy(temp->Date, "Invalid");
			}
			else
				strcpy(temp->Date, token);
		}
		else
		{
		Irrelevant:
			printf("Error!, Irrelevant words are in the set");
			freeOneDebtor(temp);
			return;
		}
	}
	if (temp->ID[0] == 0)
	{
		printf("\nYou can't set new line without Id\n");
		freeOneDebtor(temp);
		return;
	}
	if (temp->Debt == 0)
	{
		printf("\nYou can't set new line without debt\n");
		freeOneDebtor(temp);
		return;
	}
	if(temp->FirstName == NULL)
	{
		temp->FirstName = (char*)malloc(8);
		strcpy(temp->FirstName, "Missing");
		printf("\n*Note the first name is missing\n");
	}
	if (temp->LastName == NULL)
	{
		temp->LastName = (char*)malloc(8);
		strcpy(temp->LastName, "Missing");
		printf("\n*Note the last name is missing\n");
	}
	if (temp->PhoneNumber[0] == 0)
	{
		strcpy(temp->PhoneNumber, "Missing");
		printf("\n*Note the phone number is missing\n");

	}
	if (temp->Date[0] == 0)
	{
		strcpy(temp->Date, "Missing");
		printf("\n*Note the date is missing\n");

	}
	//---------------------------------------------------
	/*Now we linking the user Debtor to the link list*/
	//---------------------------------------------------
	addNodeUserToList(fptr, head, temp, countLines);

}
void addNodeUserToList(FILE* fptr, Debtor** head, Debtor* node, int* countLines)
{
	int flag = 0;
	Debtor* current, * prev, * after, * temp1, * temp2;
	if (*head == NULL)//If it's the first Detor and the link list is empty
	{
		node->next = NULL;
		*head = node;
		/*1)Increasing the count lines by one
		  2)We add the valid line to the file
		  3)Notify user that his line added to the file successfully (in line x)*/
		(*countLines)++;
		fprintf(fptr, "\n%s,%s,%s,%s,%.2f,%s", node->FirstName, node->LastName, node->ID, node->PhoneNumber, node->Debt, node->Date);
		printf("\n\nYour set line added to the file successfully (in line %d)", *countLines);
	}
	else//There are alredy Detors in the linked list
	{
		current = *head;
		while (current != NULL)
		{
			if (!strcmp(current->ID, node->ID))//check by comparing Ids if this Debtor is alredy exsits  
				break;
			current = current->next;
		}
		if (current == NULL)//i.e not exists this Detor in the link list with the same Id. 
		{
			current = *head;
			if (node->Debt < current->Debt)
			{
				node->next = current;
				*head = node;
			}
			else
			{
				prev = *head;
				after = prev->next;
				while ((after != NULL) && (node->Debt > after->Debt))
				{
					prev = after;
					after = after->next;
				}
				if (after == NULL)
				{
					prev->next = node;
					node->next = NULL;
				}
				else
				{
					node->next = after;
					prev->next = node;
				}
			}
			/*1)Increasing the count lines by one
			2)We add the valid line to the file
			3)Notify user that his line added to the file successfully (in line x)*/

			(*countLines)++;
			fprintf(fptr, "\n%s,%s,%s,%s,%.2f,%s", node->FirstName, node->LastName, node->ID, node->PhoneNumber, node->Debt, node->Date);
			printf("\n\nYour set line added to the file successfully (in line %d)", *countLines);
		}
		else//This Detor is alredy in the linked list
		{
			//checks matching between the names of an exsist DetorList with the same Id.

			/*If node->FirstName != Missing and current->FirstName = Missing*/
			if ((strcmp(node->FirstName, "Missing")) && !(strcmp(current->FirstName, "Missing")))
			{
				strcpy(current->FirstName, node->FirstName);
			}
			/*If node->FirstName != Missing, and current->FirstName != Missing, and their names are diffrent*/
			else if(strcmp(node->FirstName, "Missing") && strcmp(current->FirstName, "Missing") && strcmp(node->FirstName, current->FirstName))
			{
				printf("\nError, The first name does not match the name that is already exists in the file with the same ID.\n");
				goto free;
			}

			if ((strcmp(node->LastName, "Missing")) && !(strcmp(current->LastName, "Missing")))
			{
				strcpy(current->LastName, node->LastName);
			}
			/*If node->FirstName != Missing, and current->FirstName != Missing, and their names are diffrent*/
			else if (strcmp(node->LastName, "Missing") && strcmp(current->LastName, "Missing") && strcmp(node->LastName, current->LastName))
			{
				printf("\nError, The last name does not match the name that is already exists in the file with the same ID.\n");
				goto free;
			}
			else//The names are matchinig.
			{/*1)Increasing the count lines by one
			   2)We add the valid line to the file
			   3)Notify user that his line added to the file successfully (in line x)*/
				(*countLines)++;
				fprintf(fptr, "\n%s,%s,%s,%s,%.2f,%s", node->FirstName, node->LastName, node->ID, node->PhoneNumber, node->Debt, node->Date);
				printf("\n\nYour set line added to the file successfully (in line %d)", *countLines);
				//then we update the TotalSum for our list.
				//and update firstDetsDate to the oldest date for our list.
				//as well we free all the temp inculding all is dynamic fields
				strcpy(current->PhoneNumber, node->PhoneNumber);
				current->Debt += node->Debt;
				/*The function olderDate return the int who's date is older
				then if temp->FirstDebtsDate is older date we copy him
				to the linked list in the field of the date
				otherwise we do nothing*/
				if (!strcmp(node->Date, "Missing"))
					strcpy(current->Date, "Missing");
				else if (!strcmp(node->Date, "Invalid") && strcmp(current->Date, "Missing"))
					strcpy(current->Date, "Invalid");
				else if(strcmp(current->Date, "Missing") && strcmp(current->Date, "Invalid"))
				{
					if(checkEarlierDate(node->Date, current->Date) == -1)
						strcpy(current->Date, node->Date);
				}
				/*Now we search the place for current to link it in the appropriate order*/
				if (*head == current)//i.e head is alredy pointinig on the node(because it Total Debt was the smallest debt)
				{
					prev = (*head)->next;
					if (current->Debt <= prev->Debt)
						goto free;
					else
					{
						*head = prev;
						current->next = prev->next;
						prev->next = current;
					}
				}
				prev = after = temp1 = temp2 = *head;
				/*In case that current->totalDebt < head
				So we need to update the head as well to point on current*/
				if(prev->Debt > current->Debt)//current = node from earlier
				{
					while (after->next != current)
						after = after->next;
					after->next = current->next;
					current->next = prev;
					*head = current;
				}
				/*In case that current->totalDebt > head*/
				else
				{
					// this while is also for the else ahead
					while (prev->next != current)
						prev = prev->next;
					if (prev->Debt > current->Debt)//primary case
					{
						while (temp1->Debt < current->Debt && temp1->next != prev)
							temp1 = temp1->next;
						if (temp1->next == prev)
						{
							prev->next = current->next;
							current->next = prev;
							temp1->next = current;
						}
						else
						{
							while (temp2->next != temp1)
								temp2 = temp2->next;
							prev->next = current->next;
							current->next = temp1;
							temp2->next = current;
						}

					}
					else if (prev->Debt < current->Debt)//primery case 
					{//here we need to check if the node after cuurrent smaller than current (but in case that prev equal to current so for shur the node after is ok
						after = current->next;
						if (after == NULL)
						{
							goto free;
						}
						if (current->Debt > after->Debt)
						{
							if (after->next == NULL)
							{
								prev->next = after;
								after->next = current;
								current->next = NULL;
							}
							//after->next != NULL
							else
							{
								temp1 = after->next;
								while (current->Debt > temp1->Debt && temp1->next != NULL)
									temp1 = temp1->next;
								if (temp1->next == NULL)
								{
									prev->next = after;
									temp1->next = current;
									current->next = NULL;
								}
								else
								{
									while (temp2->next != temp1)
										temp2 = temp2->next;
									prev->next = after;
									temp2->next = current;
									current->next = temp1;
								}
							}
						}
					}
				}
			}
		free:
			freeOneDebtor(node);
		}
	}
}

void freeOneDebtor(Debtor* debtor)
{
	if (debtor->FirstName != NULL)
		free(debtor->FirstName);
	if (debtor->LastName != NULL)
		free(debtor->LastName);
	if (debtor != NULL);
		free(debtor);
}

void freeAllDebtors(Debtor* head)
{
	Debtor* current = head;
	while (current != NULL)
	{
		head = head->next;
		freeOneDebtor(current);
		current = head;
	}
}