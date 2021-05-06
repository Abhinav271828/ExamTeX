#include "../Headers/structs.h"
#include "../Headers/functions.h"
#include "../Headers/stack.h"

Bank* parse_bank(FILE* B)
{
    Bank* bk = init_bank();
    char c;
    Stack part = create_empty();
    Stack brack = create_empty();
    char wd[10];
    fscanf(B,"%c",&c);
    while(1)
    {
        if (c == '\\')
        {
            for (int i = 0; i < 5; i++) fscanf(B,"%c",&wd[i]); wd[5] = '\0';
            if (strcmp(wd,"begin"))
            {
                printf("Unrecognised sequence \\%s\n",wd);
                exit(0);
            }
            fscanf(B,"%c",&c);
            if (c == '{')
                push(brack,'{');
            else
            {
                printf("Unrecognised sequence begin%c\n",c);
                exit(0);
            }
        }

        if (top(brack) = '{')
        {
            for (int i = 0; i < 5; i++) fscanf(B,"%c",&wd[i]); wd[5] = '\0';
            if (strcmp(wd,"type="))
            {
                printf("Unrecognised sequence %s\n",wd);
                exit(0);
            }
            push(part,'t');
            int j = 0;
            fscanf(B,"%c",&wd[j++]);
            while (wd[j-1] != '}')
            {
                fscanf(B,"%c",&wd[j++]);
            }
            wd[j-1] = '\0';
            fscanf(B,"%c",&c);
            while (c == ' ' || c == '\t' || c == '\n') fscanf(B,"%c",&c);
            fseek(B,-1L,SEEK_CUR);
            if (!strcmp(wd,"mcq"))
            {
                bk->mcq_list = parse_MCQ(B,part);
            }
            if (!strcmp(wd,"fitb"))
            {
                bk->fitb_list = parse_FITB(B,part);
            }
            if (!strcmp(wd,"num"))
            {
                bk->num_list = parse_NUM(B,part);
            }
            if (!strcmp(wd,"tf"))
            {
                bk->tf_list = parse_TF(B,part);
            }
        }

        fscanf(B," %c",&c);
    }
}

