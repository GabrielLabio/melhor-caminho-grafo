#define N 20

typedef struct fila{
    int n;
    int ini;
    vertex vet[N];
}Fila;

Fila *fila_cria() { //QUEUEinit()
	Fila *f=(Fila*)malloc(sizeof(Fila));
	f->n=0;
	f->ini=0; 
	return f;
} 

void fila_insere (Fila *f, vertex v) { //QUEUEput()
	if(f->n==N){
		printf("Capacidade da fila esgotada.\n");
		return; 
    }
	f->vet[f->n]=v;
	f->n++; 
}

void compacta(Fila *f) { 
	for(int i=0; i<f->n; i++) {
		f->vet[i] = f->vet[i+1];
	}
	(f->n)--;
}

vertex fila_retira(Fila *f) { //QUEUEget()
	vertex v;
    
	v = f->vet[0]; 
	compacta(f); 
	
	return v;
}

int fila_vazia(Fila *f) { //QUEUEempty()
	if(f->n==f->ini) 
		return 1;
	else 
		return 0; 
}
	  
void fila_libera(Fila *f) { //QUEUEfree()
	free(f);
} 
  
  
  
  
  
                          
void mostra_fila(Fila *f){
     printf("Conteudo da fila\n");
     int i;
     for(i=f->ini;i<f->n;i++)
        printf("%d\n",f->vet[i]);
     printf("\n");
} 








