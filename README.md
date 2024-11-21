# Finding a Good Path

 Finding a good path determines the lowest and highest points and whether there is a path between them that never goes down.
 There was a similar problem in the BOSPRE 2018 competition

Your input would be 
<fname> File name for the 2-dimensional map
<M>     Number of rows
<N>     Number of columns 

Where 5 <= M,N <= 100 and each elevation in the grid is 0 <= E <= 100
The path can follow a number equal to the previous number or higher. It can't go down.

Example:
./path map.txt 5 5

2 3 3 4 5

2 4 4 1 4

2 1 0 2 1

4 2 1 3 4

3 1 2 2 3

./path map1.txt 5 5
3 3 1 5 yes

The code tracks each number and will run recursively if a "wall" is hit, which means it will go back wards until it finds another path to follow
This code was part of a homework assignment for the Data Structures and Abstractions available at my school
