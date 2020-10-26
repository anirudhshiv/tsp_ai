#include <bits/stdc++.h>
#include <string.h>
using namespace std;

vector<vector<int>> best_tour_calculator(string S, int N, vector<pair<float,float>> &city_coords, vector<vector<float>> &distances)
{
	vector<vector<int>> _ret;
	std::vector<int> temp;
	int base=0;
	float last_tour_cost = FLT_MAX;
	float tour_cost = 2*accumulate(distances[base].begin(),distances[base].end(),0.0);
	float temp_cost = 0.0;
	int temp_i,temp_j;
	std::vector<int> edges_to_base(N,2);
	edges_to_base[base] = 0;
	vector<vector<bool>> adj_mat;
	vector<bool> temp(N,false);
	vector<bool> temp_t(N,true);
	temp[base] = true;
	temp_t[base] = false;
	priority_queue<tuple<float,int,int>> savings;
	for (int i = 0; i < N; ++i)
	{
		if(i!=base)
			adj_mat.push_back(temp);
		else
			adj_mat.push_back(temp_t);
	}
	for(int i=0; i<N-1; i++)
	{
		if(base!=i)
		{
			for(int j=i+1; j<N-1; j++)
			{
				if(base!=j)
				{
					savings.push(make_tuple(distances[base][j]+distances[base][i]-distances[i][j], i, j));
				}
			}
		}
	}
	while(!savings.empty())
	{
		auto top = savings.top();
		if(edges_to_base[get<1>(top)]||edges_to_base[get<2>(top)])
		{
			savings.pop();
			break;
		}
		if((edges_to_base[get<1>(top)]==1)&&(edges_to_base[get<2>(top)]==1))
		{
			if(form_loop(adj_mat,get<1>(top),get<2>(top),base))
			{
				savings.pop();
				break;
			}
			adj_mat[get<1>(top)][get<2>(top)]=true;
			adj_mat[get<2>(top)][get<1>(top)]=true;
			tour_cost -= get<0>(top);
			edges_to_base[get<2>(top)]--;
			edges_to_base[get<1>(top)]--;
		}
		else
		{
			adj_mat[get<1>(top)][get<2>(top)]=true;
			adj_mat[get<2>(top)][get<1>(top)]=true;
			tour_cost -= get<0>(top);
			edges_to_base[get<2>(top)]--;
			edges_to_base[get<1>(top)]--;
		}
		savings.pop();
	}
	
		// int max1_in=-1,max2_in=-1;
		// float max1=0.0, max2=0.0, save=0.0;
		// for(int j=0; j<edges.size(); j++)
		// {
		// 	if(get<2>(edges[j]) > max2)
		// 	{
		// 		if(get<2>(edges[j]) > max1)
		// 		{
		// 			max2 = max1;
		// 			max2_in = max1_in;
		// 			max1 = get<2>(edges[j]);
		// 			max1_in = j;
		// 		}
		// 		else
		// 		{
		// 			max2_in = j;
		// 			max2 = get<2>(edges[j]);
		// 		}
		// 	}
		// }
	return _ret;
}

bool form_loop(vector<vector<bool>> &adj_mat, int i, int j,int base)
{
	int curr_node=i;
	int prev_node=i;
	for(int k=0;k<adj_mat[curr_node].size();k++)
	{
		if(adj_mat[curr_node][k])
		{
			if(k==j)
				return true;
			else if(k==base);
			else
				curr_node = k;
		}
	}
	while(1)
	{
		for(int k=0;k<adj_mat[curr_node].size();k++)
		{
			if((adj_mat[curr_node][k])&&(prev_node!=k))
			{
				if(k==j)
					return true;
				else if(k==base)
					return false;
				else
				{
					prev_node = curr_node;
					curr_node = k;
					break;
				}
			}
		}
	}
}

int main()
{
	string S;
	int no_of_cities;
	float dist,x,y;
	vector<pair<float,float>> city_coords;
	vector<vector<float>> distances;
	vector<float> temp;
	vector<vector<int>> tours; 
	getline(cin,S);
	cin>>no_of_cities;
	for(int i=0; i<no_of_cities; i++)
	{
		cin>>x>>y;
		city_coords.push_back(make_pair(x,y));
	}
	for(int i=0; i<no_of_cities; i++)
	{
		for(int j=0; j<no_of_cities; j++)
		{
			cin>>dist;
			temp.push_back(dist);
		}
		distances.push_back(temp);
		temp.clear();
	}
	printf("input read succesful\n");
	tours = best_tour_calculator(S,no_of_cities,city_coords,distances);
	for(int i=0; i<tours.size(); i++)
	{
		for(int j=0; j<tours[i].size(); j++)
		{
			cout<<tours[i][j]<<" ";
		}
		cout<<endl;
	}
	printf("output ends\n");
	return 0;
}