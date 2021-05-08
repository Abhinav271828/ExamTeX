#include "Headers/structs.h"
#include "Headers/stack.h"
#include "Headers/functions.h"

int main (void)
{
    char paper[50], bank[50], output[50]; char c;
    FILE *bk, *pr, *op; Bank* B; Paper* P;
    printf("Enter question bank filename: ");
    scanf("%s",bank);
    printf("Enter question paper filename: ");
    scanf("%s",paper);
    printf("Enter output filename: ");
    scanf("%s",output);

    bk = fopen(bank,"r");
    pr = fopen(paper,"r");
    B = parse_bank(bk);
    printf("Bank parsed\n");
    P = parse_paper(pr);
    printf("Paper parsed\n");

    op = fopen(output,"w");
    printf("Output file opened in write mode\n");
    find_MCQ(op,P,B);
    find_FITB(op,P,B);
    find_TF(op,P,B);
    find_NUM(op,P,B);
    fclose(op);
}