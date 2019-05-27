#include <iostream>
#include <queue>
#include <chrono>
#define KNOTEN_ANZAHL 8
//#define KNOTEN_ANZAHL 6
//#define KANTEN_KAPAZITAETEN_MATRIX {{0, 6, 7, 0, 0, 0},{0, 0, 4, 5, 0, 0},{ 0, 0, 0, 6, 3, 0 },{ 0, 0, 0, 0, 5, 3 },{ 0, 0, 0, 0, 0, 7 },{ 0, 0, 0, 0, 0, 0 }}
#define KANTEN_KAPAZITAETEN_MATRIX {{0, 1, 0, 0, 1, 0, 0, 0},{0, 0, 1, 0, 0, 0, 1, 0},{ 0, 0, 0, 1, 0, 0, 0, 0 },{ 0, 0, 0, 0, 0, 0, 0, 1 },{ 0, 0, 0, 0, 0, 1, 0, 0 },{ 0, 0, 0, 0, 0, 0 ,1 ,0 },{ 0, 0, 0, 0, 0, 0 ,0 ,1 },{ 0, 0, 0, 0, 0, 0 ,0 ,0 }}
using namespace std::chrono;
bool breitensuche(float residualgraph[KNOTEN_ANZAHL][KNOTEN_ANZAHL], float startgraph[KNOTEN_ANZAHL][KNOTEN_ANZAHL] , int s, int t, int vorKnoten[]){ //Ein augmentierender Pfad wird mit Breitensuche gesucht
	bool besucht[KNOTEN_ANZAHL];
	for (int i = 0; i < KNOTEN_ANZAHL; i++){
		besucht[i] = false;
	}
	std::queue <int> qu;
	qu.push(s);
	besucht[s] = true;
	vorKnoten[s] = -1;
	while (!qu.empty()){
		int a = qu.front();
		qu.pop();
		for (int b = 0; b < KNOTEN_ANZAHL; b++){
			if (besucht[b] == false && (residualgraph[a][b] > 0 )){ 
				vorKnoten[b] = a;
				if (b == t) {return true;}
				besucht[b] = true;
				qu.push(b);
			}
		}
	}
	return besucht[t];
}
float edmondsKarp(float graph[KNOTEN_ANZAHL][KNOTEN_ANZAHL], int s, int t){
	int a, b; //Hilfsvariablen, die Knotenindices repräsentieren
	float residualgraph[KNOTEN_ANZAHL][KNOTEN_ANZAHL];
	for (a = 0; a < KNOTEN_ANZAHL; a++){
		for (b = 0; b < KNOTEN_ANZAHL; b++){
			residualgraph[a][b] = graph[a][b];
		}
	}
	int vorKnoten[KNOTEN_ANZAHL];
	float maxFlow = 0;
	while (breitensuche(residualgraph, graph, s, t, vorKnoten)){
		float augFlow = INT_MAX;
		for (b= t; b != s; b = vorKnoten[b]){
			std::cout << b;
			a = vorKnoten[b];
			augFlow = std::min(augFlow, residualgraph[a][b]);
		}
		std::cout << "0 @ " << augFlow << " Flow" << std::endl;
		for (b = t; b != s; b = vorKnoten[b]){
			a = vorKnoten[b];
			residualgraph[a][b] -= augFlow;
			residualgraph[b][a] += augFlow;
		}
		maxFlow += augFlow;
	}
	return maxFlow;
}
int main(){
	auto t1 = std::chrono::high_resolution_clock::now();
	//graph = new float[KNOTEN_ANZAHL][KNOTEN_ANZAHL]; 
	float graph[KNOTEN_ANZAHL][KNOTEN_ANZAHL] = KANTEN_KAPAZITAETEN_MATRIX;
	float ek = edmondsKarp(graph, 0, KNOTEN_ANZAHL-1);
	auto t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> fp_ms = t2 - t1;
	auto int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
	std::chrono::duration<long, std::micro> int_usec = int_ms;
	std::cout << "MaxFlow: " << ek << " in " << fp_ms.count() << " ms, " << std::endl;
}