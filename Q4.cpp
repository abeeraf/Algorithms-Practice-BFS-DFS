#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <queue>
#include <vector>
#include <list>

using namespace std;

void PrintMinDist(int** graph,int num_cities,int num_roads)
{
	//source=1-1
	//dest=num_cities-1

	//Will apply DFS now

	queue<int>recurver;//store the path
	int dist_from_source[num_cities];
	bool visited[num_cities];

	recurver.push(0);	//first vertex
	dist_from_source[0]=0;
	visited[0]=1;
	
	for( int x = 1 ; x < num_cities ; x++)
	{
		dist_from_source[x]=1000;
		visited[x]=0;
	}
	while(!recurver.empty())
	{
		queue<int>neighbours;

		for( int x = 0 ; x < num_cities ; x++)
		{	
			if(graph[recurver.front()][x])
			neighbours.push(x);
		}
		int size=neighbours.size();
		for( int x = 0 ; x < size ; x++)
		{	
			if(!visited[neighbours.front()])
			{
				visited[neighbours.front()]=1;
				dist_from_source[neighbours.front()]=dist_from_source[recurver.front()]+1;
				recurver.push(neighbours.front());
			}
			if(neighbours.front()==num_cities-1)
			break;
			neighbours.pop();
		}
		recurver.pop();
	}	
	cout << "Minimum Number of cities is : "<< dist_from_source[num_cities-1]<<endl; 
}

int main()
{

	string Name_file;
	string line;
	int Num_Countries=0;
	int Num_Countries2=0;
	
	int count=1;

	string num_cities1=" ";
	string num_roads1=" ";

	cout<<"Enter Text File name"<<endl;
	cin>>Name_file;
	
	fstream obj;
	obj.open(Name_file);
	while (!obj.eof())
	{	
		
		if (count==1)
		{	
			getline (obj,line);
			istringstream convert(line);
			convert >> Num_Countries;
			count++;
		}
		if (count==2)
	  	{
			Num_Countries2++;
			if(Num_Countries<Num_Countries2)
			break;

			getline (obj,line);
			num_cities1=line[0];
			num_roads1=line[2];
			//convert to integers
			istringstream convert2(num_cities1);
			istringstream convert3(num_roads1);
			
			int num_cities;
			int num_roads;

			convert2 >> num_cities;
			convert3 >> num_roads;

			int** graph=new int*[num_cities];
			for( int x = 0 ; x < num_cities ; x++)
			{
				graph[x]=new int[num_cities]; //2D matrix of graph initialised with 0s
	
			}
			for( int x = 0 ; x < num_cities ; x++)
			{
				for( int y = 0 ; y < num_cities ; y++)
				graph[x][y]=0;
			}
			count=1;
			while (count<=num_roads)
			{
				getline (obj,line);
				num_cities1=line[0];//reusing simply
				num_roads1=line[2];//reusing simply

				istringstream convert4(num_cities1);
				istringstream convert5(num_roads1);
				
				int city1;
				int city2;
				
				convert4 >> city1;
				convert5 >> city2;

				graph[city1-1][city2-1]=1;
				graph[city2-1][city1-1]=1;
				count++;
			
			}
		PrintMinDist(graph,num_cities,num_roads);
		}
		count=2;
	}

}
















