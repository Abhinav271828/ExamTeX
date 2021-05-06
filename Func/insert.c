#include "../Headers/structs.h"
#include "../Headers/functions.h"

void InsertFITB(ListFITB L,FITB* X)
{
    X->Next = L->Next;
    L->Next = X;
}

void InsertNUM(ListNUM L , NUM* X)
{
    X->Next = L->Next;
    L->Next = X;     
}

void InsertMCQ(ListMCQ L, MCQ* X)
{
    X->Next = L->Next;
    L->Next = X;
}
void InsertTF(ListTF L , TF* X)
{
    X->Next = L->Next;
    L->Next = X;     
}
