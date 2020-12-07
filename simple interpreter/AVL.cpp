#include <cstdio>
#include <cstdlib>
#include <string.h>
#include "AVL.h"

treeNode* getNewtreeNode(variable* data)
{
    treeNode * newtreeNode= (treeNode*)malloc(sizeof(treeNode));
    newtreeNode->data=data;
    newtreeNode->height=1;
    newtreeNode->left=newtreeNode->right=NULL;
    return newtreeNode;
}

treeNode * minValuetreeNode(treeNode* node)
{
    treeNode* current = (treeNode*)node;
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
    {
        current = current->left;
    }

    return current;
}

treeNode * maxValuetreeNode(treeNode* node)
{
    if (!node)
        return NULL;
    if (node->right)
        return maxValuetreeNode(node->right);
    return node;
}

BinarySearchTree* createNewTree()
{
    BinarySearchTree* bst = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
    bst->root=NULL;
    return bst;
}

variable * getVal(treeNode *node)
{
    return node->data;
}

int getHeight( treeNode* node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

int max(int a, int b)
{
    return (a > b)? a : b;
}

int min(int a, int b)
{
    return (a < b)? a : b;
}

int my_strcasecmp(char* a,char *treeElement)
{
    int i,j;
    i=j=0;
    if (a[0]=='-')
    {
        j++;
    }
    while(a[j] && treeElement[i])
    {
        if(a[j] > treeElement[i] || treeElement[i]=='\0')
        {
            return 1;
        }
        else if (a[j] < treeElement[i] || a[j]=='\0')
        {
            return -1;
        }
        i++;
        j++;
    }
    if(a[j]==treeElement[i])
    {
        return 0;
    }
    else if(a[j]=='\0')
    {
        return -1;
    }
    else
        return 1;
}

void freetreeNode(treeNode *node)
{
    free(node->data->key);
    free(node->data);
    free(node);
}

int count(treeNode *node)
{
    if (node)
        return 1+count(node->left)+count(node->right);
    return 0;
}

int treeCount(BinarySearchTree* tree)
{
    return count(tree->root);
}

treeNode *rightRotate( treeNode *y)
{
    treeNode* x = y->left;
    treeNode *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(getHeight(y->left), getHeight(y->right))+1;
    x->height = max(getHeight(x->left), getHeight(x->right))+1;
    return x;
}

treeNode *leftRotate( treeNode *x)
{
    treeNode *y = x->right;
    treeNode *T2 = y->left;
    // Perform rotation
    y->left = x;
    x->right = T2;
    //  Update heights
    x->height = max(getHeight(x->left), getHeight(x->right))+1;
    y->height = max(getHeight(y->left), getHeight(y->right))+1;
    // Return new root
    return y;
}

int getBalance( treeNode *N)
{
    if (N == NULL)
        return 0;
    return getHeight(N->left) - getHeight(N->right);
}

treeNode* inserter(treeNode* node, float data, char* key)
{
    if (node == NULL)
        return (treeNode*)(getNewtreeNode(newVariable(data,key)));
    if (my_strcasecmp(key,node->data->key)<0)
        node->left  = (treeNode*) inserter(node->left,data,key);
    else if (my_strcasecmp(key,node->data->key)>0)
        node->right = (treeNode*) inserter(node->right, data,key);
    else
        node->data->value=data; ///OVERWRITE OLD DATA;
    return node;
    node->height = 1 + max(getHeight(node->left),
                           getHeight(node->right));
    int balance = getBalance(node);
    // LEFT LEFT CASE
    if (balance > 1 && (my_strcasecmp(key, node->left->data->key)<0))
        return rightRotate(node);
    // Right Right Case
    if (balance < -1 && (my_strcasecmp(key, node->right->data->key)>0))
        return leftRotate(node);
    // Left Right Case
    if (balance > 1 && (my_strcasecmp(key, node->left->data->key)>0))
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
    // Right Left Case
    if (balance < -1 && my_strcasecmp(key, node->right->data->key)<0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    /* return the (unchanged) node pointer */
    return node;
}

void put(BinarySearchTree *tree, float data, char* key)
{
    if (tree->root==NULL)
    {
        tree->root=getNewtreeNode(newVariable(data,key));
    }
    else
    {
        tree->root= inserter((tree->root), data,key);
    }
}

treeNode* searchNodes(treeNode* root,char* key)
{
    if (root == NULL || strcmp(key,root->data->key) == 0)
    {
        return root;
    }
    else if (strcmp(key,root->data->key)>0)
    {
        return searchNodes(root->right,key);
    }
    else
    {
        return searchNodes(root->left, key);
    }
}

treeNode* searchTree(BinarySearchTree* tree,char* key)
{
    return searchNodes(tree->root,key);
}

void printInorder(treeNode* node)
{
    if (node == NULL)
        return;

    printInorder(node->left);
    printf("%s = %.2f\n", node->data->key,node->data->value);
    printInorder(node->right);
}

void traverse_inorder(treeNode* tree, variable* vptr, int* i)
{
    if(tree)
    {
        traverse_inorder((treeNode*)tree->left, vptr, i);
        *(vptr + (*i)++) = *tree->data;
        traverse_inorder((treeNode*)tree->right, vptr, i);
    }
}

variable* extract_value(treeNode* tree)
{
    variable* vptr = (variable*) malloc(count(tree) * sizeof(variable));
    int i = 0;
    traverse_inorder(tree, vptr, &i);

    return vptr;
}
