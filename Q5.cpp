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
#include <stack>

using namespace std;
int main()
{
	
	fstream obj;
	obj.open("friends.csv");
	string line;
	string name1;
	string name2;

	int x=0;
	int count=0;

	int num_lines=0;
	int num_lines2=0;
	string* uninames;
	
	while (getline (obj,line))//First time getting num of lines 
	{	
		num_lines++;
	}

	uninames=new string[num_lines*2];
	int num_uninames=0;
	bool unique1=0;
	bool unique2=0;

	obj.close();
	obj.open("friends.csv");

	while (getline (obj,line))//First time getting unique names
	{	
		name1="            ";
		name2="            ";
		x=0;
		count=0;
		unique1=0;
		unique2=0;

		while(line[x]!='	')
		name1[count++]=line[x++];

		name1.resize(count);		

		x++;
		count=0;

		while(x!=line.size())
		name2[count++]=line[x++];

		x++;

		name2.resize(count);
		for( int x = 0 ; x < num_uninames ; x++)
		{
			if (uninames[x]==name1)
			unique1=1;
			if (uninames[x]==name2)
			unique2=1;
		}
		
		if (!unique1)
		{
			uninames[num_uninames++]=name1;
		}		
		if (!unique2)
		{		
			uninames[num_uninames++]=name2;
		}
	 
	}

	struct Node{
	string name;
	vector<string>friends;
	};

	Node* graph=new Node[num_uninames];
	for( int x = 0 ; x < num_uninames ; x++) //adding unique names to the graph
	{
		graph[x].name=uninames[x];
		//cout<<graph[x].name<<endl;
	}

	obj.close();			//adding friends
	obj.open("friends.csv");
	while (getline (obj,line))
	{	
		name1="            ";
		name2="            ";
		x=0;
		count=0;
		unique1=0;
		unique2=0;

		while(line[x]!='	')
		name1[count++]=line[x++];

		name1.resize(count);		

		x++;
		count=0;

		while(x!=line.size())
		name2[count++]=line[x++];

		x++;

		name2.resize(count);
		for( int x = 0 ; x < num_uninames ; x++)
		{
			if(graph[x].name==name1)//becuase undirected both sides friends 
			graph[x].friends.push_back(name2);
			if(graph[x].name==name2)
			graph[x].friends.push_back(name1);

		}
	}

	int most_fri=graph[0].friends.size();
	for( int x = 0 ; x < num_uninames ; x++)
	{
		if(graph[x].friends.size()>most_fri)
		{
			most_fri=graph[x].friends.size();
		}
	}

	int least_fri=graph[0].friends.size();
	for( int x = 0 ; x < num_uninames ; x++)
	{
		if(graph[x].friends.size()<least_fri)
		{
			least_fri=graph[x].friends.size();
		}
	}
	int fri;
	cout<<"Here is what we found out:"<<endl;

	for( int x = 0 ; x < num_uninames ; x++)
	{	
		if(graph[x].friends.size()==most_fri)
		cout<<graph[x].name<<" has the most number of friends, which are "<<most_fri<<endl;
	}
	for( int x = 0 ; x < num_uninames ; x++)
	{	
		if(graph[x].friends.size()==least_fri)
		cout<<graph[x].name<<" has the least number of friends, which are "<<least_fri<<endl;	
	}

	//jump:
	cout<<"Enter the number of friends and we will tell you who has them."<<endl;
	cin>>fri;
	//char choice;
	//int lilcount=0;
	for( int x = 0 ; x < num_uninames ; x++)
	{	
		if(graph[x].friends.size()==fri)
		{
			cout<<graph[x].name<<" has this number of friends."<<endl;//lilcount++;
		}
		/*else if (!lilcount)
		{
			cout<<"Person Not Found. Want to Try again? [Y/N]"<<endl;
			cin>>choice;
			if(choice=='Y' or choice=='y')
			goto jump;
			else
			goto here;
		}*/
	}
	//here:
	string a,b;
	cout<<"Enter names of two friends and we will tell you who are their mutual friends."<<endl;
	cout<<"if Nothing shows up :( There are no Mutual Friends"<<endl;
	cin>>a>>b;
	for( int x = 0 ; x < num_uninames ; x++)
	{
		for( int y = 0 ; y < num_uninames ; y++)
		{
			if(graph[x].name==a && graph[y].name==b)// found their indexes
			{
				
				for(vector<string>::iterator it1 = graph[x].friends.begin() ; it1 != graph[x].friends.end(); ++it1)
				{
					for(vector<string>::iterator it = graph[y].friends.begin() ; it != graph[y].friends.end(); ++it)
					{
						if(*it1 == *it)
						cout<<*it<<" is a mutual friend."<<endl;
					}

				}
			}
		}
	}

	///////////////////////BFS////////////////////////
	string first_node;
	queue<string>recurver;
	cout<<"Enter name to start BFS from (OutPut is in file)"<<endl;
	cin>>first_node;

	bool visited[num_uninames];
	int node;
	for( int x = 0 ; x < num_uninames ; x++)
	{
		visited[x]=0;//Empty

		if(graph[x].name==first_node)
		node=x;
	}
	fstream obj2;
	obj2.open("BFS.txt");
	obj2<<"Here is the Breadth First Search starting from :"<<first_node<<endl;

	visited[node]=1;
	recurver.push(first_node);
	while(!recurver.empty()) 
	{ 
		for( int x = 0 ; x < num_uninames ; x++)
		{

			if(graph[x].name==first_node)
			{node=x;}
		}
		
		obj2<<recurver.front()<<",";
		
		for(vector<string>::iterator it1 = graph[node].friends.begin() ; it1 != graph[node].friends.end(); ++it1)
		{	int node2;
			for( int x = 0 ; x < num_uninames ; x++)
			{
				if(graph[x].name==*it1)
				node2=x;
			}
				if(visited[node2]==0)//Empty
			{
				visited[node2] = true; 
				recurver.push(*it1); 
			} 
		}
		recurver.pop();
	}
	//obj2.close();
	////////////////////////////////////DFS///////////////////////////
/*	string first_node2;
	stack<string>recurver2;
	cout<<"Enter name to start DFS from"<<endl;
	cin>>first_node2;

	bool visited2[num_uninames];
	int node3;
	for( int x = 0 ; x < num_uninames ; x++)
	{
		visited[x]=0;//Empty

		if(graph[x].name==first_node2)
		node3=x;
	}
	fstream obj3;
	obj3.open("DFS.txt");
	obj3<<"Here is the Depth First Search starting from :"<<first_node<<endl;

	visited2[node]=1;
	recurver2.push(first_node2);
	while(!recurver2.empty()) 
	{ 
		for( int x = 0 ; x < num_uninames ; x++)
		{

			if(graph[x].name==first_node2)
			{node3=x;}
		}
		
		obj2<<recurver2.top()<<",";
		
		for(vector<string>::iterator it1 = graph[node3].friends.begin() ; it1 != graph[node3].friends.end(); ++it1)
		{	int node4;
			for( int x = 0 ; x < num_uninames ; x++)
			{
				if(graph[x].name==*it1)
				node4=x;
			}
				if(visited2[node4]==0)//Empty
			{
				visited[node4] = true; 
				recurver2.push(*it1); 
			} 
		}
		recurver2.pop();
	}
	obj3.close();
*/	
}

