ListMCQ parse_MCQ(FILE* B, Stack part)
{
    //FILE* B = fopen("qbankmcq.txt","r");
    char c;
    char wd[10];
    char text[50];
    float diff;
    int pos, opcount;
    Stack brack = create_empty(); //Stack part = create_empty();
    ListMCQ L = init_MCQ();
    MCQ* M = init_MCQ();
 
    //push(part,'t');
    fscanf(B,"%c",&c);
    while (1)
    {
        if (c == '\\')
        {
            for (int i = 0; i < 3; i++) fscanf(B,"%c",&wd[i]); wd[3] = '\0';
            if (!strcmp(wd,"end"))
            {
                fscanf(B,"%c",&c);
                if (c == '{')
                {
                    push(brack,c);
                    continue;
                }
            }
            for (int i = 3; i < 5; i++) fscanf(B,"%c",&wd[i]); wd[5] = '\0';
            if (strcmp(wd,"begin"))
            {
                printf("Unrecognised sequence \\%s\n",wd);
                exit(0);
            }
            fscanf(B,"%c",&c);
            if (c == '{')
            {
                push(brack,c);
                continue;
            }
        }
    
        if (top(brack) == '{')
        {
            if (top(part) == 't')
            {
                for (int i = 0; i < 4; i++) fscanf(B,"%c",&wd[i]); wd[4] = '\0';
                if (!strcmp(wd,"type"))
                {
                    fscanf(B,"%c",&c);
                    if (c != '}')
                    {
                        printf("Unrecognised sequence {%s%c}\n",wd,c);
                        exit(0);
                    }
                    pop(brack);
                    pop(part);
                    break;
                }
                for (int i = 4; i < 8; i++) fscanf(B,"%c",&wd[i]); wd[8] = '\0';
                if (strcmp(wd,"question"))
                {
                    printf("Unrecognised part %s\n",wd);
                    exit(0);
                }
                fscanf(B,"%c",&c);
                if (c != ';')
                {
                    printf("Unrecognised difficulty delimiter\n");
                    exit(0);
                }
    
                fscanf(B,"%f",&diff);
                M->diff = diff;
                
                fscanf(B,"%c",&c);
                if (c == '}')
                {
                    pop(brack);
                }
                else
                {
                    printf("Difficulty NaN\n");
                    exit(0);
                }
                push(part,'q');
            }
    
            else if (top(part) == 'q')
            {
                for (int i = 0; i < 8; i++) fscanf(B,"%c",&wd[i]); wd[8] = '\0';
                if (strcmp(wd,"question"))
                {
                    printf("Unrecognised question terminator {%s}\n",wd);
                    exit(0);
                }
                fscanf(B,"%c",&c);
                if (c == '}')
                {
                    pop(brack);
                }
                else
                {
                    printf("Unrecognised question terminator {%s}\n",wd);
                    exit(0);
                }
                pop(part);
 
            }
        }
    
        if (top(part) == 'q')
        {
            fscanf(B," %c",&c);
            if (c != '\"')
            {
                printf("\" missing\n");
                exit(0);
            }
            pos = 0;
            fscanf(B,"%c",&c);
            while (c != '\"')
            {
                text[pos++] = c;
                fscanf(B,"%c",&c);
            }
            text[pos] = '\0';
            M->text = (char*)malloc(strlen(text) * sizeof(char));
            strcpy(M->text,text);
    
            fscanf(B," %c%c",&wd[0],&wd[1]); wd[2] = '\0';

            if (strcmp(wd,"\\\\"))
            {
                printf("Unrecognised option delimiter\n");
                exit(0);
            }
            
            opcount = 0;
            fscanf(B," %c",&c);
            if (c != '\"')
            {
                printf("\" missing\n");
                exit(0);
            }
            pos = 0;
            fscanf(B,"%c",&c);
            while (c != '\"')
            {
                text[pos++] = c;
                fscanf(B,"%c",&c);
            }
            text[pos] = '\0';
            M->corr = (char**)malloc(sizeof(char*));
            M->corr[0] = (char*)malloc(strlen(text) * sizeof(char));
            strcpy(M->corr[0],text);
            opcount++;
    
            fscanf(B," %c",&c);
            
            while (c == '&')
            {
                fscanf(B," %c",&c);
                if (c != '\"')
                {
                    printf("\" missing\n");
                    exit(0);
                }
                pos = 0;
                fscanf(B,"%c",&c);
                while (c != '\"')
                {
                    text[pos++] = c;
                    fscanf(B,"%c",&c);
                }
                text[pos] = '\0';
                M->corr = realloc(M->corr,(opcount + 1) * sizeof(char*));
                M->corr[opcount] = (char*)malloc(strlen(text) * sizeof(char));
                strcpy(M->corr[opcount++],text);
    
                fscanf(B," %c",&c);
            }
    
            M->no_corr = opcount;
    
            if (c != '\\')
            {
                printf("Unrecognised correct option delimiter\n");
                exit(0);
            }

            fscanf(B,"%c",&c);
            if (c != '\\')
            {
                printf("Unrecognised correct option delimiter\n");
                exit(0);
            }
    
            opcount = 0;
            fscanf(B," %c",&c);
            if (c != '\"')
            {
                printf("\" missing\n");
                exit(0);
            }
            pos = 0;
            fscanf(B,"%c",&c);
            while (c != '\"')
            {
                text[pos++] = c;
                fscanf(B,"%c",&c);
            }
            text[pos] = '\0';
            M->wrong = (char**)malloc(sizeof(char*));
            M->wrong[0] = (char*)malloc(strlen(text) * sizeof(char));
            strcpy(M->wrong[0],text);
            opcount++;
    
            fscanf(B," %c",&c);
            
            while (c == '&')
            {
                fscanf(B," %c",&c);
                if (c != '\"')
                {
                    printf("\" missing\n");
                    exit(0);
                }
                pos = 0;
                fscanf(B,"%c",&c);
                while (c != '\"')
                {
                    text[pos++] = c;
                    fscanf(B,"%c",&c);
                }
                text[pos] = '\0';
                M->wrong = realloc(M->wrong,(opcount + 1) * sizeof(char*));
                M->wrong[opcount] = (char*)malloc(strlen(text) * sizeof(char));
                strcpy(M->wrong[opcount++],text);
    
                fscanf(B," %c",&c);
            }
            M->no_ops = M->no_corr + opcount;
            
            InsertMCQ(L,M);
            M = init_MCQ();

            if (c != '\\')
            {
                printf("Unrecognised question terminator\n");
                exit(0);
            }

            for (int i = 0; i < 3; i++) fscanf(B,"%c",&wd[i]); wd[3] = '\0';
            if (strcmp(wd,"end"))
            {
                printf("Unrecognised sequence \\%s\n",wd);
                exit(0);
            }
            
            fscanf(B,"%c",&c);
            if (c == '{')
            {
                push(brack,'{');
                continue;
            }
        }
    
        fscanf(B," %c",&c);
    }

    return L;
}

