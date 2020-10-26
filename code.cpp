#include <bits/stdc++.h>
#include <string.h>
using namespace std;

vector<vector<int>> best_tour_calculator(string S, intwwdw N, vector<pair<float,float>> city_coords, vector<vector<float>> distances)
{
	vector<vector<int>> _ret;
	std::vector<int> temp;
	for(int i=0; i<N; i++)
	{
		temp.push_back(N-1-i);
	}
	_ret.push_back(temp);
	return _ret;
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
	cin>>S>>no_of_cities;
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
