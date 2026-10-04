

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INITIAL_CAPACITY 5
#define MAX_INPUT 1000

/* Dynamic array of strings */
char **lines = NULL;
int lineCount = 0;
int capacity = INITIAL_CAPACITY;


/* --------------------------------------------------
   Remove newline from a string
   -------------------------------------------------- */
void removeNewline(char *str)
{
    str[strcspn(str, "\n")] = '\0';
}


/* --------------------------------------------------
   Initialize document
   -------------------------------------------------- */
void initializeDocument()
{
    lines = (char **)malloc(capacity * sizeof(char *));

    if (lines == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
}


/* --------------------------------------------------
   Increase array capacity using realloc()
   -------------------------------------------------- */
void increaseCapacity()
{
    if (lineCount >= capacity)
    {
        capacity = capacity * 2;

        char **temp = (char **)realloc(
            lines,
            capacity * sizeof(char *)
        );

        if (temp == NULL)
        {
            printf("Memory reallocation failed.\n");
            exit(1);
        }

        lines = temp;
    }
}


/* --------------------------------------------------
   INSERT
   Insert a new line at a given position
   -------------------------------------------------- */
void insertLine()
{
    int position;
    char input[MAX_INPUT];

    printf("\nEnter line number to insert (1 to %d): ", lineCount + 1);
    scanf("%d", &position);
    getchar();

    if (position < 1 || position > lineCount + 1)
    {
        printf("Invalid line number.\n");
        return;
    }

    printf("Enter text: ");
    fgets(input, MAX_INPUT, stdin);
    removeNewline(input);

    /* Increase capacity if required */
    increaseCapacity();

    /* Shift lines to the right */
    for (int i = lineCount; i >= position; i--)
    {
        lines[i] = lines[i - 1];
    }

    /* Allocate memory for new line */
    lines[position - 1] =
        (char *)malloc((strlen(input) + 1) * sizeof(char));

    if (lines[position - 1] == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    strcpy(lines[position - 1], input);

    lineCount++;

    printf("Line inserted successfully.\n");
}


/* --------------------------------------------------
   DELETE
   Delete a line from document
   -------------------------------------------------- */
void deleteLine()
{
    int position;

    if (lineCount == 0)
    {
        printf("\nDocument is empty. Nothing to delete.\n");
        return;
    }

    printf("\nEnter line number to delete (1 to %d): ", lineCount);
    scanf("%d", &position);
    getchar();

    if (position < 1 || position > lineCount)
    {
        printf("Invalid line number.\n");
        return;
    }

    /* Free memory of selected line */
    free(lines[position - 1]);

    /* Shift remaining lines to the left */
    for (int i = position - 1; i < lineCount - 1; i++)
    {
        lines[i] = lines[i + 1];
    }

    lineCount--;

    printf("Line deleted successfully.\n");
}


/* --------------------------------------------------
   DISPLAY
   Display complete document
   -------------------------------------------------- */
void displayDocument()
{
    if (lineCount == 0)
    {
        printf("\nDocument is empty.\n");
        return;
    }

    printf("\n========== DOCUMENT ==========\n");

    for (int i = 0; i < lineCount; i++)
    {
        printf("%d. %s\n", i + 1, lines[i]);
    }

    printf("==============================\n");
}


/* --------------------------------------------------
   SAVE
   Save document to a text file
   -------------------------------------------------- */
void saveFile()
{
    char filename[100];

    printf("\nEnter filename to save: ");
    scanf("%99s", filename);
    getchar();

    FILE *file = fopen(filename, "w");

    if (file == NULL)
    {
        printf("Unable to open file.\n");
        return;
    }

    for (int i = 0; i < lineCount; i++)
    {
        fprintf(file, "%s\n", lines[i]);
    }

    fclose(file);

    printf("Document saved successfully to '%s'.\n", filename);
}


/* --------------------------------------------------
   LOAD
   Load document from a text file
   -------------------------------------------------- */
void loadFile()
{
    char filename[100];
    char buffer[MAX_INPUT];

    printf("\nEnter filename to load: ");
    scanf("%99s", filename);
    getchar();

    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Unable to open file.\n");
        return;
    }

    /* Clear existing document */
    for (int i = 0; i < lineCount; i++)
    {
        free(lines[i]);
    }

    lineCount = 0;

    /* Read file line by line */
    while (fgets(buffer, MAX_INPUT, file) != NULL)
    {
        removeNewline(buffer);

        increaseCapacity();

        lines[lineCount] =
            (char *)malloc((strlen(buffer) + 1) * sizeof(char));

        if (lines[lineCount] == NULL)
        {
            printf("Memory allocation failed.\n");
            fclose(file);
            return;
        }

        strcpy(lines[lineCount], buffer);

        lineCount++;
    }

    fclose(file);

    printf("Document loaded successfully from '%s'.\n", filename);
}


/* --------------------------------------------------
   SEARCH
   Search for a word/text in document
   -------------------------------------------------- */
void searchText()
{
    char search[MAX_INPUT];
    int found = 0;

    if (lineCount == 0)
    {
        printf("\nDocument is empty.\n");
        return;
    }

    printf("\nEnter text to search: ");
    fgets(search, MAX_INPUT, stdin);
    removeNewline(search);

    if (strlen(search) == 0)
    {
        printf("Search text cannot be empty.\n");
        return;
    }

    printf("\nSearch Results:\n");

    for (int i = 0; i < lineCount; i++)
    {
        if (strstr(lines[i], search) != NULL)
        {
            printf("Found in line %d: %s\n",
                   i + 1,
                   lines[i]);

            found = 1;
        }
    }

    if (!found)
    {
        printf("Text not found.\n");
    }
}


/* --------------------------------------------------
   COUNT
   Count lines and words
   -------------------------------------------------- */
void countDocument()
{
    int wordCount = 0;

    for (int i = 0; i < lineCount; i++)
    {
        int inWord = 0;

        for (int j = 0; lines[i][j] != '\0'; j++)
        {
            if (!isspace((unsigned char)lines[i][j]))
            {
                if (!inWord)
                {
                    wordCount++;
                    inWord = 1;
                }
            }
            else
            {
                inWord = 0;
            }
        }
    }

    printf("\n========== COUNT ==========\n");
    printf("Number of lines : %d\n", lineCount);
    printf("Number of words : %d\n", wordCount);
    printf("===========================\n");
} 
/* --------------------------------------------------
   HELP
   Display available commands
   -------------------------------------------------- */
void showHelp()
{
    printf("\n========== HELP ==========\n");

    printf("INSERT  - Insert a new line\n");
    printf("DELETE  - Delete an existing line\n");
    printf("DISPLAY - Display the document\n");
    printf("SAVE    - Save document to a file\n");
    printf("LOAD    - Load document from a file\n");
    printf("SEARCH  - Search text in the document\n");
    printf("COUNT   - Count lines and words\n");
    printf("HELP    - Display available commands\n");
    printf("EXIT    - Exit the editor\n");

    printf("==========================\n");
}


/* --------------------------------------------------
   FREE DOCUMENT
   Release all dynamically allocated memory
   -------------------------------------------------- */
void freeDocument()
{
    for (int i = 0; i < lineCount; i++)
    {
        free(lines[i]);
    }

    free(lines);

    lines = NULL;
    lineCount = 0;
}


/* --------------------------------------------------
   MAIN FUNCTION
   -------------------------------------------------- */
int main()
{
    char command[20];

    initializeDocument();

    printf("=====================================\n");
    printf("       SIMPLE LINE EDITOR IN C       \n");
    printf("=====================================\n");

    printf("Type HELP to see available commands.\n");

    while (1)
    {
        printf("\nEDITOR > ");
        scanf("%19s", command);
        getchar();

        /* Convert command to uppercase */
        for (int i = 0; command[i] != '\0'; i++)
        {
            command[i] =
                (char)toupper((unsigned char)command[i]);
        }

        if (strcmp(command, "INSERT") == 0)
        {
            insertLine();
        }
        else if (strcmp(command, "DELETE") == 0)
        {
            deleteLine();
        }
        else if (strcmp(command, "DISPLAY") == 0)
        {
            displayDocument();
        }
        else if (strcmp(command, "SAVE") == 0)
        {
            saveFile();
        }
        else if (strcmp(command, "LOAD") == 0)
        {
            loadFile();
        }
        else if (strcmp(command, "SEARCH") == 0)
        {
            searchText();
        }
        else if (strcmp(command, "COUNT") == 0)
        {
            countDocument();
        }
        else if (strcmp(command, "HELP") == 0)
        {
            showHelp();
        }
        else if (strcmp(command, "EXIT") == 0)
        {
            printf("\nExiting editor...\n");

            freeDocument();

            printf("Memory released successfully.\n");
            printf("Thank you for using the Line Editor!\n");

            break;
        }
        else
        {
            printf("Unknown command. Type HELP for commands.\n");
        }
    }

    return 0;
}