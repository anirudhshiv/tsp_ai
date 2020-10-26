#include <stdlib.h>
#include<string.h>
 
typedef struct {
    unsigned int first;
    unsigned int second;
    unsigned int weight;
} weighted_edge;
 
static int compare_weighted_edges(const weighted_edge *edge1, const weighted_edge *edge2)
{
    return edge1->weight - edge2->weight;
}
 
static unsigned int cyclic_recursive(const weighted_edge *edges, unsigned int n,
        unsigned int *visited, unsigned int order, unsigned int vertex, 
        unsigned int predecessor)
{
    unsigned int i;
    unsigned int cycle_found = 0;
    visited[vertex] = 1;
    for (i = 0; i < n && !cycle_found; i++) {
        if (edges[i].first == vertex || edges[i].second == vertex) {
            /* Adjacent */
            const unsigned int neighbour = edges[i].first == vertex ?
                    edges[i].second : edges[i].first;
            if (visited[neighbour] == 0) {
                /* Not yet visited */
                cycle_found = cyclic_recursive(edges, n, visited, order, neighbour, vertex);
            }
            else if (neighbour != predecessor) {
                /* Found a cycle */
                cycle_found = 1;
            }
        }
    }
    return cycle_found;
}
  
unsigned int cyclic(const weighted_edge *edges, unsigned int n, unsigned int order)
{
    unsigned int *visited = (unsigned int*)calloc(order, sizeof(unsigned int));
    unsigned int cycle_found;
    if (visited == NULL) {
        return 0;
    }
    cycle_found  = cyclic_recursive(edges, n, visited, order, 0, 0);
    free(visited);
    return cycle_found;
}
 
weighted_edge *cheapest_link_tsp(weighted_edge *edges, unsigned int size, unsigned int order)
{
    unsigned int t, e = 0;
    weighted_edge *tour = (weighted_edge*) malloc(order * sizeof(weighted_edge));
    unsigned int *degrees = (unsigned int*) calloc(order, sizeof(unsigned int));
    if (tour == NULL || degrees == NULL) {
        free(tour);
        free(degrees);
        return NULL;
    }
    /* Sort the edges by weight */
    qsort(edges, size, sizeof(weighted_edge),
            (int(*)(const void *, const void *))compare_weighted_edges);
    /* Main algorithm */
    for (t = 0; t < order; t++) {
        unsigned int added = 0;
        while (!added && e < size) {
            if (degrees[edges[e].first] < 2 && degrees[edges[e].second] < 2) {
                tour[t] = edges[e];
                if (t == order - 1 /* It's the last edge */
                    || !cyclic(tour, t + 1, order)) /* It doesn't close the circuit */
                { 
                    added = 1;
                    degrees[edges[e].first]++;
                    degrees[edges[e].second]++;
                }
            }
            e++;
        }
        if (!added) {
            /* Edges were not correct */
            free(tour);
            free(degrees);
            return NULL;
        }
    }
    free(degrees);
    return tour;
}
// 
#include <stdio.h>
#include <stdlib.h>
 
/* Connect two edges */
void connect(weighted_edge *edges, unsigned int first, unsigned int second, 
        unsigned int weight, unsigned int *pos)
{
    edges[*pos].first = first;
    edges[*pos].second = second;
    edges[*pos].weight = weight;
    (*pos)++;
}
 
static void print_edges(const weighted_edge *edges, unsigned int n)
{
    unsigned int e;
    for (e = 0; e < n; e++) {
        printf("(%u, %u, %u) ", edges[e].first, edges[e].second, edges[e].weight);
    }
    putchar('\n');
}
 
int main(void)
{
    char* S;
	int no_of_cities;
	float dist,x,y;
	// vector<pair<float,float>> city_coords;
	// vector<vector<float>> distances;
    float** distances;
	float* temp;
	// int  tours; 
    scanf("%s%d",S,&no_of_cities);
	// cin>>S>>no_of_cities;
    int E = (no_of_cities*no_of_cities);
    E-=no_of_cities;
    E/=2;
    // Graph* G;
    // G->E=E;
    // G->V=no_of_cities;
    unsigned int p = 0;
    const unsigned int size = E; /* Edges */
    const unsigned int order = no_of_cities; /* Vertices */
    weighted_edge *edges = (weighted_edge*)malloc(size * sizeof(weighted_edge));
    weighted_edge *tour;
    for(int i=0; i<no_of_cities; i++)
	{
        scanf("%f %f",&x,&y);
		// cin>>x>>y;
		// city_coords.push_back(make_pair(x,y));
	}
    for(int i=0; i<no_of_cities; i++)
	{
		for(int j=0; j<no_of_cities; j++)
		{
			scanf("%f", &dist);
            if(j>=i)
            {
                connect(edges, i, j, dist, &p);
            }
			// temp.push_back(dist);
		}
		// distances.push_back(temp);
		// temp.clear();
	}
	printf("input read succesful\n");

    tour = cheapest_link_tsp(edges, size, order);
    print_edges(tour, order);
     
    free(tour);
    free(edges);
    return 0;
}