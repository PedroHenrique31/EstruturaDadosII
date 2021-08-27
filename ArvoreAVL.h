/**
 *          autor: Pedro Henrique Carneiro de Araújo   Matricula: 22108287
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

typedef struct FolhaAVL{
    int dado;
    int FatorBalanco;
    struct FolhaAVL *Esq;
    struct FolhaAVL *Dir;
}FolhaAVL;

FolhaAVL* rotacao_Direita(FolhaAVL *no);
void rotacao_Esquerda(FolhaAVL **no);
FolhaAVL* rotacao_Esq_Dir(FolhaAVL *no);
void rotacao_Dir_Esq(FolhaAVL **no);
int alturaDir(FolhaAVL *no);
int alturaEsq(FolhaAVL *no);
void calculaFatorBalanco(FolhaAVL *no);
FolhaAVL criaRegistro(int info);
FolhaAVL* inserir(FolhaAVL **pPonteiroParaRaiz,int numero,int *cresceu);
void insereAux(int info,FolhaAVL **pontRaiz);
void percorreCalculandoFB(FolhaAVL *pNo);
void visita(FolhaAVL *no);
void emOrdem(FolhaAVL *pNo);
void preOrdem(FolhaAVL *pNo);
void posOrdem(FolhaAVL *pNo);
