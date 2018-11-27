typedef struct no{
    string nome;
    string desc;
    struct no *prox;
    struct no *ant;
    struct no *rot;
    no(){//construtor
        nome = "";
        desc = "";
        prox = NULL;
        ant = NULL;
        rot = NULL;
    }
} No;

typedef struct lista{
    No *inicio;
    No *fim;
    int tamanho;
    lista(){//construtor
        inicio = NULL;
        fim = NULL;
        tamanho = 0;
    }
    ~lista(){//destrutor
        No *n = inicio;
        while(n){
            No *aux = n;
            n = n->prox;
            delete aux; //libera memória;
        }
        inicio = NULL;
        fim = NULL;
        tamanho = 0;
    }
} Lista;


void inserirInicio(Lista *l, string nome, string desc){
    No *novo = new No();
    novo->nome = nome;
    novo->desc = desc;
    novo->prox = l->inicio;
    if(!l->inicio){//quer dizer que a lista estava vazia
        l->fim = novo;
    }else{
        l->inicio->ant = novo;
    }
    l->inicio = novo;
    l->tamanho++;
}


void insereOrdenado(Lista *l, string valor){
    No *anterior = NULL;
    No *atual = l->inicio;
    while(atual && atual->nome < valor){
        anterior = atual;
        atual = atual->prox;
    }
    No *novo = new No();
    novo->nome = valor;
    if(!anterior){//Se não tiver nenhum elemento da lista
        novo->prox = l->inicio;
        if(l->inicio){// a lista já tinha valores
            l->inicio->ant = novo;
        }
        l->inicio = novo;
        if(!l->fim){//a lista estava vazia
            l->fim = l->inicio;
        }
    }else{//se incluido no meio ou no fim
        novo->prox = atual;
        novo->ant = anterior;
        anterior->prox = novo;
        if(atual){//se não for incluir no fim
            atual->ant = novo;
        }
        if(!novo->prox){//se for incluir no fim
            l->fim = novo;
        }
    }
    l->tamanho++;
}

bool removeValor(Lista *l, string valor){
    No *anterior = NULL;
    No *atual = l->inicio;
    while(atual && atual->nome != valor){
        anterior = atual;
        atual = atual->prox;
    }
    if(!atual){//não achou
        return false;
    }
    if(!anterior){//valor a ser removido é o primeiro da lista
        l->inicio = atual->prox;
        if(!l->inicio){//lista vai ficar vazia
            l->fim = l->inicio;
        }else{
            l->inicio->ant = NULL;
        }
    }else{
        anterior->prox = atual->prox;
        if(!atual->prox){//o valor a ser excluido é o ultimo da lista
            l->fim = anterior;
        }else{
            atual->prox->ant = anterior;
        }
    }
    l->tamanho--;
    delete(atual);
    return true;
}

void imprime(Lista *l){
    No *n = l->inicio;
    while(n){
        cout << "-----------------------------\n";
        cout << n->nome;
        cout << '\t';
        cout << n->desc;
        cout << '\t';
        No *x = n->rot;
        while(x != NULL){
            cout << x->nome << '\t';
            x = x->prox;
        }
        n = n->prox;
        if(n){
            cout << "\n";
        }
    }
    cout << "\n";
}

void imprimeInverso(Lista *l){
    No *n = l->fim;
    while(n){
        cout << "-----------------------------\n";
        cout << n->nome;
        cout << '\t';
        cout << n->desc;
        cout << '\t';
        cout << n->rot->nome;
        n = n->ant;
        if(n){
            cout << "\n";
        }
    }
    cout << "\n";
}

void imprimeDescritor(Lista *l){
    if(l->inicio){
        cout << l->inicio->nome;
    }else{
        cout << "NULL";
    }
    cout << ", ";
    if(l->fim){
        cout << l->fim->nome;
    }else{
        cout << "NULL";
    }
    cout << ", " << l->tamanho << "\n";
}


No* buscaRecursiva(No *lista, string valor){
    if (!lista) { // se n�o tiver mais elementos
        return NULL;
    }else if (lista->nome == valor){
        return lista;
    }else{
        return buscaRecursiva(lista->prox, valor);
    }
}

int frequencia(No *lista, string valor, int c){
    if (!lista) { // se n�o tiver mais elementos
        return c;
    }else if (lista->desc == valor){
        c++;
    }
    return frequencia(lista->prox, valor, c);
}

No* conectaRoteadorTerminal(No *roteador, string valor,No *terminal){
    if (!roteador) { // se n�o tiver mais elementos
        return NULL;
    }else if (roteador->nome == valor){
        terminal->rot = roteador;
        return roteador;
    }else{
        return conectaRoteadorTerminal(roteador->prox, valor, terminal);
    }
}

bool checkRemocaoRoteador(No *lista, string valor){
    if (!lista) { // se n�o tiver mais elementos
        return false;
    }else if (lista->nome == valor){
        return true;
    }else{
        cout << lista->nome << "\n";
        return buscaRecursiva(lista->prox, valor);
    }
}

//ROTEADORES Lista
void insereRoteador(No *rot1, No* rot2){
    No *novo = new No();
    novo->prox = rot1->rot;
    novo->nome = rot2->nome;
    rot1->rot = novo;
}

bool removeRoteador(No *rot1, string nome){
    No *atual = rot1->rot;
    if (!atual->ant){ //valor está no primeiro nó da rot1 -> anterior == NULL
        rot1 = atual->prox;
    }else // valor está no meio/final da rot1
        atual->ant->prox = atual->prox;
    delete(atual); //libera a memória do nó
    return true;
}

bool enviaPacotes(No *rot1, No *rot2){
    if (!rot1) { // se n�o tiver mais elementos
        return false;
    }else if (rot1->nome == rot2->nome){
        return true;
    }else{
        return enviaPacotes(rot1->prox, rot2);
    }
}


//Sobrecarga de operador
ostream& operator<<(ostream& os, const No *n){
    return os << n->nome;
}

ostream& operator << (ostream& os, const Lista *l){
    No *n = l->inicio;
    while(n){
        os << n;
        n = n->prox;

        if(n){
            os << ", ";
        }
    }
    return os;
}
