#ifndef __FUNCS
#define __FUNCS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Header file declaring functions

//Initialisation
Bank* init_bank();
MCQ*  init_MCQ();
FITB* init_FITB();
TF*   init_TF();
NUM*  init_NUM();
Paper* init_paper();
void init_request(Request* R);


//Creating nodes
MCQ* create_MCQ(char* text, float diff);
FITB* create_FITB(char* text, char* ans , float diff);
TF* create_TF(char* text, char ans , float diff);
NUM* create_NUM(char* text, int ans , float diff);

//Parsing QBank
Bank* parse_bank(FILE* B);
ListMCQ  parse_MCQ(FILE* B, Stack part);
ListFITB parse_FITB(FILE* B, Stack part);
ListTF   parse_TF(FILE* B, Stack part);
ListNUM  parse_NUM(FILE* B, Stack part);

// Inserting nodes in linked list
void InsertMCQ(ListMCQ L , MCQ* X);
void InsertFITB(ListFITB L , FITB* X);
void InsertTF(ListTF L , TF* X);
void InsertNUM(ListNUM L , NUM* X);

#endif
