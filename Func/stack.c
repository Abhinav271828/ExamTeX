void push(Stack S, char val)
{
    PtrToNode new = create_node(val);
    new->next = S->next;
    S->next = new;
}

char pop(Stack S)
{
    char c = S->next->part;
    S->next = S->next-> next;
    return c;
}

Stack create_empty()
{
    PtrToNode temp;
    temp = (PtrToNode)malloc(sizeof(Node));
    temp -> part = ' ';
    temp -> next = NULL;
    return temp;
}
PtrToNode create_node(char val)
{
    Node* val1;
    val1 = (Node*)malloc(sizeof(Node));
    val1 -> part = val;
    val1 ->next = NULL;
    return val1;
}

char top(Stack S)
{
    return (S->next->part);
}
