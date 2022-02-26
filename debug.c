#include <stdio.h>
#include <dogsh.h>

void printTokens( char** tokensBuffer ) {
    
    int count = 0;
    char* token = tokensBuffer[count];

    while (token != NULL) {

        printf("Token::%s", token);

        count++;

        token = tokensBuffer[count];

    }

    printf("::End::Tokens=%d", count);

    return;

}