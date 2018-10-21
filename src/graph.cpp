#include "graph.h"

#define MAX_ROUNDS 3000
#define MAX_ROUNDS_WI 10
#define TABU_ROUNDS 7
#define INF_NEG (-999999)

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
		ans = nn_tsp(i,aux);
		if(ans < best){
			best = ans;
			path = aux;
		}
		aux.clear();
	}

	return best;
}

void reverse(vector<int> &v,int i, int j){
	int left = i, right = j;

	while(left<right){
		int tmp = v[left];
		v[left++] = v[right];
		v[right--] = tmp;
	}
}


int Graph::sum_up(vector<int> &path){
	int sum = 0;
	for(int i = 0; i<n;i++){
		sum+=adj_matrix[path[(i-1) < 0 ? n-1 : i-1]*n +path[i]];
		//cout << path[(i-1) < 0 ? n-1 : i-1] << " ";
	}
	//cout << endl;
	return sum;
}

void print_v(vector <int> v){
	for (auto a : v){
		cout << a << ",";
	}
	cout << endl;
}

int Graph::opt_3_test(vector<int> &path,int a,int b, int c){
	int A = path[a==0 ? n-1 : a-1], B = path[a], 
	C = path[b-1], D = path[b], E = path[c-1], 
	F = path[c%n];
	int d0 = adj_matrix[A*n + B] + adj_matrix[C*n + D] + adj_matrix[E*n + F];
	int d1 = adj_matrix[A*n + C] + adj_matrix[B*n + E] + adj_matrix[D*n + F];
	int d2 = adj_matrix[A*n + D] + adj_matrix[B*n + E] + adj_matrix[C*n + F];
	int d3 = adj_matrix[A*n + D] + adj_matrix[B*n + F] + adj_matrix[C*n + E];
	int d4 = adj_matrix[A*n + E] + adj_matrix[B*n + D] + adj_matrix[C*n + F];

	if(d1 < d0 && d1 < d2 && d1<d3 && d1<d4){
		reverse(path,a,b-1);
		reverse(path,b,c-1);
		return d0-d2;
	}else if(d2 < d0 && d2 < d1 && d2<d3 && d2<d4){				
		path.insert(path.begin()+c,path.begin()+a,path.begin()+b);
		path.erase(path.begin()+a,path.begin()+b);
		return d0-d2;
	}else if(d3 < d0 && d3 < d1 && d3<d2 && d3<d4){
		reverse(path,a,b-1);
		path.insert(path.begin()+c,path.begin()+a,path.begin()+b);
		path.erase(path.begin()+a,path.begin()+b);
		return d0-d3;
	}else if(d4 < d0 && d4 < d1 && d4<d3 && d4<d2){
		reverse(path,b,c-1);	
		vector <int> tmp;
		tmp.insert(tmp.begin(),path.begin()+b,path.begin()+c);
		path.erase(path.begin()+b,path.begin()+c);
		path.insert(path.begin()+a,tmp.begin(),tmp.end());
		return d0-d4;
	}

	return 0;
}

void Graph::opt_3_rec(vector<int> &path){
	int improve = 0;
	do{
		improve = 0;
		for(int i = 0; i < n; i++){
			for(int j = i+2; j < n; j++){
				for(int k = j+2; k < (n + (i==0 ? -1 : i==1 ? 0 : 1 )); k++){
					improve += opt_3_test(path,i,j,k);
				}
			}	
		}
	}while(improve);
}

int Graph::opt_3(vector<int> &path){
	opt_3_rec(path);
	return sum_up(path);	
}

int Graph::opt_2_test(vector<int> &path,int a,int b){
	int A = path[(a==0) ? n-1 : a-1], B = path[a], 
	C = path[b-1], D = path[b%n];

	int d0 = adj_matrix[A*n + B] + adj_matrix[C*n + D];
	int d1 = adj_matrix[A*n + C] + adj_matrix[B*n + D];

	if(d1 < d0){
		reverse(path,a,b-1);
		return d0-d1;
	}

	return 0;
}

void Graph::opt_2_rec(vector<int> &path){
	int improve = 1;
	while(improve){
		improve = 0;
		for(int i = 0; i < n; i++){
			for(int j = i+2; j < (n + (i==0 ? -1 : i==1 ? 0 : 1 )); j++){
				improve += opt_2_test(path,i,j);	
			}
		}	
	}
}

int Graph::opt_2(vector<int> &path){
	opt_2_rec(path);
	return sum_up(path);	
}

void Graph::print_graph(){
	for(int i = 0; i<n; i++){
		for(int j = 0; j<n; j++){
			cout << adj_matrix[i*n+j] << "  ";
		}
		cout << "\n\n";
	}
}

int Graph::opt_2_ver(vector<int> &path,int a,int b){
	int A = path[(a==0) ? n-1 : a-1], B = path[a], 
	C = path[b-1], D = path[b%n];

	int d0 = adj_matrix[A*n + B] + adj_matrix[C*n + D];
	int d1 = adj_matrix[A*n + C] + adj_matrix[B*n + D];

	return d0-d1;
}


int Graph::tabu_search(vector<int> &path){
	int best_improve;
	int next_a,next_b;

	vector<vector<int>> tabu_list(n+1, vector<int>(n+1,0));
	
	for (int it = 0; it < MAX_ROUNDS; it++){
		best_improve = INF_NEG;

		for(int i = 0; i < n; i++){
			for(int j = i+2; j < (n + (i==0 ? -1 : i==1 ? 0 : 1 )); j++){
				int improve = opt_2_ver(path,i,j);

				if((improve > best_improve && tabu_list[i][j]<=it)
					|| improve > 0){
					next_a = i;
					next_b = j;
					best_improve = improve;
				}
			}
		}
		
		reverse(path,next_a,next_b-1);

		int tabu = rand() % 10 + 3; 

		tabu_list[next_a][next_b] = it + tabu;
		tabu_list[next_b][next_a] = it + tabu;
	}

	return sum_up(path);
}
