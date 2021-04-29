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

void InsertMCQ(List MCQ, MCQ* X)
{
    X->Next = L->Next;
    L->Next = X;
}