Paper* parse_paper(FILE* P)
{
    Paper* pr = init_paper();
    char c;
    Stack part = create_empty();
    Stack brack = create_empty();
    char wd[10];
    fscanf(B,"%c",&c);
    while(c != EOF)
    {
        if (c != '\\')
        {
            printf("Unrecognised beginning character\n");
            exit(0);
        }

        for (int i = 0; i < 6; i++) fscanf(B,"%c",&wd[i]); wd[6] = '\0';
        if (strcmp(wd,"sample"))
        {
            printf("Unrecognised sequence %s\n",wd);
            exit(0);
        }

        fscanf(B,"%c",&c);
        if (c != '{')
        {
            printf("Unrecognised sample%c\n",c);
            exit(0);
        }
        for (int i = 0; i < 5; i++) fscanf(B,"%c",&wd[i]); wd[5] = '\0';
        if (strcmp(wd,"type="))
        {
            printf("Unrecognised sequence %s\n",wd);
            exit(0);
        }
        fscanf(B,"%c",&c);
        if (c == 'm')
        {
            wd[0] = 'm';
            fscanf(B,"%c%c",&wd[1],&wd[2]); wd[3] = '\0';
            if (strcmp(wd,"mcq"))
            {
                printf("Unrecognised type %s\n",wd);
                exit(0);
            }
            fscanf(B,"%c",&c);
            if (c != '(')
            {
                printf("No_ops not given\n");
                exit(0);
            }
            for (k = 0; k < 10; k++) if (pr->mcq_reqs[k] == 0) break;
            if (k == 10)
            {
                printf("Too many mcq requests!\n");
                exit(0);
            }
            fscanf(B,"%d",&pr->mcq_reqs[k].no_ops);
            fscanf(B,"%c",&c);
            if (c != ')')           
            {
                printf("No_ops NaN\n");
                exit(0);
            }
            fscanf(B,"%c",&c);
            if (c != '}')
            {
                printf("Intervening characters before }\n");
                exit(0);
            }
            fscanf(B,"%c",&c);
            if (c != '{')
            {
                printf("Intervening characters before {\n");
                exit(0);
            }
            fscanf(B,"%c%c",&wd[0],&wd[1]); wd[2] = '\0';
            if (strcmp(wd,"#="))
            {
                printf("Unrecognised sequence %s\n",wd);
                exit(0);
            }
            fscanf(B,"%d",&pr->mcq_reqs[k].no_req);
            fscanf(B,"%c",&c);
            if (c != '}')
            {
                printf("Intervening characters before }\n");
                exit(0);
            }
            fscanf(B,"%c",&c);
            if (c != '{')
            {
                printf("Intervening characters before {\n");
                exit(0);
            }

            for (int i = 0; i < 8; i++) fscanf(B,"%c",&wd[i]); wd[8] = '\0';
            if (strcmp(wd,"diff in "))
            {
                printf("Unrecognised sequence %s\n",wd);
                exit(0);
            }
            fscanf(B,"%d",&pr->mcq_reqs[k].diff_lb);
            fscanf(B,"%c",&c)
            if (c != ',')
            {
                printf("Unrecognised LB/UB delimiter %c\n",c);
                exit(0);
            }
            fscanf(B,"%d",&pr->mcq_reqs[k].diff_ub);
            fscanf(B,"%c",&c);
            if (c != '}')
            {
                printf("UB NaN\n");
                exit(0);
            }
        }
        if (c == 'f')
        {
            wd[0] = 'f';
            fscanf(B,"%c%c%c",&wd[1],&wd[2],&wd[3]); wd[4] = '\0';
            if (strcmp(wd,"fitb"))
            {
                printf("Unrecognised type %s\n",wd);
                exit(0);
            }
            fscanf(B,"%c",&c);
            if (c != '}')
            {
                printf("Unrecognised type fitb%c\n",c);
                exit(0);
            }
            fscanf(B,"%c",&c);
            if (c != '{')
            {
                printf("Intervening characters before {\n");
                exit(0);
            }
            fscanf(B,"%c%c",&wd[0],&wd[1]); wd[2] = '\0';
            if (strcmp(wd,"#="))
            {
                printf("Unrecognised sequence %s\n",wd);
                exit(0);
            }
            fscanf(B,"%d",&pr->fitb_reqs.no_req);
            fscanf(B,"%c",&c);
            if (c != '}')
            {
                printf("No_req NaN");
                exit(0);
            }
            fscanf(B,"%c",&c);
            if (c != '{')
            {
                printf("Intervening characters before {\n");
                exit(0);
            }

            for (int i = 0; i < 8; i++) fscanf(B,"%c",&wd[i]); wd[8] = '\0';
            if (strcmp(wd,"diff in "))
            {
                printf("Unrecognised sequence %s\n",wd);
                exit(0);
            }
            fscanf(B,"%d",&pr->fitb_reqs.diff_lb);
            fscanf(B,"%c",&c)
            if (c != ',')
            {
                printf("Unrecognised LB/UB delimiter %c\n",c);
                exit(0);
            }
            fscanf(B,"%d",&pr->fitb_reqs.diff_ub);
            fscanf(B,"%c",&c);
            if (c != '}')
            {
                printf("UB NaN\n");
                exit(0);
            }
        }
        if (c == 't')
        {
            wd[0] = 't';
            fscanf(B,"%c",&wd[1]); wd[2] = '\0';
            if (strcmp(wd,"tf"))
            {
                printf("Unrecognised type %s\n",wd);
                exit(0);
            }
            fscanf(B,"%c",&c);
            if (c != '}')
            {
                printf("Unrecognised type tf%c\n",c);
                exit(0);
            }
            fscanf(B,"%c",&c);
            if (c != '{')
            {
                printf("Intervening characters before {\n");
                exit(0);
            }
            fscanf(B,"%c%c",&wd[0],&wd[1]); wd[2] = '\0';
            if (strcmp(wd,"#="))
            {
                printf("Unrecognised sequence %s\n",wd);
                exit(0);
            }
            fscanf(B,"%d",&pr->tf_reqs.no_req);
            fscanf(B,"%c",&c);
            if (c != '}')
            {
                printf("No_req NaN");
                exit(0);
            }
            fscanf(B,"%c",&c);
            if (c != '{')
            {
                printf("Intervening characters before {\n");
                exit(0);
            }

            for (int i = 0; i < 8; i++) fscanf(B,"%c",&wd[i]); wd[8] = '\0';
            if (strcmp(wd,"diff in "))
            {
                printf("Unrecognised sequence %s\n",wd);
                exit(0);
            }
            fscanf(B,"%d",&pr->tf_reqs.diff_lb);
            fscanf(B,"%c",&c)
            if (c != ',')
            {
                printf("Unrecognised LB/UB delimiter %c\n",c);
                exit(0);
            }
            fscanf(B,"%d",&pr->tf_reqs.diff_ub);
            fscanf(B,"%c",&c);
            if (c != '}')
            {
                printf("UB NaN\n");
                exit(0);
            }
        }
        if (c == 't')
        {
            wd[0] = 't';
            fscanf(B,"%c%c",&wd[1],&wd[2]); wd[3] = '\0';
            if (strcmp(wd,"num"))
            {
                printf("Unrecognised type %s\n",wd);
                exit(0);
            }
            fscanf(B,"%c",&c);
            if (c != '}')
            {
                printf("Unrecognised type num%c\n",c);
                exit(0);
            }
            fscanf(B,"%c",&c);
            if (c != '{')
            {
                printf("Intervening characters before {\n");
                exit(0);
            }
            fscanf(B,"%c%c",&wd[0],&wd[1]); wd[2] = '\0';
            if (strcmp(wd,"#="))
            {
                printf("Unrecognised sequence %s\n",wd);
                exit(0);
            }
            fscanf(B,"%d",&pr->num_reqs.no_req);
            fscanf(B,"%c",&c);
            if (c != '}')
            {
                printf("No_req NaN");
                exit(0);
            }
            fscanf(B,"%c",&c);
            if (c != '{')
            {
                printf("Intervening characters before {\n");
                exit(0);
            }

            for (int i = 0; i < 8; i++) fscanf(B,"%c",&wd[i]); wd[8] = '\0';
            if (strcmp(wd,"diff in "))
            {
                printf("Unrecognised sequence %s\n",wd);
                exit(0);
            }
            fscanf(B,"%d",&pr->num_reqs.diff_lb);
            fscanf(B,"%c",&c)
            if (c != ',')
            {
                printf("Unrecognised LB/UB delimiter %c\n",c);
                exit(0);
            }
            fscanf(B,"%d",&pr->num_reqs.diff_ub);
            fscanf(B,"%c",&c);
            if (c != '}')
            {
                printf("UB NaN\n");
                exit(0);
            }
        }

        fscanf(B," %c",&c);
    }
    
    return pr;
}
ListNUM parse_NUM(FILE* B, Stack part)
{
//     FILE* B = fopen("numtest.txt","r");
    char c,poop;
    int ans;
    char wd[10];
    char text[50];
    float diff;
    int pos;
    Stack brack = create_empty(); //Stack part = create_empty();
    ListNUM L = init_NUM();
    NUM* M = init_NUM();
 
    // push(part,'t');
    fscanf(B," %c",&c);
    while (1)
    {
        if (c == '\\')
        {
            for (int i = 0; i < 3; i++) fscanf(B,"%c",&wd[i]); wd[3] = '\0';
            if (!strcmp(wd,"end"))
            {
                fscanf(B,"%c",&c);
                if (c == '{')
                {
                    push(brack,c);
                    continue;
                }
            }
            for (int i = 3; i < 5; i++) fscanf(B,"%c",&wd[i]); wd[5] = '\0';
            if (strcmp(wd,"begin"))
            {
                printf("Unrecognised sequence \\%s\n",wd);
                exit(0);
            }
            fscanf(B,"%c",&c);
            if (c == '{')
            {
                push(brack,c);
                continue;
            }
        }
    
        if (top(brack) == '{')
        {
            if (top(part) == 't')
            {
                for (int i = 0; i < 4; i++) fscanf(B,"%c",&wd[i]); wd[4] = '\0';
                if (!strcmp(wd,"type"))
                {
                    fscanf(B,"%c",&c);
                    if (c != '}')
                    {
                        printf("Unrecognised sequence {%s%c}\n",wd,c);
                        exit(0);
                    }
                    poop=pop(brack);
                    //printf("%c\n",poop);
                    poop=pop(part);
                    //printf("%c\n",poop);
                    break;
                }
                for (int i = 4; i < 8; i++) fscanf(B,"%c",&wd[i]); wd[8] = '\0';
                if (strcmp(wd,"question"))
                {
                    printf("Unrecognised part %s\n",wd);
                    exit(0);
                }
                fscanf(B,"%c",&c);
                if (c != ';')
                {
                    printf("Unrecognised difficulty delimiter\n");
                    exit(0);
                }
    
                fscanf(B,"%f",&diff);
                M->diff = diff;
                
                fscanf(B,"%c",&c);
                if (c == '}')
                {
                    poop=pop(brack);
                    //printf("%c\n",poop);
                }
                else
                {
                    printf("Difficulty NaN\n");
                    exit(0);
                }
                push(part,'q');
            }
    
            else if (top(part) == 'q')
            {
                for (int i = 0; i < 8; i++) fscanf(B,"%c",&wd[i]); wd[8] = '\0';
                if (strcmp(wd,"question"))
                {
                    printf("Unrecognised question terminator {%s}\n",wd);
                    exit(0);
                }
                fscanf(B,"%c",&c);
                if (c == '}')
                {
                    poop=pop(brack);
                    //printf("%c\n",poop);
                }
                else
                {
                    printf("Unrecognised question terminator {%s}\n",wd);
                    exit(0);
                }
                poop=pop(part);
                //printf("%c\n",poop);
            }
        }
    
        if (top(part) == 'q')
        {
            fscanf(B," %c",&c);
            // printf("%c",c);
            if (c != '\"')
            {
                printf("\" missing\n");
                exit(0);
            }
            // printf("%c",c);

            pos = 0;
            fscanf(B,"%c",&c);
            while (c != '\"')
            {
                text[pos++] = c;
                fscanf(B,"%c",&c);
            }
            text[pos] = '\0';
            M->text = (char*)malloc((strlen(text)+1) * sizeof(char));
            strcpy(M->text,text);
    
            fscanf(B," %c%c",&wd[0],&wd[1]); wd[2] = '\0';
    
            if (strcmp(wd,"\\\\"))
            {
                printf("Unrecognised option delimiter\n");
                exit(0);
            }
            
            fscanf(B," %d",&ans);
            M->ans = ans;
            
            InsertNUM(L,M);

            M = init_NUM();

            fscanf(B," %c",&c);

            if (c != '\\')
            {
                printf("Unrecognised question terminator\n");
                exit(0);
            }

            for (int i = 0; i < 3; i++) fscanf(B,"%c",&wd[i]); wd[3] = '\0';
            if (strcmp(wd,"end"))
            {
                printf("Unrecognised sequence \\%s\n",wd);
                exit(0);
            }
            
            fscanf(B,"%c",&c);
            if (c == '{')
            {
                push(brack,'{');
                continue;
            }
        }
    
        fscanf(B," %c",&c);
    }
    return L;
}

