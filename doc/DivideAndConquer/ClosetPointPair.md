# Closest Point Pair Finding Algorithm

叶璨铭, 12011404@mail.sustech.edu.cn

The corresponding code of this documentation is [here](https://github.com/2catycm/P_Algorithm_Design_and_Analysis_cpp/tree/master/src/main/cpp/cn/edu/SUSTech/YeCanming/Algs/DivideAndConquer/ClosestPoint.hpp)
and it has a Google test suite [here](https://github.com/2catycm/P_Algorithm_Design_and_Analysis_cpp/tree/master/src/test/cpp/cn/edu/SUSTech/YeCanming/Algs/DivideAndConquer/GTestClosestPoint.cpp)

The test suite is passed and has a code coverage of 97%

![image-20220404150143009](ClosetPointPair.assets\image-20220404150143009.png)

[TOC]

##  1. Design Algorithm for 3D points

### 1.1 Problem Description

$$
Given\ a\ multi\ set\ P \subseteq \R^3,\ find \ p1, p2 \in P\\
such\ that\ p1\ne p2\\
euclideanDistance(p1, p2)\le euclideanDistance(p3, p4)\\
for\ \forall \ p3, p4\in P\ and\ p3\ne p4
$$

in which the Euclidean distance is calculated by the square root of the sum of the square of the coordinate differences. 

### 1.2 Divide

We can order the set elements by their x coordinate. 

Then the problem can be divide according to x coordinate order.

In the space, what we are doing is recursively finding the closest point pair in small x part of P and large x part of P, and the next question is how to merge the answer to be the closest point pair on the whole set P.

### 1.3 Conquer *

#### 1.3.1 merged_min_dist and mergedClosestPoint

Calculate the less distance from the answer of left and right

#### 1.3.2 




## 2. Analysis for the algorithm

### 1.1 Problem Description

To describe the problem,  we can use std::vector in c++ to represent P, and iterator to represent where the closest points are. See 3.2 . 

Then, the essential basic operations like random access and division for point P are O(1). 

### 1.2 Divide

Efficient divide should exactly divide the set into 2 parts such that their length l1 and l2 satisfies:
$$
|l1-l2|<=1
$$
Before doing loop, an O(nlogn) sorting is done to get the x sorted array.

### 1.3 Conquer



## 3. Five Nonnegligible Implementation Details and Potential Pitfalls

The idea shown in section 1. and analysis in section 2. have created an illusion that the algorithm is easy to implement and easy to be efficient. However, when I tried to implement the 2D closest point algorithm, I have found 5 nonnegligible Implementation Details on the solution decision tree. If you fail to notice them, the algorithm may not be O(NlogN) and would output wrong answers in some cases. Some open-source codes I found on CSDN and github were trapped in too. Check your code now!

### 3.1 Pitfall 1: How do you rebuild y-ordered points?



### 3.2 Pitfall 2: d or 2d? The choice of logically existing auxiliary boxes

### 3.2 Detail 1: C++ algorithm lib style —— iterators to represent range

### 3.3 Detail 2: How do you filter the points between middle x range?

### 3.4 Detail 3: Conquer：merge-sort first or closest point first?

### 3.5 Pitfall 3: "Wrong right pitfall" in X-division 

## 4. Further questions

- Is there a O(NlogN) algorithm given the dimension k? (k>3)

  

## References

[^1]: [ 最邻近点对问题(Closest-Pair Problem)：一二三维下的分治解法详解_oO悠悠游游Oo的博客-CSDN博客](https://blog.csdn.net/Carl_Rabbit/article/details/106822028)

