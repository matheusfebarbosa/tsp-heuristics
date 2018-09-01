#include <iostream>
#include "graph.h"

using namespace std;

int main(int agr_c,char **arg_v){

	Graph g;
	vector<int> path;

	g.read_graph(arg_v[1]);

	//g.print_graph();

	clock_t begin = clock();
	cout << "Answer: " << g.multi_nn_tsp(path) << endl;
  	clock_t end = clock();

  	double time = double(end - begin) / CLOCKS_PER_SEC;

  	cout << "Time: " << time << endl;

	return 0;
}