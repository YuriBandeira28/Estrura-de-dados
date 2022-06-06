#include <stdio.h>
#include <stdlib.h>
int folha=0;


struct nodo{
  int dado;              //Nodo será armazenado como inteiro
  struct nodo *sad;      //Subárvore direita
  struct nodo *sae;      //Subárvore esquerda
  int altura;            //AVL: informação da altura do nó
};


//Função para criar um nodo
struct nodo* novoNodo(int x){
  struct nodo *p;
  p = malloc(sizeof(struct nodo));
  p->dado = x;
  p->sae = NULL;
  p->sad = NULL;
  p->altura = 0; // AVL: seta a altura do nó
  
  return p;
}


//Buscar um valor na árvore
struct nodo* buscar(struct nodo *raiz, int x)
{
  if (raiz != NULL){
    if(raiz->dado == x) //Se raiz->dado igual a x o elemento foi encontrado
      return raiz;
    else if(x > raiz->dado) //Se x é maior, buscar na subárvore direita
      return buscar(raiz->sad, x);
    else  //Se x é menor, buscar na subárvore esquerda
      return buscar(raiz->sae, x);
  }
  return raiz;
}


//Exibe quantidade de nodos da árvore
int numeroNodos(struct nodo *raiz){
  if(raiz == NULL) return(0);
  return (numeroNodos(raiz->sae) + 1 + numeroNodos(raiz->sad));
}


//Exibir árvore
void exibirArvore(struct nodo *raiz){
  if (raiz != NULL){
    printf("%i", raiz->dado);
    printf("(");
    exibirArvore(raiz->sae);
    exibirArvore(raiz->sad);
    printf(")");
  }
  else printf("()"); 
}


//Encontrar o menor nodo
struct nodo* menorNodo(struct nodo *raiz){
  if(raiz == NULL) return NULL;
  else if(raiz->sae != NULL) return menorNodo(raiz->sae);
  return raiz;
}


//Encontrar o maior nodo
struct nodo* maiorNodo(struct nodo *raiz){
  if(raiz == NULL) return NULL;
  else if(raiz->sad != NULL) return maiorNodo(raiz->sad);
  return raiz;
}


//Função para encontrar os nodos folha
void exibirFolhas(struct nodo *raiz){
  if (raiz != NULL){
    if (raiz->sae == NULL && raiz->sad == NULL) {
      printf("%i, ", raiz->dado);
    }
    exibirFolhas(raiz->sae);
    exibirFolhas(raiz->sad); 
  }
  else printf(""); 
}


//percorrer a árvore em inorder
void inorder(struct nodo *raiz)
{
  if(raiz != NULL) //Verifica se a raíz não é nula
  {
    inorder(raiz->sae); //Visita filho da esquerda
    printf(" %d ", raiz->dado); //Imprime dado da raíz
    inorder(raiz->sad);//Visita filho da direita
  }
}


//percorrer a árvore em preorder
void preorder(struct nodo *raiz)
{
  printf(" %d ", raiz->dado);                 
  if (raiz->sae != NULL) preorder(raiz->sae); 
  if (raiz->sad != NULL) preorder(raiz->sad);
}


//percorrer a árvore em postorder
void postorder(struct nodo *raiz)
{
  if (raiz->sae != NULL) postorder(raiz->sae); 
  if (raiz->sad != NULL) postorder(raiz->sad);
  printf(" %d ", raiz->dado);  
}


//=========================================================================
//FUNÇÕES A SEREM DESENVOLVIDAS PARA COMPLEMENTAR O CÓDIGO DA ÁRVORE AVL
//=========================================================================


//AVL: rotação à esquerda
struct nodo* rotEsquerda(struct nodo *raiz){
  struct nodo *temp1, *temp2;

  //realocação para rotação
  temp1 = raiz->sad;
  temp2 = temp1->sae;

