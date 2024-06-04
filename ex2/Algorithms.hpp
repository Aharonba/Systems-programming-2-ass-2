// Algorithms.hpp

/**Aharon bassous
 * aharonba123@gmail.com
 * 0545526575
*/

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "Graph.hpp"
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>
#include <unordered_set> // Add this line
#include <climits>
#include <limits>
#include <set>
#include <algorithm>

using namespace std;
using namespace ariel;

enum Color
{
    WHITE,
    GRAY,
    BLACK
};

namespace ariel
{

    class Algorithms
    {

    public:
        static bool isDirected(Graph &g);
        static void reverseEdges(int size, Graph &g);
        static void DFSUtil(int v, std::vector<bool> &visited, std::stack<int> &stack, Graph &g);
        static int isDirectedConnected(Graph g);
        static int isConnected(Graph &g);
        static void BFS(int startVertex, std::vector<bool> &visited, Graph &g);
        static void shortestPath(Graph g, int v, int u);
        static void printPath(std::vector<int> &path);
        static void bellmanFord(Graph graph, int src, int dest);
        static void printPath(std::vector<int> &parent, int j);
        static bool isBipartiteUtil(vector<vector<int>> &graph, int src, int colorArr[]);
        static void isBipartite(Graph &g);
        static bool isBipartiteCheck(vector<vector<int>> graph);
        static bool negativeCycleCheck(Graph &graph);
        static void negativeCycle(Graph &graph);
        static string isContainsCycle(Graph &g);
        static string isContainsCycleUtil(Graph &g, size_t src, vector<Color> *colors, vector<int> *parents, vector<int> *path);
        static string constructCyclePath(vector<int> &path, int start);
    };

}

#endif