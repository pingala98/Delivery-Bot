/*
*
* Team Id: 2487
* Author List:utkarsh
* Filename:NS_Task1_Sandbox.cpp
* Theme: Nutty Squirrel – eYRC Specific
* Functions:take_values(),other predefined functions
*Global Variables: a, b, c (all bool type)
*
*/
#include "NS_Task_1_Sandbox.h"
#include<vector>
#include<algorithm>
#include<tuple>
#define V 35
using namespace std;
/*
*
* Function Name: take_values
* Input: void
* Output: void
* Logic: used to simplify the reading of each sensor,convert them in binary format and also prints them
* Example Call: take_values()
*
*/
int d;
char color;
bool a, b, c;   //a= left_sensor , b= center_sensor , c= right_sensor, d=proximity_sensor
void take_values()
{
	_delay_ms(1);
	a = ADC_Conversion(1); b = ADC_Conversion(2); c = ADC_Conversion(3);
	//printf("a=%d\tb=%d\tc=%d    %d\n", a, b, c, d);
}

char detectColor()
{
	int green=0, red=0;
		filter_green();
		green = color_sensor_pulse_count;
		filter_red();
		red = color_sensor_pulse_count;
	//green /= 10;
	//red /= 10;
	//printf("%d   %d\n ", green, red);
	//_delay_ms(200);
	if (green > 3500 && red < 2000)
		return 'g';
	else if (red > 3500 && green<2000)
		return 'r';
	else if (red < 1800 && green<1800)
		return 'n';
	else
		return 'b';

}

vector<int> col(35, 0);
vector<vector<int>> graph(35, col);
vector<tuple<int, int, char>> dir[35];
vector<int> sol;
vector<char> path;
int currentNode, nextNode, prevNode, currentPath, prevPath;     //currentPath tracks realtime bot location in terms of iterator to path array
bool obstacle = false;

