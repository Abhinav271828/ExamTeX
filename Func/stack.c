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