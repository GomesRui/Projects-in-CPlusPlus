# Project Range_me() C++

Exercise:

"You need to provide an API that will allow other developers to create and manipulate ranges of
numbers.
A range is a pair of numbers that represent the interval between them. So, a range defined by
the numbers 3 and 7 will represent an interval that includes all numbers between 3 and 7 (3, 4, 5
and 6 and even non-integer numbers).
A range can also be more than one interval. You can also create a range that is both the interval
(3, 7) and the interval (10, 12). This range will represent any number between 3 and 7 and any
number between 10 and 12 but not numbers between 7 and 10.
You must create an API that will represent this concept and allow for the creation of these
ranges.
It will also allow for the Union operation between two ranges. This will result
in a range that includes all the values between the two ranges. For example: union( (3, 7), (6, 10)
) = (3, 10)
It will also allow for the Intersection operation between them. This will result in a range that
includes only the values that are in both the ranges. For example: intersection( (3, 7), (6, 10) ) =
(6, 7)
It will also allow the developer to check if a number is contained in a range."

The project was divided into 2 parts:

1) OFFICIAL_SRC is the container for the DLL and Static libraries, including the corresponding source code, where there's no User interaction. Just the function, along with the needed input variables, which will result in a string output.
2) DABOT_SRC is the container for a static library and its source code, which is mostly used for the user to understand how the function range_me() works and how it's showing its results. Here, we have user interaction through console (Windows CMD).

For more information about this project and the function range_me(), please check the "Function range_meV2.docx".
