#include "Headers/structs.h"
#include "Headers/stack.h"
#include "Headers/functions.h"

int main(void)
{
    char paper[50], bank[50], output[50];
    char c;
    FILE *bk, *pr, *op;
    Bank *B;
    Paper *P;
    
    printf("Enter question bank filename: ");
    scanf("%s", bank);

    printf("Enter question paper filename: ");
    scanf("%s", paper);

    printf("Enter output filename: ");
    scanf("%s", output);

    // Opens the question bank in read mode 
    bk = fopen(bank, "r");                                 
    if (bk == NULL)
    {
        printf("Bank file %s failed to open.\n", bank);
        exit(0);
    }

    // Opens the question paper in read mode 
    pr = fopen(paper, "r");
    if (pr == NULL)
    {
        printf("Paper file %s failed to open.\n", paper);
        exit(0);
    }

    // Starts reading the question bank
    B = parse_bank(bk);
    printf("Bank parsed successfully.\n");

    // Starts reading the question paper
    P = parse_paper(pr);
    printf("Paper parsed successfully.\n");

    // Opens the output file in write mode
    op = fopen(output, "w");
    if (op == NULL)
    {
        printf("Output file %s failed to open.\n", output);
        exit(0);
    }
    printf("Output file opened in write mode\n");

    // Finds MCQ type question to 
    // be added in the Output file
    find_MCQ(op, P, B);

    // Finds Fill in the blank type question to 
    // be added in the Output file
    find_FITB(op, P, B);

    // Finds True/False type question to 
    // be added in the Output file
    find_TF(op, P, B);

    // Finds Numerical type question to 
    // be added in the Output file
    find_NUM(op, P, B);

    free(B);
    free(P);
    // Closes the Output file
    fclose(op);

    MCQ* trav1 = B->mcq_list;
    MCQ* temp1;
    while (trav1->next != NULL)
    {
        temp1 = trav1->next;
        trav1->next = trav1->next->next;
        free(temp1->text);
        for (int i = 0; i < temp1->no_corr ; i++) free(temp1->corr[i]);
        for (int i = 0; i < temp1->no_ops - temp1->no_corr;i++) free(temp1->wrong[i]);
        free(temp1);
    }
    free(trav1);

    FITB* trav2 = B->fitb_list;
    FITB* temp2;
    while (trav2->next != NULL)
    {
        temp2 = trav2->next;
        trav2->next = trav2->next->next;
        free(temp2->text);
        free(temp2);
    }
    free(trav2);

    TF* trav3 = B->tf_list;
    TF* temp3;
    while (trav3->next != NULL)
    {
        temp3 = trav3->next;
        trav3->next = trav3->next->next;
        free(temp3->text);
        free(temp3);
    }
    free(trav3);

    NUM* trav4 = B->num_list;
    NUM* temp4;
    while (trav4->next != NULL)
    {
        temp4 = trav4->next;
        trav4->next = trav4->next->next;
        free(temp4->text);
        free(temp4);
    }
    free(trav4);

    for (int i = 0; i < 10; i++)
        free(P->mcq_reqs[i]);
    free(P->fitb_reqs);
    free(P->tf_reqs);

}
