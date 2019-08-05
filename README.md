# RunLengthEncoding
Takes an "image" with different grey scale values and compresses it by eliminating redundancies.

Input files should have a header conaining number of rows, number or columns, min value and max value respectively.

The "image" are numbers separated by spaces and new lines

Try Me:
 - git clone https://github.com/jevangelista0/RunLengthEncoding.git
 - cd RunLengthEncoding
 - g++ -std=c++11 RunLengthEncodeDecode.cpp
 - a.exe Image1.txt
 - (You can then pick any method from 1-4. Either w/ 0 no wrap, no 0 no wrap, w/ 0 wrap, no 0 wrap) y to continue n to stop.
