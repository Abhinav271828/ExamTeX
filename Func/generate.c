#include "../Headers/functions.h"
#include "../Headers/stack.h"
#include "../Headers/structs.h"

void find_MCQ(FILE *op, Paper *P, Bank *B)
{
    MCQ *trav;
    MCQ **possible;
    int found = 0;
    int no_req, no_ops;
    for (int i = 0; i < 10; i++)
    {
        no_req = P->mcq_reqs[i]->no_req;
        no_ops = P->mcq_reqs[i]->no_ops;
        if (no_req == 0)
            break;
        trav = B->mcq_list->next;
        found = 0;

        while (trav != NULL)
        {
            if (trav->no_corr <=->no_ops && trav->diff >= P->mcq_reqs[i]->diff_lb &&
                trav->diff <= P->mcq_reqs[i]->diff_ub)
                possible[found++] = trav;

            trav = trav->next;
        }

        if (found < no_req)
        {
            printf("Not enough!\n");
            exit(0);
        }

        select_MCQ(op, possible, found, no_req, no_ops);
    }
}

void select_MCQ(FILE *op, MCQ **possible, int found, int no_req, int no_ops)
{
    int rem;
    srand(time(0));
    while (found != no_req)
    {
        rem = rand() % found;
        for (int i = found - 1; i > rem; i++)
            possible[i] = possible[i - 1];
        found--;
    }
    for (int i = 0; i < found; i++)
        fileput_MCQ(op, possible[i]);
}

void fileput_MCQ(FILE *op, MCQ *M)
{
    srand(time(0));
    int r, corr = 0, wrong = 0;
    fprintf("%s\n", M->text);
    for (int i = 0; i < M->no_ops; i++)
    {
        r = rand() % 2;
        if (r == 0)
            fprintf("%d) %s\n", i + 1, M->corr[corr++]);
        if (r == 1)
            fprintf("%d) %s\n", i + 1, M->wrong[wrong++]);
    }
}

void find_FITB(FILE *op, Paper *P, Bank *B)
{
    FITB *trav;
    FITB **possible;
    int found = 0;
    int no_req;
    no_req = P->fitb_reqs->no_req;
    if (no_req == 0)
        break;
    trav = B->fitb_list->next;
    found = 0;

    while (trav != NULL)
    {
        if (trav->diff >= P->fitb_reqs->diff_lb && trav->diff <= P->fitb_reqs->diff_ub)
            possible[found++] = trav;

        trav = trav->next;
    }

    if (found < no_req)
    {
        printf("Not enough!\n");
        exit(0);
    }

    select_FITB(op, possible, found, no_req);
}

void select_FITB(FILE *op, FITB **possible, int found, int no_req)
{
    int rem;
    srand(time(0));
    while (found != no_req)
    {
        rem = rand() % found;
        for (int i = found - 1; i > rem; i++)
            possible[i] = possible[i - 1];
        found--;
    }
    for (int i = 0; i < found; i++)
        fileput_FITB(op, possible[i]);
}

void fileput_FITB(FILE *op, FITB *F)
{
    srand(time(0));
    int r, corr = 0, wrong = 0;
    fprintf("%s\n", F->text);
}

void find_TF(FILE *op, Paper *P, Bank *B)
{
    TF *trav;
    TF **possible;
    int found = 0;
    int no_req;
    no_req = P->tf_reqs->no_req;
    if (no_req == 0)
        break;
    trav = B->tf_list->next;
    found = 0;

    while (trav != NULL)
    {
        if (trav->diff >= P->tf_reqs->diff_lb && trav->diff <= P->tf_reqs->diff_ub)
            possible[found++] = trav;

        trav = trav->next;
    }

    if (found < no_req)
    {
        printf("Not enough!\n");
        exit(0);
    }

    select_TF(op, possible, found, no_req);
}

void select_TF(FILE *op, TF **possible, int found, int no_req)
{
    int rem;
    srand(time(0));
    while (found != no_req)
    {
        rem = rand() % found;
        for (int i = found - 1; i > rem; i++)
            possible[i] = possible[i - 1];
        found--;
    }
    for (int i = 0; i < found; i++)
        fileput_TF(op, possible[i]);
}

void fileput_TF(FILE *op, TF *T)
{
    srand(time(0));
    int r, corr = 0, wrong = 0;
    fprintf("%s\n", T->text);
}

void find_NUM(FILE *op, Paper *P, Bank *B)
{
    NUM *trav;
    NUM **possible;
    int found = 0;
    int no_req;
    no_req = P->num_reqs->no_req;
    if (no_req == 0)
        break;
    trav = B->num_list->next;
    found = 0;

    while (trav != NULL)
    {
        if (trav->diff >= P->num_reqs->diff_lb && trav->diff <= P->num_reqs->diff_ub)
            possible[found++] = trav;

        trav = trav->next;
    }

    if (found < no_req)
    {
        printf("Not enough!\n");
        exit(0);
    }

    select_NUM(op, possible, found, no_req);
}

void select_NUM(FILE *op, NUM **possible, int found, int no_req)
{
    int rem;
    srand(time(0));
    while (found != no_req)
    {
        rem = rand() % found;
        for (int i = found - 1; i > rem; i++)
            possible[i] = possible[i - 1];
        found--;
    }
    for (int i = 0; i < found; i++)
        fileput_NUM(op, possible[i]);
}

void fileput_NUM(FILE *op, NUM *N)
{
    srand(time(0));
    int r, corr = 0, wrong = 0;
    fprintf("%s\n", N->text);
}

