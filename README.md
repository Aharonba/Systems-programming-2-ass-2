# Graph Class Operator Overloads

## Overview
This README provides an overview of the operator overloads implemented in the `Graph` class. These operators allow manipulation and comparison of graphs represented by adjacency matrices.

## Class Definition
The `Graph` class provides functionalities for:
- Loading a graph from an adjacency matrix.
- Printing information about the graph.
- Checking if the graph is directed.
- Performing operations such as addition, subtraction, equality comparison, etc.

## Operators Implemented
### Binary Operators
- **Addition (`+`)**: Adds two graphs element-wise.
- **Compound Addition (`+=`)**: Modifies the current graph by adding another graph to it.
- **Subtraction (`-`)**: Subtracts one graph from another element-wise.
- **Compound Subtraction (`-=`)**: Modifies the current graph by subtracting another graph from it.
- **Multiplication (`*`)**: Multiplies the adjacency matrix by a scalar or performs matrix multiplication.

### Unary Operators
- **Unary Plus (`+`)**: Placeholder operator (no operation defined).
- **Unary Minus (`-`)**: Negates all elements of the adjacency matrix.
- **Prefix Increment (`++`)** and **Prefix Decrement (`--`)**: Increment or decrement each element of the adjacency matrix.
- **Postfix Increment (`++`)** and **Postfix Decrement (`--`)**: Increment or decrement the graph and return the original or a copy.

### Comparison Operators
- **Equality (`==`)**: Checks if two graphs are identical.
- **Inequality (`!=`)**: Checks if two graphs are not identical.
- **Greater Than (`>`)**, **Greater Than or Equal To (`>=`)**, **Less Than (`<`)**, **Less Than or Equal To (`<=`)**: Compares graphs based on their sizes and number of edges.
- **isContains**: Checks if the current graph contains a subgraph isomorphic to the input graph.

### Output Operator
- **Output Stream (`<<`)**: Outputs the adjacency matrix of the graph in a readable format.

## Usage
Refer to the `Graph.cpp` file for examples demonstrating the usage of these operators. Each operator is designed to handle different graph operations efficiently and safely, ensuring compatibility and consistency.

## Contact Information
- **Name**: Aharon Bassous
- **Email**: aharonba123@gmail.com
- **Phone**: 0545526575
