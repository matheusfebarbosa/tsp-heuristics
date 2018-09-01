#include <iostream>
#include "graph.h"

using namespace std;

int main(int agr_c,char **arg_v){

	Graph g;
	vector<int> path;

	g.read_graph(arg_v[1]);

	//g.print_graph();

	cout << g.nn_tsp(0,path);

	return 0;
}