#define _CRT_SECURE_NO_WARNINGS
#include "MainHeader.h"

void buildNodeFile(FILE* file_ptr, Debtor** head, int* countLines)
{
	int flag, length,i;
	char date[11];
	char line[MAX_LINE];
	char copyLine[MAX_LINE];/*Using to check if fileds are empty between the commas*/
	char delimiter[2] = ",";
	char* token = NULL,*del;
	Debtor* temp;

	while (fgets(line, MAX_LINE, file_ptr) != NULL)
	{
		length = strlen(line);
		if (line[length - 1] == '\n')
			line[length - 1] = '\0';
		(*countLines)++;
		flag = 0;
		del = NULL;//reset del for the new line
		int count = countDelimiters(line, ',');
		if (!strcmp(line, ""))
		{
			printf("(An empty line in line %d) --> (Please ERASE!! that line)\n\n", *countLines);
			continue;
		}
		else if (count > 5)
		{
			printf("(Error in line %d) --> Too many arguments.\nthe program didn't get the line\n(Please make shure that evry line, contains exactly 6 arguments)\n", *countLines);
			continue;
		}
		else if (count < 5)
		{
			printf("(Error in line %d) --> Too few arguments.\nthe program didn't get the line.\n(Please make shure that evry line, contains exactly 6 arguments)\n", *countLines);
			continue;
		}
		temp = (Debtor*)malloc(sizeof(Debtor));
		if (temp == NULL)//check if the allocation failed
		{
			Error_Msg("Memmory allocation failed!!. (Try closing other programs that are currently running.\nIf you are still having a problem try restarting your computer.)\n");
		}
		strcpy(copyLine, line);
		/*Get the first token(the First Name)*/
		if (line[0] == ',')
		{/*Means that the first field is empty*/
			printf("\n(Warning in line %d) --> The First Name is missing.\nthe program got the line\n(Please add the First Name in the file)\n", *countLines);
			temp->FirstName = (char*)malloc(8);
			strcpy(temp->FirstName, "Missing");
			flag = 1;
		}
		else
		{
			token = strtok(line, delimiter);
			if (!checkAlphabet(token))
			{
				printf("\n(Warning in line %d) --> The First Name is Unknown Characters.\nthe program got the line\n(Please correct the First Name in the file)\n", *countLines);
				temp->FirstName = (char*)malloc(13);
				strcpy(temp->FirstName, "UnknownChars");
			}
			else
			{
				length = strlen(token);
				temp->FirstName = (char*)malloc(length + 1);
				strcpy(temp->FirstName, token);
			}
		}
		/*for the Last Name*/
		del = strchr(copyLine, ',');
		/*del gets evry time a ',' from copyLine.
		And then he advances one char after the ','
		to see if ther's right away another ','.
		If so it means that we have empty field.
		So we dont't use for this field the function strtok*/
		del = strchr(del, ',');
		del++;
		if (*del == ',')//if LaststName,Missing(So we don't use strtok(line))
		{
			printf("\n(Warning in line %d) --> The Last Name is missing.\nthe program got the line\n(Please add the Last Name in the file)\n", *countLines);
			temp->LastName = (char*)malloc(8);
			strcpy(temp->LastName, "Missing");
		}
		else
		{
			if (flag)//Meaning we didn't use "line" for strtok
			{
				token = strtok(line, delimiter);
				flag = 0;
			}
			else
				token = strtok(NULL, delimiter);
			if (!checkAlphabet(token))
			{
				printf("\n(Warning in line %d) --> The Last Name is Unknown Characters.\nthe program got the line\n(Please correct the Last Name in the file)\n", *countLines);
				temp->LastName = (char*)malloc(13);
				strcpy(temp->LastName, "UnknownChars");
			}
			else
			{
				length = strlen(token);
				temp->LastName = (char*)malloc((length + 1));
				strcpy(temp->LastName, token);
			}
		}
		/*for the ID*/
		del = strchr(del, ',');
		del++;
		if (*del == ',')//i.e Id's field is empty
		{
			printf("\n(Error in line %d) --> The Id Missing.\nthe program didn't get the line.\n(Please add the Id in file)\n\n", *countLines);
			del = NULL;
			continue;
		}
		//(we don't need the else scope. But for ease of reading I used it)
		else//i.e Id's field is not empty
		{
			if (flag)//i.e stil we didn't use "line" for strtok
				token = strtok(line, delimiter);
			else
				token = strtok(NULL, delimiter);
		}
		if (!checkSizeAndDigits(token, 9))
		{
			printf("\n(Error in line %d) --> The Id should be exactly 9 digits(not letters).\nthe program didn't get the line.\n(Please make shure that evry Id in file, contains exactly 9 digits only)\n\n", *countLines);
			freeOneDebtor(temp);
			continue;
		}
		strcpy(temp->ID, token);

		/*for the TelphonNumber*/
		del = strchr(del, ',');
		del++;
		if (*del == ',')
		{
			printf("\n(Warning Missing Telphon Number in line % d) -- > The program got the line.\n(Please add the Telphon Number in the file)\n\n", *countLines);
			strcpy(temp->TelphonNumber, "Missing");
		}
		else
		{/*Here we don't need to check that flag == 0.
		Because if indeed flag was 0 so it means that the Id's field
		was empty and hence our line wasn't accepted at all.
		Because if Id missing we would continue to the next line*/
			token = strtok(NULL, delimiter);
			if (*token != '0')
			{
				printf("\n(Warning Invalid Telphon Number in line % d) -- > The Telphon Number should start with digit 0.\nthe program got the line(Not the Telphon number).\n", *countLines);
				strcpy(temp->TelphonNumber, "Invalid");
			}
			else if (!checkSizeAndDigits(token, 10))
			{
				printf("\n(Warning Invalid Telphon Number in line % d) -- > The Telphon Number should be exactly 10 digits(not leters).\nthe program got the line(Not the Telphon number).\n", *countLines);
				strcpy(temp->TelphonNumber, "Invalid");
			}
			else
				strcpy(temp->TelphonNumber, token);
		}
		/*for the amountDebt*/
		del = strchr(del, ',');
		del++;
		if (*del == ',')
		{
			printf("\n(Error in line %d) --> The amount debt is missinig.\nthe program didn't get the line\n(Please add the debt in the file)\n", *countLines);
			freeOneDebtor(temp);
			continue;
		}
		token = strtok(NULL, delimiter);
		if (!(isCorrectAmount(token)))
		{
			printf("\n(Error in line %d) --> The amount debt is incorrect.\nthe program didn't get the line\n(Please fix the debt in the file)\n", *countLines);
			freeOneDebtor(temp);
			continue;
		}
		temp->Debt = atof(token);

		/*for the dateDebt*/
		token = strtok(NULL, delimiter);
		if (token == NULL)
		{
			printf("\n(Warning in line %d) --> The debt date is missing.\nthe program got the line\n(Please add the debt date in the file)\n", *countLines);
			strcpy(temp->Date, "Missing");
		}
		else
		{
			if (strstr(token, " ") || strstr(token, "\t"))
			{
				printf("\n(Error in line %d) --> Irrelevant words at the line end.\nthe program didn't get the line.\n(Please delete these words)\n\n", *countLines);
				freeOneDebtor(temp);
				continue;
			}
			for (i = 0; i < 10; i++)
				date[i] = token[i];
			date[i] = '\0';
			if(!checkDateValidation(token))
			{
				printf("\n(Warning Invalid Date in line % d) -- > The Date should be in this format  _ _/_ _/_ _ _ _, and with days from 01 to 12 and month from 01 to 31.\nthe program got the line(Not the Date).\n(Please correct the date in the file\n", *countLines);
				strcpy(temp->Date, "Invalid");
			}
			else
				strcpy(temp->Date, date);
		}
		//---------------------------------------------------
		/*Now we linking the new Detor to the link list*/
		//---------------------------------------------------
		addNodeFileToList(head, temp, countLines);
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
			if (strcmp(node->FirstName, current->FirstName) || strcmp(node->LastName, current->LastName))
			{
				if (strcmp(node->FirstName, current->FirstName))//if not 0 means they are not equal
					printf("\n(Error in line %d) --> The first name does not match the name that is already exists in the file with the same ID.\n", *lineNumber);
				if (strcmp(node->LastName, current->LastName))
					printf("\n(Error in line %d) --> The last name does not match the name that is already exists in the file with the same ID.\n", *lineNumber);
				printf("The program didn't get this line. (Please correct the names in the file).\n");
				freeOneDebtor(node);
			}
			else//The names are matchinig.
			{//so we update the TotalSum.
			//and update firstDetsDate to the oldest date.
			//as well we free all the temp inculding all is dynamic fields
				strcpy(current->TelphonNumber, node->TelphonNumber);
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
				else if(strcmp(current->Date, "Missing") && strcmp(current->Date, "Invalid"))
				{
					if (checkEarlierDate(node->Date, current->Date) == -1)
						strcpy(current->Date, node->Date);
				}
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
	temp->FirstName = (char*)malloc(strlen(current->FirstName)+1);
	strcpy(temp->FirstName, current->FirstName);
	temp->LastName = (char*)malloc(strlen(current->LastName) + 1);
	strcpy(temp->LastName, current->LastName);
	strcpy(temp->ID, current->ID);
	strcpy(temp->TelphonNumber, current->TelphonNumber);
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
				printf("\Warning, The phone number should start with digit \"0\"\n");
				strcpy(temp->TelphonNumber, "Invalid");
			}
			else if (!checkSizeAndDigits(token, 10))
			{
				printf("\Warning, The phone number should be exactly 9 digits\n");
				strcpy(temp->TelphonNumber, "Invalid");
			}
			else
			{
				strcpy(temp->TelphonNumber, token);
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
	if (temp->TelphonNumber[0] == 0)
	{
		strcpy(temp->TelphonNumber, "Missing");
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
		fprintf(fptr, "\n%s,%s,%s,%s,%.2f,%s", node->FirstName, node->LastName, node->ID, node->TelphonNumber, node->Debt, node->Date);
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
			fprintf(fptr, "\n%s,%s,%s,%s,%.2f,%s", node->FirstName, node->LastName, node->ID, node->TelphonNumber, node->Debt, node->Date);
			printf("\n\nYour set line added to the file successfully (in line %d)", *countLines);
		}
		else//This Detor is alredy in the linked list
		{
			//checks matching between the names of an exsist DetorList with the same Id. 
			if (strcmp(node->FirstName, current->FirstName) || strcmp(node->LastName, current->LastName))
			{
				if (strcmp(node->FirstName, current->FirstName))//if not 0 means they are not equal
					printf("\nError, The first name does not match the name that is already exists in the file with the same ID.\n");
				if (strcmp(node->LastName, current->LastName))
					printf("\nError, The last name does not match the name that is already exists in the file with the same ID.\n");
				printf("\nThe line was not added to the file.\n");
				goto free;
			}
			else//The names are matchinig.
			{/*1)Increasing the count lines by one
			   2)We add the valid line to the file
			   3)Notify user that his line added to the file successfully (in line x)*/
				(*countLines)++;
				fprintf(fptr, "\n%s,%s,%s,%s,%.2f,%s", node->FirstName, node->LastName, node->ID, node->TelphonNumber, node->Debt, node->Date);
				printf("\n\nYour set line added to the file successfully (in line %d)", *countLines);
				//then we update the TotalSum for our list.
				//and update firstDetsDate to the oldest date for our list.
				//as well we free all the temp inculding all is dynamic fields
				strcpy(current->TelphonNumber, node->TelphonNumber);
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
				/*Now we search the place for current if needed*/
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
					if (prev->Debt > current->Debt)//primery case
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
							else if (after->next != NULL)
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
									temp2->next = temp1;
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