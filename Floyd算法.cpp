#include <stdio.h>
#include <limits.h>

#define MAX_VERTEX 100
#define INF INT_MAX 
/*Floyd�㷨
* ���Դ�����зǸ�Ȩֵ������ͼ��directed graph��������ͼ��undirected graph�������·������
* 
* �൱��Ϊÿ���������Dijkstra�㷨
* ����������dist����Ϊһ����ά����
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
    // ��ʼ���ڽӾ���
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
    // ��ӱߣ�����ͼ��
    graph->adjMatrix[from][to] = weight;
}

void floyd(Graph* graph, int dist[][MAX_VERTEX])
{
    int numVertices = graph->numVertices;

    // ��ʼ����������
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            dist[i][j] = graph->adjMatrix[i][j];
        }
    }

    // ִ��floyd�㷨
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