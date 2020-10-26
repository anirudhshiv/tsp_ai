#include <bits/stdc++.h>
#include <string.h>
using namespace std;

class Edge {
public:
    int src, dest, weight;
};
 
class Graph {
public:
     
    int V, E;
    Edge* edge;
};

 
// Creates a graph with V vertices and E edges
Graph* createGraph(int V, int E)
{
    Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
 
    graph->edge = new Edge[E];
 
    return graph;
}
 
// A structure to represent a subset for union-find
class subset {
public:
    int parent;
    int rank;
};
 
// A utility function to find set of an element i
// (uses path compression technique)
int find(subset subsets[], int i)
{
    // find root and make root as parent of i
    // (path compression)
    if (subsets[i].parent != i)
        subsets[i].parent
            = find(subsets, subsets[i].parent);
 
    return subsets[i].parent;
}
 
// A function that does union of two sets of x and y
// (uses union by rank)
void Union(subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
 
    // Attach smaller rank tree under root of high
    // rank tree (Union by Rank)
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
 
    // If ranks are same, then make one as root and
    // increment its rank by one
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}
 
// Compare two edges according to their weights.
// Used in qsort() for sorting an array of edges
int myComp(const void* a, const void* b)
{
    Edge* a1 = (Edge*)a;
    Edge* b1 = (Edge*)b;
    return a1->weight > b1->weight;
}
 
// The main function to construct MST using Kruskal's
// algorithm
void KruskalMST(Graph* graph)
{
    int V = graph->V;
    unordered_map <int,int> result(V);
    // Edge result[V]; // Tnis will store the resultant MST
    int e = 0; // An index variable, used for result[]
    int i = 0; // An index variable, used for sorted edges
 
    // Step 1: Sort all the edges in non-decreasing
    // order of their weight. If we are not allowed to
    // change the given graph, we can create a copy of
    // array of edges
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]),
          myComp);
 
    // Allocate memory for creating V ssubsets
    subset* subsets = new subset[(V * sizeof(subset))];
 
    // Create V subsets with single elements
    for (int v = 0; v < V; ++v) 
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    vector<int> deg(V);
 
    // Number of edges to be taken is equal to V-1
    while (e < V  && i < graph->E) 
    {
        // Step 2: Pick the smallest edge. And increment
        // the index for next iteration
        Edge next_edge = graph->edge[i++];
 
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);
 
        // If including this edge does't cause cycle,
        // include it in result and increment the index
        // of result for next edge
        if (x != y) {
            if((deg[next_edge.src]<2)&&(deg[next_edge.dest]<2))
            {
                result[next_edge.src]=next_edge.dest;
                Union(subsets, x, y);
                deg[next_edge.src]++;
                deg[next_edge.dest]++;
                e++;
            }
            // result[e++] = next_edge;
        }
        // Else discard the next_edge
    }
 
    // print the contents of result[] to display the
    // built MST
    cout << "Following are the edges in the constructed "
            "MST\n";
    int minimumCost = 0;
    int s=0,d=result[0];
    while(s!=d)
    {
        cout<< s<< " - " << d << " - " ;
        s=d;
        d=result[s];
    }
    // for (i = 0; i < e; ++i) 
    // {
    //     cout << result[i].src << " -- " << result[i].dest
    //          << " == " << result[i].weight << endl;
    //     minimumCost = minimumCost + result[i].weight;
    // }
    // return;
    // cout << "Minimum Cost Spanning Tree: " << minimumCost
    //      << endl;
}

// vector<vector<int>> best_tour_calculator(string S, int N, vector<pair<float,float>> city_coords, vector<vector<float>> distances)
// {
// 	vector<vector<int>> _ret;
// 	std::vector<int> temp;
// 	for(int i=0; i<N; i++)
// 	{
// 		temp.push_back(N-1-i);
// 	}
// 	_ret.push_back(temp);
// 	return _ret;
// }

int main()
{
	string S;
	int no_of_cities;
	float dist,x,y;
	vector<pair<float,float>> city_coords;
	vector<vector<float>> distances;
	vector<float> temp;
	vector<vector<int>> tours; 
	cin>>S>>no_of_cities;
    int E = (no_of_cities*no_of_cities);
    E-=no_of_cities;
    E/=2;
    Graph* G = createGraph(no_of_cities, E);
	for(int i=0; i<no_of_cities; i++)
	{
		cin>>x>>y;
		city_coords.push_back(make_pair(x,y));
	}
    cout<<E<<" "<<no_of_cities<<endl;
    int p=0;
	for(int i=0; i<no_of_cities; i++)
	{
		for(int j=0; j<no_of_cities; j++)
		{
			cin>>dist;
            if(j>=i)
            {
                G->edge[p].src=i;
                G->edge[p].dest=j;
                G->edge[p].weight=dist;
                p++;
            }
			// temp.push_back(dist);
		}
		// distances.push_back(temp);
		// temp.clear();
	}
	printf("input read succesful\n");
	// tours = best_tour_calculator(S,no_of_cities,city_coords,distances);
    KruskalMST(G);
	// for(int i=0; i<tours.size(); i++)
	// {
	// 	for(int j=0; j<tours[i].size(); j++)
	// 	{
	// 		cout<<tours[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }
	printf("output ends\n");
	return 0;
}
