/**Aharon bassous
 * aharonba123@gmail.com
 * 0545526575
*/

#include "Algorithms.hpp"
using namespace ariel;
using namespace std;
#define MAXN 100
const int INF = 1e7;

/**
 * Check if the graph is directed.
 */
bool Algorithms::isDirected(Graph &g)
{
    vector<vector<int>> adjMatrix = g.getAdjMatrix();
    int n = g.getSize();

    // Check for asymmetric edges
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            // If there's an edge from i to j but not from j to i, the graph is directed
            if (adjMatrix[(size_t)i][(size_t)j] != adjMatrix[(size_t)j][(size_t)i])
            {
                return true; // Asymmetric edges found, graph is directed
            }
        }
    }

    // If no asymmetric edges are found, the graph is undirected
    return false;
}

/**
 * Perform Breadth First Search (BFS) traversal starting from a given vertex.
 */
void Algorithms::BFS(int startVertex, std::vector<bool> &visited, Graph &g)
{
    std::queue<int> q;
    q.push(startVertex);
    visited[(size_t)startVertex] = true;

    while (!q.empty())
    {
        int v = q.front();
        q.pop();

        // Traverse all vertices adjacent to the current vertex
        for (int u = 0; u < g.getSize(); ++u)
        {
            // If there is an edge from v to u and u is not visited, enqueue u and mark it visited
            if (g.getAdjMatrix()[(size_t)v][(size_t)u] && !visited[(size_t)u])
            {
                q.push(u);
                visited[(size_t)u] = true;
            }
        }
    }
}

// Function to check if the graph is connected

int Algorithms::isConnected(Graph &g)
{
    // If the graph is directed, check for strong connectivity
    if (isDirected(g))
    {
        return isDirectedConnected(g);
    }
    else // If the graph is undirected, check for connectivity using BFS
    {
        std::vector<bool> visited((size_t)(g.getSize()), false);
        int startVertex = 0; // Start BFS from vertex 0
        BFS(startVertex, visited, g);
        // Check if all vertices are visited
        for (bool v : visited)
        {
            if (!v)
                return 0; // If any vertex is not visited, the graph is not connected
        }
        return 1; // All vertices are visited, so the graph is connected
    }
}

/**
 * Reverse the edges of the graph.
 */
void Algorithms::reverseEdges(int size, Graph &g)
{
    const auto &originalMatrix = g.getAdjMatrix();
    std::vector<std::vector<int>> reversed((size_t)size, std::vector<int>((size_t)size, 0));

    for (int u = 0; u < size; ++u)
    {
        for (int v = 0; v < size; ++v)
        {
            if (originalMatrix[(size_t)u][(size_t)v] != 0)
            {
                // Reverse the edge and its weight
                reversed[(size_t)v][(size_t)u] = originalMatrix[(size_t)u][(size_t)v];
            }
        }
    }

    g.setAdjMatrix(reversed); // Update the adjacency matrix with reversed edges
}

/**
 * Utility function for Depth-First Search (DFS) traversal.
 */
void Algorithms::DFSUtil(int v, std::vector<bool> &visited, std::stack<int> &stack, Graph &g)
{
    visited[(size_t)v] = true;
    for (int u = 0; u < g.getSize(); ++u)
    {
        if (g.getAdjMatrix()[(size_t)v][(size_t)u] && !visited[(size_t)u])
        {
            DFSUtil(u, visited, stack, g);
        }
    }
    stack.push(v); // Push vertex in reverse topological order (finishing time)
}

/**
 * Check if the directed graph is strongly connected.
 */

int Algorithms::isDirectedConnected(Graph g)
{
    int n = g.getSize();
    std::vector<bool> visited((size_t)n, false);
    std::stack<int> stack;

    // First Pass (DFS)
    for (int v = 0; v < n; ++v)
    {
        if (!visited[(size_t)v])
        {
            DFSUtil(v, visited, stack, g);
        }
    }

    // Reverse edges in the graph
    Graph reversedGraph = g; // Make a copy of the original graph
    reverseEdges(g.getSize(), reversedGraph);

    // Reset visited array
    std::fill(visited.begin(), visited.end(), false);

    // Second Pass (DFS on reversed graph)
    while (!stack.empty())
    {
        int v = stack.top();
        stack.pop();
        if (!visited[(size_t)v])
        {
            DFSUtil(v, visited, stack, reversedGraph); // DFS from a vertex not yet explored
            for (int u = 0; u < n; ++u)
            {
                if (!visited[(size_t)u])
                {
                    return 0; // Not strongly connected if any vertex is not reachable
                }
            }
        }
    }

    return 1; // Strongly connected if all vertices are reachable in both directions
}

