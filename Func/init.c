#include "../Headers/structs.h"
#include "../Headers/functions.h"

NUM* create_NUM(char* text, int ans , float diff)
{
    NUM* P = (NUM*)malloc(sizeof(NUM));
    P->text = (char*)malloc(sizeof(MCQ));
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

MCQ* create_MCQ(char* text, float diff)
{
    MCQ* P = (MCQ*)malloc(sizeof(MCQ));
    P->text = (char*)malloc(strlen(text) * sizeof(char));
    strcpy(P->text,text);
    P->diff = diff;
    P->score = 0;
    P->next = NULL;
    
    return P;
}

MCQ* init_MCQ()
{
    MCQ* P = create_MCQ("",0.0f);
    return P;
}

FITB* create_FITB(char* text,char* ans,float diff)
{
    FITB* P = (FITB*)malloc(sizeof(FITB));
    P->text = (char*)malloc(strlen(text) * sizeof(char));
    P->ans = (char*)malloc(strlen(ans) * sizeof(char));
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
TF* create_TF(char* text, char ans , float diff)
{
    TF* P = (TF*)malloc(sizeof(TF));
    P->text = (char*)malloc(sizeof(MCQ));
    strcpy(P->text,text);
    P->ans = ans;
    P->diff = diff;
    P->score = 0;
    P->next = NULL;

    return P;
}

TF* init_TF()
{
    TF* P = create_TF("",' ',0.0f);
    return P;
}

Bank* init_bank()
{
    Bank* B = (Bank*)malloc(sizeof(Bank));
    B->mcq_list = init_MCQ();
    B->fitb_list = init_FITB();
    B->tf_list = init_TF();
    B->num_list = init_NUM();

    return B;
}

Paper* init_paper()
{
    Paper* P = (Paper*)malloc(sizeof(Paper));

    for (int i = 0; i < 11; i++)
    {
        init_request(&(P->mcq_reqs[i]));
    }

    init_request(&(P->fitb_reqs));
    init_request(&(P->tf_reqs));
    init_request(&(P->num_reqs));

    return P;
}

void init_request(Request* R)
{
    R->no_ops = 0;
    R->no_req = 0;
    R->diff_lb = 0.0f;
    R->diff_ub = 0.0f;
}
