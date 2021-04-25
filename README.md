# ExamTeX
DSA Miniproject, Spring 2021, IIIT Hyderabad

## Syntax
Question Bank:

\begin{type=<type>(params)}
<list of questions>
\end{type}

mcq ("mcq"):

\begin{question;diff}
"question\_text" \\ "corr\_op1" & "corr\_op2" \\ "op3" & "op4"
\end{question}

short answer ("fitb"):

\begin{question;diff}
"question\_text" \\ "ans"
\end{question}

numerical ("num"):

\begin{question;diff}
"text" \\ ans
\end{question}

true/false ("tf"):

\begin{question;diff}
"question\_text" \\ ans
\end{question}

Sample QBank File:
\begin{type=mcq}
    \begin{question;2.0}
        "What kind of language is C?" \\ "object-oriented" & "imperative" \\ "functional" & "object-based"
    \end{question}
\end{type}

\begin{type=fitb}
    \begin{question;3.0}
        "C is a \_\_\_\_\_ language." \\ "imperative"
    \end{question}
\end{type}

\begin{type=num}
    \begin{question;5.0}
        "How many years ago was C created?" \\ 52
    \end{question}
\end{type}

\begin{type=tf}
    \begin{question;1.0}
             "C is a functional language." \\ F
    \end{question}
\end{type}


Question Paper:

\sample{type=<type>}{#=<num>}{diff in LB,UB}
(for mcq, give no\_ops)

Sample QPaper File:
\sample{type=mcq(3)}{#=1}{diff in 2.0,3,0}
\sample{type=tf}{#=1}{diff in 0.5,2.5}

Output:
1. What kind of language is C?
(a) functional
(b) object-oriented
(c) imperative

2. True or false: C is a functional language.
