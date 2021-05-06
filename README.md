# ExamTeX
DSA Miniproject, Spring 2021, IIIT Hyderabad

## Syntax
The syntax of the question bank file is as follows: for each type,  

    \begin{type=<type>}
    <list of questions>
    \end{type}

In the list of questions, each question's format is as follows: for MCQs,  

    \begin{question;<diff>}
    "question_text" \\ "corr_op1" & "corr_op2" \\ "wrong_op1" & "wrong_op2"
    \end{question}

for fill in the blanks,

    \begin{question;<diff>}
    "question_text" \\ "ans"
    \end{question}

for numerical,

    \begin{question;<diff>}
    "text" \\ ans
    \end{question}

for true/false,  

    \begin{question;<diff>}
    "question_text" \\ ans
    \end{question}



The syntax of the question paper file is as follows: a "request" for each type of question has the format  

    \sample{type=<type>}{#=<num>}{diff in <LB>,<UB>}

In the case of MCQs, the number of options required must be given in parentheses (e.g. `mcq(3)`).

## Running Test Cases
For compiling the program, `cd` into the repo and run the `make` command. To run it, execute `./a.out`. If you want to run one of the included tests, please enter the file path at the prompt as follows:

    Enter question bank filename: Sample\ Files/QBanks/test1.txt
    Enter question paper filename: Sample\ Files/QPapers/test1.txt

The output file will be generated in the root directory itself.