  temp1->sae = raiz;
  raiz->sad = temp2;
   //ajuste de alturas
  raiz->altura = maior(alturaNodo(raiz->sae),alturaNodo(raiz->sad)) + 1;
  temp1->altura = maior(alturaNodo(temp1->sae), alturaNodo(temp1->sad)) + 1;
  return temp1;
}

//AVL: rotação à direita
struct nodo* rotDireita(struct nodo *raiz){
 struct nodo *temp3, *temp4;
  
  temp3 = raiz->sae;
  temp4 = temp3->sad;
  
  temp3->sad = raiz;
  raiz->sae = temp4;

  raiz->altura = maior(alturaNodo(raiz->sae), alturaNodo(raiz->sad)) + 1;
  temp3->altura = maior(alturaNodo(temp3->sae), alturaNodo(temp3->sad)) + 1;

   return temp3;

  //return temp2;
}


//AVL: rotação dupla esq/dir
struct nodo* rotEsquerdaDireita(struct nodo *raiz){
  raiz->sae = rotEsquerda(raiz->sae);
  return rotDireita(raiz);
}

//AVL: rotação dupla dir/esq
struct nodo* rotDireitaEsquerda(struct nodo *raiz){
  raiz->sad = rotDireita(raiz->sad);
  return rotEsquerda(raiz);
}



//AVL: Função para balancear a árvore depois de uma inserção/remoção
//Recebe o nó que está desbalanceado e retorna a nova raiz após o balanceamento
struct nodo* balancear(struct nodo *raiz){  
    //rotção à esquerda
    if(fatorBalanc(raiz) < -1 && fatorBalanc(raiz->sad) <= 0){
      raiz =  rotEsquerda(raiz);
    }
    else if(fatorBalanc(raiz) > 1 && fatorBalanc(raiz->sae) >=0){
      raiz =  rotDireita(raiz);
    }
    else if(fatorBalanc(raiz) > 1 && fatorBalanc(raiz->sae) < 0){
      printf("\n rotacao esquerda direita");
      raiz = rotEsquerdaDireita(raiz);
    }
    else if (fatorBalanc(raiz) < -1 && fatorBalanc(raiz->sad) > 0){
      printf("\n rotacao  direita esquerda");
      raiz = rotDireitaEsquerda(raiz);
    }

    return raiz;
}



//=========================================================================
//                ALTERAÇÕES/INSERÇÕES PARA ÁRVORES AVL
//=========================================================================

//AVL: Imprimir a árvore de forma mais visual
void imprimirAVL(struct nodo *raiz, int nivel){
  int i;
  if(raiz){
    imprimirAVL(raiz->sad, nivel + 1);
    printf("\n\n");
    
    for(i = 0; i < nivel; i++)
      printf("\t");
    
    printf("%d", raiz->dado);
    imprimirAVL(raiz->sae, nivel + 1);
  }
}


//AVL: retorna a maior altura entre dois nós
int maior(int a, int b){
  if (a > b)
    return a;
  else
    return b;
}


//AVL: retornar a altura de um nó
int alturaNodo(struct nodo *raiz){
  if (raiz == NULL)
    return -1;
  else
    return raiz->altura;
}


//AVL: Fator de Balanceamento (FB)
int fatorBalanc(struct nodo *raiz){
  if(raiz)
    return(alturaNodo(raiz->sae) - alturaNodo(raiz->sad));
  else
    return 0;
}

//AVL: Função para inserir um valor alterada para AVL
struct nodo* inserir(struct nodo *raiz, int x){
  if(raiz == NULL) // árvore vazia
    return novoNodo(x);
  else if(x > raiz->dado)  //x é maior, então inserir à direita
    raiz->sad = inserir(raiz->sad, x);
  else   //x é menor, então inserir à esquerda
    raiz->sae = inserir(raiz->sae, x);
  
  //AVL: recalcula altura dos nós entre a raíz e o nó inserido
  raiz->altura = maior(alturaNodo(raiz->sae), alturaNodo(raiz->sad))+1;
  //AVL: verifica se precisa rebalancear a árvore
  //raiz = balancear(raiz);
  printf ("\na raiz é %i: ", raiz->dado);