/**
 * Find the shortest path between two vertices using the Bellman-Ford algorithm.
 */
void Algorithms::shortestPath(Graph graph, int v, int u)
{
    size_t size = (size_t)graph.getSize();
    vector<vector<int>> adjMatrix = graph.getAdjMatrix();

    // Initializes all vertices that do not have an edge between them to infinity
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if ((i != j) && (adjMatrix[(size_t)i][(size_t)j] == 0))
            {
                adjMatrix[(size_t)i][(size_t)j] = INF;
            }
        }
    }

    bellmanFord(graph, v, u);
}

/**
 * Perform the Bellman-Ford algorithm to find the shortest path.
 */
void Algorithms::bellmanFord(Graph graph, int src, int dest)
{
    int V = graph.getSize();
    vector<int> dist((size_t)V, INF);
    vector<int> parent((size_t)V, -1);
    dist[(size_t)src] = 0;
    vector<vector<int>> adjMatrix = graph.getAdjMatrix();

    // Relax edges |V| - 1 times
    for (int i = 0; i < V - 1; i++)
    {
        for (int u = 0; u < V; u++)
        {
            for (int v = 0; v < V; v++)
            {
                if (adjMatrix[(size_t)u][(size_t)v] != 0 && dist[(size_t)u] != INF && dist[(size_t)u] + adjMatrix[(size_t)u][(size_t)v] < dist[(size_t)v])
                {
                    dist[(size_t)v] = dist[(size_t)u] + adjMatrix[(size_t)u][(size_t)v];
                    parent[(size_t)v] = u;
                }
            }
        }
    }

    // Check for negative weight cycles
    for (int u = 0; u < V; u++)
    {
        for (int v = 0; v < V; v++)
        {
            if (adjMatrix[(size_t)u][(size_t)v] != 0 && dist[(size_t)u] != INF && dist[(size_t)u] + adjMatrix[(size_t)u][(size_t)v] < dist[(size_t)v])
            {
                cout << "Graph contains negative weight cycle" << endl;
                return;
            }
        }
    }

    // Print the shortest path
    cout << "Shortest path from " << src << " to " << dest << " is: ";
    if (parent[(size_t)dest] == -1)
    {
        cout << -1 << endl;
    }
    else
    {
        printPath(parent, dest);
        cout << endl;
    }
}

/**
 * Recursively print the shortest path.
 */
void Algorithms::printPath(vector<int> &parent, int j)
{
    if (parent[(size_t)j] == -1)
    {
        cout << j << " ";
        return;
    }
    printPath(parent, parent[(size_t)j]);
    cout << j << " ";
}

/**
 * Utility function to check if a graph is Bipartite starting from a given source vertex.
 */
bool Algorithms::isBipartiteUtil(vector<vector<int>> &graph, int src, int colorArr[])
{
    size_t V = graph.size();
    colorArr[src] = 1;

    // Create a queue (FIFO) of vertex numbers and enqueue source vertex for BFS traversal
    queue<int> q;
    q.push(src);

    // Run while there are vertices in queue (Similar to BFS)
    while (!q.empty())
    {
        // Dequeue a vertex from queue
        int u = q.front();
        q.pop();

        // Find all non-colored adjacent vertices
        for (int v = 0; v < V; ++v)
        {
            // An edge from u to v exists and destination v is not colored
            if (graph[(size_t)u][(size_t)v] != 0 && colorArr[v] == -1)
            {
                // Assign alternate color to this adjacent v of u
                colorArr[v] = 1 - colorArr[u];
                q.push(v);
            }
            // An edge from u to v exists and destination v is colored with same color as u
            else if (graph[(size_t)u][(size_t)v] != 0 && colorArr[v] == colorArr[u])
                return false;
        }
    }

    // If we reach here, then all adjacent vertices can be colored with alternate color
    return true;
}

/**
 * Check if the graph is Bipartite.
 */
void Algorithms::isBipartite(Graph &g)
{
    if (isBipartiteCheck(g.getAdjMatrix()))
    {
        std::cout << "graph is Bipartite\n"
                  << std::endl;
    }
    else
    {
        std::cout << "graph is not Bipartite\n"
                  << std::endl;
    }
}

/**
 * Check if a given graph is Bipartite using BFS traversal.
 */
