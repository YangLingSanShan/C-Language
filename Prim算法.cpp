#include <stdio.h>
#define MAX 100 //������󶥵���
#define inf 9999999
int graph[MAX][MAX]; //�ڽӾ����ʾͼ
int dist[MAX]; //�洢��ǰ���������������̾���
int visited[MAX]; //��Ƕ����Ƿ��ѷ���
int n; //������
/*
* ������G��ѡ��һ��һ���������V��,��һ��������U��,����Ȩֵ��С�ı߼��뼯��TE,ͬʱ���ñ߽���V �е��Ǹ�������뼯��U��
  �ظ���������n�C1��,ʹ��U=V,��ʱTΪG����С������
*/
void prim(int start) {
    //��ʼ��
    for (int i = 0; i < n; i++) {
        dist[i] = graph[start][i];
        visited[i] = 0;
    }
    dist[start] = 0;
    visited[start] = 1;

    //����n-1����
    for (int i = 1; i < n; i++) 
    {
        int minDist = inf, index = -1;
        //�ҵ���ǰ�������������̵Ķ���
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                index = j;
            }
        }
        visited[index] = 1;

        //���¾���
        for (int j = 0; j < n; j++) {
            if (!visited[j] && graph[index][j] > 0 && graph[index][j] < dist[j]) 
            {
                dist[j] = graph[index][j];
            }
        }
    }
}

int main() {
    //���붥�����ͱ���
    scanf("%d", &n);
    int m;
    scanf("%d", &m);

    //����ÿ���ߵ���Ϣ
    for (int i = 0; i < m; i++) {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        graph[a][b] = w;
        graph[b][a] = w; //����ͼ
    }

    //����С������
    prim(0);

    //������
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += dist[i];
    }
    printf("Weight of minimum spanning tree: %d", sum);
    return 0;
}