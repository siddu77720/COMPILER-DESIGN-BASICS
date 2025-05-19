#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char keywords[][10] = {
    "int", "float", "char", "if", "else", "while", "do", "return", "break",
    "continue", "void", "for", "switch", "case", "long", "double", "static",
    "struct", "sizeof"
};

int isKeyword(char *word) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int isOperator(char ch) {
    return strchr("+-*/%=<>!&|^", ch) != NULL;
}

void analyze(FILE *file) {
    char ch, buffer[100];
    int i = 0;

    while ((ch = fgetc(file)) != EOF) {
        if (isalnum(ch) || ch == '_') {
            buffer[i++] = ch;
        } else {
            buffer[i] = '\0';
            i = 0;

            if (strlen(buffer) > 0) {
                if (isKeyword(buffer))
                    printf("[Keyword]    => %s\n", buffer);
                else
                    printf("[Identifier] => %s\n", buffer);
            }

            if (isOperator(ch)) {
                printf("[Operator]   => %c\n", ch);
            }
        }
    }
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Failed to open input.txt\n");
        return 1;
    }

    printf("Lexical Analysis Output:\n");
    analyze(file);

    fclose(file);
    return 0;
}
