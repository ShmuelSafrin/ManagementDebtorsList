/*
unsigned char column_index = 0;
char* column_p[MAX_COLUMN];
char line[] = "john,doe,123456789,-100";
char* column = strtok(line, ",");
while (column)
{
    if (strlen(column) < MAXFIELD) column_p[column_index] = column;
    column = strtok(NULL, ",");
    column_index++;
}
*/