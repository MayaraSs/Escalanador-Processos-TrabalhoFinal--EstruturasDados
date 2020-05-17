/*
Estruturas de Dados I - ARA 7125
Segundo Ep

*/


#include <stdio.h>
#include <stdlib.h>
#include <String.h>
#define MAX 400


struct proc_ {
  char nome [4];
  int prioridade;
  int tempo;
};


typedef struct proc_ processo;

processo remove_max (processo v[], int *n);
void Insere_na_Fila (processo *v, int *n, processo c);

int main () {
  processo fp[MAX];
  processo v [MAX];
  processo aux;

  int n, ti, j, i, npti, np=0;
  /**
  * n       -  N DE PROCESSOS
  * TI      -  TEMPO INICIO
  * NTPI    -  N DE PROCESSOS NO TEMPO I
  * J       -  INDICE
  **/


  ti = 1;

  printf ("\n----------------------------------------------");
  printf ("\n- ESCALANADOR DE PROCESSOS SIMPLIFICADOS 1.0 -");
  printf ("\n----------------------------------------------\n\n");
   printf ("\n n: numero de linhas, npti: numero de processos por linha\n\n");
   printf ("\n Ordem de entrada:\n\n -> n, npti, nome processo(s), prioridade(s) e tempo(s) \n\n");
  printf("\n n: ");
  scanf ("%d", &n);


  while (ti <= n) {

    printf("\n");
    printf("\n npti: ");
    scanf ("%d", &npti);


    printf("\n");

    /**Inicio da leitura de processos da linja**/
    for (j = 0; j < npti; j++){

        scanf (" %s", v[j].nome);
        /*Tratamento para evitar a existencia de processos com mesmo nome na FP*/
        for ( i = 0; i < np; i++) {
            while ( strcmp (v[j].nome, fp[i].nome) == 0){
                printf("\n -> Processo ja existente, por favor insira outro nome! \n");
                scanf (" %s", v[j].nome);
            }
        }
        /*Tratamento para evitar a existencia de processos com mesmo nome antes de serem inseridos na FP*/
        for ( i = 0; i < j; i++) {
            while ( strcmp (v[j].nome, v[i].nome) == 0){
                printf("\n -> Processo ja existente, por favor insira outro nome! \n");
                scanf (" %s", v[j].nome);
            }
        }


    }
    printf("\n");
    for (j = 0; j < npti; j++) {
        scanf (" %d", &(v[j].prioridade));
    }
    printf("\n");
    for (j = 0; j < npti; j++) {
        scanf (" %d", &(v[j].tempo));
    }
    printf("\n");

    /*incluir os processos lidos na FP*/
    for (j = 0; j < npti; j++) {
        Insere_na_Fila (fp, &np, v[j]);
    }
    /**Fim da leitura de processos da linja**/


    /*remove o processo com maior prioridade da FP e atribui o mesmo a aux*/
    aux = remove_max(fp, &np);
    printf("\n -> processo escolhido = [%s] ", aux.nome);




    /* Verifia se o processo necessita ser inserido novamente na FP, caso seu tempo for mair que 50ms **/
    if(aux.tempo > 50){
        aux.tempo = aux.tempo - 50;
        printf("\n -> interrompido!");
        printf("\n -> inserido novamente na FP!");
        Insere_na_Fila (fp, &np, aux);
    }   else{
            printf("\n -> processamento ok!");
        }
    ti++;

  }

  /* Processos que sobraram na heap que não foram processados*/

    printf ("\n\n HEAP FINAL:: \n\n");
    printf(" np = %i \n\n", np);
    for (j = 1; j <= np; j++) {
        printf("\n -> Processo: ");
        printf (" %s, ", fp[j].nome);
        printf (" prio: %d, ", (fp[j].prioridade));
        printf (" temp: %d. ", (fp[j].tempo));
    }
    printf ("\n");



  return 0;
}

/*Corrige(atualiza posicões) a max heap por cima*/
void fix_up( processo *fp, int n) {
    int i = n;

    processo aux;

    while ((i>=2) && (fp[i/2].prioridade < fp[i].prioridade)) {
        aux = fp[i];
        fp[i] = fp[i/2];
        fp[i/2] = aux;
        i = i / 2;
    }

}

/*Corrige(atualiza posicões) a max heap por baixo*/
void fix_down ( processo *fp, int n, int i ) {
	processo aux;
	int f,j;
	j = i;
	while ( 2*j <= n ) {
		f = 2 * j;
		if ((f < n) && (fp[f].prioridade < fp[f+1].prioridade)) {
			f = f + 1;
		}

		if (fp[j].prioridade >= fp[f].prioridade) {
			j = n;

		} else {
			aux = fp[j];
			fp[j] = fp[f];
			fp[f] = aux;
			j = f;
		}


	}


}


/*Insere um unico elemento na FP (Fila de prioridade)*/
void Insere_na_Fila (processo *fp, int *n, processo c) {
    fp[*n+1] = c;
    fix_up (fp, *n+1);
    *n = *n + 1;
}


/*Remove e retorna o processo com maior prioridade da FP*/
processo remove_max (processo *fp, int *n) {

	processo maxi = fp[1];
	fp[1] = fp[*n];
	*n = *n - 1;
	fix_down(fp, *n, 1);

	return maxi;
}

