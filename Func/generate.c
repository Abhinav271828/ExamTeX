#include "../Headers/functions.h"
#include "../Headers/stack.h"
#include "../Headers/structs.h"

void find_MCQ(FILE *op, Paper *P, Bank *B)
{
    MCQ *trav;
    MCQ **possible = (MCQ**)malloc(sizeof(MCQ*));
    int found = 0;
    int no_req, no_ops;
    for (int i = 0; i < 10; i++)
    {
        no_req = P->mcq_reqs[i].no_req;
        no_ops = P->mcq_reqs[i].no_ops;
        if (no_req == 0)
        {
            break;
        }
        trav = B->mcq_list->next;
        found = 0;

        while (trav != NULL)
        {
            if (trav->no_corr <= no_ops && trav->diff >= P->mcq_reqs[i].diff_lb &&
                trav->diff <= P->mcq_reqs[i].diff_ub)
            {
                possible = (MCQ**)realloc(possible,(found+1)*sizeof(MCQ*));
                possible[found++] = trav;
            }

            trav = trav->next;
        }
        if (found < no_req)
        {
            printf("Not enough MCQs, not adding!\n");
        }
        else
        {
            select_MCQ(op, possible, found, no_req, no_ops);
            printf("MCQs found and added!\n");
        }
    }
}

void select_MCQ(FILE *op, MCQ **possible, int found, int no_req, int no_ops)
{
    int rem;
    srand(time(0));
    while (found != no_req)
    {
        rem = rand() % found;
        for (int i = rem; i < found-1; i++)
            possible[i] = possible[i + 1];
        found--;
    }
    fprintf(op,"MCQ:\n");
    for (int i = 0; i < found; i++)
    {
        fprintf(op, "%d) ",i+1);
        fileput_MCQ(op, possible[i], no_ops);
    }
    fprintf(op,"--------------------\n");
}

void fileput_MCQ(FILE *op, MCQ *M, int no_ops)
{
    srand(time(0));
    int r, corr = 0, wrong = 0;
    fprintf(op, "%s\n", M->text);
    for (int i = 0; i < no_ops; i++)
    {
        if (corr < M->no_corr && (corr + wrong) < no_ops)
        {
            r = rand() % 2;
            if (r == 0)
            {
                fprintf(op, "%d) %s\n", i + 1, M->corr[corr++]);
            }
            if (r == 1)
            {
                fprintf(op, "%d) %s\n", i + 1, M->wrong[wrong++]);
            }
        }
        else if ((corr+wrong) >= no_ops)
            fprintf(op, "%d) %s\n", i + 1, M->corr[corr++]);
        else
            fprintf(op, "%d) %s\n", i + 1, M->wrong[wrong++]);
    }
}

void find_FITB(FILE *op, Paper *P, Bank *B)
{
    FITB *trav;
    FITB **possible = (FITB**)malloc(sizeof(FITB*));
    int found = 0;
    int no_req;
    no_req = P->fitb_reqs.no_req;
    trav = B->fitb_list->next;
    found = 0;

    while (trav != NULL)
    {
        if (trav->diff >= P->fitb_reqs.diff_lb && trav->diff <= P->fitb_reqs.diff_ub)
        {
            possible = (FITB**)realloc(possible,(found+1)*sizeof(FITB*));
            possible[found++] = trav;
        }

        trav = trav->next;
    }

    if (found < no_req)
    {
        printf("Not enough FITBs, not printing!\n");
    }
    else
    {
        select_FITB(op, possible, found, no_req);
        printf("FITBs found and added!\n");
    }
}

void select_FITB(FILE *op, FITB **possible, int found, int no_req)
{
    int rem;
    srand(time(0));
    while (found != no_req)
    {
        rem = rand() % found;
        for (int i = rem; i < found-1; i++)
            possible[i] = possible[i + 1];
        found--;
    }
    fprintf(op,"FITB:\n");
    for (int i = 0; i < found; i++)
    {
        fprintf(op,"%d) ",i+1);
        fileput_FITB(op, possible[i]);
    }
    fprintf(op,"--------------------\n");
}

void fileput_FITB(FILE *op, FITB *F)
{
    srand(time(0));
    int r, corr = 0, wrong = 0;
    fprintf(op, "%s\n", F->text);
}

void find_TF(FILE *op, Paper *P, Bank *B)
{
    TF *trav;
    TF **possible = (TF**)malloc(sizeof(TF*));
    int found = 0;
    int no_req;
    no_req = P->tf_reqs.no_req;
    trav = B->tf_list->next;
    found = 0;

    while (trav != NULL)
    {
        if (trav->diff >= P->tf_reqs.diff_lb && trav->diff <= P->tf_reqs.diff_ub)
        {
            possible = (TF**)realloc(possible,(found+1)*sizeof(TF*));
            possible[found++] = trav;
        }

        trav = trav->next;
    }

    if (found < no_req)
    {
        printf("Not enough TFs, not printing!\n");
    }
    else
    {
        select_TF(op, possible, found, no_req);
        printf("TFs found and added!\n");
    }
}

void select_TF(FILE *op, TF **possible, int found, int no_req)
{
    int rem;
    srand(time(0));
    while (found != no_req)
    {
        rem = rand() % found;
        for (int i = rem; i < found-1; i++)
            possible[i] = possible[i + 1];
        found--;
    }
    fprintf(op,"TF:\n");
    for (int i = 0; i < found; i++)
    {
        fprintf(op, "%d) ",i+1);
        fileput_TF(op, possible[i]);
    }
    fprintf(op,"--------------------\n");
}

void fileput_TF(FILE *op, TF *T)
{
    srand(time(0));
    int r, corr = 0, wrong = 0;
    fprintf(op, "%s\n", T->text);
}

void find_NUM(FILE *op, Paper *P, Bank *B)
{
    NUM *trav;
    NUM **possible = (NUM**)malloc(sizeof(NUM*));
    int found = 0;
    int no_req;
    no_req = P->num_reqs.no_req;
    trav = B->num_list->next;
    found = 0;

    while (trav != NULL)
    {
        if (trav->diff >= P->num_reqs.diff_lb && trav->diff <= P->num_reqs.diff_ub)
        {
            possible = (NUM**)realloc(possible,(found+1)*sizeof(NUM*));
            possible[found++] = trav;
        }

        trav = trav->next;
    }
    if (found < no_req)
    {
        printf("Not enough NUMs, not printing!\n");
    }
    else
    {
        select_NUM(op, possible, found, no_req);
        printf("NUMs found and added!\n");
    }
}

void select_NUM(FILE *op, NUM **possible, int found, int no_req)
{
    int rem;
    srand(time(0));
    while (found != no_req)
    {
        rem = rand() % found;
        for (int i = rem; i < found-1; i++)
            possible[i] = possible[i + 1];
        found--;
    }
    fprintf(op,"NUM:\n");
    for (int i = 0; i < found; i++)
    {
        fprintf(op,"%d) ",i+1);
        fileput_NUM(op, possible[i]);
    }
    fprintf(op,"--------------------\n");
}

void fileput_NUM(FILE *op, NUM *N)
{
    srand(time(0));
    int r, corr = 0, wrong = 0;
    fprintf(op, "%s\n", N->text);
}

