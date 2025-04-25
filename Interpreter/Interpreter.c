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
        "unsigned", "void", "volatile", "while"
};

void find_comments(int *line_comment_counter, int *block_comment_counter) {
}

int find_idents(void) {
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
