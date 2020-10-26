#include <bits/stdc++.h>
#include <string.h>
using namespace std;

bool form_loop(vector<vector<bool>> &adj_mat, int x, int y,int base)
{
	int curr_node=x;
	int prev_node=base;
	while(1)
	{
		int j=0;
		while(j<adj_mat[x].size())
		{
			if(adj_mat[curr_node][j] && j!=prev_node)
			{
				if(j==y)
					return false;
				if(j==base)
					return true;
				break;
			}
			j++;
		}
		if(j==adj_mat[x].size())
			break;
		prev_node = curr_node;
		curr_node = j;
	}
	return true;
}

bool check_val(vector<vector<bool>> &adj_mat, int base)
{
	int count = 0;
	int curr_node=base;
	int prev_node=base;
	// cout<<base<<" ";
	for(int k=0;k<adj_mat[curr_node].size();k++)
	{
		if(adj_mat[curr_node][k])
		{
			count++;
			curr_node = k;
		}
	}
	while(curr_node!=base)
	{
		for(int k=0;k<adj_mat[curr_node].size();k++)
		{
			if((adj_mat[curr_node][k])&&(prev_node!=k))
			{
				count++;
				prev_node = curr_node;
				curr_node = k;
				break;
			}
		}
	}
	if(count==adj_mat.size())
		return true;
	return false;
}

vector<int> print_tour(vector<vector<bool>> &adj_mat, int base)
{
	vector<int> v;
	int curr_node=base;
	int prev_node=base;
	// cout<<base<<" ";
	for(int k=0;k<adj_mat[curr_node].size();k++)
	{
		if(adj_mat[curr_node][k])
		{
			cout<<k<<" ";
			v.push_back(k);
			curr_node = k;
		}
	}
	while(curr_node!=base)
	{
		for(int k=0;k<adj_mat[curr_node].size();k++)
		{
			if((adj_mat[curr_node][k])&&(prev_node!=k))
			{
				cout<<k<<" ";
				v.push_back(k);
				prev_node = curr_node;
				curr_node = k;
				break;
			}
		}
	}
	// cout<<"\n*end of tour*\n";
	cout<<endl;
	return v;
}

// vector<vector<bool>> make_adj(vector<pair<int,int>> edge_set, int N)
// {
// 	vector<vector<bool>> adj_mat;
// 	vector<bool> temp_fv(N,false);
// 	for (int i = 0; i < N; ++i)
// 	{
// 		adj_mat.push_back(temp_fv);
// 	}
// 	for (int i = 0; i < edge_set.size(); ++i)
// 	{
// 		adj_mat[edge_set[i].first][edge_set[i].second]=true;
// 		adj_mat[edge_set[i].second][edge_set[i].first]=true;
// 	}
// 	return adj_mat;	
// }

// void two_opt(vector<int> tour,vector<vector<float>> dist)
// {
// 	vector<pair<int,int>> edge_set;
// 	for(int i=0; i<tour.size(); i++)
// 	{
// 		edge_set.push_back(make_pair(tour[i],tour[(i+1)%tour.size()]));
// 	}
// 	for(int i=0; i<edge_set.size()-1; i++)
// 	{
// 		for(int j=i+1; j<edge_set.size(); j++)
// 		{
// 			if(edge_set[i].first!=edge_set[j].first && edge_set[i].first!=edge_set[j].second && edge_set[i].second!=edge_set[j].first && edge_set[i].second!=edge_set[j].second)
// 			{
// 				if(dist[edge_set[i].first][edge_set[i].second] + dist[edge_set[j].first][edge_set[j].second] > dist[edge_set[i].first][edge_set[j].second] + dist[edge_set[j].first][edge_set[i].second])
// 				{
// 					// cout<<"saved:"<<dist[edge_set[i].first][edge_set[i].second] + dist[edge_set[j].first][edge_set[j].second] - (dist[edge_set[i].first][edge_set[j].second] + dist[edge_set[j].first][edge_set[i].second]);
// 					int temp = edge_set[i].first;
// 					edge_set[i].first = edge_set[j].first;
// 					edge_set[j].first = temp;
// 				}
// 			}
// 		}
// 	}
// 	auto adj_mat = make_adj(edge_set,tour.size());
// 	if(!check_val(adj_mat,0))
// 		print_tour(adj_mat,0);
// }

