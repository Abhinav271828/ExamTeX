void InsertFITB(ListFITB L,FITB* X)
{

X->Next = L->Next;
L->Next = X;

}