ListTF parse_TF(FILE* B, Stack part)
{
//     FILE* B = fopen("numtest.txt","r");
    char c,poop;
    char ans;
    char wd[10];
    char text[50];
    float diff;
    int pos;
    Stack brack = create_empty(); //Stack part = create_empty();
    ListTF L = init_TF();
    TF* M = init_TF();
 
    // push(part,'t');
    fscanf(B," %c",&c);
    while (1)
    {
        if (c == '\\')
        {
            for (int i = 0; i < 3; i++) fscanf(B,"%c",&wd[i]); wd[3] = '\0';
            if (!strcmp(wd,"end"))
            {
                fscanf(B,"%c",&c);
                if (c == '{')
                {
                    push(brack,c);
                    continue;
                }
            }
            for (int i = 3; i < 5; i++) fscanf(B,"%c",&wd[i]); wd[5] = '\0';
            if (strcmp(wd,"begin"))
            {
                printf("Unrecognised sequence \\%s\n",wd);
                exit(0);
            }
            fscanf(B,"%c",&c);
            if (c == '{')
            {
                push(brack,c);
                continue;
            }
        }
    
        if (top(brack) == '{')
        {
            if (top(part) == 't')
            {
                for (int i = 0; i < 4; i++) fscanf(B,"%c",&wd[i]); wd[4] = '\0';
                if (!strcmp(wd,"type"))
                {
                    fscanf(B,"%c",&c);
                    if (c != '}')
                    {
                        printf("Unrecognised sequence {%s%c}\n",wd,c);
                        exit(0);
                    }
                    poop=pop(brack);
                    //printf("%c\n",poop);
                    poop=pop(part);
                    //printf("%c\n",poop);
                    break;
                }
                for (int i = 4; i < 8; i++) fscanf(B,"%c",&wd[i]); wd[8] = '\0';
                if (strcmp(wd,"question"))
                {
                    printf("Unrecognised part %s\n",wd);
                    exit(0);
                }
                fscanf(B,"%c",&c);
                if (c != ';')
                {
                    printf("Unrecognised difficulty delimiter\n");
                    exit(0);
                }
    
                fscanf(B,"%f",&diff);
                M->diff = diff;
                
                fscanf(B,"%c",&c);
                if (c == '}')
                {
                    poop=pop(brack);
                    //printf("%c\n",poop);
                }
                else
                {
                    printf("Difficulty NaN\n");
                    exit(0);
                }
                push(part,'q');
            }
    
            else if (top(part) == 'q')
            {
                for (int i = 0; i < 8; i++) fscanf(B,"%c",&wd[i]); wd[8] = '\0';
                if (strcmp(wd,"question"))
                {
                    printf("Unrecognised question terminator {%s}\n",wd);
                    exit(0);
                }
                fscanf(B,"%c",&c);
                if (c == '}')
                {
                    poop=pop(brack);
                    //printf("%c\n",poop);
                }
                else
                {
                    printf("Unrecognised question terminator {%s}\n",wd);
                    exit(0);
                }
                poop=pop(part);
                //printf("%c\n",poop);
            }
        }
    
        if (top(part) == 'q')
        {
            fscanf(B," %c",&c);
            // printf("%c",c);
            if (c != '\"')
            {
                printf("\" missing\n");
                exit(0);
            }
            // printf("%c",c);

            pos = 0;
            fscanf(B,"%c",&c);
            while (c != '\"')
            {
                text[pos++] = c;
                fscanf(B,"%c",&c);
            }
            text[pos] = '\0';
            M->text = (char*)malloc((strlen(text)+1) * sizeof(char));
            strcpy(M->text,text);
    
            fscanf(B," %c%c",&wd[0],&wd[1]); wd[2] = '\0';
    
            if (strcmp(wd,"\\\\"))
            {
                printf("Unrecognised option delimiter\n");
                exit(0);
            }
            
            fscanf(B," %d",&ans);
            M->ans = ans;
            
            InsertTF(L,M);

            M = init_TF();

            fscanf(B," %c",&c);

            if (c != '\\')
            {
                printf("Unrecognised question terminator\n");
                exit(0);
            }

            for (int i = 0; i < 3; i++) fscanf(B,"%c",&wd[i]); wd[3] = '\0';
            if (strcmp(wd,"end"))
            {
                printf("Unrecognised sequence \\%s\n",wd);
                exit(0);
            }
            
            fscanf(B,"%c",&c);
            if (c == '{')
            {
                push(brack,'{');
                continue;
            }
        }
    
        fscanf(B," %c",&c);
    }
    return L;
}
