#include <bits/stdc++.h>
#include <string.h>
using namespace std;

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
		
	}
}