#include "Headers/structs.h"
#include "Headers/stack.h"
#include "Headers/functions.h"

int main (void)
{
    char paper[50], bank[50];
    FILE* bk, pr, op; Bank* B; Paper* P;
    printf("Enter question bank filename: ");
    scanf("%s",&bank);
    printf("Enter question paper filename: ");
    scanf("%s",&paper);
    
    bk = fopen(bank,"r");
    pr = fopen(paper,"r");
    B = parse_bank(bk);
    P = parse_paper(pr);

    op = fopen("output.txt","a");
    find_MCQ(op,P,B);
    find_FITB(op,P,B);
    find_TF(op,P,B);
    find_NUM(op,P,B);
}
