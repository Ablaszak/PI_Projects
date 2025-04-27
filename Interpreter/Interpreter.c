#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_ID_LEN 64
#define MAX_IDS 1024
#define MAX_LINE 128

void find_comments(int*, int*);
int find_idents(void);

char identifiers[MAX_IDS][MAX_ID_LEN];

const char *keywords[] = {
        "auto", "break", "case", "char",
        "const", "continue", "default", "do",
        "double", "else", "enum", "extern",
        "float", "for", "goto", "if",
        "int", "long", "register", "return",
        "short", "signed", "sizeof", "static",
        "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while",
        NULL
};
int is_in_arrays(char* word, char array_ids[][MAX_ID_LEN]) // bool
{
    int i = 0;
    while(keywords[i] != NULL)
    {
        if(strcmp(word, keywords[i]) == 0)
            return 1;
        i++;
    }
    i = 0;
    while(i < MAX_IDS)
    {
        if(strcmp(word, array_ids[i]) == 0)
            return 1;
        i++;
    }
    return 0;
}

// function deletes all strings ("this stuff") and comments (strong version)
void prepere_line(char* line, int* inside, int* inside_strong, int strong)
{
    size_t n = strlen(line);

    char fragment[3]; // Used for strong part
    fragment[2] = '\0';

    for(size_t i=0; i<n; i++)
    {
        if(*inside_strong == 0)
        {
            if(line[i] == '"')
                *inside = (*inside + 1) % 2; // Switches inside value
    
            if(*inside == 1)
                line[i] = ' ';
        }

        if(*inside == 0 && strong == 0 && i>0)
        {
            fragment[0] = line[i-1];
            fragment[1] = line[i];

            if(strcmp(fragment, "//") == 0) // We are done with this line
                return;

            if(*inside_strong == 0 && strcmp(fragment, "/*") == 0) // Beggining of block comment
            {
                *inside_strong = 1;
            }
            else if(*inside_strong == 1 && strcmp(fragment, "*/") == 0) // End of block comment
            {
                *inside_strong = 0;
            }
            // At this point idgaf about /*/ situation

        }
        if(*inside == 0 && strong == 1 && i>0) // Strong part
        {
            fragment[0] = line[i-1];
            fragment[1] = line[i];

            if(*inside_strong == 0 && strcmp(fragment, "//") == 0)
            { // Now we have to delete the rest of the line
                for(size_t k = i-1; k<n; k++)
                    line[k] = ' ';
                return;
            }

            if(*inside_strong == 0 && strcmp(fragment, "/*") == 0) // Beggining of block comment
            {
                *inside_strong = 1;
                line[i-1] = ' ';
                line[i] = ' ';
            }
            else if(*inside_strong == 1 && strcmp(fragment, "*/") == 0) // End of block comment
            {
                *inside_strong = 0;
                line[i-1] = ' ';
                line[i] = ' ';

                if(i >= 2)
                    line[i-2] = ' '; // It has to be here
            }

            // Deleting the text inside block comment:
            if(*inside_strong == 1 && i>1)
                line[i-2] = ' '; // I have to delete characters with a delay, because otherwise it would delete the end of comment ( */ )
        }
    }
}
int comment(char* line, char* fragment, int* in_comment, int* block)
{
    //printf("%s\n", fragment);
    switch(*in_comment)
    {
        case 0:
            if(strcmp(fragment, "/*") == 0)
            {
                *in_comment = 1;
                *block += 1;
                line[1] = '0'; // To prevent situation like "/*/"
            }
            else
            {
                //printf("%s %d\n", fragment, strcmp(fragment, "//"));
                if(strcmp(fragment, "//") == 0)
                    return 1;
            }
            return 0;

        case 1:
            if(strcmp(fragment, "*/") == 0)
            {
                *in_comment = 0;
                line[1] = '0'; // To prevent situation like "*//"
            }
            return 0;
    }
    return 0;
}
void find_comments(int *line_comment_counter, int *block_comment_counter) 
{
    int trash_for_function = 0; // Trust me
    int in_comment = 0; // bool
    int incom_copy = in_comment;
    size_t len;
    char line[MAX_LINE];
    char fragment[3]; // [char, char, \0]
    int theend = 0;

    *line_comment_counter = 0;
    *block_comment_counter = 0;

    while(fgets(line, MAX_LINE, stdin) != NULL && theend == 0)
    {
        len = strlen(line);
        if(line[len-1] == EOF)
            theend = 1;

        incom_copy = in_comment;
        prepere_line(line, &trash_for_function, &incom_copy, 0);
        //printf("%s\n", line);
        
        // Making copy of 2 firts digits in line:
        strncpy(fragment, line, 2);
        fragment[2] = '\0';

        // Checking beggining of the line
        if(comment(line, fragment, &in_comment, block_comment_counter) == 1)
        {
            *line_comment_counter += 1;
        }
        // Checking the rest of the line:
        else
        {
            for(size_t i=2; i<len; i++)
            {
                // Stepping forward:
                fragment[0] = fragment[1];
                fragment[1] = line[i];
                // Checking:
                *line_comment_counter += comment(line, fragment, &in_comment, block_comment_counter);
            }
        }
    }
}

void append(char* line, char c)
{
    while(*line++);
    *(line-1) = c;
    *line = '\0';
}

int find_idents(void) 
{
    char ids[MAX_IDS][MAX_ID_LEN];
    int idit = 0; // id iterator
    for(int i=0; i<MAX_IDS; i++)
        strcpy(ids[i], "");
    
    char line[MAX_LINE];
    int inside1 = 0;
    int inside2 = 0;
    size_t i=0;
    size_t n=0;
    char word[MAX_ID_LEN];
    int theend = 0; //bool

    while(fgets(line, MAX_LINE, stdin) != NULL && theend == 0)
    {
        i = 0;
        n = strlen(line);
        if(line[n-1] == EOF)
            theend = 1;

        prepere_line(line, &inside1, &inside2, 1);
        //printf("%s\n", line);
        while(i < n)
        {
            strcpy(word, "");
            while(i < n && (isalnum(line[i]) || line[i] == '_'))
            {
                append(word, line[i]);
                i++;
            }
            if(isalpha(word[0]) || word[0] == '_')
                if(is_in_arrays(word, ids) == 0)
                {
                    //printf("\n%s\n", word);
                    strcpy(ids[idit], word);
                    idit++;
                }
            i++;
        }
    }
    return idit;
    
}

int read_int() {
        char line[MAX_LINE];
        fgets(line, MAX_LINE, stdin); // to get the whole line
        return (int)strtol(line, NULL, 10);
}

int main(void) {
        int line_comment_counter, block_comment_counter;
        const int to_do = read_int();
        switch (to_do) {
                case 1:
                        find_comments(&line_comment_counter, &block_comment_counter);
                        printf("%d %d\n", block_comment_counter, line_comment_counter);
                        break;
                case 2:
                        printf("%d\n", find_idents());
                        break;
                default:
                        printf("NOTHING TO DO FOR %d\n", to_do);
                        break;
        }
        
        return 0;
}
