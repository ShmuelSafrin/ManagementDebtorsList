
/*This function gets the pointer to the file and
the pointer to the linked list and the number lines
of the file(which is zero at the begining)
In order to notify user, if problemtic field will be found.
to know in which line it is. The function gets
line by line from the file after geting each line
it checks that there are 5 commas and then checks
field by field in all fields if they are
missing or invalid.It gets the line anyway.
and prints warning with details of the problem
and the line of it Apart from the ID number
and the amount of debt. it prints an error and does
not pick get this line.After each line it gets
and after the validations are performed on the line
and the craetion of the node for the line.
the function turns to the addNodeFileToList
function, which inserts the
node that it receives into the linked list.*/
void buildNodeFile(FILE*, Debtor**, int*);

/*This function receives the new node from function
buildNodeFile. and checks if such a node
already exists in the list according to the ID.
If not then she links it to the list from the head and
if there is already a node with such an ID then she checks
if the names are matching if not it notify an error
and free the new node it received otherwise
updates the debt and the earliest date on the existing
alredy node in the list and free the new node*/
void addNodeFileToList(Debtor**, Debtor*, int*);

/*When the user chooses to request a query.
Then this function is activated it gets the
nodes found suitable for the query and builds
a new node. It updates its fields according to
the node it received and then calls the
addNodeQueryToList function sends it the new node
to link it to the link list*/
void buildNodeQuery(Debtor**, Debtor**, Debtor*);

/*The function gets head and tail and the new node
created by the function buildNodeQuery
if the head == NULL then it updates the head and tail
to point to it otherwise it links the new node to the tail
i.e. to the end of the list.
(the reason the link is not made through the head
Because if the insertion would done through the head
we would got the linked list of the query sorted exactly upside down
i.e. in descending order and then we will have to run
a sorting function on the list. Because we get the new nodes in ascending
order. So if we insert from the tail it will be saved in ascending order
and we won't have to later sort the query list)*/
void addNodeQueryToList(Debtor** headQuery, Debtor** tailQuery, Debtor* node);

/*In fact this function is very similar to the function buildNodeFile
it accepts the line entered by the user and does validations checks
on each field then creates a new node with The user's fields
and sends the new node to the addNodeUserToList function
to link the new node to the list*/
void buildNodeUser(FILE*, Debtor**, int*);

/*In fact this function is very similar to the function addNodeFileToList
This function gets its arguments from the function buildNodeUser
Unlike the function addNodeFileToList it checks where to connect the new node
so that the list remains sorted and then links it in the proper place
if there is a node with the same ID but the names do not match
so it does not accept the user line and informs it and free the node
otherwise it increse by one the number of rows file by one
adds the user row to the file and informing him that the row
has been added to the file successfully and in which number row's file*/
void addNodeUserToList(FILE*, Debtor**, Debtor*, int*);

/*If after we got the debtore's namas(dynamically)
we see that either Id or debt are problematic
so we don't get the line we notify to user
and we free the alredy the allocated node*/
void freeOneDebtor(Debtor*);

/*free all structs(nodes) Debtor in the link list.
as well free the firstand the last names
in evry struct Debtor.*/
void freeAllDebtors(Debtor*);