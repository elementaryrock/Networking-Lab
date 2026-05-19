#include <stdio.h>
#include <limits.h>

void printPath(int parent[], int j) {
    if (parent[j] == -1) {
        return;
    }
    printPath(parent, parent[j]);
    printf(" -> %d", j);
}

void dijkstra(int n, int g[n][n], int src) {
    int d[n], vis[n], parent[n];

    for(int i = 0; i < n; i++) {
        d[i] = INT_MAX;
        vis[i] = 0;
        parent[i] = -1;
    }

    d[src] = 0;

    for(int i = 0; i < n - 1; i++) {
        int u = -1, min = INT_MAX;

        for(int j = 0; j < n; j++)
            if(vis[j]==0 && d[j] < min)
                min = d[j], u = j;

        if(u == -1) break;

        vis[u] = 1;

        for(int v = 0; v < n; v++) {
            if(g[u][v] != 0 && vis[v] == 0 && d[u] + g[u][v] < d[v]) {
                d[v] = d[u] + g[u][v];
                parent[v] = u;
            }
        }
    }

    printf("\nNode\tDistance\tPath\n");
    for(int i = 0; i < n; i++) {
        if (d[i] == INT_MAX) {
            printf("%d\tUnreachable\t-\n", i);
        } else {
            printf("%d\t%d\t\t%d", i, d[i], src);
            printPath(parent, i);
            printf("\n");
        }
    }
}

int main() {
    int n, src;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    int g[n][n];

    printf("Enter adjacency matrix (0 for no edge):\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            scanf("%d", &g[i][j]);

    printf("Enter source node (0 to %d): ", n - 1);
    scanf("%d", &src);

    dijkstra(n, g, src);

    return 0;
}
