# Closest Point Pair Finding Algorithm

叶璨铭, 12011404@mail.sustech.edu.cn

[TOC]

## 0. Problem Introduction

The closest pair problem is one of the classical problems in computational geometry.[^4]The problem of finding closest point pair is also called Geometric Proximity Problems[^2].Given n points in metric space, it is required to find the two points closest to each other. [^4]

### 0.0 Basic version of the problem

$$
\begin{align}
&Given\ a\ multi\ set\ P \subseteq \R^k,\ find \ p1, p2 \in P\\
&such\ that\ p1\ne p2 \ and\\
&euclideanDistance(p1, p2)\le euclideanDistance(p3, p4)\\
&for\ \forall \ p3, p4\in P\ and\ p3\ne p4
\end{align}
$$

in which the Euclidean distance is calculated by the square root of the sum of the square of the coordinate differences and k is the dimention of the points.

To get a better understanding of the basic problem, you can view the basic divide and conquer solution on [oO悠悠游游Oo 's CSDN blog](https://blog.csdn.net/Carl_Rabbit/article/details/106822028) [^1] and Algorithm Design textbook[^6]. 

To get a more computational theoretical understanding, see the literature review part 1.0 .

### 0.1 Online version of the problem

What happens if new points are being added continuously? Given a sequence of k-dimensional points p1, p2, p3,..., pn arriving one after another, calulate the closest point pair in every time t greater than 2. This is called the online closest pair problem[^4]. Schwarz, Smid and Snoeyink gave an algorithm that solves this prolem in O(NlogN) time[^4]. We will not discuss this algorithm in the rest of the article. 

### 0.2 Applications of the algorithms for this problem

Knowing the closest point pair is important to bruteForceSolve problems in  graphics, computer vision, pattern recognition, clustering, geographical, information systems, molecular modeling, geometric problems and numerous matching problems[^4].

For more concrete examples, ships sailing in the sea and aircrafts flying on the sky can be treated as points in 2d and 3d space. To avoid collision, the traffic control system uses the algorithm to find the most likely vessels or planes to be met[^5]. 

### 0.3 Similar but quite different problems

The following problems looks similar to the closest point pairt problem, but are quite different.

- Iterative closest point algorithm used in point cloud registration
- All cloesest points problem 

> *Given* *N* *points* *in* *the Euclidean* plane, *find* *the* *nearest* *neighbor* *of* ***each**.* [^3]

​	The input P is the same, but this problems requires n points as output O, each one O<sub>i</sub> representing that the nearest neighbour of P<sub>i</sub> . By 1975, no algorithm has yet been found to bruteForceSolve this problem.[^3]  However, Shamosand Hoey designed a good algorithm which can construct the Voronoi diagram in  O(NlogN) time to bruteForceSolve it[^3]. The constants are too big to let it efficient[^4]. But I think the online version of closest point pair problem can bruteForceSolve this with smaller constants.  //TODO demand more research.

- K-nearest neighbour in machine learning
- K-clustering in machine learning

##  1. Literature Review

### 1.0 What is the lower bound and upper bound of the problem?

In order to design an algorithm excellent in time complexity, it\`s quite important to know the lower bound and upper bound of the problem. For example, if we know the lower bound is NlogN[^7], I will feel free to use any O(N) actions and O(NlogN) actions to do data preprocessing.

A method called reduction is used. 

- To begin with, reduction simply means that algorithm B is at least no simplier than (i.e. as complex as or more complex than) algorithm A if A can delegate his input I<sub>a</sub> to algorithm B and gets output O<sub>a</sub> by doing transforms of input and output that are no more complex than algorithm B[^6]. This is because algorithm B is more "versatile" and "reliable", if even a "valuable" problem like B is solved, a easy problem A, which is a "special case of B", can be easily solved. 

- Next, we take the algorithm for a problem called "element-uniqueness-problem"  to be algorithm A. 

  > In [computational complexity theory](https://en.wikipedia.org/wiki/Computational_complexity_theory), the **element distinctness problem** or **element uniqueness problem** is the problem of determining whether all the elements of a list are distinct.[^8]

  It is well known that element uniqueness problem has a lower bound of nlogn (determinstic algorithm)[^3][^4]. This is a typical contribution from the decision tree model. 

- Finally, we can bruteForceSolve the element uniqueness problem by solving the closest point pair problem. If we found the closest distance is 0, then their exists non-unique element, indicating the lower bound of closest point problem, no matter what the dimension k is, is NlogN[^4]. 
- Moreover, the "all cloest point problem" mentioned earlier also has the same lower bound[^3].

On the other hand, the upper bound is quite easy to see. By enumerating the all C<sup>2</sup><sub>n</sub> pairs, we got an θ(N<sup>2</sup>) algorithm. 

[^7]: Note: When I say T(n) has a lower bound of f(n), I mean it is found that T(n)=Ω(f(n)).  Do not say the lower bound of T(n) is Ω(f(n))， by that you mean the lower bounds are at least Ω(f(n)), which is incorrect because 1 is also an lower bound of T(n). In shamos and hoey's essay, they stated that the lower bound is O(N log N), which means all lower bounds of T(n) should not be greater than N logN, allowing the exactly NlogN algorithm to exist. However, their statements are controversal because no other papers I've listed in the reference page state like that.

### 1.1 What algorithms have been proposed?

Shamos and  Hoey proposed a classical algorithm for the two-dimensional closest point pair problem based on divide-and-conquer method., which has been learnt in lecture[^6].  Actually, their orginal paper is far more than two-dimensional closest point pair problem. Shamos and Hoey proposed and proved that the **Voronoi diagram,** which can be constructed in O(NlogN) time, can be applied to obtain O(NlogN) algorithms for all the problems including the eucliean minumum spanning tree, finding closest pairs and constructing triangulation in any finite dimension space[^3]. 

After that milestone, the coming algorithms focus on the practical speed. Research for **2-d** closest point pair are abundant. Zhou, Xiong and Zhu and later in 2006 Ge, Wang and Zhu and then Jiang and Gillespie presented impoved versions for the planar case, **reducing the points to compare for each central slab point from 7 to 4, then to 3 and 2**. Then Hinrichs, Nievergelt and Schorn and later Dalkılıç and Ergun presented empirical fast algorithms for planar case, but not optimal.[^4] In 2019, Ma and Zhan, stated that their algorithm is the better in complexity from the perspective that takes multiplier coefficient into acount. Their algorithm is ~**4/3NlogN**, while the 2006 algorithm is ~3/2NlogN[^5].

So it seems there are few research on developing a practical fast algorithm for k dimension, not even for 3 dimension. The reason may be that the researchers who came up with splendid 2d algorithm fully exploit the property of 2d space. The research for ICP is much more popular in 3d space. 

What's more, Aaronson et. al did research on **quantum time complexity** and got an *Õ*(*n*2/3) algorithm[^9]. 

### 1.2 Algortihms pseudocode

- Basic-2 algorithm proposed by Jiang and Gillespie[^10]

  ```pseudocode
  Step 1. Filter the two arrays Yl and Yr to two arrays Yl` and Yr` of points within distance d from the vertical line through the pivot point.
  Step 2. While both Yl` and Yr` are not empty, choose the lowest point p in Yl` ∪ Yr` then do the following:
  （a) if p is in  Yl`, compute the  distances from p to the（at most) two  lowest points in  Yr`, then set Yl` ← Yl`\{p};
  （b) if p is in  Yr`, compute the  distances from p to the（at most) two  lowest points in  Yl` , then set Yr` ← Yr`\{p}; 
  Let dm be the minimum of these distances. Return min{dl, dr, dm}.
  ```

- Pair-Pruned_CP proposed by Zhou and Yu. [^4]

  ```pseudocode
  Algorithm Pair-Pruned_CP(A)
  Input: An array A[1..n][1..k] containing the n points in kdimensional space
  Output: The closest pair of points and the distance between
  them
  1. presort the n data points according to the values of the
  dimension with the largest range among all the k
  dimensions and store the data points in a two dimensional
  array A[1..n][1..k], so that A[i][1]  A[j][1] if i < j.
  2. determine the initial minimum distance of point pair:
  doptimal.
  3. for i = 1..n-1
  j = i+1;
  while A[j][1]-A[i][1] < doptimal and j <= n
  if |A[j][2]-A[i][2]| < doptimal
  d = distance(A[i],A[j]) // distance computation
  if d < doptimal
  doptimal = d;
  index1 = i; index2 = j; j++;
  end while
  end for
  4. return A[index1], A[index2], doptimal
  ```

## 2. My C++ Implementation: Detail Study on Unravelled Potential Pitfalls 
Although the ideas shown in section 1.  seems easy to implement and easy to be efficient, when I tried to implement the 2D closest point algorithm, I have found 5 nonnegligible Implementation Details on the solution decision tree(the tree to decide what solution should be used to implement the idea properly). If you fail to notice them, the algorithm may not be O(NlogN) and would output wrong answers in some cases. Some open-source codes I found on CSDN and github were trapped in these pitfalls too. Check your code now!

### 2.0 Brute force algorithm serving as performance baseline and correctness criteria

As the proverb goes, "*Speed gets you* *nowhere if you’re* *headed the wrong way.*" Therefore, the first thing we should do is to define the euclidean distance by a template function, making sure we did not goes into the wrong way of "closest".

```cpp
template<typename T, size_t K>
        T euclideanDistance(const std::array<T, K> &a, const std::array<T, K> &b) const {
            T sum = 0;
            for (int i = 0; i < K; ++i) {
                T diff = a[i] - b[i];
                sum += diff * diff;
            }
            return std::sqrt(sum);
        }
