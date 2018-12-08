#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#define vertex int
#include "fila.h"
#include <math.h>
#include <locale.h>

struct graph {
   int V; 
   int A; 
   int **adj; 
   char **grf;
};
typedef struct graph Graph;

static int **MATRIXint(int r, char val) {
 
   int **m = (int **)malloc(r * sizeof (int*));
   
   int c=1;
   for (vertex i = 0; i < r; ++i) { 
   		m[i] = (int*)malloc(c * sizeof(int));
		c++;
	}
	
	c=1;
	for (vertex i = 0; i < r; ++i) {
		for (vertex j = 0; j < c; ++j) {
			m[i][j] = val;
		}
        c++;
	}
	return m;
}

static char **MATRIXGRFinit(int v) {
	
	int rAux = (v==1) ? 1 : 2;
	int cAux = (v%2==0) ? v/2 : (v+1)/2;
	
	int r = rAux + (rAux-1);
	int c = cAux + (cAux-1);
	
	int aASCII = 97;
	
	char **m = (char **)malloc(r * sizeof (char*));
	
	for (int i = 0; i < r; ++i) { 
   		m[i] = (char*)malloc(c * sizeof(char));
	}
	
	for (int i = 0; i < r; ++i) {	
		if(i%2==0) {
			for(int j=0; j<c; j++) {
				if(j%2==0 && v>0) {
					m[i][j]=aASCII;
					aASCII++;
					v--;
				}
				else
					m[i][j]=' ';
			}
		}
		else {
			for(int j=0; j<c; j++) {
				m[i][j]=' ';
			}
		}
		
	}
	return m;
}

Graph *GRAPHinit(int V) { 
   Graph *G = (Graph*)malloc(sizeof(Graph));
   G->V = V; 
   G->A = 0;
   G->adj = MATRIXint(V, '0');
   G->grf = MATRIXGRFinit(V);
   return G;
}

bool posGrafo(Graph *G, char v1, int *a, int *b) {
	int v = G->V;
	
	int rAux = (v==1) ? 1 : 2;
	int cAux = (v%2==0) ? v/2 : (v+1)/2;
	
	int r = rAux + (rAux-1);
	int c = cAux + (cAux-1);
	
	for (int i = 0; i < r; ++i) {	
		for (int j = 0; j < c; ++j) {
		
			if(G->grf[i][j] == v1) {
				*a = i;
				*b = j;
				
				return true;
			}
		}
	}
	return false;
}

