void InsertNUM(ListNUM L , NUM* X)
{
    X->Next = L->Next;
    L->Next = X;     
}