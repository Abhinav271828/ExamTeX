#include "../Headers/functions.h"
#include "../Headers/structs.h"

void InsertFITB(ListFITB L, FITB *X)
{
    X->next = L->next;
    L->next = X;
}

void InsertNUM(ListNUM L, NUM *X)
{
    X->next = L->next;
    L->next = X;
}

void InsertMCQ(ListMCQ L, MCQ *X)
{
    X->next = L->next;
    L->next = X;
}
void InsertTF(ListTF L, TF *X)
{
    X->next = L->next;
    L->next = X;
}
