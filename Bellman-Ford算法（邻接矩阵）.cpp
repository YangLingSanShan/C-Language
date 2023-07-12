#include <stdio.h>
#include <limits.h>

#define MAX_VERTEX 100
#define INF INT_MAX 
/*时间复杂度O(VE)
* 用于处理单源，有负权边的最短路径问题
* 思想：动态规划
* 设s为起点，dist[v]为s到v的最短路径 
*/
typedef struct Graph
{
    int adjMatrix[MAX_VERTEX][MAX_VERTEX];
    int numVertices, numEdges;
} Graph;

void initGraph(Graph* graph, int numVertices, int numEdges)
{
    graph->numVertices = numVertices;
    graph->numEdges = numEdges;
    // 初始化邻接矩阵
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            graph->adjMatrix[i][j] = INF;
        }
    }
}

void addEdge(Graph* graph, int from, int to, int weight)
{
    // 添加边，注意是有向图
    graph->adjMatrix[from][to] = weight;
}

void bellmanFord(Graph* graph, int start, int* dist)
{
    int numVertices = graph->numVertices;

    // 初始化距离数组
    for (int i = 0; i < numVertices; i++)
        dist[i] = INF;
    dist[start] = 0;

    // 执行n-1轮松弛操作
    for (int i = 0; i < numVertices - 1; i++)
    {
        for (int u = 0; u < numVertices; u++)
        {
            for (int v = 0; v < numVertices; v++)
            {
                int w = graph->adjMatrix[u][v];
                if (w != INF && dist[u] != INF && dist[u] + w < dist[v])
                    dist[v] = dist[u] + w;
            }
        }
    }

    // 检测是否存在负环路
    for (int u = 0; u < numVertices; u++)
    {
        for (int v = 0; v < numVertices; v++)
        {
            int w = graph->adjMatrix[u][v];
            if (w != INF && dist[u] != INF && dist[u] + w < dist[v])
            {
                printf("Graph contains negative weight cycle\n");
                return;
            }
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

    for (int i = 0; i < numEdges; i++)
    {
        int from, to, weight;
        scanf("%d %d %d", &from, &to, &weight);
        addEdge(&graph, from, to, weight);
    }

    bellmanFord(&graph, start, dist);

    for (int i = 0; i < numVertices; i++)
        printf("Distance from %d to %d is %d\n", start, i, dist[i]);

    return 0;
}