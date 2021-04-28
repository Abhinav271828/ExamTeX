#include"adt.h"

NUM* create_NUM(char* text, int ans , float diff)
{
    NUM* P = (NUM*)malloc(sizeof(NUM));

    strcpy(P->text,text);
    P->ans = ans;
    P->diff = diff;
    P->score = 0;
    P->next = NULL;

    return P;
}

NUM* init_NUM()
{
    NUM* P = create_NUM("",0,0.0f);
    return P;
}

MCQ* create_MCQ(char* text, int co_op, int total_op, float diff)
{
    MCQ* P = (MCQ*)malloc(sizeof(MCQ));
    strcpy(P->text,text);
    P->corr = (char**)malloc(co_op * sizeof(char*));
    P->wrong = (char**)malloc((total_op - co_op) * sizeof(char*));
    P->no_ops = total_op;
    P->diff = diff;
    P->score = 0;
    P->next = NULL;
    
    return P;
}

MCQ* init_MCQ()
{
    MCQ* P = create_MCQ("",0,0,0.0f);
    return P;
}

FITB* create_FITB(char* text,char* ans,float diff)
{
    FITB* P = (FITB*)malloc(sizeof(FITB));

    strcpy(P->text,text); 
    strcpy(P->ans,ans);
    P->diff = diff;
    P->score = 0; 
    P->next = NULL;

    return P;
}
FITB* init_FITB()
{
    FITB* P = create_FITB("","",0.0f);
    return P;
}
