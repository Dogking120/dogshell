#include <stdio.h>
#include <stdlib.h>
#include <dogsh.h>

int interpretTokens( char** tokensBuffer, char* charBuffer ) {

    char* command = tokensBuffer[0];

    if (command[0] == '\0') {

        printf("Invalid null command!\n");

        return 1;

    }

    for (int i = 0; i < builtins_count(); i++) {

        if (strcmp(tokensBuffer[0], builtin_str[i]) == 0) {

            int status = (*functions[i])(tokensBuffer);

            addHistory(i);

            return status;

        }
    }

    return launch(charBuffer);

}

char** lineTokens( char* buffer ) {

    char** tokensBuffer = (char**)malloc(sizeof(char*) * TOKS_BUFFER);
    char* token;

    int count = 0;
    int iterateCount = 0;
    int bufferCount = 0;

    char readChar = buffer[count];
    char escape = 0b1;

    token = (char*)malloc(sizeof(char) * TOK_SIZE);

    while (readChar != '\0') {

        if (readChar == '"') {

            escape = !escape;

            count++;

            readChar = buffer[count];

            continue;

        }

        if (escape == 0b1) {

            if (readChar == ' ') {

                token[iterateCount] = '\0';
                tokensBuffer[bufferCount] = token;

                count++;
                bufferCount++;

                iterateCount = 0;

                token = (char*)malloc(sizeof(char) * TOK_SIZE);
                readChar = buffer[count];

                continue;

            }

        }

        token[iterateCount] = readChar;

        count++;
        iterateCount++;

        readChar = buffer[count];

    }

    token[iterateCount] = '\0';
    tokensBuffer[bufferCount] = token;
    tokensBuffer[bufferCount + 1] = (char*) NULL;

    return tokensBuffer;

}

char* getLine( char* buffer ) {

    int count = 0;
    int inChar = 0;

    while (1) {

        inChar = getchar();
        
        if (inChar == EOF || inChar == '\n') {

            buffer[count] = '\0';

            break;

        }

        buffer[count] = inChar;

        count++;

    }

    return buffer;

}

void init_shell() {

    char* charBuffer = (char*)malloc(sizeof(char) * INIT_BUFFER);
    char** tokensBuffer;

    if (charBuffer == NULL) { return; }

    for (int i = 0; i < MAX_HISTORY; ++i) {

        cmdhistory[i] = -1;

    }

    int shellStatus = 1;

    printf("Dog Shell online...\n");

    while (shellStatus) {

        d_dir(NULL);

        printf(">>> ");

        getLine(charBuffer);

        tokensBuffer = lineTokens(charBuffer);

        shellStatus = interpretTokens(tokensBuffer, charBuffer);

        free_tokens(tokensBuffer);

    }

    free(charBuffer);

    free_tokens(tokensBuffer);

    printf("Exiting shell!\n");

    return;

}