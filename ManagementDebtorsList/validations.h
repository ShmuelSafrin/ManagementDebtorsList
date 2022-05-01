typedef struct Debtor
{
	char* FirstName;
	char* LastName;
	char ID[10];//should be exactly 9 chars. Of digits only.
	char TelphonNumber[11];//should be exactly 10 chars.Digits only, And start with digit 0
	float TotalDebt;
	char FirstDebtsDate[11];
	struct DetorList* next;
}Debtor;


/*This function is for the fields of the first name and the last name
it checks that they contain only the letters of the alphabet
by passing on evry character of the name if a character is found
that is not an alphabet then it notify warning to user and instead
put in the name field "UnknownChars"*/
int checkAlphabet(char*);

/*This function goes over the string line
and each time it finds a given delimter character.
It increases the count by 1*/
int checkCountDelim(char*, char);

/*This function checkes proper size of chars, if not return 0.
then the func go through all the charecters in the string
checking if all charecter are digits.
If the function while it going on the string, finding a
non-digit character then it returns 0 immediately.
And if it finishes and does not find a non-digit
character then returns 1*/
int checkSizeAndDigits(char*, int);//return 1 if correct else return 0.

/*This function checks the (float)debt field which has only digits
or minus only at the beginning And that he has no more than one point
and that it is neither at the beginning nor at the end*/
int isCorrectAmount(char*);

/*The function calls the checkCountDelim function
and checks that there are exactly two slashes
Then cuts the date to day month and year
and checks that the day is not smaller than 01
and not larger than 31 and then checks
the month which is not smaller than 01
and not larger than 12 and then calls
the checkSizeAndDigits function to check
that the year is 4 digits*/
int checkDateValidation(char*);

/*This function cuts the strings according to the slash
and then assembles them back in reverse order
i.e. years before and so on. Then return the int of the function
strcmp to check who's date earlier*/
int checkEarlierDate(char* str1, char* str2);

/*Checks that there are no unnecessary words
in the user input if thre's it notifies error and does not accept the query
or if the user enter print or quit with unnecessary words after
if there are only spaces or tabs.
The program goes on to present the user's request.*/
int checkUnnecessaryWordsInputAtEnd();

/*Checks that there are no unnecessary words
if thre's it notifies error and does not accept the user line
if there are only spaces or tabs then it deletes them
and gets the user line set.*/
char* checkEndSet(char*);