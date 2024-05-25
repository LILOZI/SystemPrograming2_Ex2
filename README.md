In this exercise I created a c++ library that has a Graph class and usefull
    algorithms that you can use on it.

Graph class:
A class that represents an undirected/ directed unweighted/ weighted graph.
    * To create a graph you create a refrence using the defult constuctor and then
    load values to it using the loadGraph method that receivecs a two dimensional
    integer's vector. After loading the graph you can not change the values of a certain edge or add another vertex, you need to override the previous graph with another loadGraph assignment.
    * After loading a graph you can ask for information about the graph using 
    isDirected, isWeighted and isNegValues. You can also print the graph using printGraph, for example "This is a directed graph with 4 vertices and 6 edges".
    To ask if a graph has been initialized with values you can use isLoaded.

Algoriths:
Set of function that you can use on any graph implemention that supports a certain interface







