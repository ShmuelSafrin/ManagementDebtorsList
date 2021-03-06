#define _CRT_SECURE_NO_WARNINGS
#include "MainHeader.h"

int checkAlphabet(char* name)
{
	while (*name)
	{
		if ((*name < 'A' || *name > 'Z') && (*name < 'a' || *name > 'z'))
			return 0;
		name++;
	}
	return 1;
}

int checkSizeAndDigits(char* str, int size)
{
	if (strlen(str) != size)
		return 0;
	while (*str)
	{
		if (*str < '0' || *str++ > '9')
			return 0;
	}
	return 1;
}


int countDelimiters(char* str, char delim)
{
	int count = 0;
	while (*str)
	{
		if (*str++ == delim)
			count++;
	}
	return count;
}
int checkFormatLine(char* line,int *lineNumber)
{
	int count = countDelimiters(line, ',');
	if (count == 0)
		return 0;
	if (count != 5)
	{
		printf("\n(Error in line %d) --> Incorrect format line(need 5 commas).\nThe line was not accepted in the program.\n",*lineNumber);
		return 0;
	}
	return 1;
}
int isCorrectAmount(char* token)
{
	char* str = token;
	int len = strlen(str);
	if (countDelimiters(str, '.') > 1)
	{
		free(str);
		return 0;
	}
	if ((*str != '-') && (*str < '0' || *str > '9'))
	{
		free(str);
		return 0;
	}
	if (str[len - 1] < '0' || str[len - 1] > '9')
	{
		free(str);
		return 0;
	}
	str++;
	while (*(str + 1))
	{
		if ((*str < '0' || *str > '9') && (*str != '.'))
		{
			free(str);
			return 0;
		}
		str++;
	}
	return 1;
}

int checkDateValidation(char* date)
{
	if (countDelimiters(date, '/') != 2)
		return 0;
	date = strtok(date, "/");
	if (strcmp(date, "01") == -1)
		return 0;
	if (strcmp(date, "31") == 1)
		return 0;
	date = strtok(NULL, "/");
	if (strcmp(date, "01") == -1)
		return 0;
	if (strcmp(date, "12") == 1)
		return 0;
	date = strtok(NULL, "/");
	if (!checkSizeAndDigits(date, 4))
		return 0;
	return 1;
}

int checkEarlierDate(char* str1, char* str2)
{
	char container[11];
	strcpy(container, str1);

	char temp1[9];
	char temp2[9];

	int result;
	char day[3];
	char month[3];
	char year[5];
	char* token;

	token = strtok(container, "/");
	strcpy(day, token);

	token = strtok(NULL, "/");
	strcpy(month, token);

	token = strtok(NULL, "/");
	strcpy(year, token);

	strcpy(temp1, year);
	strcat(temp1, month);
	strcat(temp1, day);
	//-----------Again for str2------------

	strcpy(container, str2);

	token = strtok(container, "/");
	strcpy(day, token);

	token = strtok(NULL, "/");
	strcpy(month, token);

	token = strtok(NULL, "/");
	strcpy(year, token);

	strcpy(temp2, year);
	strcat(temp2, month);
	strcat(temp2, day);

	return strcmp(temp1, temp2);;
}

int checkUnnecessaryInputAtQueryEnd()
{
	char end[20];
	fgets(end, 20, stdin);
	char* ptr = end;
	while (*ptr != '\n')
	{
		if (*ptr != ' ' && *ptr != '\t')
		{
			printf("Unnecessary words/letters at the end of your input"
				"\nPlease re-enter query again.");
			return 0;
		}
		ptr++;
	}
	return 1;
}

char* stringToLower(char *word)
{
	int i = 0;
	char letter;
	char lowerWord[20];
	while(word[i])
	{
		letter = tolower(word[i]);
		lowerWord[i] = letter;
		i++;
	}
	lowerWord[i] = '\0';
	return lowerWord;
}



