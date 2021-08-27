
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