  return raiz;
}

//AVL: Função para excluir um nodo
struct nodo* excluir(struct nodo *raiz, int x) {
  if(raiz == NULL){
    printf("Valor nao encontrado!\n");
    return NULL;
  } 
  else { // procura o nó a remover
    if(raiz->dado == x) {
      // remove nós folhas (nós sem filhos)
      if(raiz->sae == NULL && raiz->sad == NULL) {
        free(raiz);
        return NULL;
      }
      else{
        // remover nós que possuem 2 filhos
        if(raiz->sae != NULL && raiz->sad != NULL){
          struct nodo *aux = raiz->sae;
          while(aux->sad != NULL)
            aux = aux->sad;
          raiz->dado = aux->dado;
          aux->dado = x;
          raiz->sae = excluir(raiz->sae, x);
          return raiz;
        }
        else{
          // remover nós que possuem apenas 1 filho
          struct nodo *aux;
          if(raiz->sae != NULL)
            aux = raiz->sae;
          else
            aux = raiz->sad;
          free(raiz);
          return aux;
        }
      }
    } 
    else {
      if(x < raiz->dado)
        raiz->sae = excluir(raiz->sae, x);
      else
        raiz->sad = excluir(raiz->sad, x);
    }
    
    // Recalcula a altura de todos os nós entre a raiz e o nó excluído
    raiz->altura = maior(alturaNodo(raiz->sae), alturaNodo(raiz->sad)) + 1;
    
    // verifica a necessidade de rebalancear a árvore
    raiz = balancear(raiz);
    
    return raiz;
  }
}


//========================================================
// FUNÇÃO PRINCIPAL DO PROGRAMA
//========================================================
int main()
{
  int opcao, valor;
  struct nodo *raiz = NULL;
  
  do{
    printf("\n\n\t0 - Sair\n\t1 - Inserir\n\t2 - Excluir\n\t3 - ImprimirAVL\n\t4 - Imprimir estrutura\n\t5 - Buscar\n\t6 - Qtd nodos\n\t7 - Menor nodo\n\t8 - Maior nodo\n\t9 - Nodos folha\n\t10 - Imprimir inorder\n\t11 - Imprimir postorder\n\t12 - Imprimir preorder\n\n");
    scanf("%d", &opcao);
    
    switch(opcao){
      case 0:
        printf("Programa encerrado pelo usuário.");
        break;
      case 1:
        printf("\tDigite o valor a ser inserido: ");
        scanf("%d", &valor);
        raiz = inserir(raiz, valor);
        break;
      case 2:
        printf("\tDigite o valor a ser excluído: ");
        scanf("%d", &valor);
        raiz = excluir(raiz, valor);
        break;
      case 3:
        printf("\tImprimindo a árvore: ");
        imprimirAVL(raiz, 1);
        break;
      case 4:
        printf("\tImprimindo a estrutura da árvore: ");
        exibirArvore(raiz);
        break;
      case 5:
        printf("\tDigite o valor a procurar: ");
        scanf("%d", &valor);
        if (buscar(raiz, valor)==NULL)
          printf("\nValor não encontrado.\n");
        else
          printf("\nValor encontrado.\n");
        break;
      case 6:
        printf("\tQuantidade de nodos da árvore: %d", numeroNodos(raiz));
        break;
      case 7:
        printf("Menor nodo: %d\n", menorNodo(raiz)->dado);
        break;
      case 8:
        printf("Maior nodo: %d\n", maiorNodo(raiz)->dado);
        break;
      case 9:
        exibirFolhas(raiz);
        break;
      case 10:
        inorder(raiz);
        break;
      case 11:
        postorder(raiz);
        break;
      case 12:
        preorder(raiz);
        break;
      default:
        printf("\nOpção inválida!!!\n");
    }
    
  }while(opcao != 0);
  
  return 0;  
}
