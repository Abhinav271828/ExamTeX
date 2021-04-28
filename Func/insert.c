void InsertNUM(ListNUM L , NUM* X)
{
    ListNUM PNew = create_NUM(X);
        
    PNew->Next = L->Next;    
    L->Next = PNew;        
    
}