# Closest Point Pair Finding Algorithm

叶璨铭, 12011404@mail.sustech.edu.cn



[TOC]

## 0. Problem Introduction
### 0.0 Basic version of the problem

$$
Given\ a\ multi\ set\ P \subseteq \R^3,\ find \ p1, p2 \in P\\
such\ that\ p1\ne p2\\
euclideanDistance(p1, p2)\le euclideanDistance(p3, p4)\\
for\ \forall \ p3, p4\in P\ and\ p3\ne p4
$$

in which the Euclidean distance is calculated by the square root of the sum of the square of the coordinate differences.

More generally, the dimension of the points can be a constant K. 

To get a better understanding of the basic problem, you can view the basic divide and conquer solution on [oO悠悠游游Oo 's CSDN blog](https://blog.csdn.net/Carl_Rabbit/article/details/106822028) [^1]
### 0.1Online version of the problem

##  1. Literature Review: what algorithms have been proposed?


## 2. Analysis for those algorithm: how to understand their research?



## 3. My C++ Implementation: Details and Unravelled Potential Pitfalls 
Although the ideas shown in section 1. and analysis in section 2. seems easy to implement and easy to be efficient, when I tried to implement the 2D closest point algorithm, I have found 5 nonnegligible Implementation Details on the solution decision tree. If you fail to notice them, the algorithm may not be O(NlogN) and would output wrong answers in some cases. Some open-source codes I found on CSDN and github were trapped in too. Check your code now!
### 3.1 basic divide and conquer solution
The corresponding code of this documentation is [here](https://github.com/2catycm/P_Algorithm_Design_and_Analysis_cpp/tree/master/src/main/cpp/cn/edu/SUSTech/YeCanming/Algs/DivideAndConquer/ClosestPoint.hpp)
and it has a Google test suite [here](https://github.com/2catycm/P_Algorithm_Design_and_Analysis_cpp/tree/master/src/test/cpp/cn/edu/SUSTech/YeCanming/Algs/DivideAndConquer/GTestClosestPoint.cpp)

The test suite is passed and has a code coverage of 97%

![image-20220404150143009](ClosetPointPair.assets\image-20220404150143009.png)


### 3.1.1 Pitfall 1: How do you rebuild y-ordered points?



### 3.1.2 Pitfall 2: d or 2d? The choice of logically existing auxiliary boxes

### 3.1.3 Detail 1: C++ algorithm lib style —— iterators to represent range

### 3.1.4 Detail 2: How do you filter the points between middle x range?

### 3.1.5 Detail 3: Conquer：merge-sort first or closest point first?

### 3.1.6 Pitfall 3: "Wrong right pitfall" in X-division 


## References

[^1]: [ 最邻近点对问题(Closest-Pair Problem)：一二三维下的分治解法详解_oO悠悠游游Oo的博客-CSDN博客](https://blog.csdn.net/Carl_Rabbit/article/details/106822028)

