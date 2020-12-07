#include <cstdio>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <stack>
#include <bits/stdc++.h>

using namespace std;

int is_valid_name(char* c)
{
    for(unsigned int i = 0; i < strlen(c); i++)
    {
        /// first character
        if(!strcasecmp(&c[0], "_") || !isalpha(c[0]))
        {
            return 0;
        }
        /// rest of the characters
        if(!isalnum(c[i]) && c[i] != ' ')
        {
            return 0;
        }
    }
    return 1;
}

int isOperator(char c)
{
    switch(c)
    {
    case('^'):
    case('*'):
    case('/'):
    case('+'):
    case('-'):
        return 1;
    default:
        return 0;
    }
}

int is_string(char* token)
{
    for(int i = 0; i < strlen(token); i++)
    {
        if(!isalpha(*(token + i)))
        {
            return 0;
        }
    }
    return 1;
}

int lastIndexOfEqual(char* exp)
{
    int flag=0;
    for(unsigned int i=0; exp[i]; i++)
    {
        if(exp[i]=='=')
        {

            flag=i;
        }
    }
    return flag;
}

int bracketCheck(char* exp) ///DONE
{
    int ourBrackets[3][2],flag=1; ///BRACKET , CURLY BRACKET , SQUARE BRACKET.

    for(int i=0; i<4; i++)
    {
        for(int j=0 ; j<2; j++)
        {
            ourBrackets[i][j]=0;
        }
    }
    char c;
    for(unsigned int i = 0; exp[i]; i++)
    {
        c = exp[i];
        if(c == '(')
        {
            ourBrackets[0][0]++;
            if(i!=0 &&!isOperator(exp[i-1]))
            {
                flag=0;
                break;
            }
        }
        if(c==')')
        {
            ourBrackets[0][1]++;
            if (!isalnum(exp[i - 1]))
            {
                flag = 0;
            }
        }
        if(c=='{')
        {
            if(exp[i+1]!='\0' && isalnum(exp[i+1]))
            {
                ourBrackets[1][0]++;
            }
            flag= 0;
        }
        if(c == '}')
        {
            if(isalnum(exp[i-1]))
            {
                ourBrackets[1][1]++;
            }
            flag = 0;
        }
        if(c == '[')
        {
            if(exp[i+1]!='\0' && isalnum(exp[i+1]))
            {
                ourBrackets[2][0]++;
            }
            flag = 0;
        }
        if(c == ']')
        {
            if(isalnum(exp[i-1]))
            {
                ourBrackets[2][1]++;
            }
            flag = 0;
        }
        if(flag==0)
        {
            break;
        }

    }
    /*
    for(int i=0 ; i<3 ; i++)
    {
        for(int j=0 ; j<2; j++)
        {
            printf("%d ",ourBrackets[i][j]);
        }
        printf("\n");
    }
    */

    for(int i =0; i<3; i++)
    {
        if(ourBrackets[i][0]!=ourBrackets[i][1])
        {
            flag=0;
            break;
        }
    }
    return flag;
}

int plusOneOperator(char*exp) ///STILL NEEDS UPDATES
{
    if( (exp[0]=='+') || (exp[0]=='*') || (exp[0]=='/') || (exp[0]=='^'))
    {
        return 0;
    }
    bool isNumber=false;
    int numberCounter=0;
    int operatorCounter=0;

    for(unsigned int i=0 ; exp[i]; i++)
    {
        if(isalnum(exp[i]))
        {
            if(isNumber==false)
            {
                numberCounter++;
                isNumber=true;
            }
        }
        else if (isOperator(exp[i]) &&i!=0)
        {
            if(exp[i]=='-'&&isOperator(exp[i-1]))
            {
                continue;
            }
            else if(isNumber==true)
            {
                operatorCounter++;
                isNumber=false;
            }
        }
    }

    return (numberCounter>=operatorCounter+1);
}

int noMoreThanEqual(char* exp)
{
    for(unsigned int i=0; exp[i]; i++)
    {
        if(exp[i]=='='&&exp[i+1]=='=')
        {
            return 0;
        }
    }

    return 1;
}

int isPostEqualValid(char* exp)
{
    return (bracketCheck(exp)&&plusOneOperator(exp)&&noMoreThanEqual(exp));
}

char** splitString(char* exp)///SACRIFICING COMPLEXITY FOR CLARITY & EASE OF DEBUGGING
{
    unsigned int indexOfEqual = lastIndexOfEqual(exp);
    unsigned int expressionSize = strlen(exp);
    unsigned int sizeOfPost=expressionSize-indexOfEqual;
    unsigned int sizeOfPre=indexOfEqual+1;
    char** stringMatrix = (char**) malloc(2*sizeof(char*));
    stringMatrix[0] = (char *)malloc(sizeOfPre * sizeof(char));
    stringMatrix[1] = (char *)malloc(sizeOfPost * sizeof(char));
    memcpy(stringMatrix[0],exp,indexOfEqual);
    stringMatrix[0][indexOfEqual]='\0';
    memcpy(stringMatrix[1],exp+indexOfEqual+1,sizeOfPost-1);
    stringMatrix[1][sizeOfPost-1]='\0';

    return stringMatrix;
}

int isPreEqualValid (char* exp)
{
    unsigned int size =strlen(exp);
    unsigned int varNumber=0;
    char temp[size+1];
    strcpy(temp,exp);
    char* token = strtok(temp, "=");

    while (token != NULL)
    {
        if(!is_valid_name(token))
        {
            return 0;
        }
        token = strtok(NULL, "=");
        varNumber++;
    }
    return (varNumber * noMoreThanEqual(exp));
}

int paired(char open,char close)
{
    if(open=='{'&& close=='}')
        return 1;
    else if (open=='('&& close==')')
        return 1;
    else if (open=='['&& close==']')
        return 1;
    return 0;
}

int isValidExpression(char* exp)
{
    stack<char> openedbrackets;
    for(int i = 0; i < strlen(exp); i++)
    {
        if(exp[i]=='{'||exp[i]=='('||exp[i]=='[')
            openedbrackets.push(exp[i]);
        else if(exp[i]=='}'||exp[i]==')'||exp[i]==']')
        {
            if(openedbrackets.size() == 0)
                return 0;
            else if(paired(openedbrackets.top(),exp[i])==0)
                return 0;
            openedbrackets.pop();
        }
    }
    if(openedbrackets.size() == 0)
        return 1;
    else
        return 0;
}
