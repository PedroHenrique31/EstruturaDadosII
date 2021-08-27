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


 /* Tipo estruturado FolhaAVL é uma folha que armazena um inteiro e o fator de balanço
 */
/*typedef struct FolhaAVL{
    int dado;
    int FatorBalanco;
    struct FolhaAVL *Esq;
    struct FolhaAVL *Dir;
}FolhaAVL;
*/

/*
 * Par funcionar a arvore AVL faz uso de 4 funcoes basicas que a mantém balanceada são elas:
 *      1- rotação a direita;
 *      2-rotação a esquerda;
 *      3-rotação dupla a direita;(operação composta de 2 e 1);
 *      4-rotação dupla a esquerda;(operação composta de 1 e 2).
*/
FolhaAVL* rotacao_Direita(FolhaAVL *no){

    printf("\t\tROTACAO DIREITA\n\t");
    printf("no->dado:%d no.dir: %x no.esq:%x\n",no->dado,no->Dir,no->Esq);
    FolhaAVL *q,*temporario;
    temporario=no;//copia o valor de no para mexer nele
    q=no->Esq;printf("q=%x\n",q);//q aponta para esquerda de nó isso pode ser uma região vazia ué
    if(q==NULL){temporario->Esq=NULL;printf("tmp->esq=%x\n",temporario->Esq);}
    else{temporario->Esq=q->Dir;}// esquerda de nó aponta para direita de q (pois o valor no>q.DIR>q)
    if(q!=NULL){
        q->Dir=temporario;//direita de q aponta para no (pois valor no>q)
        q->FatorBalanco=0;//zera o FB de q
        temporario->FatorBalanco=0;//zera o fb de no
        no=q;//troca no de lugar para q
        printf("no=%x\n",no);
    }else{
        printf("q é nulo\n");
        no=temporario;
    }
    printf("no=%d no.esq:%x no.dir:%x no.dir.dado:%d\n",no->dado,no->Esq,no->Dir,no->Dir->dado);
    return no;
}
void rotacao_Esquerda(FolhaAVL **no){
    FolhaAVL *a,*b;
    a=*no;//salva o valor de no
    b=a->Dir;//b aponta para direita de no (logo valor b>no)
    a->Dir=b->Esq;//no aponta para esquerda de b (pois valor b->esq<b>no)
    b->Esq=a;//esquerda de b aponta no (pois b->esq<b>no)
    a->FatorBalanco=0;
    b->FatorBalanco=0;
    *no=b;//troca no de lugar para b
}
FolhaAVL* rotacao_Esq_Dir(FolhaAVL *no){
    printf("\t\t\t\t <<<< ROTACAO ESQUERDA-DIREITA >>>>\n");
    int FatorBalancoNo=no->FatorBalanco;
    rotacao_Esquerda(&no->Esq);
    no=rotacao_Direita(no);

    FolhaAVL *a=no->Esq,*b=no->Dir;
    switch(FatorBalancoNo){
        case -1:
            a->FatorBalanco=0;b->FatorBalanco=1;break;
        case 0:
            a->FatorBalanco=0;b->FatorBalanco=0;break;
        case 1:
            a->FatorBalanco=-1;b->FatorBalanco=0;break;
    }
    //no->FatorBalanco=0;//ja foi iterado
    printf("no->FB antes:%d depois:%d\n\tno.esq.dado:%d no.esq.fatorbalanço:%d\n",no->FatorBalanco,FatorBalancoNo,no->Esq->dado,no->Esq->FatorBalanco);
    return no;
}
void rotacao_Dir_Esq(FolhaAVL **no){//essa função retorna void por isso devo passar um **no para trabalhar mas como nao foi chamada...
    printf("\t\t\t\t <<<< Rotação Direita-Esquerda >>>>\n");
    FolhaAVL *noAtual=*no;
    int FatorBalancoNo=noAtual->FatorBalanco;
    noAtual->Dir=rotacao_Direita(noAtual->Dir);
    rotacao_Esquerda(&noAtual);

    FolhaAVL *a=noAtual->Esq,*b=noAtual->Dir;
    switch(FatorBalancoNo){
        case -1:
            a->FatorBalanco=0;b->FatorBalanco=1;break;
        case 0:
            a->FatorBalanco=0;b->FatorBalanco=0;break;
        case 1:
            a->FatorBalanco=-1;b->FatorBalanco=0;break;
    }
    //no->FatorBalanco=0;//ja iterado
    *no=noAtual;
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
FolhaAVL* inserir(FolhaAVL **pPonteiroParaRaiz,int numero,int *cresceu){
    FolhaAVL *pRaiz=*pPonteiroParaRaiz;

    if(pRaiz==NULL)
    {
        pRaiz=(FolhaAVL *)malloc(sizeof(FolhaAVL));
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
            printf("inseriu na raiz:%d\n",numero);
            return pRaiz;//sucesso inserção
        }
    }else if(numero<=(pRaiz)->dado){

        //printf("numero menor \n");
        if(pRaiz->Esq=inserir(&(pRaiz)->Esq,numero,cresceu)){
            if(*cresceu){//caso tenha conseguido inserir a esquerda.
                    printf("AVALIA BALANCO ESQUERDA,no->dado:%d\n",pRaiz->dado);
                switch((*pRaiz).FatorBalanco){
                    case -1://desbalanceado a esquerda

                        if((pRaiz)->Esq->FatorBalanco==-1){
                            pRaiz=rotacao_Direita(pRaiz);
                        }else{pRaiz=rotacao_Esq_Dir(pRaiz);}//Sinais trocados
                        *cresceu=FALSE;
                        break;
                    case 0:
                        (pRaiz)->FatorBalanco=-1;
                        *cresceu=TRUE;
                        break;
                    case 1://direita maior

                        (pRaiz)->FatorBalanco=0;
                        *cresceu=FALSE;
                        break;
                }//Fimswitch
            }//FimIF(cresceu)
            return pRaiz;
        }
        else return FALSE;
    }else{
        FolhaAVL *Direita=pRaiz->Dir;

        if(pRaiz->Dir=inserir(&(pRaiz)->Dir,numero,cresceu)){
            if(*cresceu){//inseriu a direita, agora verifica balanco
                    printf("AVALIA BALANCO DIREITA,pRaiz->dado:%d\n",pRaiz->dado);
                switch ((pRaiz)->FatorBalanco){
                    case -1:
                        (pRaiz)->FatorBalanco=0;
                        *cresceu=FALSE;
                        break;
                    case 0:
                        (pRaiz)->FatorBalanco=1;*cresceu=TRUE;
                        break;
                    case 1:
                        if((pRaiz)->Dir->FatorBalanco==1){
                            rotacao_Esquerda(&pRaiz);*cresceu=TRUE;
                        }else rotacao_Dir_Esq(&pRaiz);*cresceu=FALSE;
                        break;
                }//FIMSWITCH
            }
            return pRaiz;
        }//FIMIF(insereDireita)
        else return FALSE;// nao conseguiu inserir
    }
}//FimInsere
void insereAux(int info,FolhaAVL **pontRaiz){
    int Aumentou=0;
    inserir(pontRaiz,info,&Aumentou);
    percorreCalculandoFB(*pontRaiz);
}
void percorreCalculandoFB(FolhaAVL *pNo){
    if(pNo != NULL) {
         percorreCalculandoFB(pNo->Esq);
         calculaFatorBalanco(pNo);
         percorreCalculandoFB(pNo->Dir);
     }
}
/*
 * Existem também as famosas funções recursivas para percorrimento da arvore em diversas ordens
*/
void visita(FolhaAVL *no){
    if(no->Dir!=NULL && no->Esq!=NULL){
        printf("No: %d No.FatorBalanco: %d No.esq: %d No.dir: %d &No: %x\n",no->dado,no->FatorBalanco,no->Esq->dado,no->Dir->dado,
               no);
    }else{
        printf("No: %d &No:%x No.FatorBalanco: %d um destes é nulo No.esq:%x No.dir:%x\n",no->dado,no,no->FatorBalanco,no->Esq,no->Dir);
    }
    calculaFatorBalanco(no);
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