void best_tour_calculator(string S, int N, vector<pair<float,float>> &city_coords, vector<vector<float>> &distances)
{
	// int fail_itr=0;
	vector<vector<int>> _ret;
	vector<int> temp;
	int base=0;
	float last_tour_cost = FLT_MAX;
	for(int i=0;i<N;i++)
	{
		base = i;
		float tour_cost = 2*accumulate(distances[base].begin(),distances[base].end(),0.0);
		// float temp_cost = 0.0;
		int temp_i,temp_j;
		vector<int> edges_to_base(N,2);
		edges_to_base[base] = 0;
		vector<vector<bool>> adj_mat;
		vector<bool> temp_fv(N,false);
		vector<bool> temp_tv(N,true);
		temp_fv[base] = true;
		temp_tv[base] = false;
		priority_queue<tuple<float,int,int>> savings;
		for (int i = 0; i < N; ++i)
		{
			if(i!=base)
				adj_mat.push_back(temp_fv);
			else
				adj_mat.push_back(temp_tv);
		}
		for(int i=0; i<N; i++)
		{
			if(base!=i)
			{
				for(int j=i+1; j<N; j++)
				{
					if(base!=j)
					{
						savings.push(make_tuple(distances[base][j]+distances[base][i]-distances[i][j], i, j));
					}
				}
			}
		}
		// cout<<"savings size:"<<savings.size()<<endl;
		// cout<<savings.empty()<<endl;
		// auto top = savings.top();
		// cout<<get<0>(top)<<" "<<get<1>(top)<<" "<<get<2>(top)<<endl;
		while(!savings.empty())
		{

			// cout<<"edges of 5 to base"<<edges_to_base[5]<<endl;
			auto top = savings.top();
			int i=get<1>(top),j=get<2>(top);
			float cost = get<0>(top);
			if(edges_to_base[i]>0 && edges_to_base[j]>0)
			{
				if((edges_to_base[i]==1)&&(edges_to_base[j]==1))
				{
					// cout<<"going to check loop with i and j as"<<i<<" and "<<j<<endl;
					if(form_loop(adj_mat,i,j,base))
					{
						// cout<<"func out true"<<endl;
						adj_mat[i][j]=true;
						adj_mat[j][i]=true;
						adj_mat[i][base]=false;
						adj_mat[base][i]=false;
						adj_mat[j][base]=false;
						adj_mat[base][j]=false;
						tour_cost -= cost;
						edges_to_base[j]--;
						edges_to_base[i]--;
						// cout<<"added "<<i<<" "<<j<<endl;
					}
					// else
						// cout<<"func out false"<<endl;
				}
				else
				{
					adj_mat[i][j]=true;
					adj_mat[j][i]=true;
					if(edges_to_base[i]==1)
					{
						adj_mat[i][base]=false;
						adj_mat[base][i]=false;
					}
					if(edges_to_base[j]==1)
					{
						adj_mat[j][base]=false;
						adj_mat[base][j]=false;
					}
					tour_cost -= cost;
					edges_to_base[j]--;
					edges_to_base[i]--;
					// cout<<"added "<<i<<" "<<j<<endl;
				}
			}
			savings.pop();
		}
		// cout<<savings.empty()<<endl;
		if((tour_cost<last_tour_cost)&&(check_val(adj_mat,base)))
		{
			temp = print_tour(adj_mat,base);
			last_tour_cost = tour_cost;
			// fail_itr=0;
		}
		// else
		// {
		// 	fail_itr++;
		// 	if(fail_itr>N/10)
		// 	{
		// 		two_opt(temp, distances);
		// 	}
		// }
		// two_opt(temp, distances);
	}
	return ;
}


int main()
{
	string S;
	int no_of_cities;
	float dist,x,y;
	vector<pair<float,float>> city_coords;
	vector<vector<float>> distances;
	vector<float> temp;
	// vector<vector<int>> tours; 
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
	// printf("input read succesful\n");
	best_tour_calculator(S,no_of_cities,city_coords,distances);
	// printf("output ends\n");
	return 0;
}