```

Next, we define the function interface for the problem.

```cpp
template<typename T, size_t K, typename It = typename std::vector<std::array<T, N>>::const_iterator>
        std::tuple<std::array<It, 2>, T> findClosestPointPairKD(It first, const It last) const;
```

It looks intimidating with inctricate templates, but don't worry.  Let's look at a client example. 

The function desired a range of a points in a vector. For example, we only want to find the closest point pair among the third element, we can use pass v.cbegin()+2 and v.cend() as the argument. This follows the convention of C++ algortihm lib in header \<algorithm\>. The benefit for this convention is that you can bruteForceSolve the problem on the input that you are really interterst. Moreover, it is easy to articulate divide and conquer algorithms or recursive algorithms using iterators to specify the range. 

```cpp
void testClosestPointND(){
    ThisPackage::ClosestPoint closestPoint; //get the algorithm instance. 
    std::vector<std::array<double, 2>> v = {{1, 2},{3, 4}, {2.5, 10}, {10, 2.5}}; // 2d real points contained in a vector.
    auto [pair, dist] = closestPoint.ClosestPointND(v.cbegin()+2, v.cend());
    assert(std::distance(pair[0], pair[1])!=0);//pair[0] and pair[1] are iterators refering to the element in the vector. make sure they are not the same element.
    printf("The cloest point pair is {(%g, %g), (%g, %g)} .\n", (*pair[0])[0], (*pair[0])[1], (*pair[1])[0], (*pair[1])[1]); // *pair[0] is the point itself. and a point is defined as an fixed-length array, where the length k is the dimension of the point.(*pair[0])[0] gets the x coordinate out of it, and (*pair[0])[1] gets the y coordinate out of it. 
    printf("The distance is %g .\n", dist);
}
```

Then the implementation is not hard to understand, we just follows the problem definition.

```cpp
template<typename T, size_t K, typename It = typename std::vector<std::array<T, K>>::const_iterator>
        std::tuple<std::array<It, 2>, T> findClosestPointPairKD(It first, const It last) const {
            const auto size = std::distance(first, last);
            assert(size >= 2);
            T min_dist = std::numeric_limits<T>::max();
            std::array<It, 2> min_index{first, first + 1};
            for (; first != last; ++first) {
                for (It another = first + 1; another != last; ++another) {
                    T dist = this->euclideanDistance(*first, *another);
                    if (min_dist > dist) {
                        min_dist = dist;
                        min_index[0] = first;
                        min_index[1] = another;
                    }
                }
            }
            return std::make_tuple(min_index, min_dist);
        }
