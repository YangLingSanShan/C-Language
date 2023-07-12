#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTEX 1000

typedef struct Edge
{
    int from, to, weight;
} Edge;

typedef struct Graph
{
    Edge edges[MAX_VERTEX];
    int numVertices, numEdges;
} Graph;

void initGraph(Graph* graph, int numVertices, int numEdges)
{
    graph->numVertices = numVertices;
    graph->numEdges = numEdges;
}

void addEdge(Graph* graph, int from, int to, int weight)
{
    graph->edges[graph->numEdges].from = from;
    graph->edges[graph->numEdges].to = to;
    graph->edges[graph->numEdges].weight = weight;
    graph->numEdges++;
}

void bellmanFord(Graph* graph, int start, int* dist)
{
    int numVertices = graph->numVertices;
    int numEdges = graph->numEdges;

    // 初始化距离数组
    for (int i = 0; i < numVertices; i++)
        dist[i] = INT_MAX;
    dist[start] = 0;

    // 执行n-1轮松弛操作
    for (int i = 0; i < numVertices - 1; i++)
    {
        for (int j = 0; j < numEdges; j++)
        {
            int u = graph->edges[j].from;
            int v = graph->edges[j].to;
            int w = graph->edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }

    // 检测是否存在负环路
    for (int j = 0; j < numEdges; j++)
    {
        int u = graph->edges[j].from;
        int v = graph->edges[j].to;
        int w = graph->edges[j].weight;

        if (dist[u] != INT_MAX && dist[u] + w < dist[v])
        {
            printf("Graph contains negative weight cycle\n");
            return;
        }
    }
}

int main()
{
    Graph graph;
    int dist[MAX_VERTEX];
    int numVertices, numEdges, start;

    scanf("%d %d %d", &numVertices, &numEdges, &start);
    initGraph(&graph, numVertices, numEdges);
    int from, to, weight;
    for (int i = 0; i < numEdges; i++)
    {
       
        scanf("%d %d %d", &from, &to, &weight);
        addEdge(&graph, from, to, weight);
    }

    bellmanFord(&graph, start, dist);

    for (int i = 0; i < numVertices; i++)
        printf("Distance from %d to %d is %d\n", start, i, dist[i]);

    return 0;
}