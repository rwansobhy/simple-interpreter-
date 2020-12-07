#ifndef NEWPROJECT_VARIABLE_H
#define NEWPROJECT_VARIABLE_H

#define kTYPE char*
#define vTYPE float

typedef struct{
    kTYPE key;
    vTYPE value;
} variable;

variable* newVariable(vTYPE value,kTYPE key);

#endif //NEWPROJECT_VARIABLE_H
