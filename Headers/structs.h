#ifndef __ADT__
#define __ADT__

#include <stdio.h>
#include <stdlib.h>

//Header file defining ADTs

typedef struct Bank Bank;
typedef struct MCQ MCQ;
typedef struct FITB FITB;
typedef struct TF TF;
typedef struct NUM NUM;
typedef struct Paper Paper;
typedef struct Request Request;

typedef struct MCQ* ListMCQ;
typedef struct FITB* ListFITB;
typedef struct TF* ListTF;
typedef struct NUM* ListNUM;

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
    float diff, score;
    float score;
    struct MCQ* next;
};

//Fill in the Blank type question
struct FITB
{
    char* text;
    char* ans;
    float diff,score;
    float score;
    struct FITB* next;
};

//True/False type question
struct TF
{
    char* text;
    char ans;
    float diff, score;
    float score;
    struct TF* next;
};

//Numerical type question
struct NUM
{
    char* text;
    int ans;
    float diff, score;
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

//Each request in question paper
struct Request
{
    int no_req;
    float diff, score_lb;
    float diff, score_ub;
    int no_ops;
};