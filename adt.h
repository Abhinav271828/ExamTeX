#include <stdio.h>
#include <stdlib.h>

#ifndef __ADT__
#define __ADT__

//Header file defining ADTs

typedef struct Bank Bank;
typedef struct MCQ MCQ;
typedef struct FITB FITB;
typedef struct TF TF;
typedef struct NUM NUM;
typedef struct Paper Paper;
typedef struct Request Request;

//Question bank file; linked list of questions for each type
struct Bank
{
    struct MCQ* mcq_list;
    struct FITB* fitb_list;
    struct TF* tf_list;
    struct NUM* num_list;
};

//MCQ type question
struct MCQ
{
    char* text;
    char** corr;
    char** wrong;
    int no_ops;
    float diff;
    float score;
    struct MCQ* next;
};

//Fill in the Blank type question
struct FITB
{
    char* text;
    char* ans;
    float diff;
    float score;
    struct FITB* next;
};

//True/False type question
struct TF
{
    char* text;
    char ans;
    float diff;
    float score;
    struct TF* next;
};

//Numerical type question
struct NUM
{
    char* text;
    int ans;
    float diff;
    float score;
    struct NUM* next;
};

//Question paper file; list of requests, one for each type
struct Paper
{
    struct Request mcq_reqs[10];
    struct Request fitb_reqs;
    struct Request tf_reqs;
    struct Request num_reqs;
};

//Each request
struct Request
{
    int no_req;
    float diff_lb;
    float diff_ub;
    int no_ops;
};

//Functions
//Initialisation
Bank* create_bank();
MCQ*  create_MCQ();
FITB* create_FITB();
TF*   create_TF();
NUM*  create_NUM();

//Parsing QBank
Bank* parse_bank();
MCQ*  parse_MCQ();
FITB* parse_FITB();
TF*   parse_TF();
NUM*  parse_NUM();

#endif
