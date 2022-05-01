/*print the sorted debtors link list.
The print will be as follow,
for each debtor one line with his private details,
his totalTebt,and his earliest date of his debts.*/
void print(Debtor*, int);

/*The function presents the user 3 options to  do, either query
or insert a new line into the file or print the updated sorted list
(including the lines the user entered into the file).
The function will work in a loop until the user enters the word "quit" and
then the program ends*/
void QueriesSetPrint(FILE*, Debtor*, int*);

/*The function gets a word by word from the query input.
Checks that the word is suitable and in the right sequense.
and that there are no unnecessary words in the query.
Then according to the specific query
goes over the linked list(which contains the file lines and user lines)
and when it finds a suitable node it turns to the buildDebtorAndList function.
to build a new node by coping the detalis that in the founded node.
To the new node.Then buildDebtorAndList turns to buildListQuery function
that builds a list from all the appropriate nodes that we created.
(If there are none, then the function prints a message to the user)
.Then queries turn to print function.and afterwards immediately
releases all the nodes of the list by turns to freeAllDebtors function*/
void queries(Debtor*);