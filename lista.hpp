typedef struct node{
    string dado;
    struct node *prox;
} Node;

void inicializa(Node **lista)
{
    *lista = NULL;
}

void insere(Node **lista, string valor)
{// insere no início
    Node *novo = new Node();
    novo->dado = valor;
    novo->prox = *lista;
    *lista = novo;
}

bool remover(Node **lista, string valor)
{ //remove o valor recebido por parâmetro - busca na lista
    Node *anterior = NULL;
    Node *atual = *lista;
    while (atual && atual->dado != valor)
    {
        anterior = atual;
        atual = atual->prox;
    }
    if (!atual) //se não encontrou valor -> atual == NULL
        return false;
    if (!anterior) //valor está no primeiro nó da lista -> anterior == NULL
        *lista = atual->prox;
    else // valor está no meio/final da lista
        anterior->prox = atual->prox;
    delete(atual); //libera a memória do nó
    return true;
}

void mostrar(Node *lista)
{
    Node *n = lista;
    while(n)
    {
        cout << n->dado;
        n = n->prox;
        if (n)
            cout << ", ";
    }
    cout << endl;
}

void destruir(Node **lista)
{
    Node *n = *lista;
    while (n)
    {
        Node *aux = n;
        n = n->prox;
        delete aux;
    }
    *lista = NULL;
}


Node* busca(Node *lista, string valor){
    Node *n = lista;
    while(n){
        if(n->dado == valor)
            return n;

        n = n->prox;
    }
    return NULL;
}

bool vazia(Node *lista){


    return lista ? false : true;
    /*
    if(lista)
        return false;
    else
        return true;*/
}

bool igual(Node *lista1, Node *lista2){

    Node *n1 = lista1;
    Node *n2 = lista2;
    while(n1 && n2){
        if (n1->dado != n2->dado)
            return false;
        n1 = n1->prox;
        n2 = n2->prox;
    }
    if (!n1 && !n2)
        return true;
    else
        return false;
}


void insereOrdenado(Node **lista, string valor){

    Node *anterior = NULL;
    Node *atual = *lista;
    while(atual && atual->dado < valor){

        anterior = atual;
        atual = atual->prox;
    }
    Node *novo = new Node();
    novo->dado = valor;
    if (!anterior){ //se o primeiro da lista é maior que o valor ou lista vazia
        novo->prox = *lista;
        *lista = novo;
    }else{
        novo->prox = anterior->prox;
        anterior->prox = novo;
    }
}











