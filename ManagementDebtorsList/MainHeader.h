
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "validations.h"
#include "buildDeleteFuncs.h"
#include "userFuncs.h"
#include "utilities.h"
#define MAX_LINE 200
char FileName[] = "DebtorsList.csv";


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
