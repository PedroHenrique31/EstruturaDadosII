#include <stdio.h>
#include <stdlib.h>
#include<locale.h>
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


 /* Tipo estruturado FolhaAVL é uma folha que armazena um inteiro e o fator de balanço
 */
typedef struct FolhaAVL{
    int dado;
    int FatorBalanco;
    struct FolhaAVL *Esq;
    struct FolhaAVL *Dir;
}FolhaAVL;

/*
 * Par funcionar a arvore AVL faz uso de 4 funcoes basicas que a mantém balanceada são elas:
 *      1- rotação a direita;
 *      2-rotação a esquerda;
 *      3-rotação dupla a direita;(operação composta de 2 e 1);
 *      4-rotação dupla a esquerda;(operação composta de 1 e 2).
*/
void rotacao_Direita(FolhaAVL *no){
    printf("\t\trotacao direita\n\tno->dado:%d",no->dado);
    FolhaAVL *q,*temporario;
    q=no->Esq;
    temporario=no->Dir;
    q->Dir=no;
    no->Esq=temporario;
    q->FatorBalanco=0;
    //temporario->FatorBalanco=0;
    no=q;
    printf("\t fim rotacao direita\tno->dado:%d no->esq:%x no->dir:%d\n",no->dado,no->Esq,no->Dir->dado);
}
void rotacao_Esquerda(FolhaAVL *no){
    printf("ROTACAO ESQUERDA COM NO:%x cujo valor eh %d e direita eh %d\n",no,no->dado,no->Dir->dado);
    FolhaAVL *q,*temporario;printf("temporario:%x\n",temporario);
    q=no->Dir;printf("DIREITA de %d é %d e esquerda de 24 é %x e o valor é nulo\n",no->dado,q->dado,q->Esq);
    temporario=q->Esq;printf("esquerda de %d eh %x\n",q->dado,temporario);
    q->Esq=no;
    no->Dir=temporario;
    q->FatorBalanco=0;//printf("q->fb=0\n");printf("temporario:%x valor:\n",temporario,temporario->dado);
    //temporario->FatorBalanco=0;printf("temporario->fb=0\n");
    no=q;printf("no=q\n");
}
void rotacao_Esq_Dir(FolhaAVL *no){
    rotacao_Esquerda(no->Esq);printf("ROTACAo esq\n");printf("\tvai paraROTACAO DIREITA no:%x cujo valor é %d\n",no,no->dado);
    rotacao_Direita(no);printf("ROTACAO DIREITA\n");
}
void rotacao_Dir_Esq(FolhaAVL *no){
    rotacao_Direita(no->Dir);
    rotacao_Esquerda(no);
}
/* Outra funcionalidade extra é a de calcular a altura de um nó para mais tarde calcular o Fator de balanco*/

int alturaDir(FolhaAVL *no){
    return (no==NULL)? 0:1+alturaDir(no->Dir);
}
int alturaEsq(FolhaAVL *no){
    return (no==NULL)? 0:1+alturaEsq(no->Esq);
}
void calculaFatorBalanco(FolhaAVL *no){
    int altDir,altEsq;
    altDir=alturaDir(no);
    altEsq=alturaEsq(no);
    no->FatorBalanco=altDir-altEsq;
}
/* No mais uma arvore AVL é uma arvore binaria e realiza as mesmas operações
 * porém com algumas modificações.
 */

 //criaRegistro: cria e armazena um tipo FolhaAVL a partir de um valor inteiro.
