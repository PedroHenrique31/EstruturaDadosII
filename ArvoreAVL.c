#include <stdio.h>
#include <stdlib.h>
#include<locale.h>

#include "ArvoreAVL.h"

#define LimEsq -2
#define LimDir 2

//#include "CUnit/Basic.h"


/**
* Breve comentário: temos aqui uma arvore binária. Funciona e seu tempo de busca é em teoria O(log n)
* acontece que a arvore binaria é sensível à ordem de inserção dos dados nela, podendo se desconfigurar
* e com isso perder as vantagens de arvore logo precisamos de uma função que de tempos em tempos faça
* o rebalanceamento da mesma, isso poderia ser evitado se tivessemos funções que balanceassem a arvore a
* cada inserção, mantendo-a sempre nivelada.
* Daí temos a arvore binaria de busca AVL que possui operações para tal objetivo.
* */

/**
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
        q->FatorBalanco=BALANCEADO;//zera o FB de q
        temporario->FatorBalanco=BALANCEADO;//zera o fb de no
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
    a->FatorBalanco=BALANCEADO;
    b->FatorBalanco=BALANCEADO;
    *no=b;//troca no de lugar para b
}
FolhaAVL* rotacao_Esq_Dir(FolhaAVL *no){
    printf("\t\t\t\t <<<< ROTACAO ESQUERDA-DIREITA >>>>\n");

    int FatorBalancoNo=no->FatorBalanco;
    if(no->dado!=no->Esq->dado){
        rotacao_Esquerda(&no->Esq);
        no=rotacao_Direita(no);
    }

    FolhaAVL *a=no->Esq,*b=no->Dir;
    switch(FatorBalancoNo){
        case DESB_ESQUERDA:
            a->FatorBalanco=BALANCEADO;b->FatorBalanco=DESB_DIREITA;break;
        case BALANCEADO:
            a->FatorBalanco=BALANCEADO;b->FatorBalanco=BALANCEADO;break;
        case DESB_DIREITA:
            a->FatorBalanco=DESB_ESQUERDA;b->FatorBalanco=BALANCEADO;break;
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
        case DESB_ESQUERDA:
            a->FatorBalanco=BALANCEADO;b->FatorBalanco=DESB_DIREITA;break;
        case BALANCEADO:
            a->FatorBalanco=BALANCEADO;b->FatorBalanco=BALANCEADO;break;
        case DESB_DIREITA:
            a->FatorBalanco=DESB_ESQUERDA;b->FatorBalanco=BALANCEADO;break;
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
    novo.FatorBalanco=BALANCEADO;
    novo.Dir=NULL;
    novo.Esq=NULL;

    return novo;
}
//insere: busca uma posição e insere uma nova FolhaAVL a uma subarvore.
//inserir: Cria um novo registro e o insere na arvore.
FolhaAVL* inserir(FolhaAVL **pPonteiroParaRaiz,int numero,int *cresceu){
    FolhaAVL *pRaiz=*pPonteiroParaRaiz;

    if(pRaiz==NULL)//ARVORE VAZIA
    {
        pRaiz=(FolhaAVL *)malloc(sizeof(FolhaAVL));
        if(pRaiz==NULL)
            return 0;// erro de insercao, não tem memória.
        else
        {
            (pRaiz)->dado=numero;//printf("inserido numero:%d em pRaiz:%x que esta em %x\n",(pRaiz)->dado,pRaiz,&pRaiz);
            (pRaiz)->Dir=NULL;
            (pRaiz)->Esq=NULL;
            (pRaiz)->FatorBalanco=BALANCEADO;
            *pPonteiroParaRaiz=pRaiz;
            *cresceu=TRUE;
            printf("inseriu na raiz:%d\n",numero);
            return pRaiz;//sucesso inserção
        }
    }else //if(numero==(pRaiz)->dado){return 0;}

    if(numero<(pRaiz)->dado){

        //printf("numero menor \n");
        if(pRaiz->Esq=inserir(&(pRaiz)->Esq,numero,cresceu)){
            if(*cresceu){//caso tenha conseguido inserir a esquerda.
                    printf("AVALIA BALANCO ESQUERDA,no->dado:%d no.FatorBalanco:%d esq:%x dir:%x\n",pRaiz->dado,
                           pRaiz->FatorBalanco,pRaiz->Esq,pRaiz->Dir);
                           if(pRaiz->FatorBalanco==-2||pRaiz->FatorBalanco==2){
                                printf("\t\t FB==|2|\n");
                                calculaFatorBalanco(pRaiz);
                                preOrdem(pRaiz);
                           }

                           /*if(pRaiz->Esq!=NULL){printf("pRaiz->Esq:%d\n",pRaiz->Esq->dado);
                                if(pRaiz->Dir!=NULL){printf("pRaiz->Dir:%d\n",pRaiz->Dir->dado);}
                           }*/
                switch((*pRaiz).FatorBalanco){
                    case DESB_ESQUERDA://desbalanceado a esquerda

                        if((pRaiz)->Esq->FatorBalanco==DESB_ESQUERDA){
                            pRaiz=rotacao_Direita(pRaiz);
                        }else{pRaiz=rotacao_Esq_Dir(pRaiz);}//Sinais trocados
                        *cresceu=FALSE;
                        break;
                    case BALANCEADO:
                        (pRaiz)->FatorBalanco=DESB_ESQUERDA;*cresceu=TRUE;
                        break;
                    case DESB_DIREITA://direita maior

                        (pRaiz)->FatorBalanco=BALANCEADO;
                        *cresceu=FALSE;
                        break;
                }//Fimswitch
            }//FimIF(cresceu)

            return pRaiz;
        }//TERMINA DE INSERIR MENOR
        else return FALSE;
    }else{//SE MAIOR
        FolhaAVL *Direita=pRaiz->Dir;

        if(pRaiz->Dir=inserir(&(pRaiz)->Dir,numero,cresceu)){
            if(*cresceu){//inseriu a direita, agora verifica balanco
                    printf("AVALIA BALANCO DIREITA,pRaiz->dado:%d\n",pRaiz->dado);
                switch ((pRaiz)->FatorBalanco){
                    case DESB_ESQUERDA:
                        (pRaiz)->FatorBalanco=BALANCEADO;
                        *cresceu=FALSE;
                        break;
                    case BALANCEADO:
                        (pRaiz)->FatorBalanco=DESB_DIREITA;*cresceu=TRUE;
                        break;
                    case DESB_DIREITA:
                        if((pRaiz)->Dir->FatorBalanco==DESB_DIREITA){
                            rotacao_Esquerda(&pRaiz);*cresceu=TRUE;
                        }else rotacao_Dir_Esq(&pRaiz);*cresceu=FALSE;
                        break;
                }//FIMSWITCH
            }

            return pRaiz;
        }//FIMIF(insereDireita)
        else return FALSE;// nao conseguiu inserir
    }//FIM INSERE MAIOR
}//FimInsere
void insereAux(int info,FolhaAVL **pontRaiz){
    int Aumentou=0;
    inserir(pontRaiz,info,&Aumentou);
    emOrdem(*pontRaiz);
    //percorreCalculandoFB(*pontRaiz);
}
void percorreCalculandoFB(FolhaAVL *pNo){
    if(pNo != NULL) {
         percorreCalculandoFB(pNo->Esq);
         calculaFatorBalanco(pNo);
         percorreCalculandoFB(pNo->Dir);
     }
}
/*
void rebalanceia(FolhaAVL *arv){
    switch(arv->FatorBalanco){
    case DESB_ESQUERDA:
        if(arv->Esq->FatorBalanco==DESB_ESQUERDA){pRaiz=rotacao_Direita(pRaiz);}else{pRaiz=rotacao_Esq_Dir(pRaiz);}
        //if(ALGUMACOISA_POISFOI_INSERCAO_ESQUERDA){arv->FatorBalanco=BALANCEADO;*cresceu=FALSE;}
        break;
    case BALANCEADO:
        if(FOI_INSERCAO_A_ESQUERDA){pRaiz)->FatorBalanco=DESB_ESQUERDA;*cresceu=TRUE;}
        if(FOI_INSERCAO_A_DIREITA){(pRaiz)->FatorBalanco=DESB_DIREITA;*cresceu=TRUE;}
        break;
    case DESB_DIREITA:

    }
}
*/
/*
 * Existem também as famosas funções recursivas para percorrimento da arvore em diversas ordens
*/
void visita(FolhaAVL *no){
    if(no->Dir!=NULL && no->Esq!=NULL){
        printf("No: %d <No.FatorBalanco: %d > No.esq: %d No.dir: %d &No: %x\n",no->dado,no->FatorBalanco,no->Esq->dado,no->Dir->dado,
               no);
    }else{
        printf("No: %d <No.FatorBalanco: %d > um destes é nulo (esq:%x dir:%x) &No:%x\n",no->dado,no->FatorBalanco,no->Esq,no->Dir,no);
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

 FolhaAVL* predecessor(FolhaAVL *no){
    no=no->Esq;
    while(no->Dir!=NULL){
        no=no->Dir;
    }
    return no;
}

 int removeAVL(FolhaAVL *noRaiz,int valRemover,int *mudouAltura){
    FolhaAVL *noAux;//ponteiro auxiliarpara nó
    //printf("entrou na função linha 291\n");
    if(noRaiz==NULL){
        //caso a arvore esteja vazia
        return FALSE;printf("será que entrou aqui?\n");
    }else{
        //caso valor seja menor que o dado vai pra esquerda
        if(valRemover<noRaiz->dado){
                printf("valRemover < noRaiz->dado,linha 298\n");
            if(removeAVL(noRaiz->Esq,valRemover,mudouAltura)){
                if(*mudouAltura)
                {
                    noRaiz->FatorBalanco++;
                    switch(noRaiz->FatorBalanco){
                        case LimDir:rotacao_Esquerda(&noRaiz);if(noRaiz->FatorBalanco==DESB_DIREITA){*mudouAltura=FALSE;printf("Foi pra esquerda\n");}
                        break;
                        case DESB_DIREITA:*mudouAltura=FALSE;break;
                    }//FIMCASES
                    return TRUE;//Conseguiu remover e finaliza função
                }
                //SE nao mudou altura faz o que???
            }
        }else{//valRemover > noRaiz->dado ou valRemover==noRaiz->dado
            if(valRemover > noRaiz->dado){
                    printf("valRemover > noRaiz->dado,linha 313\n");
                if(removeAVL(noRaiz->Dir,valRemover,mudouAltura)){
                    noRaiz->FatorBalanco--;
                    switch(noRaiz->FatorBalanco){
                        case LimEsq:noRaiz=rotacao_Direita(noRaiz);if(noRaiz->FatorBalanco=DESB_ESQUERDA){*mudouAltura=FALSE;};break;
                        case DESB_ESQUERDA:*mudouAltura=FALSE;break;
                    }//avalia balanceamento da arvore
                    return TRUE;//finaliza remocao a direita
                }//conseguiu remover algo a esquerda
            }//valRemove dado
            else{
                //caso valRemove==noRaiz->dado
                if(noRaiz->dado==valRemover)
                {
                    printf("valRemover == noRaiz->dado,linha 328\n");
                    if(noRaiz->Esq==NULL && noRaiz->Dir==NULL)
                    {
                        free(noRaiz);printf("removeu no,linha 331\n");
                        noRaiz=NULL;
                        *mudouAltura=TRUE;
                    }//caso no nao tenha filhos
                }//caso valRemove seja igual a dado
                else if(noRaiz->Esq!=NULL || noRaiz->Dir!=NULL){//caso nó não possui filhos
                    printf("nó não possui filhos\n");
                    noAux=predecessor(noRaiz);//pega o predecessor de noRaiz
                    noRaiz->dado=noAux->dado;
                    removeAVL(noRaiz->Esq,noRaiz->dado,mudouAltura);//promove o nó e remove a esquerda
                }//Fim caso um dos nós nao seja vazio
                else if(noRaiz->Esq!=NULL){//caso nó possui sub-árvore a esquerda:repassa esquerda para o pai
                    printf("nó possui filho a esquerda\n");
                    noRaiz->dado=noRaiz->Esq->dado;
                    free(noRaiz->Esq);
                    noRaiz->Esq=NULL;
                }// Fim caso arvore a esquerda nao seja nula
                else{// caso nó possui sub-árvore direita: atribui ao pai
                    printf("nó possui filho a direita\n");
                    noRaiz->dado=noRaiz->Dir->dado;
                    free(noRaiz->Dir);
                    noRaiz->Dir=NULL;
                }// Fim
                *mudouAltura=TRUE;
            }//Fim caso encontre valRemove na arvore
            *mudouAltura=TRUE;
        }// Fim caso valRemover seja menor ou igual noRaiz->dado
    }//Fim Arvore não-vazia
    *mudouAltura=FALSE;
 }

