#include "../Headers/functions.h"
#include "../Headers/stack.h"
#include "../Headers/structs.h"

void find_MCQ(FILE *op, Paper *P, Bank *B)
{
    MCQ *trav;
    MCQ **possible = (MCQ **)malloc(sizeof(MCQ *));         //Will store the suitable questions [array]
    int found = 0;
    int no_req, no_ops;
    for (int i = 0; i < 11; i++)
    {
        no_req = P->mcq_reqs[i]->no_req;                    //To avoid repeatedly accessing
        no_ops = P->mcq_reqs[i]->no_ops;
        if (no_req == 0)                                    //All mcq requests done
        {
            break;
        }
        trav = B->mcq_list->next;                           
        found = 0;

        while (trav != NULL)                                                          //Traverse through linked
        {                                                                             //list and add suitable
            if (trav->no_ops >= no_ops && trav->diff >= P->mcq_reqs[i]->diff_lb &&    //questions to array using
                trav->diff <= P->mcq_reqs[i]->diff_ub)                                //realloc; "found" stores
            {                                                                         //total number found
                possible = (MCQ **)realloc(possible, (found + 1) * sizeof(MCQ *));
                possible[found++] = trav;
            }

            trav = trav->next;
        }
        if (found < no_req)                         //Not enough
        {
            printf("Not enough MCQs (%d found, %d required), not adding!\n", found, no_req);
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
    while (found != no_req)                             //Randomly removes
    {                                                   //questions from
        rem = rand() % found;                           //possible array
        for (int i = rem; i < found - 1; i++)           //until required
            possible[i] = possible[i + 1];              //number is left
        found--;
    }
    fprintf(op, "MCQ with %d options:\n", no_ops);      //Section heading
    for (int i = 0; i < found; i++)                 //Prints each
    {                                               //question and
        fprintf(op, "%d) ", i + 1);                 //its options
        fileput_MCQ(op, possible[i], no_ops);       
    }
    fprintf(op, "--------------------\n");              //End of section
}

void fileput_MCQ(FILE *op, MCQ *M, int no_ops)
{
    srand(time(0));
    int r, corr = 0, wrong = 0;

    fprintf(op, "%s\n", M->text);                                           //Print question text

    for (int i = 0; i < no_ops; i++)
    {
        if (corr < M->no_corr && wrong < M->no_ops - M->no_corr)            //Shuffles options and
        {                                                                   //prints until either
            r = rand() % 2;                                                 //correct or wrong
            if (r == 0)                                                     //options are over; then
            {                                                               //prints remaining correct
                fprintf(op, "   %c) %s\n", i + 97, M->corr[corr++]);        //options and remaining
            }                                                               //wrong options
            if (r == 1)
            {
                fprintf(op, "   %c) %s\n", i + 97, M->wrong[wrong++]);
            }
        }
        else if (wrong >= M->no_ops - M->no_corr)
            fprintf(op, "   %c) %s\n", i + 97, M->corr[corr++]);
        else
            fprintf(op, "   %c) %s\n", i + 97, M->wrong[wrong++]);
    }
}

void find_FITB(FILE *op, Paper *P, Bank *B)
{
    FITB *trav;
    FITB **possible = (FITB **)malloc(sizeof(FITB *));          //Stores the suitable questions [array]
    int found = 0;
    int no_req;
    no_req = P->fitb_reqs->no_req;                              //To avoid repeatedly accessing
    trav = B->fitb_list->next;
    found = 0;

    while (trav != NULL)                                                                    //Traverse through linked
    {                                                                                       //list and add suitable
        if (trav->diff >= P->fitb_reqs->diff_lb && trav->diff <= P->fitb_reqs->diff_ub)     //questions to array using
        {                                                                                   //realloc; "found" stores
            possible = (FITB **)realloc(possible, (found + 1) * sizeof(FITB *));                                                                                       //total number found
            possible[found++] = trav;
        }

        trav = trav->next;
    }

    if (found < no_req)                     //Not enough
    {
        printf("Not enough FITBs (%d found, %d required), not adding!\n", found, no_req);
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
    while (found != no_req)                         //Randomly removes
    {                                               //questions from
        rem = rand() % found;                       //possible array
        for (int i = rem; i < found - 1; i++)       //until required
            possible[i] = possible[i + 1];          //number is left
        found--;
    }
    fprintf(op, "FITB:\n");                         //Section heading
    for (int i = 0; i < found; i++)             //Prints
    {                                           //each
        fprintf(op, "%d) ", i + 1);             //question
        fileput_FITB(op, possible[i]);
    }
    fprintf(op, "--------------------\n");          //End of section
}

void fileput_FITB(FILE *op, FITB *F)
{
    srand(time(0));
    int r, corr = 0, wrong = 0;
    fprintf(op, "%s\n", F->text);               //Only print question text
}

void find_TF(FILE *op, Paper *P, Bank *B)
{
    TF *trav;
    TF **possible = (TF **)malloc(sizeof(TF *));        //Stores the suitable questions [array]
    int found = 0;
    int no_req;
    no_req = P->tf_reqs->no_req;                        //To avoid repeatedly accessing
    trav = B->tf_list->next;
    found = 0;

    while (trav != NULL)                                                                //Traverse through linked   
    {                                                                                   //list and add suitable 
        if (trav->diff >= P->tf_reqs->diff_lb && trav->diff <= P->tf_reqs->diff_ub)     //questions to array using
        {                                                                               //realloc; "found" stores  
            possible = (TF **)realloc(possible, (found + 1) * sizeof(TF *));            //total number found
            possible[found++] = trav;
        }

        trav = trav->next;
    }

    if (found < no_req)                                 //Not enough
    {
        printf("Not enough TFs (%d found, %d required), not adding!\n", found, no_req);
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
    while (found != no_req)                         //Randomly removes
    {                                               //questions from
        rem = rand() % found;                       //possible array
        for (int i = rem; i < found - 1; i++)       //until required
            possible[i] = possible[i + 1];          //number is left
        found--;
    }
    fprintf(op, "TF:\n");                           //Section heading
    for (int i = 0; i < found; i++)         //Prints
    {                                       //each
        fprintf(op, "%d) ", i + 1);         //question
        fileput_TF(op, possible[i]);
    }
    fprintf(op, "--------------------\n");          //End of section
}

void fileput_TF(FILE *op, TF *T)
{
    srand(time(0));
    int r, corr = 0, wrong = 0;
    fprintf(op, "%s\n", T->text);               //Only print question text
}

void find_NUM(FILE *op, Paper *P, Bank *B)
{
    NUM *trav;
    NUM **possible = (NUM **)malloc(sizeof(NUM *));     //Stores the suitable question [array]
    int found = 0;
    int no_req;
    no_req = P->num_reqs->no_req;                       //To avoid repeatedly accessing
    trav = B->num_list->next;
    found = 0;

    while (trav != NULL)                                                                 //Traverse through linked  
    {                                                                                    //list and add suitable  
        if (trav->diff >= P->num_reqs->diff_lb && trav->diff <= P->num_reqs->diff_ub)    //questions to array using
        {                                                                                //realloc; "found" stores
            possible = (NUM **)realloc(possible, (found + 1) * sizeof(NUM *));           //total number found
            possible[found++] = trav;
        }

        trav = trav->next;
    }
    if (found < no_req)                                 //Not enough
    {
        printf("Not enough NUMs (%d found, %d required), not adding!\n", found, no_req);
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
    while (found != no_req)                         //Randomly removes
    {                                               //questions from
        rem = rand() % found;                       //possible array
        for (int i = rem; i < found - 1; i++)       //until required
            possible[i] = possible[i + 1];          //number is left
        found--;
    }
    fprintf(op, "NUM:\n");                          //Section heading
    for (int i = 0; i < found; i++)         //Prints
    {                                       //each
        fprintf(op, "%d) ", i + 1);         //question
        fileput_NUM(op, possible[i]);
    }
    fprintf(op, "--------------------\n");          //End of section
}

void fileput_NUM(FILE *op, NUM *N)
{
    srand(time(0));
    int r, corr = 0, wrong = 0;
    fprintf(op, "%s\n", N->text);               //Only print question
}
