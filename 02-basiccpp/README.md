# Basic C++ Workshop

## Purpose

In this workshop, you will learn how to write and edit basic C++ programs.
If you are not able to attend the workshop, please complete it before onboarding starts as this is crucial to be able to work with your team.

We will be available during the workshop time to help you if you have any problems related to the workshop exercises.
If you have any other questions but are not able to ask during the workshop, don't hesitate to message us on Slack!

## Preparation

1. Go through this [guide](https://github.com/Hyp-ed/hyped-2022/wiki/CPP-Getting-Started) to set up a C++ development environment.
2. Go through [Codecademy C++ course](https://www.codecademy.com/learn/learn-c-plus-plus).
3. (Recommended) Read chapters 0, 1, 2, 4, 5 and 6 from [Learn C++](https://www.learncpp.com/).

## Exercises

A basic C++ project using CMake and GoogleTest has been set up in this folder.
If you were able to compile and run the tests in the official HYPED repository, this one should work just as well.

You can try compiling and running the tests with

```
$ mkdir build
$ cd build
$ cmake ..
$ make test
```

Most tests should fail.

It is recommended that you create a branch `ws2-<your name>` that you will be working on.
This branch won't be merged, but it will help you practice the workflow of adding, commiting and pushing changes.

The exercises may seem easy to some of you, especially the actual programming involved.

### Exercise 1 - Temperatures

In `src/01_temperatures.cpp` there are two functions, `celsiusToKelvin` and `celsiusToFahrenheit`. Both take a `double` and return another `double`.

> From Celsius to Kelvin: `K = C + 273.15`
 
> From Celsius to Fahrenheit: `F = C * 9 / 5 + 32`

### Exercise 2 - Pancakes

In `src/02_pancakes.hpp` you can see a struct containing information about how many pancakes a particular person had for breakfast.

```cpp
struct PancakesEatenBy {
  std::string name;
  int num_pancakes_eaten;
};
```

In particular, each object of type `PancakesEatenBy` has two attributes:

1. A string containing the name of the person, and
2. an integer representing the number of pancakes eaten by that person.

In the source file (`src/02_pancakes.cpp`) you can find a function `mostPancakesEaten`.

> Modify it so that, given a vector of `PancakesEatenBy` objects, it returns the the one where the number of eaten pancakes is the highest.

Below this, you can see another function, `moreThanNPancakesEaten`, which not only takes a vector of `PancakeEaten` objects, but also an integer `n`.

> Modify it so that it returns a vector of those `PancakeEaten` objects where the number of pancakes eaten is strictly greater than `n`.

### Exercise 3 - Vectors

In `src/03_vectors.cpp` there are four functions `sum`, `absoluteSum`, `countNegatives` and `average`. Fill out the implementation for all 4 functions

> Modify the `sum` function implementation so that it returns the sum of all the elements of the vector.

You may want to use range-based `for`-loops:

```cpp
const std::vector<double> v = {1, 2, 3, 4, 5};
for (const double x : v) {
    // in each iteration, x will take the value of the next element of v
}
```

The next function in the file is called `absoluteSum`.
By absolute sum we mean the sum of the absolute values of all the elements.

> Modify `absoluteSum` so that it computes the absolute sum of all the elements of the given vector.

You may find the [abs](https://www.cplusplus.com/reference/cmath/abs/) function from the C++ standard library helpful.
Note that you will have to include the appropriate header file! (see the example on the linked page)

The next function in the file is called `countNegatives`.
It also takes a vector of floating point numbers, but it returns an unsigned integer.

> Modify it so that it returns the number of negative elements in the vector.

The last function in the file is called `average`. 
It takes a vector of floating point numbers, and returns the average.

> Modify it so that it returns the average of all elements in the vector.

### Exercise 4 - Prime Number

In `src/04_isprime.cpp`, there's a function `isPrime` that takes an integer `n` and returns a boolean indicating whether the number is a prime or not.

> Prime numbers are numbers that are only divisable by itself and 1.

You can be creative with the algorithm you use to do this