```

Now that we have made a perfect brute force algorithm, we can use it as the performance baseline and the answer checker for local algotithm judge (unit test suite), taking advantage of its absolute correctness.

### 2.1 Classical divide and conquer solution

The corresponding code of this documentation is [here](https://github.com/2catycm/P_Algorithm_Design_and_Analysis_cpp/tree/master/src/main/cpp/cn/edu/SUSTech/YeCanming/Algs/DivideAndConquer/ClosestPoint.hpp)
and it has a Google test suite [here](https://github.com/2catycm/P_Algorithm_Design_and_Analysis_cpp/tree/master/src/test/cpp/cn/edu/SUSTech/YeCanming/Algs/DivideAndConquer/GTestClosestPoint.cpp)

The test suite is passed and has a code coverage of 97%

![image-20220404150143009](ClosetPointPair.assets\image-20220404150143009.png)


#### 2.1.1 Pitfall 1: How do you rebuild y-ordered points?

Assume we divide the points according to the order of x coordinate.  

Role model: closest-pair-3d library written by eyny[^11]

#### 2.1.2 Pitfall 2: d or 2d? The choice of logically existing auxiliary boxes

#### 2.1.3 Detail 1: C++ algorithm lib style —— iterators to represent range

#### 2.1.4 Detail 2: How do you filter the points between middle x range?

Typical wrong code example: closest-pair-3d library written by eyny[^11]

```cpp
//In case of there are other balls which share same X position as middle point
	bool putToRightArr = true;
	//Distribute balls into left and right vectors
	for (int i = 0; i < size; i++)
	{
		if (sortedY[i]->posX < midBall->posX)
			leftVector.push_back(sortedY[i]);
		else if (sortedY[i]->posX > midBall->posX)
			rightVector.push_back(sortedY[i]);
		else //if (sortedY[i].posX == midBall.posX)
		{
			if (putToRightArr)
				rightVector.push_back(sortedY[i]);
			else
				leftVector.push_back(sortedY[i]);
			putToRightArr = !putToRightArr;
		}
	}
