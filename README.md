
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

Answer:

```cpp
void Example2(int a = 0, int n) {
   int i = n;
   while (i > 0) {
       a += i;
       i /= 2;
   }
}
```

Answer:

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

Answer:

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

Answer:

## Question 3 (10 Points. Easy)

What does it mean when we say that the Merge Sort (MS) algorithm is asymptotically more efficient than the Bubble Sort (BS) algorithm? Support your choice with an explanation.

1. MS will always be a better choice for small inputs
2. MS will always be a better choice for large inputs
3. BS will always be a better choice for small inputs
4. MS will always be a better choice for all inputs

Answer:

## Question 4 (10 Points. Easy)

Create an account on GitHub and Stack Overflow and paste the link to your profile.

Answer:

GitHub profile link:

Stack Overflow profile link:

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

