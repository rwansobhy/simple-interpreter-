#ifndef NEWPROJECT_IFPTF_H
#define NEWPROJECT_IFPTF_H

#include "AVL.h"

using namespace std;

bool nonOperand(char *token);
char* inToPost(char* infix );
float evaluatePostfix(char* postfix,BinarySearchTree* tree, char* vKEY);
char* deblank(char* infix);


#endif //NEWPROJECT_IFPTF_H
