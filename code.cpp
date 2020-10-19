#include <bits/stdc++.h>
#include <string.h>
using namespace std;

vector<vector<int>> best_tour_calculator(int N, vector<pair<float,float>> city_coords, vector<vector<float>> distances)
{
	vector<vector<int>> _ret;
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
	tours = best_tour_calculator(no_of_cities,city_coords,distances);
	for(int i=0; i<tours.size(); i++)
	{
		for(int i=0; i<tours[1].size(); i++)
		{
			cout<<tours[1][i]<<" ";
		}
		cout<<endl;
	}
}