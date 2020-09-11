
# HW1 EE599 - Computing Principles for Electrical Engineers

- Plesae clone the repository, edit [README.md](README.md) to answer the questions, and fill up functions to finish the hw.
- For non-coding quesitions, you will find **Answer** below each question. Please write your answer there.
- For coding questions, please make sure that your code can run ```blaze run/test```. In this homework, you will need to fill up [cpplib.cc](src/lib/cpplib.cc), [q5_student_test.cc](tests/q5_student_test.cc), [q6_student_test.cc](tests/q6_student_test.cc), [q7_student_test.cc](tests/q7_student_test.cc) for question  5, 6, 7.
- For submission, please push your answers to Github before the deadline.
- Deadline: Friday, September 4th by 6:30 pm
- Total: 120 points. 100 points is considered full credit.

## Question 1 (10 Points. Medium)

Use proof by contradiction to prove that the FindMax function always finds the maximum value in the input vector.

```cpp
int FindMax(std::vector<int> &inputs) {
   if (inputs.size() == 0) {
       return -1;
   }
   int result = INT32_MIN;
   for (auto n : inputs) {
       if (n > result) {
           result = n;
       }
   }
   return result;
}
```

Answer:
1. When the inputs.size == 0;
It is meaningless. The function will return -1 to show no inputs (unsuccessful).

2. When the inputs.size !=0;
Assuming that the value that the FindMax function finds is not the maximum value. However, if the result finally is still INT32_MIN, all items in inputs should be INT32_MIN. In this case, INT32_MIN is the maximun value, so our assuming is wrong.
If the value of result finally is x, since x is not the maximum value in our assuming, the final result should be the maximum value when n == the maximum value. This is contradictory. For this reason, our assuming is wrong.

All in all, we prove that the FindMax function always finds the maximum value in the input vector.

## Question 2 (20 Points. Medium)

What is the time complexity of the below functions?

```cpp
int Example1(int n) {
   int count = 0;
   for (int i = n; i > 0; i /= 2) {
       for (int j = 0; j < i; j++) {
           count += 1;
       }
   }
   return count;
}
```

Answer: O(n)
Think about how many times count++ will run.
When i = n, it will run n times.
When i = n/2, it will run n/2 times.
When i = n/4, it will run n/4 times and so on.
Total number of times count++ will run is n + n/2 + n/4 +...+ 1 = 2*n. So the time complexity will be O(n).


```cpp
void Example2(int a = 0, int n) {
   int i = n;
   while (i > 0) {
       a += i;
       i /= 2;
   }
}
```

Answer: O(logn)
i could be n, n/2, n/4, n/8 ... 1. It means that i is n*(1/2)^k. When n*(1/2)^k = 1; k = logn. So a += i will run logn times, the time complexity will be O(logn). 


```cpp
void Example3(int n) {
   int count = 0;
   for (int i=n/2; i<=n; i++) {
       for (int j=1; j<=n; j = 2 * j) {
           for (int k=1; k<=n; k = k * 2) {
               count++;
           }
       }
   }
}
```

Answer: O(n*(log2)^2)
For the third loop, count++ will run logn times (just like the upper question).
For the second loop, it will also run logn times for itself. And since the third loop doesn't need to use j, so everytime j++, the third one will run logn times. In this case, count++ of the seond and the third ones will run (logn)^2 times.
For the first loop, it will run n/2 + 1. And other loops also don't depend on i, so total number of times count++ will run is n*(log2)^2.


```cpp
void Example4(int n) {
   int count = 0;
   for (int i=0; i<n; i++)
       for (int j=i; j< i*i; j++)
           if (j%i == 0)
           {
               for (int k=0; k<j; k++)
                   cout<<"*";
           }
}
```

Answer: O(n^4)
When we only think about the second loop, it will run i^2-i times.
For the third loop, when j = i, 2*i, 3*i, 4*i,..., (i-1)*i,  cout<<"*" will run i, 2*i, 3*i, 4*i,..., (i-1)*i times.
So for the second and the third loops, it will run i^2-i + i + 2*i + 3*i + ... + (i-1)*i = (i^3)/2 + 2*i^2 - i.
When we only think about the first loop, it will run n times. For all loops, we need the summation of i^3. So the time complexity will be O(n^4).
## Question 3 (10 Points. Easy)

What does it mean when we say that the Merge Sort (MS) algorithm is asymptotically more efficient than the Bubble Sort (BS) algorithm? Support your choice with an explanation.

1. MS will always be a better choice for small inputs
2. MS will always be a better choice for large inputs
3. BS will always be a better choice for small inputs
4. MS will always be a better choice for all inputs

Answer: 2.
For this question, we only think the worst case. The worst case of BS is O(n^2), but the worst case of MS is O(n*logn). So when the inputs are larger, the gap between n and logn will be larger and logn is smaller that n for larger inputs. So for large inputs, MS always will be a bettery choice.

## Question 4 (10 Points. Easy)

Create an account on GitHub and Stack Overflow and paste the link to your profile.

Answer:

GitHub profile link: https://github.com/Jimmy-Lu-iK

Stack Overflow profile link: https://stackoverflow.com/users/14173055/jimmy-lu?tab=profile

## Question 5 (15 Points. Easy)

Write a simple function ```std::string CPPLib::PrintIntro()``` in [cpplib.cc](src/lib/cpplib.cc) to print your name, email, and any information about you that you want (e.g. your major, your expertise, your interests, etc) and write a test using GTest for your finction in [tests/q5_student_test.cc](tests/q5_student_test.cc).
We will run your code and see your printout!

Please create your test cases and run the following command to verify the functionality of your program.
```
bazel test tests:q5_student_test
```

## Question 6 (25 Points. Medium)

 Write a function ```std::vector<int> CPPLib::Flatten2DVector(const std::vector<std::vector<int>> &input)``` in [cpplib.cc](src/lib/cpplib.cc) to flatten a 2D vector into a 1D vector.

Example:\
Input: inputs = [[1, 2, 3, 4], [5, 6], [7, 8]].\
Output: result = [1, 2, 3, 4, 5, 6, 7, 8].

Write several tests using GTest for your function in [tests/q6_student_test.cc](tests/q6_student_test.cc).\
(Hint: inculde cases with empty vectors)

Please create your test cases and run the following command to verify the functionality of your program.
```
bazel test tests:q6_student_test
```

## Question 7 (30 Points. Medium)

Write a function ```double CPPLib::CalFactorial(int N)``` in [cpplib.cc](src/lib/cpplib.cc) using recursion to find the factorial of any number. Your function should accept positive numbers and return the factorial value. Further, write several tests using GTest for your function in [tests/q7_student_test.cc](tests/q7_student_test.cc) and compute the time complexity of your implementation.

*Definition of the factorial function*\
In mathematics, the factorial of a positive integer n, denoted by n!, is the product of all positive integers less than or equal to n:

```
n ! = n x (n - 1) x (n - 2) x (n - 3) ... (3) x (2) x (1)
```

For example, 4! = 4 × 3 × 2 × 1 = 24.\
The value of 0! is 1. For negative input, please return -1.

Please create your test cases and run the following command to verify the functionality of your program.
```
bazel test tests:q7_student_test
```

For question 5, 6, 7, if you want to run all the tests at the same time , you could run
```
bazel test tests:tests
```

Answer:

