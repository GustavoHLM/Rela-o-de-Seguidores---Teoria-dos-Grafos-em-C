/*Gustavo Henrique Mendonca
BCC3�

Trabalho ED
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>

// Estrutura de Dados Fila Dinâmica
typedef struct TipoCelula *TipoApontador;

typedef struct TipoItem {
    char placa[10];
    int deslocamento;
	int prioridade;
	int Estacionado;//1=sim, 0=não
} TipoItem;

typedef struct TipoCelula {
	TipoItem Item;
	TipoApontador Prox;
} TipoCelula;

typedef struct TipoFila {
	TipoApontador Frente, Tras;
}TipoFila;

// Funções de manipulação da Fila Dinâmica
void FFVazia(TipoFila *Fila ) {
	Fila ->Frente = (TipoApontador) malloc(sizeof(TipoCelula ));
	Fila ->Tras = Fila ->Frente;
	Fila ->Frente ->Prox = NULL;
}

int Vazia(TipoFila Fila ) {
	return ( Fila.Frente == Fila.Tras) ;
}

void Enfileira (TipoItem x, TipoFila *Fila ) {
	Fila ->Tras ->Prox = (TipoApontador) malloc(sizeof(TipoCelula ));
	Fila ->Tras = Fila ->Tras ->Prox;
	Fila ->Tras ->Item = x;
	Fila ->Tras ->Prox = NULL;
}

void Desenfileira(TipoFila *Fila , TipoItem *Item) {
	TipoApontador q;
	if (Vazia( *Fila ) ) {
		printf ( "Erro fila esta vazia\n" ) ; return;
	}
	q = Fila ->Frente;
	Fila ->Frente = Fila ->Frente ->Prox;
	*Item = Fila ->Frente ->Item;
	free(q);
}

void exibe (TipoFila fila){
    int i=1;
	TipoApontador aux=fila.Frente->Prox;
	while(aux!=NULL){
		printf("\nOrdem: %i, placa: %s\tprioridade: %i\tDeslocamento: %i",i,  aux->Item.placa, aux->Item.prioridade, aux->Item.deslocamento);
		if(aux->Item.Estacionado==1){
            printf("\tEstacionado");
		}else{
		printf("\tNa fila");
		}
		i++;
		aux=aux->Prox;
	}
}

////Funções
void prioridade(TipoFila *fila){///// Ajusta a prioridade da fila 
	TipoFila aux; FFVazia(&aux);
	TipoApontador p=fila->Frente->Prox;
	
	while(p!=NULL){
		if(p->Item.Estacionado==1){
			Enfileira(p->Item, &aux);
		}
		p=p->Prox;
	}
	p=fila->Frente->Prox;
	while(p!=NULL){
		if(p->Item.Estacionado==0){
			if(p->Item.prioridade==1){
				Enfileira(p->Item, &aux);
			}
		}
		p=p->Prox;
	}
	p=fila->Frente->Prox;
	while(p!=NULL){
		if(p->Item.Estacionado==0){
			if(p->Item.prioridade==0){
				Enfileira(p->Item, &aux);
			}
		}
		p=p->Prox;
	}
	
	p=aux.Frente->Prox;FFVazia(fila);////Ir� manter os 0 em ordem porem os com prioridade 1 ficam acima.
	while(p!=NULL){
		Enfileira(p->Item, fila);
		p=p->Prox;
	}
	
}

void FILADECARROS(TipoFila *fila, TipoItem x){//// Adiciona os Carros
    TipoApontador p=fila->Frente->Prox;
    int cont=0;
    while(p!=NULL){
        cont++;
        p=p->Prox;
    }
     if(cont<5){
        x.Estacionado=1;
         Enfileira(x, fila);
    }else{
        x.Estacionado=0;
         Enfileira(x, fila);
         printf("\n\n\t\t****Nao ha vaga para o carro, ele se encontra na fila****\n\n");
    }
    prioridade(fila);/// Vai manter a ordem do prioridade 0 por�m quem tiver prioridade 1 vai para cima
}

void somaDeslocamento(TipoFila *fila){/// Soma o deslocamento dos outros carros de dentro do estacionamento
	int i=0;
	TipoApontador p=fila->Frente->Prox;
	while(p!=NULL){
		if(i<5){
			p->Item.deslocamento=p->Item.deslocamento+1;
			p->Item.Estacionado=1;
		}
		i++;
		p=p->Prox;
	}
	
}

void CarroSai(TipoFila *fila){
    TipoItem x;
    if(!Vazia(*fila)){
    	somaDeslocamento(fila);
    	Desenfileira(fila, &x);
    	printf("O carro com a placa %s, se deslocou %i vezes dentro do estacionamento incluindo sua saida....",x.placa, x.deslocamento);
	}  
}


main(){
	TipoFila fila;
	FFVazia(&fila);
	TipoItem item;
	int perg, aux;

	do{
        system("cls");
        printf("\n1-Chegar carro no estacionamento(prioriadade 1)");
        printf("\n2-Chegar carro no estacionamento(prioridade 0)");
        printf("\n2-Remover carro do estacionamento");
        printf("\n3-Printar estado da fila e estacionamento\nComando:");
        scanf("%i", &perg);


        srand( time( NULL ) );
        if(perg==1){
        	item.prioridade=1;
            sprintf(item.placa, "%d", rand()+rand());/// Gerar placas com numeros aleatorios(somei dois para aumetar o numero de casas)
           	FILADECARROS(&fila, item);

            printf("\nExibindo a fila\n");
            exibe(fila);
            printf("\n\n");
            system("pause");
        }
        if(perg==2){
            item.prioridade=0;
            sprintf(item.placa, "%d", rand()+rand());/// Gerar placas com numeros aleatorios(somei dois para aumetar o numero de casas)
           	FILADECARROS(&fila, item);

            printf("\nExibindo a fila\n");
            exibe(fila);
            printf("\n\n");
            system("pause");
        }
        if(perg==3){
            if(!Vazia(fila)){
				printf("\nSaiu o primeiro carro\n");
			}else{
				printf("\nNao tem carros\n");
			}
            CarroSai(&fila);
            exibe(fila);

            printf("\n\n");
            system("pause");

        }
        if(perg==4){
    		if(!Vazia(fila)){
    			printf("\nExibindo a fila\n");
			}else{
				printf("\nNao tem carros\n");
			}
            exibe(fila);
            printf("\n\n");
            system("pause");
        }    
    
	}while(perg!=0);
}
