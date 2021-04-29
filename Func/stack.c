void push(Stack S, char val)
{
    PtrToNode new = create_node(val);
    new->next = S->next;
    S->next = new;
}