void GRAPHinsertEdg(Graph *G, char v1, char v2) { 

	int v1Int=v1-97;
	int v2Int=v2-97;
	
	int v1i, v1j;
	
	int v = G->V;	
	int rAux = (v==1) ? 1 : 2;
	int cAux = (v%2==0) ? v/2 : (v+1)/2;
	int lin = rAux + (rAux-1);
	int col = cAux + (cAux-1);
	
	bool conectar=false;
	char pesoAresta; 
	char arestaVisual; //para mostrar a aresta visualmente no grafo
	int incArI, incArJ; 
	
	if(v1Int < v2Int) {
		int aux = v1Int;
		v1Int = v2Int;
		v2Int = aux;		
	}
	
	if(v1==v2) {
		printf("NAO HÁ COMO CONECTAR UM VÉRTICE A SI MESMO.\n");
		return;
	}
	
	if (v1Int<G->V && v2Int<G->V && G->adj[v1Int][v2Int] != '0') {
		printf("ARESTA JÁ EXISTE.\n");
		return;
	}
	
	if(posGrafo(G, v1, &v1i, &v1j)) {
		
		for(int i = v1i-2; i < v1i+3; i++) { //percorrendo arredores de v1, uma vez encontrado na matriz de vértices
				
			for(int j = v1j-2; j < v1j+3; j++) { //percorrendo arredores de v1, uma vez encontrado na matriz de vértices
				
				if(!(i<0 || j<0 || i>=lin || j>=col)) {
					
					if(G->grf[i][j] == v2) { //caso alguém ao redor de v1 seja v2
										
						conectar=true;
						
						if(i!=v1i && j!=v1j) { //determinando peso da aresta
							pesoAresta='r';
							
							if((i<v1i && j<v1j) || (i>v1i && j>v1j)) { //determinando posicao da aresta no grafo em relação a v1
								
								arestaVisual='\\';
								
								if(i<v1i && j<v1j) {
								
									incArI=-1;
									incArJ=-1;
								}
								else {
								
									incArI=1;
									incArJ=1;
								}
								
							}
							else {
								
								arestaVisual='/';
								
								if(i<v1i && j>v1j) {
								
									incArI=-1;
									incArJ=1;
								}
								else {
								
									incArI=1;
									incArJ=-1;
								}	
							}
						}
						else {
							pesoAresta='1';
							
							if(i==v1i) { //determinando posicao da aresta no grafo em relação a v1
								arestaVisual='-';
								incArI=0;
								
								if(j<v1j)
									incArJ=-1;
								else
									incArJ=1;
							}
							else {
								arestaVisual='|';
								incArJ=0;
								
								if(i<v1i)
									incArI=-1;
								else
									incArI=1;
							}
						}
						
						G->adj[v1Int][v2Int] = pesoAresta; 
						G->A++;
						
						if(G->grf[v1i + incArI][v1j + incArJ] != ' ')
							G->grf[v1i + incArI][v1j + incArJ] = 'X';	 
						else
							G->grf[v1i + incArI][v1j + incArJ] = arestaVisual; 
						
					}
				}	
			}
		}
			
		if(!conectar) {
			printf("VÉRTICE %c NÃO EXISTE OU NÃO É ADJACENTE A %c.\n", v2, v1);
		}
			
	}
	else {
		printf("VÉRTICE %c NÁO ENCONTRADO NO GRAFO.\n", v1);
	}	
}

void GRAPHshowAdj(Graph *G) { 

	int c = 1;
	
	printf("Matriz de adjacências (NOTA: r = raiz quadrada de 2):\n");
	
	printf("%2c", ' ');
	for (vertex v = 0; v < G->V; ++v) 
		printf(" %2c", v+97);
	printf("\n");
	
	for (vertex v = 0; v < G->V; ++v) {
		printf("%2c", v+97);
		
		for (vertex w = 0; w < c; ++w)
			printf(" %2c", G->adj[v][w]);
		printf("\n");
		c++;
	}
	printf("\n");
}

void GRAPHshowGrf(Graph *G) { 

	int v = G->V;
	
	int rAux = (v==1) ? 1 : 2;
	int cAux = (v%2==0) ? v/2 : (v+1)/2;
	
	int r = rAux + (rAux-1);
	int c = cAux + (cAux-1);
	
	printf("Grafo:\n");
	
	for (int i = 0; i < r; ++i) {	
		for (int j = 0; j < c; ++j)
			printf(" %2c", G->grf[i][j]);
		printf("\n");
	}
	printf("\n");
}

int numeroVertices() {
	int v=0;
	
	printf("Digite a quantidade de vértices no grafo (1 a 20): ");
	scanf("%d", &v);
	
	while(v<1 || v>20) {
		printf("Número de vértices fora da faixa.\nDigite a quantidade de vértices no grafo (1 a 20): ");
		scanf("%d", &v);
	}	
	return v;
}

void GRAPHminPaths(Graph *G, vertex s, double *dist, vertex *pa) { 

	int infinity = (G->V)*2; //devido ao fato da aresta valer 1 ou 'raiz de 2', a distância total de um vértice até outro nunca será maior do que o número total de arestas vezes 2
   
	for (vertex v = 0; v < G->V; ++v) {
		pa[v] = -1;
		dist[v] = infinity;
	}
		
	Fila *fila = fila_cria(); //QUEUEinit(G->V);
	
	dist[s] = 0;
	pa[s] = s;
	
	fila_insere (fila, s); //QUEUEput(s); 
	
	while (!fila_vazia(fila)) { //QUEUEempty()
		
		vertex v = fila_retira(fila); // QUEUEget( ); 
		
		int c=1;
		for (vertex i=0; i<G->V; i++) {
			for (vertex j=0; j<c; j++) {
				
				if(i==v || j==v) {
					
					if(G->adj[i][j] != '0') {
						
						vertex w;
						if(i==v) {
							w = j;
						}
						else {
							w = i;
						}
				
						if (pa[w] == -1) { 
						
							pa[w] = v;
							
							if(G->adj[i][j] == '1')
								dist[w] = dist[v] + 1;
							else if (G->adj[i][j] == 'r')
								dist[w] = dist[v] + sqrt(2.0);
								
							fila_insere (fila, w); //QUEUEput(w); 
						}
					}
				}
			}
			c++;
		}
	}
	
	fila_libera(fila); //QUEUEfree(); 
}


