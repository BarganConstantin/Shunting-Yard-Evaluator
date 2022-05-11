# Web evaluator of mathematical expressions based on the Shunting Yard algorithm

<div align="center">
  <kbd>
    <img src="https://user-images.githubusercontent.com/60443226/166941721-71b7d086-9167-4cb9-b172-556fa9d235b8.png" alt="MarineGEO circle logo" width="800"/>
  </kbd>
</div>
<br/>

Table of Contents
=================
* [Abstract](#Abstract)
* [Introduction](#Introduction)
* [Problem and solution analysis](#Problem-and-solution-analysis)
* [Algorithm analysis](#Algorithm-analysis)
    * [The algorithm in detail](#The-algorithm-in-detail)

<br/>

# Abstract

&nbsp;&nbsp;&nbsp;&nbsp;It is surprising the transformation of algorithmic thinking, from a particular mathematical tool, into a fundamental way of approaching problems in fields that apparently have nothing to do with mathematics. This universality of algorithmic thinking is the result of the connection between the algorithm and the computer. Today, by algorithm we mean a general method of solving a certain type of problem, a method that can be implemented on a computer. In this context, an algorithm is the absolute essence of a routine. Basically, it was found that there is no field, no matter how inaccurate and fluctuating it may seem, in which we cannot discover algorithmically functioning sectors.

&nbsp;&nbsp;&nbsp;&nbsp;In this project, we analyzed and implemented the Shunting Yard algorithm, which is very important
because it simplified calculations in digital devices, and gave a new concept on technologies.

&nbsp;&nbsp;&nbsp;&nbsp;Ideally, for a given problem, we should find several algorithms, and then choose the best one from
them. But what is the criterion for comparison? The efficiency of an algorithm can be expressed in several
ways. We can analyze a empirically the behavior of the algorithm after implementation, by running different
cases on the computer. Or, we can analyze a theoretically the algorithm, before programming it, by
quantitatively determining the resources (time, memory) needed as a function of the size of the case considered,
theoretically in a similar way. Memory-execution time issues can also arise.

&nbsp;&nbsp;&nbsp;&nbsp;Understanding this algorithm, will bring us closer to knowing what is going on behind different highperformance programming languages, because the act of creating an algorithm is an art that can never be fully automated. It is basically the universal mechanism of human creativity, which produces the new through an extremely complex synthesis such as: elaboration techniques (rules) + creativity (intuition) = solution.

<br/>

# Introduction

&nbsp;&nbsp;&nbsp;&nbsp;All programmers and of course students are familiar with the use of mathematical operators. For example, to add two values x and y, will be used the plus sign. Few know, in fact, that this is borrowed from mathematical notation called infix notation, which is a big problem for digital devices. That's why math forms an internal mini-language, used in almost any programming language.

&nbsp;&nbsp;&nbsp;&nbsp;The first programming language, which was a real success, was Fortran, the main cause being related to the fact that the arithmetic expressions (ie formulas) were converted into code (translated), hence the name - FORmula TRANslation. Until then, it was necessary to write things like "make up (a, multiply (a, b))", to ensure a correct order of operations. In the Cobol language, solving the problem of implementing automatic formula conversion was considered very difficult because programmers had to write things like "Add A To B Multiply By C". The problem is that operators have properties such as priority and associativity. Therefore, defining an infix function becomes a difficult issue. For example, multiplication has a higher priority than addition or subtraction, which means that the expression "2 + 3 * 4" is not equal to the sum of 2 and 3 multiplied by 4, if we perform the operations from left to right. In fact, we need to multiply 3 by 4 and add 2.

&nbsp;&nbsp;&nbsp;&nbsp;This example shows us that the evaluation of infix expressions often requires rearranging operators and their operands, and for the expression to be easier to read we must also use parentheses, because "(2 + 3) * (4 + 5)" cannot be written without parentheses, otherwise multiplication should be performed first.

&nbsp;&nbsp;&nbsp;&nbsp;The two best known alternatives to infix expressions are writing operators before or after operands, known as prefix and postfix notations. Their logic was put in place by Jan Lukasiewicz in 1920, and since he lived in Poland, the post-fixed variant is also called reverse Polish notation. In this notation an operator is written after its operands, therefore the expression "A + B" is "A B +".
        
&nbsp;&nbsp;&nbsp;&nbsp;Therefore, we can say that the fixed notation is an arithmetic and logical representation in which the operator is placed between two operands, at the same time in this case the order of operations is indicated by the parentheses that must surround the operators and operands. In turn, post-fixed notation is the notation used to determine the value of an expression using numerical devices. These notations are called Polish notation, which is a way of writing expressions in which the order of operators and operands is changed from that used in a common expression.

&nbsp;&nbsp;&nbsp;&nbsp;The advantage of Polish notation is that it indicates the correct order of assessment of operators without the use of parentheses.

<br/>

# Problem and solution analysis

&nbsp;&nbsp;&nbsp;&nbsp;After learning that the mathematical notations we are used to are called infixed notations, which is shown below in Figure 1, I understood that the value of such expressions can be evaluated by numerical devices only when they are represented in the postfix form. Therefore, we are ready to formulate the problem that we need to solve, namely: How to transform the elementary arithmetic expressions from the infixed form to the postfixed one, and to find out later its value.

<div align="center">
  <kbd>
    <img src="https://user-images.githubusercontent.com/60443226/166949437-55285c51-57b5-4c00-8bd9-13ab2c7dec06.png" alt="MarineGEO circle logo" width="600"/>
  </kbd>
</div>
<br/>

&nbsp;&nbsp;&nbsp;&nbsp;To solve this problem we will use the algorithm presented by Edsger Dijkstra in 1961 called Shunting Yard. So, this algorithm allows us to bring the infix expressions to the postfix form, and then in a single scan to determine the value of the data entered.

The advantages of this algorithm:
- simple to understand;
- easy to implement, although a solid implementation could have several thousand lines of code;
- has a linear time complexity;
- linear space complexity;
- determines the value of the expression in a single scan;
- can be improved to handle more complicated formulas.

<br/>

# Algorithm analysis

&nbsp;&nbsp;&nbsp;&nbsp;In computer science, the shunting-yard algorithm is a method of analyzing mathematical expressions, which are represented in infix notation. The algorithm was invented by Edsger Dijkstra and is called the "sorting station", because its operation is very similar to the actions of a railway triage.

## The algorithm in detail

&nbsp;&nbsp;&nbsp;&nbsp;The given algorithm works using two strings: one input and one output, but it also includes the stack, which in turn is to store instructions that are not yet added to the output queue. As for conversion, the algorithm reads one character at a time and performs actions based on it.

&nbsp;&nbsp;&nbsp;&nbsp;In the initial version of the algorithm, it parses the expression from left to right, thus constructing its postfix equivalent, and each time an operand is encountered it is immediately transferred to the output stream. Thus, operators could be temporarily stored in the stack before being moved into the outflow to ensure the correct order of operations.

&nbsp;&nbsp;&nbsp;&nbsp;Now, let's consider what happens when the expression can contain parentheses. A pair of matching parentheses is equivalent to a compound operand, which must be analyzed as an expression in itself.

So it is understandable that:
- an open parenthesis, behaves like the beginning of a new expression, in the sense that its previous operands do not belong to the operands that are located after it. Thus, until we meet the closing parenthesis, we will not be able to examine any of the operators in it. For example, in the expression "1 * 2 + 3" we usually do the multiplication only after we have met the meeting, but if we have "1 * (2 + 3)", even if we meet the addition, the multiplication will not take place before its;
- a closed parenthesis behaves like the end of an expression, because once we get to it, we have to evaluate all the operators accumulated on the stack.

<div align="center">
  <kbd>
    <img src="https://user-images.githubusercontent.com/60443226/166941736-dadb8798-5d28-4836-8b7a-30852cee4718.png" alt="MarineGEO circle logo" width="800"/>
  </kbd>
</div>
<br/>

<div align="center">
  <kbd>
    <img src="https://user-images.githubusercontent.com/60443226/166941754-76709ac8-a2b0-452b-9565-a10463aaf6f8.png" alt="MarineGEO circle logo" width="800"/>
  </kbd>
</div>
<br/>

<div align="center">
  <kbd>
    <img src="https://user-images.githubusercontent.com/60443226/166941776-d508ad43-b50f-48e5-87da-1b43cf0dc688.png" alt="MarineGEO circle logo" width="800"/>
  </kbd>
</div>
<br/>

<div align="center">
  <kbd>
    <img src="https://user-images.githubusercontent.com/60443226/166941499-43ae4459-d220-4f78-8d3a-c2e46ac14d7e.png" alt="MarineGEO circle logo" width="800"/>
  </kbd>
</div>
<br/>
