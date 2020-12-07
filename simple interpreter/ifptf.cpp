#include <cstdlib>
#include <string>
#include<cstring>
#include <bits/stdc++.h>
#include<cstdio>
#include <cctype>
#include<cmath>
#include<stack>
#include "isValid.h"
#include "AVL.h"

#define special(a) (a=='-' )

using namespace std;

int priority(char c)  ///PRIORITY OF MATH EXPRESSIONS
{
    if (c == '+' || c == '-')
        return 1;
    else if (c == '/' || c == '*' || c == '%')
        return 2;
    else if (c == '^')
        return 3;
    else
        return 0;
}

bool nonOperand(char *token)  ///HELPER TO POF DETERMINE IS NEGATIVE / IS SIGN?
{
    if(token[1]!='\0' ||!isOperator(*token))
    {
        return true;
    }
    return false;

}

bool pof(char *infix, int i)  ///CHECKS IF IT IS A PART OF FLOAT
{

    if(infix[i]=='.' ||i==0 ||isalnum(infix[i]))
    {
        return true;
    }
    else if (special(infix[i]))
    {
        if(isOperator(infix[i-1]))
        {
            return true;
        }
        if(infix[i-1]==')')
        {
            return false;
        }
        for(i=i+1; infix[i]; i++)
        {

            if(infix[i]=='*'||infix[i]=='/'||infix[i]=='^'||infix[i]=='%')
            {
                return true;
            }
            else if (infix[i]==')')
            {
                return false;
            }
            else if (infix[i]=='+'||infix[i]=='-')
            {
                return false;
            }
        }

    }
    return false;
}

char* inToPost(char* infix)
{
    stack<char> stk;
    string exp(infix);
    stk.push('#');               //add some extra character to avoid underflow
    string postfix = "";         //initially the postfix string is empty
    string::iterator it;
    int i = 0;
    for(it = exp.begin(); it!=exp.end(); it++)
    {
        if(pof(infix,i))
        {
            postfix += *it;
            it++;
            i++;
            while (isalnum(char(*it)) || *it=='.')
            {
                postfix += *it;
                it++;
                i++;
            }
            postfix+=" ";
            it--;
            i--;
        }
        else
        {
            if(*it == '(')
            {
                stk.push('(');
            }
            else
            {
                if(*it == '^')
                {
                    stk.push('^');

                }
                else if(*it == ')')
                {
                    while(stk.top() != '#' && stk.top() != '(')
                    {

                        postfix += stk.top();
                        postfix+=" ";
                        //store and pop until ( has found
                        stk.pop();
                    }
                    stk.pop();          //remove the '(' from stack
                }
                else
                {
                    if(priority(*it) > priority(stk.top()))
                    {
                        stk.push(*it); //push if precedence is high
                    }
                    else
                    {
                        while(stk.top() != '#' && priority(*it) <= priority(stk.top()))
                        {
                            postfix += stk.top();
                            postfix+=" ";
                            //store and pop until higher precedence is found
                            stk.pop();
                        }
                        stk.push(*it);
                    }
                }
            }
        }     //add to postfix when character is letter or number
        i++;
    }

    while(stk.top() != '#')
    {
        postfix += stk.top();
        postfix+=" ";       //store and pop until stack is not empty.
        stk.pop();
    }
    char *charOutput = (char *) malloc(exp.length() * sizeof(char));
    strcpy(charOutput, postfix.c_str());
    return charOutput;
}

float evaluatePostfix(char *exp,BinarySearchTree *tree, char* var)
{
    stack<float> myStack;
    treeNode * searchNode;
    int sign=1;
    char* token = strtok(exp, " ");
    while (token != NULL)
    {
        if(nonOperand(token))
        {
            if(token[0]=='-')
            {
                sign=-sign;
            }
            else
            {
                sign=sign;
            }
            if(isdigit(token[0]) ||((token[0]=='-') && isdigit(token[1])))
            {
                myStack.push(strtof(token,NULL));
            }
            else if(is_string(token))
            {
                searchNode = searchTree(tree, token);
                printf("token: %s  current key: %s\n", token, var);
                if(searchNode)
                {
                    if(strcmp(searchNode->data->key, var) == 0)
                    {
                        printf("Invalid expression '%s'.\n", exp);
                        exit(0);
                    }
                    myStack.push(searchNode->data->value*sign);
                }
                else
                {
                    printf("Invalid expression '%s'.\n", exp);
                    exit(0);
                }
            }
        }
        else
        {
            if(myStack.empty()== false) ///HANDLE IF USER ENTERS y=--number || y=-+ number || y=+-number at input beginning
            {
                float num1 = myStack.top();
                myStack.pop();
                float num2 = myStack.top();
                myStack.pop();
                switch (token[0])
                {
                case '+':
                    myStack.push(num2 + num1);
                    break;
                case '-':
                    myStack.push(num2 - num1);
                    break;
                case '*':
                    myStack.push(num2 * num1);
                    break;
                case '/':
                    myStack.push(num2 / num1);
                    break;
                case '^':
                    myStack.push(pow(num2, num1));
                    break;
                }
            }
            else
            {
                if(token[0]=='-')
                {
                    sign=-sign;
                }
            };
        }
        token = strtok(NULL, " ");
    }
    float returner=myStack.top();
    myStack.pop();
    while(!myStack.empty())
    {
        returner +=myStack.top();
        myStack.pop();
    }
    free(exp);
    return returner;
}

char *deblank(char *infix)  ///FUNCTION TO MAKE STATMENT WITHOUT SPACES
{
    int i=-1;
    int shift=0;
    while(infix[++i])
    {
        if(infix[i]==' ')
        {
            shift++;
        }
        else
        {
            infix[i-shift]=infix[i];
        }
    }
    infix[i-shift]='\0';

    return infix;
}