int main() {
	
	setlocale(LC_ALL,"portuguese");
	char resp;
	do {
		system("CLS");
		int numV = numeroVertices();
		Graph *grafo = GRAPHinit(numV);	
		char v1, v2;
		int x1, y1, x2, y2, dm;
				
		printf("Matriz de adjacências e grafo inicializados:\n\n");
		GRAPHshowAdj(grafo);
		GRAPHshowGrf(grafo);
		
		resp='c';
		while(resp=='c') {	
			printf("Insira as letras de dois vértices que deseja conectar, separadas por um espaco: ");
			fflush(stdin);
			scanf("%c %c", &v1, &v2);
			
			system("CLS");
			
			GRAPHinsertEdg(grafo, v1, v2);
	
			GRAPHshowAdj(grafo);
			GRAPHshowGrf(grafo);
			
			printf("\n\nDeseja Continuar adicionando arestas, Parar ou Resetar?(c/p/r): ");
			fflush(stdin);
			scanf("%c", &resp);
			
			if(resp=='r') {
				
				system("CLS");
				
				printf("Grafo resetado com sucesso!\n");
				
				grafo = GRAPHinit(numV);
				GRAPHshowAdj(grafo);
				GRAPHshowGrf(grafo);
				
				printf("Deseja Continuar adicionando arestas ou Parar?(c/p): ");
				fflush(stdin);
				scanf("%c", &resp);
			}
		}
		
		do {
			printf("Insira as letras dos vértices inicial e final respectivamente, separadas por um espaço: ");
			fflush(stdin);
			scanf("%c %c", &v1, &v2);
			
			if(posGrafo(grafo, v1, &y1, &x1) && posGrafo(grafo, v2, &y2, &x2)) {
				dm = abs(x1 - x2)/2 + abs(y1 - y2)/2; //tem que dividir por dois pois a matriz do grafo também é constituída pelos caracteres que representam as arestas
				printf("A Distância Manhattan entre %c e %c é: %d\n", v1, v2, dm);
				
				double dist[grafo->V];
				vertex pa[grafo->V];
				vertex s = v1-97;
				vertex w = v2-97;
				GRAPHminPaths(grafo, s, dist, pa);
				
				if(pa[w] != -1) {
					vertex aux[grafo->V];
					aux[0] = w;
					int cont = 1;
					vertex a = w;
					while(pa[a] != a) {
						aux[cont] = pa[a];
						a = pa[a];
						cont++;
					}
					
					printf("Caminho percorrido para chegar de %c a %c (algoritmo: BFS):\n", v1, v2);
					for(vertex i = cont-1; i>=0; i--){
						if(cont==1) {
							printf("%c\n", aux[i]+97);
							break;
						}
						else{
							printf("%c -> ", aux[i]+97);
							cont--;
						}
					}
					
					printf("Distância efetivamente percorrida: %f\n", dist[w]);
				}
				else {
					printf("%c e %c não estão conectados.\n", v1, v2);
				}
			}
			else {
				printf("Um ou mais vértices não existem.");
			}
			
			printf("Deseja encontrar o caminho entre outros vértices?(s/n): ");
			fflush(stdin);
			scanf("%c", &resp);
		}while (resp == 's');
		
		printf("Deseja recomeçar um novo grafo?(s/n): ");
		fflush(stdin);
		scanf("%c", &resp);
	}while(resp == 's');	
}















