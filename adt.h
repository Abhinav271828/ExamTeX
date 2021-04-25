//Header file defining ADTs

typedef struct Bank Bank;
typedef struct MCQ MCQ;
typedef struct FITB FITB;
typedef struct TF TF;
typedef struct NUM NUM;
typedef struct Paper Paper;
typedef struct Request Request;

//Question bank file; arrays of questions for each type
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
}

//Fill in the Blank type question
struct FITB
{
    char* text;
    char* ans;
    float diff;
    float score;
}

//True/False type question
struct TF
{
    char* text;
    char ans;
    float diff;
    float score;
}

//Numerical type question
struct NUM
{
    char* text;
    int ans;
    float diff;
    float score;
}

//Question paper file; list of requests, one for each type
struct Paper
{
    struct Request mcq_reqs;
    struct Request fitb_reqs;
    struct Request tf_reqs;
    struct Request num_reqs;
}

//Each request
struct Request
{
    int no_req;
    float diff_lb;
    float diff_ub;
    int no_ops;
}
