#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <dogsh.h>

char* builtin_str[] = {
  "cd",
  "dir",
  "help",
  "exit",
  "echo",
  "history",
  "repeat"
};

int (*functions[]) (char**) = {
    &d_cd,
    &d_dir,
    &d_help,
    &d_exit,
    &d_echo,
    &d_history,
    &d_repeat
};

 int cmdhistory[MAX_HISTORY];
 int historyCnt = 0;

int builtins_count() {
    return sizeof(builtin_str) / sizeof(char*);
}

void free_tokens(char** tokensBuffer) {

    int count = 0;
    char* token = tokensBuffer[count];

    while (token != NULL) {

        free(tokensBuffer[count]);

        count++;

        token = tokensBuffer[count];

    }
    free(tokensBuffer);

    return;

}

int launch(char* args) {

    BOOL status;
    STARTUPINFO startInfo;
    PROCESS_INFORMATION processInfo;

    SecureZeroMemory(&startInfo, sizeof(startInfo));
    startInfo.cb = sizeof(startInfo);

    status = CreateProcessA(NULL, args, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &startInfo, &processInfo);

    if (!status) {
        
        printf("Cannot launch program and arguments (%s)!\n", args);

        return 1;

    }

    CloseHandle(processInfo.hProcess);
    CloseHandle(processInfo.hThread);

    return 1;

}

void addHistory(int func_index) {

    cmdhistory[historyCnt] = func_index;

    historyCnt = (historyCnt + 1) % MAX_HISTORY;

    return;

}

int d_cd(char** args) { 

    if ( args[1] == (char*) NULL ) { 

        printf("Need directory!\n");

        return 1; 
    
    }

    chdir(args[1]);

    return 1; 

};

int d_dir(char** args) {

    char buffer[128];

    getcwd(buffer, 128);

    printf("\n%s", buffer);

    return 1;

};

int d_help(char** args) { return 1; };

int d_exit(char** args) { return 0; };

int d_echo(char** args) { 

    printf("%s\n", args[1]);

    return 1; 

};

int d_history(char** args) { 

    int count = 0;
    int func_index = cmdhistory[count];

    while (func_index != -1 && count < MAX_HISTORY) {

        printf("%s\n", builtin_str[cmdhistory[count]]);

        count++;

        func_index = cmdhistory[count];

    }

    return 1; 

};

int d_repeat(char** args) {

    return 1;

};