void InsertNUM(ListNUM L , char* text , int ans , float diff)
{
    ListNUM PNew = create_NUM(text,ans,diff);
        
    PNew->Next = L->Next;    
    L->Next = PNew;        
    
}