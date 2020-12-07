//
// Created by Ayman on 6/1/2020.
//

#include <malloc.h>
#include <cstring>
#include"variable.h"
variable* newVariable(float value,char* key)
{
    variable* newVar=(variable*) malloc(sizeof(variable));
    newVar->value=value;
    newVar->key =(char*) malloc(strlen(key)*sizeof(char)+1);
    strcpy(newVar->key,key);
    return newVar;
}
