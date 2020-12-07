#ifndef NEWPROJECT_ISVALID_H
#define NEWPROJECT_ISVALID_H

#include <cstdio>
#include <stack>
#include <bits/stdc++.h>

using namespace std;

#define MAX_LENGTH 100


int is_valid_name(char* c);
int isOperator(char c);
int is_string(char*);
int lastIndexOfEqual(char* exp);
int bracketCheck(char* exp);
int plusOneOperator(char*exp);
int noMoreThanEqual(char* exp, unsigned int size);
int isPostEqualValid(char* exp);
char** splitString(char* exp);
int isPreEqualValid (char* exp);
int paired(char open,char close);
int isValidExpression(char* exp);

#endif //NEWPROJECT_ISVALID_H
