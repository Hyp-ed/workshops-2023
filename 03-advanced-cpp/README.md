# Advanced C++ Workshop

## Purpose

In this workshop, you will learn more about writing, editing and testing C++ program.
In particular, you will be introduced to using some of the most common standard library features, to writing automated tests using GoogleTest and to handling some of the more subtle behaviour that C++ allows you to introduce.

## Preparation

1. Go through the [git & GitHub Workshop](https://github.com/Hyp-ed/workshops-2023/tree/master/01-git) including the preparation steps.
2. Go through the [Basic C++ Workshop](https://github.com/Hyp-ed/workshops-2023/tree/master/02-basic-cpp) including the preparation steps.

## Exercises

Similar to the Basic C++ Workshop and the main HYPED repository, a CMake project has been set up in this workshop's folder. Make sure you can compile and run the test suit right away using the following commands 

```
$ mkdir build
$ cd build
$ cmake ..
$ make -j
$ ctest
```

Most tests should fail.

It is recommended that you create a branch `ws2-<your name>` to commit your changes 
to. This branch won't be merged, but it will help you develop the habit of adding,
committing and pushing changes asap.

### Exercise 1 - Quadaratic Polynomials and their Roots

Please have a look at `src/01_roots.hpp`. You will find a class that represents a quadratic polynomial with real coefficients. 

You may notice that a `key` method as well as the `==` and `!=` operators have been implemented for the class.
These are solely for testing pruposes. However, you may want to inspect the code anyways.
In particular, pay attention to the use of the `const` keyword which is used in several places.

> Implement the primary constructor for `QuadraticPolynomial` in `src/01_roots.cpp`.

Next, we would like to know whether a particular real number is a solution to our quadratic.
However, we are limited by [floating point representation](https://en.wikipedia.org/wiki/IEEE_754).
In essence, arithmetic operations between values of type `double` or `float` introduce an error that may cause a direct comparison to fail.
Therefore, we have introduced a constant `QuadraticPolynomial::kTolerance`.
We define the value of a polynomial `y = ax^2 + bx + c` to be equal to a real number `z` if `|y - z| < kTolerance`.

> Implement the `isRoot` function by using the `kTolerance` constant.

*Note: A root of a polynomial is a (real) number `x` such that `ax^2 + bx + c = 0`.*

Finally, we would like to find all the real roots of a particular quadratic.
Due to our definition of equality, there are potentially many more values that pass the `isRoot` test than we would expect algebraically.

> Implement the `realRoots` function such (1) that the number of roots returned matches the number of algebraic roots, (2) for each algebraic root there is at least one return value within the equality tolerance, and (3) each return value is within the equality tolerance of at least one algebraic root.

### Exercise 2 - Sorting

In `02_sorting.hpp` you will find a struct `Person` which contains a name and an age. Further, there's a function that's called `sortByAge` which is supposed to sort a vector of persons by age in ascending order.
If you now have a look at the corresponding source file, you will find that the function has already been implemented.
This is because *it will be your task to implement the tests in `test/02_sorting.test.cpp`*.

In GoogleTest, you have a couple of tools to help you. You may use 

- `ASSERT_TRUE(x)` or `ASSERT_FALSE(x)` to check whether a condition `x` is true or false respectively,
- `ASSERT_EQ(x, y)` or `ASSERT_NE(x, y)` to check whether `x` and `y` are equal or not, and
- `EXPECT_ANY_THROW(x)` if you expect `x` to throw an exception.

If an assertion fails, so will the test.
If an exception is thrown, the test will also fail.

> Implement the test `emptyInput` to verify the behaviour of `workshop::sortByAge` on an empty input vector. 

Feel free to have a look around some of the other test files if you are stuck!

> Next, implement the test `sortedInput` to verify the behaviour of `workshop::sortByAge` on a vector of persons which are already in non-decreasing age order.

> Now modify `reversedInput` so that it does what the name suggests!

Finally, we want to handle some less straight forward cases.
You can either come up with some inputs that are out of order or you may use `std::shuffle` to randomise the tests.

> Modify `randomInput` to test `workshop::sortByAge` with irregular inputs.

### Exercise 3 - Linear Regression

For this exercise, two functions have been implemented.
One to calculate the mean of a sample (a vector of points).
The other performs a simple linear regression on a sample and returns a linear model.

We think the implementations work, but we cannot be sure until we actually test them.
It will be up to you to come up with some tests to verify both of them work correctly.

> Create a file `test/03_linear_regression.hpp` add tests for both `calculateMean` and `linearRegression`.

Note that once the file has been created you may need to delete your build directory and run CMake again.

Some properties you may find interesting:

1. The mean of a single point is itself.
2. The mean of a sample lies on the linear regression line.
3. If the data has a perfect linear relation, all the points will lie on the linear regression line.
