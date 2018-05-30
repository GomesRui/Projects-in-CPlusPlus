# Project RangeMe() C++

Exercise:

You need to provide an API that will allow other developers to create and manipulate ranges of
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
It will also allow the developer to check if a number is contained in a range.
