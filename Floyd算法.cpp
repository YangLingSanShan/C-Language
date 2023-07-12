#include <stdio.h>
#include <limits.h>

#define MAX_VERTEX 100
#define INF INT_MAX 
/*Floyd算法
* 可以处理带有非负权值的有向图（directed graph）或无向图（undirected graph）的最短路径问题
* 
* 相当于为每个顶点调用Dijkstra算法
* 具体体现在dist数组为一个二维数组
* 
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
            if (i == j)
                graph->adjMatrix[i][j] = 0;
            else
                graph->adjMatrix[i][j] = INF;
        }
    }
}

void addEdge(Graph* graph, int from, int to, int weight)
{
    // 添加边（有向图）
    graph->adjMatrix[from][to] = weight;
}

void floyd(Graph* graph, int dist[][MAX_VERTEX])
{
    int numVertices = graph->numVertices;

    // 初始化距离数组
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            dist[i][j] = graph->adjMatrix[i][j];
        }
    }

    // 执行floyd算法
    for (int k = 0; k < numVertices; k++)
    {
        for (int i = 0; i < numVertices; i++)
        {
            for (int j = 0; j < numVertices; j++)
            {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
}

int main()
{
    Graph graph;
    int dist[MAX_VERTEX][MAX_VERTEX];
    int numVertices, numEdges;

    scanf("%d %d", &numVertices, &numEdges);
    initGraph(&graph, numVertices, numEdges);

    for (int i = 0; i < numEdges; i++)
    {
        int from, to, weight;
        scanf("%d %d %d", &from, &to, &weight);
        addEdge(&graph, from, to, weight);
    }

    floyd(&graph, dist);

    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            if (dist[i][j] == INF)
                printf("INF ");
            else
                printf("%d ", dist[i][j]);
        }
        printf("\n");
    }

    return 0;
}