int minDistance(int dist[], bool sptSet[])
{
	int min = INT_MAX, min_index;

	for (int v = 1; v < V; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

char getDir(int prevNode, int currentNode, int nextNode)
{
	for (unsigned int i = 0; i < dir[currentNode].size(); i++)
	{
		if (prevNode == get<0>(dir[currentNode][i]) && nextNode == get<1>(dir[currentNode][i]))
			return get<2>(dir[currentNode][i]);
	}
	return 's';
}

bool printSolution(int src, int dest, int parent[])
{
	sol.clear();
	int i = dest;
	while (i != src)
	{
		sol.push_back(i);
		i = parent[i];

	}
	reverse(sol.begin(), sol.end());
	path.clear();
	currentNode = sol[0];
	prevNode = src;
	if (obstacle)
	{
		path.push_back(getDir(prevPath, src, sol[0]));
	}
	/*if (src == 10)
	{
		path.push_back('f');
	}*/
	for (unsigned int j = 0; j < sol.size() - 1; j++)
	{
		nextNode = sol[j + 1];
		path.push_back(getDir(prevNode, currentNode, nextNode));
		prevNode = currentNode;
		currentNode = nextNode;
		//currentNode=get<0>(dir[2][0]);
	}
	cout << "\nShortest Path==>";
	for (unsigned int j = 0; j < sol.size(); j++)
		cout << sol[j] << "->";
	cout << "\nDirections==>";
	for (unsigned int j = 0; j < path.size(); j++)
		cout << path[j] << "->";
	cout << "\n";
	cout << endl;
	
	if (src == 10)
		forward_wls(1);

	
	return pathToMotion();
}

bool dijkstra(int src, int des)
{
	int dist[V];
	bool sptSet[V];
	int parent[V];
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX, sptSet[i] = false;
	dist[src] = 0;
	for (int count = 0; count < V - 2; count++)
	{
		int u = minDistance(dist, sptSet);

		sptSet[u] = true;
		for (int v = 0; v < V; v++)
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
			{
				dist[v] = dist[u] + graph[u][v];
				parent[v] = u;
			}
	}
	return printSolution(src, des, parent);
}

void AddNode(int u, int v, int x)
{
	graph[u][v] = x;
	graph[v][u] = x;
}

void GraphInput()
{
	AddNode(1, 3, 100);
	AddNode(3, 7, 125);
	AddNode(7, 8, 225);
	AddNode(8, 9, 100);
	AddNode(9, 15, 373);
	AddNode(4, 8, 100);
	AddNode(15, 17, 373);
	AddNode(16, 17, 373);
	AddNode(11, 16, 373);
	AddNode(11, 9, 1453);
	AddNode(17, 14, 150);
	AddNode(10, 14, 100);
	AddNode(12, 13, 225);
	AddNode(11, 12, 100);
	AddNode(5, 12, 100);
	AddNode(2, 6, 100);
	AddNode(13, 6, 125);
	AddNode(7, 18, 600);
	AddNode(15, 20, 600);
	AddNode(13, 19, 600);
	AddNode(16, 21, 600);
	AddNode(17, 25, 650);
	AddNode(18, 22, 590);
	AddNode(19, 28, 590);
	AddNode(21, 27, 275);
	AddNode(20, 23, 275);
	AddNode(22, 23, 200);
	AddNode(27, 28, 200);
	AddNode(24, 23, 200);
	AddNode(24, 25, 200);
	AddNode(25, 26, 200);
	AddNode(26, 27, 200);
	AddNode(29, 22, 100);
	AddNode(23, 30, 100);
	AddNode(24, 31, 100);
	AddNode(26, 32, 100);
	AddNode(27, 33, 100);
	AddNode(28, 34, 100);
	AddNode(18, 20, 300);
	AddNode(19, 21, 300);
}

void AddDir(int a, int x, int y, char z)
{
	dir[a].push_back(make_tuple(x, y, z));
}

void DirInput()
{
	AddDir(3, 1, 7, 'l');      //u
	AddDir(3, 7, 1, 's');      //stop i.e forward_wls(i),i=0
	AddDir(7, 8, 3, 'r');
	AddDir(7, 8, 18, 'l');
	AddDir(7, 18, 3, 'f');
	AddDir(7, 18, 8, 'r');
	AddDir(7, 3, 8, 'l');
	AddDir(7, 3, 18, 'f');
	AddDir(8, 7, 4, 'l');
	AddDir(8, 7, 9, 'f');
	AddDir(8, 9, 4, 'r');
	AddDir(8, 9, 7, 'f');
	AddDir(8, 4, 7, 'l');      //
	AddDir(8, 4, 9, 'r');      //
	AddDir(9, 8, 11, 'l');
	AddDir(9, 8, 15, 'r');
	AddDir(9, 15, 8, 'l');
	AddDir(9, 15, 11, 'f');
	AddDir(9, 11, 8, 'r');
	AddDir(9, 11, 15, 'f');
	AddDir(10, 0, 14, 'f');    //
	AddDir(14, 10, 17, 'f');
	AddDir(14, 17, 10, 'f');
	AddDir(11, 9, 12, 'l');
	AddDir(11, 9, 16, 'f');
	AddDir(11, 16, 9, 'f');
	AddDir(11, 16, 12, 'r');
	AddDir(11, 12, 16, 'l');
	AddDir(11, 12, 9, 'r');
	AddDir(12, 11, 5, 'l');
	AddDir(12, 11, 13, 'f');
	AddDir(12, 13, 11, 'f');
	AddDir(12, 13, 5, 'r');
	AddDir(12, 5, 11, 'l');
	AddDir(12, 5, 13, 'r');
	AddDir(13, 12, 6, 'l');
	AddDir(13, 12, 19, 'r');
	AddDir(13, 19, 6, 'f');
	AddDir(13, 19, 12, 'l');
	AddDir(13, 6, 12, 'r');
	AddDir(13, 6, 19, 'f');
	AddDir(6, 13, 2, 's');
	AddDir(6, 2, 13, 'l');			//u
	AddDir(15, 9, 17, 'f');
	AddDir(15, 9, 20, 'r');
	AddDir(15, 17, 20, 'l');
	AddDir(15, 17, 9, 'f');
	AddDir(15, 20, 9, 'l');
	AddDir(15, 20, 17, 'r');
	AddDir(16, 21, 17, 'l');
	AddDir(16, 21, 11, 'r');
	AddDir(16, 11, 21, 'l');
	AddDir(16, 11, 17, 'f');
	AddDir(16, 17, 11, 'f');
	AddDir(16, 17, 21, 'r');
	AddDir(17, 14, 15, 'r');
	AddDir(17, 14, 16, 'l');
	AddDir(17, 14, 25, 'f');
	AddDir(17, 16, 15, 'f');
	AddDir(17, 16, 25, 'l');
	AddDir(17, 16, 14, 'r');
	AddDir(17, 15, 25, 'r');
	AddDir(17, 15, 14, 'l');
	AddDir(17, 15, 16, 'f');
	AddDir(17, 25, 14, 'f');
	AddDir(17, 25, 15, 'l');
	AddDir(17, 25, 16, 'r');
	AddDir(18, 7, 22, 'f');
	AddDir(18, 7, 20, 'l');
	AddDir(18, 20, 7, 'r');
	AddDir(18, 20, 22, 'l');
	AddDir(18, 22, 7, 'f');
	AddDir(18, 22, 20, 'r');
	AddDir(19, 13, 28, 'f');
	AddDir(19, 13, 21, 'r');
	AddDir(19, 28, 13, 'f');
	AddDir(19, 28, 21, 'l');
	AddDir(19, 21, 28, 'r');
	AddDir(19, 21, 13, 'l');
	AddDir(20, 15, 23, 'f');
	AddDir(20, 15, 18, 'r');
	AddDir(20, 18, 15, 'l');
	AddDir(20, 18, 23, 'r');
	AddDir(20, 23, 15, 'f');
	AddDir(20, 23, 18, 'l');
	AddDir(21, 16, 27, 'f');
	AddDir(21, 16, 19, 'l');
	AddDir(21, 19, 16, 'r');
	AddDir(21, 19, 27, 'l');
	AddDir(21, 27, 19, 'r');
	AddDir(21, 27, 16, 'f');
	AddDir(22, 18, 29, 's');
	AddDir(22, 18, 23, 'l');
	AddDir(22, 29, 18, 'r');
	AddDir(22, 29, 23, 'l');
	AddDir(22, 23, 29, 'l');
	AddDir(22, 23, 18, 'r');
	AddDir(23, 30, 22, 'r');
	AddDir(23, 30, 20, 'u');		//u
	AddDir(23, 30, 24, 'l');
	AddDir(23, 24, 30, 'l');
	AddDir(23, 24, 20, 'r');
	AddDir(23, 24, 22, 'f');
	AddDir(23, 22, 24, 'f');
	AddDir(23, 22, 20, 'l');
	AddDir(23, 22, 30, 'r');
	AddDir(23, 20, 22, 'r');
	AddDir(23, 20, 24, 'l');
	AddDir(23, 20, 30, 's');
	AddDir(24, 31, 23, 'r');
	AddDir(24, 31, 25, 'l');
	AddDir(24, 23, 31, 'r');
	AddDir(24, 23, 25, 'f');
	AddDir(24, 25, 23, 'f');
	AddDir(24, 25, 31, 'l');
	AddDir(25, 17, 26, 'l');
	AddDir(25, 17, 24, 'r');
	AddDir(25, 26, 17, 'r');
	AddDir(25, 26, 24, 'f');
	AddDir(25, 24, 26, 'f');
	AddDir(25, 24, 17, 'l');
	AddDir(26, 25, 32, 'r');
	AddDir(26, 25, 27, 'f');
	AddDir(26, 32, 25, 'r');
	AddDir(26, 32, 27, 'l');
	AddDir(26, 27, 32, 'l');
	AddDir(26, 27, 25, 'f');
	AddDir(27, 33, 26, 'r');
	AddDir(27, 33, 28, 'l');
	AddDir(27, 33, 21, 'u');		//u
	AddDir(27, 26, 28, 'f');
	AddDir(27, 26, 33, 'r');
	AddDir(27, 26, 21, 'l');
	AddDir(27, 28, 33, 'l');
	AddDir(27, 28, 21, 'r');
	AddDir(27, 28, 26, 'f');
	AddDir(27, 21, 26, 'r');
	AddDir(27, 21, 28, 'l');
	AddDir(27, 21, 33, 's');
	AddDir(28, 27, 34, 'r');
	AddDir(28, 27, 19, 'l');
	AddDir(28, 19, 34, 's');
	AddDir(28, 19, 27, 'r');
	AddDir(28, 34, 27, 'r');
	AddDir(28, 34, 19, 'l');
	AddDir(9, 15, 15, 'u');
	AddDir(9, 11, 11, 'u');
	AddDir(15, 9, 9, 'u');
	AddDir(15, 17, 17, 'u');
	AddDir(17, 15, 15, 'u');
	AddDir(17, 16, 16, 'u');
	AddDir(16, 17, 17, 'u');
	AddDir(16, 11, 11, 'u');
	AddDir(18, 20, 20, 'u');
	AddDir(20, 18, 18, 'u');
	AddDir(20, 23, 23, 'u');
	AddDir(21, 27, 27, 'u');
	AddDir(21, 19, 19, 'u');
	AddDir(19, 21, 21, 'u');

}

/*
*
* Function Name: forward_wls
* Input: node
* Output: void
* Logic: Uses white line sensors to go forward by the number of nodes specified
* Example Call: forward_wls(2); //Goes forward by two nodes
*
*/
bool forward_wls(unsigned char node)
{
	int nodes = 0;
	bool o;
	while (a && b && c)
	{
		take_values();
		forward();
		velocity(100, 100);
	}
	
	//forward();
	//_delay_ms(300);
	while (nodes < node)
	{
		o=Square();
		nodes++;
	}
	stop();
	return o;
}
/*
*
* Function Name: left_turn_wls
* Input: void
* Output: void
* Logic: Uses white line sensors to turn left until black line is encountered
* Example Call: left_turn_wls(); //Turns right until black line is encountered
*
*/
void left_turn_wls(int i=0)
{
	if (i == 1)
		i = 820;
	else
		i = 300;
	left();
	velocity(150, 150);
	_delay_ms(i);
	//take_values();
	while(ADC_Conversion(2)<100);
	stop();
}

/*
*
* Function Name: right_turn_wls
* Input: void
* Output: void
* Logic: Uses white line sensors to turn right until black line is encountered
* Example Call: right_turn_wls(); //Turns right until black line is encountered
*/
void right_turn_wls(int i=0)
{
	if (i == 1)
		i = 820;		//620
	else
		i = 300;
	right();
	velocity(150, 150);
	_delay_ms(i);
	take_values();
	while (ADC_Conversion(2)<100);
	stop();
}

/*
*
* Function Name: Square
* Input: void
* Output: void
* Logic: Use this function to make the robot trace a square path on the arena
* Example Call: Square();
*/

int direction(char x)
{
	switch (x)
	{
	case 'r':right_turn_wls(0);
		break;
	case 'l':left_turn_wls(0);
		break;
	case 'f':
		break;
	case 's':return 0;
		break;
	case 'u':left_turn_wls(0);
		left_turn_wls(0);
		break;
	}
	return 1;
}

bool pathToMotion()
{
	int j;
	unsigned int i;
	bool o;
	for (i = 0; i < path.size()-1; i++)
	{
		currentPath = i;
		j = direction(path[i]);
		o=forward_wls(j);
		if (o)
			return true;
	}
	direction(path[i]);
	return 0;
}
int ob1[14] = { 7,18,18,22,15,20,17,25,16,21,13,19,19,28 }, ob2[14] = { 18,7,22,18,20,15,25,17,21,16,19,13,28,19 };
void obstacleDetected()
{
	bool x = false;
	obstacle = true;
	printf("ostacle detected!!!");	
	int u=sol[currentPath], v= sol[currentPath+1];
		graph[u][v] = 0;
		graph[v][u] = 0;
		left_turn_wls(1);
		for (int j = 0; j < 14; j++)
		{
			if (u == ob1[j] && v == ob2[j])
			{
				x = true;
				break;
			}
		}
		if (x)
		{
			forward_wls(1);
			prevPath = v;
		}
		else
			prevPath = sol[currentPath - 1];
		if (dijkstra(u, currentNode))
		{
			currentPath -= 1;
			obstacleDetected();
		}
		obstacle = false;

}

bool Square(void)
{
	bool temp;
	while (1)
	{
		temp = (a==1) ;
		take_values();
		d = ADC_Conversion(4);
		if (d < 70 && d > 10 && detectColor()=='b')
		{
			return 1;
		}
		if (!a && b && !c)
		{
			forward();
			velocity(170, 170);
		}
		else if (a && b && !c)
		{
			forward();
			velocity(60, 170);
		}
		else if (!a && b && c)
		{
			forward();
			velocity(170, 60);
		}
		else if (a && b && c)
		{
			forward();
			//velocity(150, 150);
			_delay_ms(315);
			stop();
			return 0;
		}
		else if (a && !b && !c)
		{
			left();
			velocity(20, 160);
		}
		else if (!a && !b && c)
		{
			right();
			velocity(160, 20);
		}
		else if (!a && !b && !c)			//brilliant implementation [  if it works ;)  ]
		{
			if (temp)
			{
				while (!a)
				{
					forward();
					velocity(0, 160);
					take_values();
				}
			}
			else
			{
				while (!c)
				{
					forward();
					velocity(160, 0);
					take_values();
				}
			}
		//	forward();
			//velocity(150, 150);
		}
	}
	
}

/*
*
* Function Name: Task_1_1
* Input: void
* Output: void
* Logic: Use this function to encapsulate your Task 1.1 logic
* Example Call: Task_1_1();
*/
void Task_1_1(void)
{
	forward_wls(1);
	right_turn_wls(1);
	forward_wls(1);
	forward();
	_delay_ms(230);
	left_turn_wls();
	forward_wls(1);
	forward_wls(1);
	left_turn_wls();
	forward_wls(1);
	left_turn_wls();
	forward_wls(1);
	right_turn_wls();
	forward_wls(1);
	right_turn_wls();
	forward_wls(1);
	soft_right();
	velocity(70, 70);
	_delay_ms(30);
	forward_wls(1);
	left_turn_wls();
	forward_wls(1);
	right_turn_wls();
	forward_wls(1);
	left_turn_wls();
	forward_wls(1);
}

/*
*
* Function Name: Task_1_2
* Input: void
* Output: void
* Logic: Use this function to encapsulate your Task 1.2 logic
* Example Call: Task_1_2();
*/

int dgreen[2] = { 1,4 }, dred[2] = { 2,5 }, spickup[6] = { 32,33,34,31,30,29 };		//source destinations and sources of nut
void Task_1_2(void)
{
	GraphInput();
	DirInput();
	//dijkstra(10, 34);
	char color;
	int n=0, g=0, r=0, s=0;		//destinstion and source array iterators and nut-count
	currentNode = 10;
	bool o;
	while (n < 4 && s < 6)
	{
		o = false;
		o=dijkstra(currentNode, spickup[s]);
		++s;
		if (o)
			obstacleDetected();
		o = false;
		color=detectColor();
		if (color == 'g')
		{
			pick();
			cout << "\ngreen nut picked!!\n";
			o=dijkstra(currentNode, dgreen[g]);
			++g;
		}
		else if (color == 'r')
		{
			pick();
			cout << "\nred nut picked!!\n";
			o=dijkstra(currentNode, dred[r]);
			++r;
		}
		else if (color == 'n')
		{
			cout << "nut not found\n";
			continue;
		}
		else
			cout << "color error!!restart the simulation";
		if (o)
			obstacleDetected();
		place();
		cout << "\nnut placed!!!";
		++n;
	}
	dijkstra(currentNode, 10);
	//forward_wls(1);
}