bool Algorithms::isBipartiteCheck(std::vector<vector<int>> g)
{
    // Create a color array to store colors assigned to all vertices.
    // Vertex number is used as index in this array. The value '-1' of colorArr[i] is used to
    // indicate that no color is assigned to vertex 'i'.
    // The value 1 is used to indicate first color is assigned and value 0 indicates second color is assigned.
    size_t V = g.size();
    int colorArr[V];
    for (int i = 0; i < V; ++i)
        colorArr[i] = -1;

    // This code is to handle disconnected graphs
    for (int i = 0; i < V; i++)
        if (colorArr[i] == -1)
            if (isBipartiteUtil(g, i, colorArr) == false)
                return false;

    return true;
}

/**
 * Check if the graph contains a negative weight cycle.
 */
void Algorithms::negativeCycle(Graph &graph)
{
    if (negativeCycleCheck(graph) == true)
    {
        cout << "Graph contains negative weight cycle" << endl;
    }
    else
    {
        cout << "Graph does not contain negative weight cycle" << endl;
    }
}

/**
 * Check if the graph contains a negative weight cycle using the Bellman-Ford algorithm.
 */
bool Algorithms::negativeCycleCheck(Graph &graph)
{
    int V = graph.getSize();
    vector<int> dist((size_t)V, INF);
    dist[0] = 0; // Assuming vertex 0 as source

    vector<vector<int>> adjMatrix = graph.getAdjMatrix();

    // Relax edges V-1 times
    for (int i = 0; i < V - 1; i++)
    {
        for (int u = 0; u < V; u++)
        {
            for (int v = 0; v < V; v++)
            {
                if (adjMatrix[(size_t)u][(size_t)v] != 0 && dist[(size_t)u] != INF && dist[(size_t)u] + adjMatrix[(size_t)u][(size_t)v] < dist[(size_t)v])
                {
                    dist[(size_t)v] = dist[(size_t)u] + adjMatrix[(size_t)u][(size_t)v];
                }
            }
        }
    }

    // Check for negative weight update after V-1 iterations
    for (int u = 0; u < V; u++)
    {
        for (int v = 0; v < V; v++)
        {
            if (adjMatrix[(size_t)u][(size_t)v] != 0 && dist[(size_t)u] != INF && dist[(size_t)u] + adjMatrix[(size_t)u][(size_t)v] < dist[(size_t)v])
            {
                return true; // Negative cycle detected
            }
        }
    }

    return false; // No negative cycle found
}

/**
 * Check if the graph contains a cycle and return the cycle path if found.
 */
string Algorithms::isContainsCycle(Graph &g)
{
    vector<Color> colors((size_t)g.getSize(), WHITE);
    vector<int> parents((size_t)g.getSize(), -1);
    vector<int> path;

    for (size_t i = 0; i < g.getSize(); i++)
    {
        if (colors[i] == WHITE)
        {
            string cycle = isContainsCycleUtil(g, i, &colors, &parents, &path);
            if (!cycle.empty())
            {
                return cycle;
            }
        }
    }
    return "-1"; // No cycle found
}

/**
 * Utility function to recursively check if the graph contains a cycle starting from a given source vertex.
 */
string Algorithms::isContainsCycleUtil(Graph &g, size_t src, vector<Color> *colors, vector<int> *parents, vector<int> *path)
{
    (*colors)[src] = GRAY;
    path->push_back(src);

    for (size_t v = 0; v < g.getSize(); v++)
    {
        if (g.getAdjMatrix()[src][v] != 0)
        {
            if ((*colors)[v] == WHITE)
            {
                (*parents)[v] = (int)src;
                string cycle = isContainsCycleUtil(g, v, colors, parents, path);
                if (!cycle.empty())
                {
                    return cycle;
                }
            }
            else if ((*colors)[v] == GRAY)
            {
                // Check if it's a directed graph and the current vertex is the parent of the source vertex
                if (!g.isDirected() && (*parents)[src] == (int)v)
                {
                    continue;
                }

                return constructCyclePath(*path, v);
            }
        }
    }

    (*colors)[src] = BLACK;
    path->pop_back();
    return ""; // No cycle found
}

/**
 * Construct the cycle path from the current traversal path.
 */
string Algorithms::constructCyclePath(vector<int> &path, int start)
{
    string cycle;
    size_t v = 0;

    for (v = 0; v < path.size(); v++)
    {
        if (path[v] == start)
        {
            break;
        }
    }

    for (size_t i = v; i < path.size(); i++)
    {
        cycle += std::to_string(path[i]) + "->";
    }

    cycle += std::to_string(start);
    return cycle;
}
