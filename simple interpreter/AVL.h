#ifndef NEWPROJECT_AVL_H
#define NEWPROJECT_AVL_H
#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED

#include "variable.h"

typedef struct treeNode
{
    int height;
    variable* data;
    struct treeNode* left;
    struct treeNode* right;
} treeNode ;

typedef struct BinarySearchTree
{
    treeNode* root;
} BinarySearchTree;

treeNode* getNewtreeNode(variable* data);
treeNode * minValuetreeNode(treeNode* node);
treeNode * maxValuetreeNode(treeNode* node);
BinarySearchTree* createNewTree();
variable * getVal(treeNode *node);
int getHeight( treeNode* node);
int max(int a, int b);
int min(int a, int b);
void freetreeNode(treeNode *node);
int count(treeNode *node);
int treeCount(BinarySearchTree* tree);
void put(BinarySearchTree *tree, float value, char* key);
treeNode* searchTree(BinarySearchTree* tree,char* key);
void printInorder(treeNode* node);
void traverse_inorder(treeNode* tree, variable* vptr, int* i);
variable* extract_value(treeNode* tree);


#endif // AVL_H_INCLUDED

#endif //NEWPROJECT_AVL_H
