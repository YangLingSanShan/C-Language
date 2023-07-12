#include <stdio.h>
#include <stdlib.h>
#define MAX 100 //������󶥵���
#define inf 9999999
int graph[MAX][MAX]; //�ڽӾ����ʾͼ
int dist[MAX]; //�洢��㵽�������̾���
int visited[MAX]; //��Ƕ����Ƿ��ѷ���
int pre[MAX]; //�洢ÿ�������ǰ���ڵ�
int n; //������

void dijkstra(int start,int end) 
{
    //��ʼ��
    for (int i = 0; i < n; i++) 
    {
        dist[i] = graph[start][i];
        visited[i] = 0;
        if (i != start && graph[start][i] < inf) 
        {
            pre[i] = start;
        }
        else 
        {
            pre[i] = -1;
        }
    }
    dist[start] = 0;
    visited[start] = 1;

    //���ڳ�����������n-1�����㣬ÿ���ҵ���С��dist[j]�����visited[j]
    for (int i = 1; i < n; i++) 
    {
        int minDist = inf, index = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                index = j;
            }
        }
        //��ֹ
        if (index==-1||index == end)	
            return;
        visited[index] = 1;
        //���¾���
        for (int j = 0; j < n; j++) {
            if (!visited[j] && graph[index][j] > 0 && dist[index] + graph[index][j] < dist[j]) 
            {
                dist[j] = dist[index] + graph[index][j];
            }
        }
    }
}
void printPath(int start, int end) 
{
    if (pre[end] == -1) {
        printf("No path from %d to %d", start, end);
        return;
    }
    if (start == end) {
        printf("%d", start);
        return;
    }
    int path[MAX], len = 0;
    path[len++] = end;
    while (pre[end] != start) {
        path[len++] = pre[end];
        end = pre[end];
    }
    path[len++] = start;
    for (int i = len - 1; i >= 0; i--) {
        printf("%d ", path[i]);
    }
}
void dijkstra(int start) //��start�㵽���ж������̾��루����ʾ·����,��forѭ���������
{
    //��ʼ��
    for (int i = 0; i < n; i++) {
        dist[i] = graph[start][i];
        visited[i] = 0;
    }
    dist[start] = 0;
    visited[start] = 1;

    //���ڳ�����������n-1�����㣬ÿ���ҵ���С��dist[j]�����visited[j]
    for (int i = 1; i < n; i++) {
        int minDist = inf, index = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                index = j;
            }
        }
        visited[index] = 1;

        //���¾���
        for (int j = 0; j < n; j++) {
            if (!visited[j] && graph[index][j] > 0 && dist[index] + graph[index][j] < dist[j]) 
            {
                dist[j] = dist[index] + graph[index][j];
            }
        }
    }
}
//���ϴ��뼴��ʵ��Dijkstra�㷨
//���ȶ��н����Ż�O��VlogV������ʹ����С��

#define INF 0x7fffffff  // ����һ������ֵ

// �����ڽӱ�Ľṹ
typedef struct _edge {
    int v;       // �ڽӵĽڵ�
    int w;       // �ߵ�Ȩ��
    struct _edge* next;   // ָ����һ���ߵ�ָ��
} Edge;

typedef struct {
    int u;       // ���
    int C;       // ·������
} Path;

// ����ѵĽṹ
typedef struct {
    int n;           // �ѵĴ�С
    Path* data;      // �洢·��������
} Heap;

// ����һ���յĶ�
Heap* createHeap(int size) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->n = 0;
    heap->data = (Path*)malloc((size + 1) * sizeof(Path));  // ע�������±�� 1 ��ʼ
    return heap;
}

// ��������һ���ڵ�
void push(Heap* heap, Path path) {
    int i = ++heap->n;
    while (i > 1 && heap->data[i / 2].C > path.C) {
        heap->data[i] = heap->data[i / 2];
        i /= 2;
    }
    heap->data[i] = path;
}

// �����Ѷ��ڵ�
Path pop(Heap* heap) {
    Path minPath = heap->data[1];
    Path lastPath = heap->data[heap->n--];
    int i = 1, j = 2;
    while (j <= heap->n) {
        if (j < heap->n && heap->data[j].C > heap->data[j + 1].C) j++;
        if (lastPath.C <= heap->data[j].C) break;
        heap->data[i] = heap->data[j];
        i = j;
        j *= 2;
    }
    heap->data[i] = lastPath;
    return minPath;
}

// Dijkstra �㷨���Ż���
void dijkstra(Edge** adjList, int n, int s, int* dist) {
    Heap* heap = createHeap(n);
    for (int i = 0; i < n; i++) dist[i] = INF;   // ��ʼ�� dist ����
    dist[s] = 0;
    Path temp = { s,0 };
    push(heap, temp);
    while (heap->n > 0) {
        Path minPath = pop(heap);
        int u = minPath.u;
        if (minPath.C > dist[u]) continue;  // ���·��������̵ľͺ���
        for (Edge* e = adjList[u]; e != NULL; e = e->next) {
            int v = e->v, w = e->w;
            if (dist[u] + w < dist[v]) {    // ��������˸��̵�·���͸���
                dist[v] = dist[u] + w;
                temp = { v,dist[v] };
                push(heap, temp );
            }
        }
    }
}

int main() //�˴���main���Ż��㷨��
{
    int n, m, s;
    scanf("%d%d%d", &n, &m, &s);//sΪ��ʼ��
    Edge** adjList = (Edge**)malloc(n * sizeof(Edge*));
    for (int i = 0; i < n; i++) 
        adjList[i] = NULL;
    int u, v, w;
    for (int i = 0; i < m; i++) 
    {
        scanf("%d%d%d", &u, &v, &w);
        Edge* e = (Edge*)malloc(sizeof(Edge));
        e->v = v;
        e->w = w;
        e->next = adjList[u];
        adjList[u] = e;
    }
    int* dist = (int*)malloc(n * sizeof(int));
    dijkstra(adjList, n, s, dist);
    for (int i = 0; i < n; i++) {
        if (dist[i] < INF) {
            printf("%d\n", dist[i]);
        }
        else {
            printf("INF\n");
        }
    }
    return 0;
}

