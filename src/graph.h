#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <set>

#define INF 0x6f6f6f

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
	int nn_tsp(int source, std::vector<int> &path);
	int multi_nn_tsp(std::vector<int> &path);
	int sum_up(std::vector<int> &path);
	void opt_3_rec(std::vector<int> &path);
	int opt_3(std::vector<int> &path);
	int opt_3_test(std::vector<int> &path,int a,int b, int c);
	void opt_2_rec(std::vector<int> &path);
	int opt_2(std::vector<int> &path);
	int opt_2_test(std::vector<int> &path,int a,int b);

};