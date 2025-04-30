#include <stdio.h>
#include <stdlib.h>

typedef struct arvore {
    int info;
    struct arvore *esq;
    struct arvore *dir;
}arvore;

arvore *LerArvore(FILE *arq){
    char c;
    int num;

    fscanf(arq,"%c",&c);
    fscanf(arq,"%d",&num);

    if(num==-1){
        fscanf(arq,"%c",&c);
        return NULL;
    }else{
        arvore *a = (arvore*)malloc(sizeof(arvore));
        a->info = num;
        a->esq = LerArvore(arq);
        a->dir = LerArvore(arq);
        fscanf(arq,"%c",&c);
        return a;
    }
}

void Imprimir(arvore *a){
    if(a!=NULL){
        printf("%d ",a->info);
        Imprimir(a->esq);
        Imprimir(a->dir);
    }
}

void ImprimirEmOrdem(arvore *a){
    if(a!=NULL){
        Imprimir(a->esq);
        printf("%d ",a->info);
        Imprimir(a->dir);
    }
}

void ImprimirPosOrdem(arvore *a){
    if(a!=NULL){
        Imprimir(a->esq);
        Imprimir(a->dir);
        printf("%d ",a->info);
    }
}

int Existe(arvore *a, int x){
    if(a==NULL){
        return 0;
    }else if(x==a->info)
        return 1;
    else if(x<a->info)
        return Existe(a->esq,x);
    else
        return Existe(a->dir,x);
}

int altura(arvore *a){
    if(a==NULL)
        return 0;
    else{
        int he = altura(a->esq);
        int hd = altura(a->dir);
        if(he>hd)
            return he+1;
        else
            return hd+1;
    }
}

void ImprimirNivelNo(arvore *a, int cont, int x){
    if(a!=NULL){
        if(a->info==x)
            printf("%d ",cont);
        else{
            ImprimirNivelNo(a->esq,cont+1,x);
            ImprimirNivelNo(a->dir,cont+1,x);
        }
    }
}

void ImprimirFolhasMenores(arvore *a, int x){
    if(a!=NULL){
        if(a->info<x){
            if(a->esq==NULL && a->dir==NULL)
                printf("%d ",a->info);
        }else{
            ImprimirFolhasMenores(a->esq,x);
        }
    }
}

void ImprimirNivel(arvore *a, int nivel){
    if(a==NULL)return;
    if(nivel==0)
        printf("%d ",a->info);
    else{
        ImprimirNivel(a->esq,nivel-1);
        ImprimirNivel(a->dir,nivel-1);
    }
}

void ImprimirEmLargura(arvore *a){
    int h = altura(a);
    for(int i = 0; i < h; i++){
        ImprimirNivel(a,i);
        printf("\n");
    }
}

arvore *Inserir(arvore *a, int x){
    if(a==NULL){
        a = (arvore*)malloc(sizeof(arvore));
        a->info=x;
        a->esq=NULL;
        a->dir=NULL;
    }else if(x<=a->info){
        a->esq = Inserir(a->esq,x);
    }else{
        a->dir = Inserir(a->dir,x);
    }
    return a;
}

arvore *Destruir(arvore *a){
    if(a!=NULL){
        a->esq = Destruir(a->esq);
        a->dir = Destruir(a->dir);
        free(a);
    }
    return NULL;
}

arvore *Remover(arvore *a,int x){  
    if(a!=NULL){
        if(a->info==x){
            if(a->esq==NULL && a->dir==NULL){
                free(a);
                return NULL;
            }
        }else if(a->esq==NULL){
            arvore *aux = a->dir;
            free(a);
            return aux;
        }else if(a->dir==NULL){
            arvore *aux = a->esq;
            free(a);
            return aux;
        }else{
            arvore *aux = a->esq;
            while(aux->dir!=NULL){
                aux = aux->dir;
            }
            a->info = aux->info;
            a->esq = Remover(a->esq,aux->info);
        }
    }else if(x<a->info){
        a->esq = Remover(a->esq,x);
    }else{
        a->dir = Remover(a->dir,x);
    }
    return a;
}
int main(){
    FILE *arq;
    arvore *a;
    int aux = 0;
    int aux2 = 0;
    while(aux!=8){
        printf("\nMENU\n"); 
        printf("1 - Ler a Arvore no arquivo\n");
        printf("2 - Imprimir a Arvore\n");
        printf("3 - Verificar se um elemento existe na Arvore\n");
        printf("4 - Imprimir um nivel de um no\n");
        printf("5 - Imprimir as folhas menores que um valor x\n");
        printf("6 - Inserir um no x na arvore\n");
        printf("7 - Remover um no x da arvore\n");
        printf("8 - Sair\n");
        scanf("%d", &aux);
        if(aux==1){
            arq = fopen("arvore.txt", "rt");
            a = LerArvore(arq);
            fclose(arq);
        }else if(aux==2){
            printf("1-Imprimir pre ordem\n2-Imprimir em Ordem\n3-Imprimir Pos Ordem\n4-Imprmir em Largura\n");
            scanf("%d",&aux2);
            if(aux2==1)
                Imprimir(a);
            else if(aux2==2)
                ImprimirEmOrdem(a);
            else if(aux2==3)
                ImprimirPosOrdem(a);
            else if(aux2==4)
                ImprimirEmLargura(a);
            else 
                printf("numero invalido\n");

        }else if(aux==3){
            printf("digite um numero: ");
            scanf("%d",&aux2);
            if(Existe(a,aux2))
                printf("Existe");
            else
                printf("Nao existe!");
        }else if(aux==4){
            printf("digite um numero: ");
            scanf("%d",&aux2);
            ImprimirNivelNo(a,0,aux2);
        }else if(aux==5){
            printf("digite um numero: ");
            scanf("%d",aux2);
            ImprimirFolhasMenores(a,aux2);
        }else if(aux==6){
            printf("digite um numero: ");
            scanf("%d",aux2);
            a = Inserir(a, aux2);
        }else if(aux==7){
            printf("digite um numero: ");
            scanf("%d",aux2);
            a = Remover(a,aux2);
        }else if(aux==8){
            a = Destruir(a);
            break;
        }else{
            printf("Escolha um numero valido!");
        }
    }
}