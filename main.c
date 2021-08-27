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

/**
* Breve comentário: temos aqui uma arvore binária. Funciona e seu tempo de busca é em teoria O(log n)
* acontece que a arvore binaria é sensível à ordem de inserção dos dados nela, podendo se desconfigurar
* e com isso perder as vantagens de arvore logo precisamos de uma função que de tempos em tempos faça
* o rebalanceamento da mesma, isso poderia ser evitado se tivessemos funções que balanceassem a arvore a
* cada inserção, mantendo-a sempre nivelada.
* Daí temos a arvore binaria de busca AVL que possui operações para tal objetivo.
* */

/**
 *          Arvore binaria AVL
 *         É um tipo de arvore binária munida de operações que a mantém balanceada na inserção e na
 *      remoção,portanto ela sobrescreve esses metodos.
 *         Para fazer isso ela utiliza 2 funções a mais que são rotaçãoDireita e rotaçãoEsquerda, além de outras
 *      2 funções que são composições dessas 2 rotaçãoDuplaDireita e rotaçãoDuplaEsquerda, além de
 *      possuir um campo a mais em seus nós que é chamado fator de balanço (FB<|1|).
 *         Essa pratica visa evitar o rebalanceamento que é deveras custoso,para fazer isso
 *      os elementos(Folhas) possuem um tipo adicional de dado chamado fator de balanço
 *      que é a diferença de altura do lado esquerdo pro direito e deve ser mantido sempre
 *      entre -1 e +1 no máximo, preferencialmente em 0 (nós com mesma altura).*/


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
