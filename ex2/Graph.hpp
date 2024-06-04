/**Aharon bassous
 * aharonba123@gmail.com
 * 0545526575
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <iostream>

namespace ariel
{

    class Graph
    {
    private:
        std::vector<std::vector<int>> adjMatrix;

    public:
        Graph();
        void loadGraph(const std::vector<std::vector<int>> &graph);
        void printGraph();
        bool isDirected();
        int getSize();
        std::vector<std::vector<int>> getAdjMatrix();
        void setAdjMatrix(std::vector<std::vector<int>> Matrix);
        Graph operator+(Graph &g);
        Graph& operator+=(Graph &g);
        void operator+();
        Graph operator-(Graph &g);
        Graph& operator-=(Graph &g);
        Graph& operator-();
        bool operator>(Graph &g);
        bool operator<(Graph &g);
        bool operator==(Graph &g);
        bool operator!=(Graph &g);
        bool operator>=(Graph &g);
        bool operator<=(Graph &g);
        Graph &operator++();
        Graph &operator--();
        Graph &operator*(int x);
        Graph operator*(Graph &g);
        Graph operator--(int);
        Graph operator++(int);
        bool isEqual(Graph &g);
        int numOfEdge();
        friend std::ostream &operator<<(std::ostream &os, Graph &g);
        bool isContains(Graph &g);
    };

}

#endif // GRAPH_HPP