FolhaAVL criaRegistro(int info){
    FolhaAVL novo;
    novo.dado=info;
    novo.FatorBalanco=0;
    novo.Dir=NULL;
    novo.Esq=NULL;

    return novo;
}
//insere: busca uma posição e insere uma nova FolhaAVL a uma subarvore.
//inserir: Cria um novo registro e o insere na arvore.
int inserir(FolhaAVL **pPonteiroParaRaiz,int numero,int *cresceu){
    FolhaAVL *pRaiz=*pPonteiroParaRaiz;
    printf("começou \nnumero a inserir:%d \npRaiz=%x\n",numero,pRaiz);
    if(pRaiz==NULL)
    {
        pRaiz=(FolhaAVL *)malloc(sizeof(FolhaAVL));printf("pRaiz==NULL\n");
        if(pRaiz==NULL)
            return 0;// erro de insercao, não tem memória.
        else
        {
            (pRaiz)->dado=numero;//printf("inserido numero:%d em pRaiz:%x que esta em %x\n",(pRaiz)->dado,pRaiz,&pRaiz);
            (pRaiz)->Dir=NULL;
            (pRaiz)->Esq=NULL;
            (pRaiz)->FatorBalanco=0;
            *pPonteiroParaRaiz=pRaiz;
            *cresceu=TRUE;
            return TRUE;//sucesso inserção
        }
    }else if(numero<=(pRaiz)->dado){
        printf("%d comparado a raiz %d\n",numero,pRaiz->dado);
        //printf("numero menor \n");
        if(inserir(&(pRaiz)->Esq,numero,cresceu)){printf("conseguiu inserir %d cresceu:%d\n",numero,*cresceu);
            if(*cresceu){//caso tenha conseguido inserir a esquerda.
                    printf("AVALIA BALANCO ESQUERDA\n");
                switch((*pRaiz).FatorBalanco){
                    case -1://desbalanceado a esquerda
                        printf("case -1\n");
                        if((pRaiz)->Esq->FatorBalanco==-1){
                            printf("ROTACAO DIREITA\n");rotacao_Direita(pRaiz);
                        }else printf("ROTACAO ESQ DIREITA\n");rotacao_Esq_Dir(pRaiz);//Sinais trocados
                        break;
                    case 0:
                        printf("case 0 FB=-1\n");
                        (pRaiz)->FatorBalanco=-1;
                        *cresceu=TRUE;printf("FATOR BALANCO:0 apenas colocou -1 em Raiz\n");
                        break;
                    case 1://direita maior
                        printf("CASE 1\n");
                        (pRaiz)->FatorBalanco=0;printf("(pRaiz)->info:%d FatorBalanco:%d\n",(pRaiz)->dado,(pRaiz)->FatorBalanco);
                        *cresceu=FALSE;
                        break;
                }//Fimswitch
            }//FimIF(cresceu)
            return TRUE;
        }
        else return FALSE;
    }else{
        printf("%d comparado a raiz %d\n",numero,pRaiz->dado);
        if(inserir(&(pRaiz)->Dir,numero,cresceu)){printf("conseguiu inserir %d cresceu:%d\n",numero,*cresceu);
            if(*cresceu){//inseriu a direita, agora verifica balanco
                    printf("AVALIA BALANCO DIREITA,pRaiz->dado:%d\n",pRaiz->dado);
                switch ((pRaiz)->FatorBalanco){
                    case -1:
                        (pRaiz)->FatorBalanco=0;
                        *cresceu=FALSE;
                        printf("case -1 fb=0\n");
                        break;
                    case 0:
                        (pRaiz)->FatorBalanco=1;*cresceu=TRUE;printf("case 0: acrescenta 1\n");
                        break;
                    case 1:
                        if((pRaiz)->Dir->FatorBalanco==1){
                            rotacao_Esquerda(pRaiz);printf("rodou Esquerda\n");
                        }else rotacao_Dir_Esq(pRaiz);*cresceu=FALSE;
                        break;
                }//FIMSWITCH
            }
            return 1;
        }//FIMIF(insereDireita)
        else return 0;// nao conseguiu inserir
    }
}//FimInsere
/*
 * Existem também as famosas funções recursivas para percorrimento da arvore em diversas ordens
*/
void visita(FolhaAVL *no){
    printf("No: %d\n",no->dado);
}
void emOrdem(FolhaAVL *pNo) {
     if(pNo != NULL) {
         emOrdem(pNo->Esq);
         visita(pNo);
         emOrdem(pNo->Dir);
     }
 }
 void preOrdem(FolhaAVL *pNo){
     if(pNo != NULL){
         visita(pNo);
         preOrdem(pNo->Esq);
         preOrdem(pNo->Dir);
     }
 }
 void posOrdem(FolhaAVL *pNo){
     if(pNo != NULL){
         posOrdem(pNo->Esq);
         posOrdem(pNo->Dir);
         visita(pNo);
     }
 }
int main()
{
    setlocale(LC_ALL,"ptb");//Traduz os caracteres para portugues.

    int valorAleatorio,total=60;
    FolhaAVL *RaizArvore,**ponteiroParaRaiz;
    RaizArvore=NULL;
    ponteiroParaRaiz=&RaizArvore;
    int cresceu=0;
    printf("RaizArvore:%x &RaizArvore:%x ponteiroParaRaiz:%x\n",RaizArvore,&RaizArvore,ponteiroParaRaiz);


    //if(RaizArvore==NULL){printf("comparou (RaizArvore==NULL)\n");}
    for(int i=0;i<total;i++){
        printf("interação:%d\n",i);
        valorAleatorio=rand()%100;
        //printf("inseriu valor: %d\n",valorAleatorio);
        inserir(ponteiroParaRaiz,valorAleatorio,&cresceu);
        printf("\nponteiroParaRaiz:%x RaizArvore:%x RaizArvore->FB:%d\n",ponteiroParaRaiz,RaizArvore,RaizArvore->FatorBalanco);
        printf("\n=============================================\n");
    }
    emOrdem(RaizArvore);

    return 0;
}
