#pragma once

#ifndef dogsh

#define dogsh

#define INIT_BUFFER 256
#define TOKS_BUFFER 64
#define TOK_SIZE 128
#define MAX_HISTORY 5

int d_cd(char** args);
int d_dir(char** args);
int d_help(char** args);
int d_exit(char** args);
int d_echo(char** args);
int d_history(char** args);
int d_repeat(char** args);

char* builtin_str[];
int cmdhistory[];

int (*functions[]) (char**);

int builtins_count();

void init_shell();

void printTokens( char** tokensBuffer );
void free_tokens(char** tokensBuffer);
void addHistory(int func_index);

#endif