```

If you divide the problem like him, when you occur input points with same x-coordinate, the program will not divide anything, only to let the points transfered to the rightVector again and again. 

Don't say that input points with same x-coordinate are impossible. Someone who uses your library may oneday wants to bruteForceSolve the problem on 2d space only, and he specifies the x coordinate to 0 on purpose to delegate the problem to your code, only to find it trapped into endless loop. In addition, the quick-sort algorithm had the same problem to consider, which cultivates a imporved method called three-way quicksort. 

#### 2.1.5 Detail 3: Conquer：merge-sort first or closest point first?

#### 2.1.6 Pitfall 3: "Wrong right pitfall" in X-division 


## References

[^1]: [ 最邻近点对问题(Closest-Pair Problem)：一二三维下的分治解法详解_oO悠悠游游Oo的博客-CSDN博客](https://blog.csdn.net/Carl_Rabbit/article/details/106822028)

[^2]: Sack, J. R., & Urrutia, J. (Eds.). (1999). *Handbook of computational geometry*， Chapter 20 Closest-Point Problems in Computational Geometry. Elsevier. 

[^3]: M. I. Shamos and D. Hoey, "Closest-point problems," 16th Annual Symposium on Foundations of Computer Science (sfcs 1975), 1975, pp. 151-162, doi: 10.1109/SFCS.1975.8.
[^4]: Y. Zhou and H. Yu, "An Efficient Comparison-Based Deterministic Algorithm to Solve the Closest Pair Problem," 2015 8th International Conference on Intelligent Computation Technology and Automation (ICICTA), 2015, pp. 145-148, doi: 10.1109/ICICTA.2015.45.
[^5]: J. Ma, B. C. Zhan and F. Li, "A New Improved Algrithom of Two-Dimensional Closest Point Pair," 2019 IEEE 5th International Conference on Computer and Communications (ICCC), 2019, pp. 29-33, doi: 10.1109/ICCC47050.2019.9064062.

[^6]: 课本：Kleinberg & Tardos 算法设计。

[^8]: [Element distinctness problem - Wikipedia](https://en.wikipedia.org/wiki/Element_distinctness_problem)
[^9]: Scott Aaronson, Nai-Hui Chia, Han-Hsuan Lin, Chunhao Wang, and Ruizhe Zhang. 2020. On the quantum complexity of closest pair and related problems. In <i>Proceedings of the 35th Computational Complexity Conference</i> (<i>CCC '20</i>). Schloss Dagstuhl--Leibniz-Zentrum fuer Informatik, Dagstuhl, DEU, Article 16, 1–43. DOI:https://doi.org/10.4230/LIPIcs.CCC.2020.16
[^10]: Jiang, M., Gillespie, J. Engineering the Divide-and-Conquer Closest Pair Algorithm. *J Comput Sci Technol* **22,** 532–540 (2007). https://doi.org/10.1007/s11390-007-9066-y
[^11]: [closest-pair-3d/ballmanager.cpp at master · eyny/closest-pair-3d (github.com)](https://github.com/eyny/closest-pair-3d/blob/master/src/ballmanager.cpp)

