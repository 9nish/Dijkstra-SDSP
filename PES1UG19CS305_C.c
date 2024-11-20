#include<stdio.h>
#include<stdlib.h>
#include "PES1UG19CS305_H.h"


int main () {

    GRAPH G;
    CREATE_GRAPH(&G);
    int s = G.cardinality_of_V;

    DIJKSTRA(&G, s);

    PRINT_SHORTEST_PATH_DEST(&G, s);

    for(int i = 1; i <= G.cardinality_of_V; i++)
        DEALLOCATE_ADJ(G.adj[i-1]);

    free(G.adj);
    free(G.V);
    return 0;
}