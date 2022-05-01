
#include "MainHeader.h"

void Error_Msg(char* msg)
{
	printf("%s\n", msg);
	exit(1);
}

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
/* sorts the linked list by changing next pointers (not data) */
void MergeSort(Debtor** headRef)
{
	Debtor* head = *headRef;
	Debtor* a;
	Debtor* b;

	/* Base case(of the recursion) -- length 0 or 1 */
	if ((head == NULL) || (head->next == NULL)) {
		return;
	}
	/* Split head into 'a' and 'b' sublists */
	FrontBackSplit(head, &a, &b);

	/* Recursively sort the sublists */
	MergeSort(&a);
	MergeSort(&b);

	/* answer = merge the two sorted lists together */
	*headRef = SortedMerge(a, b);
}

Debtor* SortedMerge(Debtor* a, Debtor* b)
{
	Debtor* result = NULL;

	/* Base cases(This will be when the recursion gose back)*/
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);

	/* Pick either a or b, and recur */
	if (a->TotalDebt < b->TotalDebt) {
		result = a;
		result->next = SortedMerge(a->next, b);
	}
	else {
		result = b;
		result->next = SortedMerge(a, b->next);
	}
	return (result);
}

/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves,
	and return the two lists using the reference parameters.
	If the length is odd, the extra node should go in the front list.
	Uses the fast/slow pointer strategy.*/
void FrontBackSplit(Debtor* source,
	Debtor** frontRef, Debtor** backRef)
{
	Debtor* fast;
	Debtor* slow;
	slow = source;
	fast = source->next;

	/* Advance 'fast' two nodes, and advance 'slow' one node */
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL) {
			slow = slow->next;
			fast = fast->next;
		}
	}
	/* 'slow' is before the midpoint in the list, so split it in two
	at that point. */
	*frontRef = source;
	*backRef = slow->next;
	/*cutting the first half of the list from the seconf half one*/
	slow->next = NULL;
}