#include <stdio.h>
#include <limits.h>

#define MAX_VERTEX 100
#define INF INT_MAX 
/*ʱ�临�Ӷ�O(VE)
* ���ڴ���Դ���и�Ȩ�ߵ����·������
* ˼�룺��̬�滮
* ��sΪ��㣬dist[v]Ϊs��v�����·�� 
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
    // ��ʼ���ڽӾ���
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
    // ��ӱߣ�ע��������ͼ
    graph->adjMatrix[from][to] = weight;
}

void bellmanFord(Graph* graph, int start, int* dist)
{
    int numVertices = graph->numVertices;

    // ��ʼ����������
    for (int i = 0; i < numVertices; i++)
        dist[i] = INF;
    dist[start] = 0;

    // ִ��n-1���ɳڲ���
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

    // ����Ƿ���ڸ���·
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