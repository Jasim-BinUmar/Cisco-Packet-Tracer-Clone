#include <stdio.h>
#include <limits.h>
#include <iostream>
#include"Path.h"
using namespace std;

#define V 8
class Dijkstra
{
private:
    Path* p;// = new Path[V];
public:
    Path* getPath() {
        return p;
    }
    int minDistance(int dist[], bool sptSet[])
    {
        int min = INT_MAX, min_index = 0;

        for (int v = 0; v < V; v++)
        {
            if (sptSet[v] == false && dist[v] <= min)
            {
                min = dist[v], min_index = v;
            }
        }
        return min_index;
    }

    void printPath(int parent[], int j, Path& p)
    {
        if (parent[j] == -1)
            return;

        printPath(parent, parent[j], p);
        cout << " -> " << ((char)(j + 65));
        p.concatTrace(j);
    }

    void printSolution(int dist[], int n, int parent[], int src)
    {
        int min = INT_MAX;
        int node = -1;
        cout << "Vertex   Distance   Path" << endl;
        for (int i = 0; i < V; i++)
        {
            cout << i << "\t" << dist[i] << "\t" << (char)(src + 65);
            p[i].setVertix(i);
            p[i].setDistance(dist[i]);
            p[i].setTrace(src);
            printPath(parent, i, p[i]);
            cout << endl;

            if (dist[i] < min && dist[i] != 0)
            {
                min = dist[i];
                node = i;
            }
        }

        cout << endl;
        /*cout << "shortest path: " << min << endl;
        cout << "Destination Node: " << node << endl << endl;*/
    }

    void runDijkstra(int **graph, int src)
    {
        int dist[V];
        bool sptSet[V];
        int parent[V];
         p = new Path[V];
        parent[src] = -1;
        for (int i = 0; i < V; i++)
        {
            dist[i] = INT_MAX;
            sptSet[i] = false;
        }

        dist[src] = 0;

        for (int count = 0; count < V - 1; count++)
        {
            int u = minDistance(dist, sptSet);

            sptSet[u] = true;

            for (int v = 0; v < V; v++)
            {
                if (!sptSet[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v])
                {
                    dist[v] = dist[u] + graph[u][v];
                    parent[v] = u;
                }
            }
        }

        printSolution(dist, V, parent, src);
    }

};