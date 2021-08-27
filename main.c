#include <stdio.h>
#include <stdlib.h>
#include<locale.h>
#include "ArvoreAVL.h"
#define TRUE 1
#define FALSE 0

//#include "CUnit/Basic.h"

/**
 *        autor: Pedro Henrique Carneiro de Araújo   Matricula: 22108287
 *
 *     Uma arvore binaria é uma estrutura de dados caracterizada de forma recursiva, definida como sendo um conjunto
 *  de nós que possuem 3 informações:
 *      1- O dado armazenado que neste caso será um inteiro;
 *      2-Um ponteiro para uma arvore a esquerda (conjunto de numeros menores que o dado)
 *      3-Um ponteiro para um arvore a direita (conjunto de numeros maiores que o dado)
 *  Na arvore binaria são feitas basicamente 3 operações emergentes (ou seja surgem
 *      do conjunto de Folhas e não delas individualmente) são elas:inserção,remoção e busca definidas por:
 *      1-inserção:Função complexa, ela avalia se o nó raiz esta vazio se -sim insere nele-, se -- não ela deve avaliar
 *      se o dado é maior ou menor que o dado raiz e chamar a função respectiva desse dado--;
 *      2-busca: operação de percorrer a arvore para averiguar se elemento existe, também é rescursiva e
 *      pode ser feito de varias maneiras: em ordem simétrica, pré-ordem (quando visita o nó antes de ir para
 *      o proximo),pós-ordem(visita os nós antes de visitar esse) e em nível;
 *      3-remoção: depende da busca para encontrar elemento e então destruir a folha.
 *
*/



int main()
{
    setlocale(LC_ALL,"ptb");//Traduz os caracteres para portugues.

    int valorAleatorio,total=199;
    FolhaAVL *RaizArvore,**ponteiroParaRaiz;
    RaizArvore=NULL;
    ponteiroParaRaiz=&RaizArvore;
    int aumentou=0;



    for(int i=0;i<total;i++){
        printf("interação:%d\n",i);
        valorAleatorio=rand()%100;
        insereAux(valorAleatorio,ponteiroParaRaiz);
        printf("\n=============================================\n");
    }
    printf("\t\t\t\t<<<Percorre em ordem>>>\n");
    emOrdem(RaizArvore);
    printf("\t\t\t\t<<<Percorre em pós-Ordem>>>\n");
    posOrdem(RaizArvore);
    printf("\t\t\t\t<<<Percorre em pré-Ordem>>>\n");
    preOrdem(RaizArvore);


    return 0;
}
