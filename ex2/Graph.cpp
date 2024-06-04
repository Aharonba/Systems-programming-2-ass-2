/**Aharon bassous
 * aharonba123@gmail.com
 * 0545526575
 */

#include "Graph.hpp"

namespace ariel
{
    Graph::Graph() {}

    /**
     * Loads a graph from a provided adjacency matrix.
     */

    void Graph::loadGraph(const std::vector<std::vector<int>> &graph)
    {
        // Before loading the graph, check that the matrix is square
        size_t numRows = graph.size();

        for (size_t i = 1; i < numRows; ++i)
        {
            if (graph[i].size() != numRows)
            {
                std::cerr << "Error: Provided matrix is not square." << std::endl;
                return;
            }
        }

        adjMatrix = graph;
    }

    /**
     * Print information about the graph.
     * Prints the number of vertices and edges in the graph.
     */
    void Graph::printGraph()
    {
        int numOfEdge = 0;

        // Count the number of non-zero elements in the adjacency matrix to find the number of edges
        for (std::vector<std::vector<int>>::size_type i = 0; i < adjMatrix.size(); i++)
        {
            for (std::vector<int>::size_type j = 0; j < adjMatrix[i].size(); j++)
            {
                if (adjMatrix[i][j] != 0)
                {
                    numOfEdge++;
                }
            }
        }

        // Print the number of vertices and edges
        std::cout << "Graph with " << adjMatrix.size() << " vertices and " << numOfEdge << " edges." << std::endl;
    }

    /**
     * Check if the graph is directed.
     *
     * @return True if the graph is directed, false otherwise.
     */
    bool Graph::isDirected()
    {
        size_t numRows = adjMatrix.size();
        for (int i = 0; i < numRows; i++)
        {
            for (int j = 0; j < numRows; j++)
            {
                // Check if there's an edge from i to j but not from j to i
                if ((adjMatrix[(size_t)i][(size_t)j]) != (adjMatrix[(size_t)j][(size_t)i]))
                {
                    return true;
                }
            }
        }
        // If no such edge is found, the graph is undirected
        return false;
    }

    int Graph::getSize()
    {
        return adjMatrix.size();
    }

    std::vector<std::vector<int>> Graph::getAdjMatrix()
    {
        return adjMatrix;
    }

    void Graph::setAdjMatrix(std::vector<std::vector<int>> Matrix)

    {
        adjMatrix = Matrix;
    }

    /**
     * Addition operator for adding two graphs.
     * Returns a new graph representing the sum of the input graphs.
     */

