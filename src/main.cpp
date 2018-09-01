#include <iostream>
#include "graph.h"

using namespace std;

int main(int agr_c,char **arg_v){

	Graph g;

	g.read_graph(arg_v[1]);

	g.print_graph();


	


	return 0;
}