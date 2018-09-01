#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

class Point{
public:	
	double x;
	double y;

	Point(){
		x=0;y=0;
	}

	Point(double cx,double cy){
		x=cx;y=cy;
	};
};

class Graph {
	int *adj_matrix;
	int n;

public:
	int init_graph(int v_n, std::vector <Point> pts, char type);
	int read_graph(std::string file_name);
	void print_graph();

};