    Graph Graph::operator+(Graph &g)
    {
        if (this->getSize() != g.getSize())
        {
            throw std::invalid_argument("The addition operation cannot operate on matrices of different sizes");
        }

        Graph result;
        size_t size = (size_t)g.getSize();
        result.adjMatrix.resize(size, std::vector<int>(size, 0));

        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < size; j++)
            {
                result.adjMatrix[i][j] = this->adjMatrix[i][j] + g.adjMatrix[i][j];
            }
        }
        return result;
    }

    /**
     * Compound addition assignment operator for adding two graphs.
     * Modifies the current graph by adding the input graph to it.
     */

    Graph &Graph::operator+=(Graph &g)
    {
        if (this->getSize() != g.getSize())
        {
            throw std::invalid_argument("The addition operation cannot operate on matrices of different sizes");
        }
        size_t size = (size_t)g.getSize();

        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < size; j++)
            {
                this->adjMatrix[i][j] = this->adjMatrix[i][j] + g.adjMatrix[i][j];
            }
        }
        return *this;
    }

    // Unary plus operator.

    void Graph::operator+()
    {
        ;
    }

    /**
     * Subtraction operator for subtracting two graphs.
     * Returns a new graph representing the difference of the input graphs.
     */

    Graph Graph::operator-(Graph &g)
    {
        if (this->getSize() != g.getSize())
        {
            throw std::invalid_argument("The subtraction operation cannot operate on matrices of different sizes");
        }
        Graph result;
        size_t size = (size_t)g.getSize();
        result.adjMatrix.resize(size, std::vector<int>(size, 0));

        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < size; j++)
            {
                result.adjMatrix[i][j] = this->adjMatrix[i][j] - g.adjMatrix[i][j];
            }
        }
        return result;
    }

    /**
     * Compound subtraction assignment operator for subtracting two graphs.
     * Modifies the current graph by subtracting the input graph from it.
     */

    Graph &Graph::operator-=(Graph &g)
    {
        if (this->getSize() != g.getSize())
        {
            throw std::invalid_argument("The subtraction operation cannot operate on matrices of different sizes");
        }
        size_t size = (size_t)g.getSize();

        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < size; j++)
            {
                this->adjMatrix[i][j] = this->adjMatrix[i][j] - g.adjMatrix[i][j];
            }
        }
        return *this;
    }

    // Unary minus operator.

    Graph &Graph::operator-()
    {
        size_t size = adjMatrix.size();

        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < size; j++)
            {
                adjMatrix[i][j] = -adjMatrix[i][j];
            }
        }

        return *this;
    }

    // Output stream operator for printing the adjacency matrix of the graph.

    std::ostream &operator<<(std::ostream &os, Graph &g)
    {
        size_t size = (size_t)g.getSize();

        for (size_t i = 0; i < size; i++)
        {
            os << "[ ";
            for (size_t j = 0; j < size; j++)
            {
                os << g.adjMatrix[i][j] << ", ";
            }
            if (i == size - 1)
            {
                os << "]" << std::endl;
            }
            else
            {
                os << "], ";
            }
        }

        return os;
    }

    /**
     * Checks if the current graph contains a subgraph isomorphic to the input graph.
     */

    bool Graph::isContains(Graph &g)
    {
        int n = this->getSize();
        int m = g.getSize();

        if (m > n)
            return false; // If submatrix is larger than the matrix, it can't be a submatrix

        for (size_t k = 0; k <= n - m; k++)
        {
            for (size_t l = 0; l <= n - m; l++)
            {
                bool isSubMatrix = true; // Assume it is a submatrix until proven otherwise
                for (size_t i = 0; i < m && isSubMatrix; i++)
                {
                    for (size_t j = 0; j < m && isSubMatrix; j++)
                    {
                        if (this->adjMatrix[k + i][l + j] != g.adjMatrix[i][j])
                        {
                            isSubMatrix = false; // Mismatch found, set flag to false
                        }
                    }
                }
                if (isSubMatrix)
                {
                    return true; // If all elements matched, return true
                }
            }
        }
        return false; // No matching submatrix found
    }

    int Graph::numOfEdge()
    {
        int n = this->getSize();
        int counter = 0;
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                if (this->adjMatrix[i][j] != 0)
                {
                    counter++;
                }
            }
        }
        return counter;
    }

    // Compares two graphs based on their sizes and number of edges.

    bool Graph::operator>(Graph &g)
    {
        size_t thisSize = (size_t)this->getSize();
        size_t gSize = (size_t)g.getSize();
        size_t thisEdges = (size_t)this->numOfEdge();
        size_t gEdges = (size_t)g.numOfEdge();

        if (this->isContains(g))
        {
            return thisSize > gSize;
        }

        if (thisEdges != gEdges)
        {
            return thisEdges > gEdges;
        }

        return thisSize > gSize;
    }

    /**
     * Equality operator.
     * Checks if two graphs are equal.
     */

    bool Graph::operator==(Graph &g)
    {
        if (this->isEqual(g))
        {
            return true;
        }
        else if ((!(*this > g)) && (!(g > *this)))
        {
            return true;
        }
        return false;
    }

    /**
     * Inequality operator.
     * Checks if two graphs are not equal.
     */

    bool Graph::operator!=(Graph &g)
    {

        return !(*this == g);
    }

    /**
     * Less than operator.
     * Compares two graphs based on their sizes and number of edges.
     */

    bool Graph::operator<(Graph &g)
    {
        if (!(*this > g) && !(*this == g))
        {
            return true;
        }

        else
        {
            return false;
        }
    }

    /**
     * Greater than or equal to operator.
     * Compares two graphs based on their sizes and number of edges.
     */

    bool Graph::operator>=(Graph &g)
    {
        if (*this > g || *this == g)
        {
            return true;
        }

        else
        {
            return false;
        }
    }

    /**
     * Less than or equal to operator.
     * Compares two graphs based on their sizes and number of edges.
     */

    bool Graph::operator<=(Graph &g)
    {
        if (*this < g || *this == g)
        {
            return true;
        }

        else
        {
            return false;
        }
    }

    // Prefix increment operator (++graph)
    Graph &Graph::operator++()
    {
        for (auto &row : adjMatrix)
        {
            for (int &weight : row)
            {
                ++weight;
            }
        }
        return *this;
    }

    // Prefix decrement operator (--graph)
    Graph &Graph::operator--()
    {
        for (auto &row : adjMatrix)
        {
            for (int &weight : row)
            {
                --weight;
            }
        }
        return *this;
    }

    // Postfix increment operator (graph++)
    Graph Graph::operator++(int)
    {
        Graph temp(*this); // Create a copy of the current graph
        ++(*this);         // Increment the current graph
        return temp;       // Return the copy
    }

    // Postfix decrement operator (graph--)
    Graph Graph::operator--(int)
    {
        Graph temp(*this); // Create a copy of the current graph
        --(*this);         // Decrement the current graph
        return temp;       // Return the copy
    }

    /**
     * Scalar multiplication operator for the graph.
     * Multiplies each element in the adjacency matrix by the scalar value.
     */

    Graph &Graph::operator*(int x)
    {
        size_t size = (size_t)this->getSize();

        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < size; j++)
            {
                this->adjMatrix[i][j] = this->adjMatrix[i][j] * x;
            }
        }
        return *this;
    }

    /**
     * Matrix multiplication operator for the graph.
     * Multiplies two square matrices representing graphs.
     */

    Graph Graph::operator*(Graph &g)
    {
        size_t n = (size_t)this->getSize();
        size_t m = (size_t)g.getSize();

        if (n != m)
        {
            throw std::invalid_argument("Matrices must be of the same size for multiplication");
        }
        else
        {
            Graph result;
            size_t size = (size_t)g.getSize();
            result.adjMatrix.resize(size, std::vector<int>(size, 0));

            for (size_t k = 0; k < n; k++)
            {
                for (size_t i = 0; i < n; i++)
                {
                    int sum = 0;
                    for (size_t j = 0; j < n; j++)
                    {
                        sum += this->adjMatrix[k][j] * g.adjMatrix[j][i];
                    }
                    result.adjMatrix[k][i] = sum;
                }
            }

            return result;
        }
    }

    /**
     * Checks if the current graph is equal to the input graph.
     */
    bool Graph::isEqual(Graph &g)
    {
        int n = this->getSize();
        int m = g.getSize();

        if (n != m)
        {
            return false;
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (this->adjMatrix[(size_t)i][(size_t)j] != g.adjMatrix[(size_t)i][(size_t)j])
                    {
                        return false;
                    }
                }
            }
            return true;
        }
    }
}
