# Graph Library - System Programing 2 Ex2
## Author
+ **Oz Atar**
+ **Email: ozfatar@gmail.com**
In this exercise I expended the c++ library that I had created in the [first exercise](https://github.com/LILOZI/SystemPrograming2_Ex1)

You are advised to read the [README](https://github.com/LILOZI/SystemPrograming2_Ex1/blob/main/README.md) of the first exercise to further understand the implemnted library.

In this exercise I used operator overloading to improve my Graph class by making it more convient and more well defeined.

## Graph class 
This is the only module that was changed, a few methods were added operators overloading was implemented.

### Overloaded operators
In the following examples **<ins>g1</ins>** and **<ins>g2</ins>** are instances of Graph, scalar is an integer.

+ **g1 = g2** - Overrides all of g1 fiels with g2 fields - flags and matrix.  

+ **g1 + g2** - Add the weight of e1, an edge between vertices u and v inside g1 with the weight of e2, an edge between u and v inside g2, for every u and v of the graphs.

+ **g1 += g2** - Perform addition between g1 and g2 and save the sum inside g1.

+ **g1++** - Returning the value of g1, but incrementing the values of each edge by 1(even creating new edges for two unincident vertices with weight 1 or removing an edge).

+ **++g1** - Incrementing the values of each edge of g1 and returning the incremented graph.

+ **+g1** - Returns g1 as is.

+ **g1 - g2** - Subtract the weight of e1, an edge between vertices u and v inside g1 with the weight of e2, an edge between u and v inside g2, for every u and v of the graphs.

+ **g1 -= g2** - Perform subtraction between g1 and g2 and save the result inside g1.

+ **g1--** - Returning the value of g1, but decrementing the values of each edge by 1(even creating new edges for two unincident vertices with weight -1 or removing an edge).

+ **--g1** - Decrementing the values of each edge of g1 and returning the decremented graph.

+ **-g1** - Returns a graph with the same weights as g1 but with opposite signs.

+ **g1 * scalar** - Multiplication of each edge of the graph by scalar, if an edge is non-existent then it is like multiplying by zero.

+ **g1 += scalar** - Multiplying g1 by scalar and saving the answer inside g1.

+ **g1 / scalar** - Division of each edge of the graph by scalar, if an edge is non-existent then it is like dividing zero. **can not divide by zzero**.

+ **g1 /= scalar** - Dividing g1 by scalar and saving the answer inside g1.

+ **g1 * g2** - Matrix multiplication of the adjecency matrices.

+ **g1 ***=*** g2** - Multiplying g1 by g2 and saving the answer inside g1.

+ **g1 == g2** - Return whether the matrices representing g1 and g2 are identical. 

+ **g1 != g2** - Return whether the matrices are not identical.

+ **g1 > g2** - g1 is greater than g2 if g2's matrix is strictly a sub matrix of g1's matrix, if no matrix is sub matrix of th other and they are not equal, g1 is greater if it has more edges, if the amount of edges is also equal the g1 is greater than g2 if it has more vertices than g2.

+ **g1 >= g2** - Return whether g1 is greater or equal to g2.

+ **g1 < g2** - The same as g2 > g1.

+ **g1 <= g2** - The same as g2 >= g1.

+ **os << g1** - Printing the matirx that represent g1.

### Important notes
When using mathematical operators on graphs the following things can happen:

+ A graph can get **<ins>zeroed</ins>** meaning all the edges original edges of a graph will be removed in particular a certain edge can disappear.

+ A **<ins>undirected</ins>** graph can become **<ins>directed</ins>** and vice versa.

+ An **<ins>Unweighted</ins>** graph can become **<ins>weighted</ins>**  and even obtain negative values, trivially the opposite is possible as well.
