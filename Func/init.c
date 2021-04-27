#include"adt.h"
#include<string.h>

NUM* create_NUM(char* text, int ans , float diff)
{
    NUM* P = (NUM*)malloc(sizeof(NUM));

    strcpy(P->text,text);
    P->ans = ans;
    P->diff = diff;
    P->next = NULL;
}

NUM* init_NUM()
{
    NUM* P = create_NUM("",0,0.0f);
    return P;
}