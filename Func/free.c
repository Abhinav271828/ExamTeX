#include "../Headers/structs.h"
#include "../Headers/functions.h"

void freeMCQ(MCQ *M)
{
    free(M->text);
    for (int i = 0; i < M->no_corr; i++)
        free(M->corr[i]);
    for (int i = 0; i < M->no_ops - M->no_corr; i++)
        free(M->wrong[i]);
    free(M);
}

void freeFITB(FITB *F)
{
    free(F->text);
    free(F->ans);
    free(F);
}

void freeTF(TF *T)
{
    free(T->text);
    free(T);
}

void freeNUM(NUM *N)
{
    free(N->text);
    free(N);
}

void freeBank(Bank *B)
{
    MCQ* trav1 = B->mcq_list;
    MCQ* temp1;
    while (trav1->next != NULL)
    {
        temp1 = trav1->next;
        trav1->next = temp1->next;
        freeMCQ(temp1);
    }
    freeMCQ(trav1);

    FITB* trav2 = B->fitb_list;
    FITB* temp2;
    while (trav2->next != NULL)
    {
        temp2 = trav2->next;
        trav2->next = temp2->next;
        freeFITB(temp2);
    }
    freeFITB(trav2);

    TF* trav3 = B->tf_list;
    TF* temp3;
    while (trav3->next != NULL)
    {
        temp3 = trav3->next;
        trav3->next = temp3->next;
        freeTF(temp3);
    }
    freeTF(trav3);

    NUM* trav4 = B->num_list;
    NUM* temp4;
    while (trav4->next != NULL)
    {
        temp4 = trav4->next;
        trav4->next = temp4->next;
        freeNUM(temp4);
    }
    freeNUM(trav4);
}

void freePaper(Paper *P)
{
    for (int i = 0; i < 10; i++)
        free(P->mcq_reqs[i]);
    free(P->fitb_reqs);
    free(P->tf_reqs);
    free(P->num_reqs);
}
