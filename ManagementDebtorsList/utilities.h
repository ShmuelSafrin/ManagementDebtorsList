#include "MainHeader.h"

/*When we try to open the file unsuccessfully
Then we notify to user and suggest him how
solve the problem then we exit the program*/
void Error_Msg(char* msg);

/*print the sorted debtors link list.
The print will be as follow,
for each debtor one line with his private details,
his totalTebt,and his earliest date of his debts.*/
void print(Debtor*, int);

/*The order of the print lines will be by ascending order
i.e. the debtor with the smallest tebt will be printed first
and the debtor with the biggest debt will be printed last*/
/*Note sorts the linked list by changing next pointers (not data) */
void MergeSort(Debtor** headRef);
Debtor* SortedMerge(Debtor*, Debtor*);
/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves,
and return the two lists using the reference parameters.
If the length is odd, the extra node should go in the front list.
Uses the fast/slow pointer strategy.*/
void FrontBackSplit(Debtor*);
Debtor** frontRef(Debtor**);