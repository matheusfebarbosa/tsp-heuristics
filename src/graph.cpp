#include "graph.h"

using namespace std;

int Graph::init_graph(int vx_n, vector <Point> pts, char type){
	int i = 0,j,xd,yd,dij;
	double rij;

	n = vx_n;
	adj_matrix = (int*) malloc(vx_n*vx_n*sizeof(int));

	for(pa : pts){
		j=0;
		for(pb : pts){
			if(i!=j){
				xd= pb.x-pa.x;
				yd= pb.y-pa.y;

				if(type == 'e'){
					dij= round(sqrt(xd*xd + yd*yd));
				}else{
					rij= sqrt((xd*xd + yd*yd)/10.0);
					dij= round(rij);

					if(dij<rij)
						dij++;
				}

				adj_matrix[i*n+j] = dij;
				adj_matrix[j*n+i] = dij;
			}
			j++;
		}
		i++;
	}

	return 0;
}

int Graph::read_graph(string file_name){
	
	ifstream file(file_name.c_str());
	int vx_n,i;
	string buffer;
	char type;
	Point p;
	vector <Point> points;

	file.ignore(256,'\n');
	file.ignore(256,'\n');
	file.ignore(256,'\n');
	file.ignore(256,':');
	file >> vx_n;

	file.ignore(256,':');
	file >> buffer;	

	if(buffer == "EUC_2D"){
		type = 'e';
	}else{
		type = 'a';
	}

	file.ignore(256,'\n');
	file.ignore(256,'\n');

	while(file >> i >> p.x >> p.y){
		points.push_back(p);
	}

	init_graph(vx_n,points,type);

	return 0;
}

int Graph::nn_tsp(int source, vector<int> &path){

	set<int> in;
	int a = source;
	int nearest,inn,sum=0;

	for(int i = 0; i<n; i++){
		in.insert(i);
	}

	in.erase(source);
	path.push_back(source);

	while(!in.empty()){
		nearest = INF;
		for(b : in){
			if(adj_matrix[a*n+b]<nearest){
				inn = b;
				nearest = adj_matrix[a*n+b];
			}
		}

		sum += nearest;
		a = inn;
		in.erase(a);
		path.push_back(a);
	}

	sum+=adj_matrix[a*n+source];

	return sum;
}

int Graph::multi_nn_tsp(vector<int> &path){

	vector<int> aux;
	int best = INF, ans;

	for(int i = 0; i<n; i++){
		ans = nn_tsp(i,path);
		if(ans < best){
			best = ans;
			path = aux;
		}
	}

	return best;
}

void Graph::print_graph(){
	for(int i = 0; i<n; i++){
		for(int j = 0; j<n; j++){
			cout << adj_matrix[i*n+j] << "  ";
		}
		cout << "\n\n";
	}
}