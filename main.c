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

    bk = fopen(bank, "r");
    if (bk == NULL)
    {
        printf("Bank file %s failed to open.\n", bank);
        exit(0);
    }
    pr = fopen(paper, "r");
    if (pr == NULL)
    {
        printf("Paper file %s failed to open.\n", paper);
        exit(0);
    }

    B = parse_bank(bk);
    printf("Bank parsed\n");

    P = parse_paper(pr);
    printf("Paper parsed\n");

    op = fopen(output, "w");
    if (op == NULL)
    {
        printf("Output file %s failed to open.\n", output);
        exit(0);
    }
    printf("Output file opened in write mode\n");

    find_MCQ(op, P, B);
    find_FITB(op, P, B);
    find_TF(op, P, B);
    find_NUM(op, P, B);
    fclose(op);
}
