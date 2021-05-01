#include <stdio.h>
#include <stdlib.h>

#ifndef __STACK
#define __STACK

typedef struct Node Node;
typedef struct Node* PtrToNode;
typedef PtrToNode Stack;


struct Node
{
    char part; // part = 't' if \begin{type} has been pushed; 'q' if \begin{question} has been pushed 
    struct Node* next;
};

Stack create_empty();
PtrToNode create_node(char val);
void push(Stack S, char val);
char pop(Stack S);
char top(Stack S);

#endif
