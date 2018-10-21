#include <iostream>
#include "graph.h"

using namespace std;

int main(int agr_c,char **arg_v){

	Graph g;
	vector<int> path;

	if(agr_c<2){
		cerr << "Missing arguments\n";
		return 1;
	}

	g.read_graph(arg_v[1]);

	//g.print_graph();

	clock_t begin = clock();

	//Generate initial solution with nearest neighbor heuristic
	cout << "Answer NN: " << g.multi_nn_tsp(path) << endl;
	//First do a local search in a smaller neighborhood with 2-opt
	g.opt_2(path);
	//Get a better answer searching with 3-opt
	cout << "Answer VND: " << g.opt_3(path) << endl;

	cout << "Answer Tabu Search: " << g.tabu_search(path) << endl;

  	clock_t end = clock();

  	double time = double(end - begin) / CLOCKS_PER_SEC;

  	cout << "Time: " << time << endl;

	return 0;
}
