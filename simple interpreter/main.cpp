#include<cstdio>
#include <cstring>
#include <cstdlib>
#include"ifptf.h"
#include "isValid.h"
#include "heap.h"

using namespace std;

BinarySearchTree* variables = createNewTree();

void Simple_Interpreter()
{
    char filename[50] = "";
    printf("Please enter your source .txt file name: ");
    read:
        scanf("%s", filename);
        FILE* fptr = fopen(filename, "r");
    if(!fptr)
    {
        printf("Please enter a valid file name: ");
        goto read;
    }
    else
    {
        char line[100] = "";
        while(!feof(fptr))
        {
            fscanf(fptr, "%[^\n]\n", line);
            /// checks if statement has = sign
            int has_equals = 0;
            for(unsigned int i = 0; i < strlen(line); i++)
            {
                if(*(line + i) == '=')
                {
                    has_equals = 1;
                    break;
                }
            }
            if(!has_equals)
            {
                printf("Missing '=' symbol from expressions '%s'.\n", line);
                continue;
            }
            /* do operations on string */
            char vKey[10];
            char vVal[90];
            char* tok = strtok(line, "=");
            strcpy(vKey, deblank(tok));
            tok = strtok(NULL, "=");
            strcpy(vVal, deblank(tok));
            /// verify variable name
            if(!is_valid_name(vKey))
            {
                printf("Invalid variable name '%s'.\n", vKey);
                printf("Exiting...\n");
                exit(0);
            }
            /// verify expression
            if(!isValidExpression(vVal))
            {
                printf("Invalid variable expression '%s'.\n", vVal);
                printf("Exiting...\n");
                exit(0);
            }
            /// expression to value
            char infix[MAX_LENGTH];
            strcpy(infix, vVal);
            printInorder(variables->root);
            float vVal_float = evaluatePostfix(inToPost(deblank(infix)), variables, vKey);
            /// store variable name as key, variable value as value
            put(variables, vVal_float, vKey);
        }
        /////////////////////////////////////////////////////////////////////////////////////////
        /// FIRST TASK: the output of the process should be the display of all variables each one
        /// with its value, sorted by the variable name.
        printf("\n");
        printf("Variables sorted by the variable name:\n");
        printInorder(variables->root);
        printf("\n");
        /////////////////////////////////////////////////////////////////////////////////////////
        /// SECOND TASK: all variables are displayed each one with its value sorted by value.
        /// Extract nodes of BST into variable array then sort using heap sort
        size_t bstsize = count(variables->root);
        variable* vals = extract_value(variables->root);
        heapSort(vals, bstsize);
        printf("\n");
        printf("Variables sorted by the variable value:\n");
        kTYPE key = (kTYPE) malloc((100 + 1) * sizeof(key));
        for(unsigned int i = 0; i < bstsize; i++)
        {
            printf("%s = %.2f ", vals[i].key, vals[i].value);
            printf("\n");
        }
        printf("\n");
        /////////////////////////////////////////////////////////////////////////////////////////

        fclose(fptr);
    }
}



int main()
{
    Simple_Interpreter();

    return 0;
}
