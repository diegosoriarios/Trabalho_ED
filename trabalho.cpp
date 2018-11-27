#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace std;

#include "listas.hpp"

bool validarString(string texto){
    for(int i = 0; i < texto.size(); i++){
        if(isspace(texto[i])){
            return false;
        }
    }
    return true;
}

bool validarRoteador(Lista *roteador, string texto){
    No *n = roteador->inicio;
    while(n){
        if(n->nome == texto){
            return false;
        }
        n = n->prox;
    }
    return true;
}

int main(){
    Lista *roteador = new Lista();
    Lista *terminal = new Lista();
    int opt;
    string nome, desc;
    
    //INSERIR VALORES
    inserirInicio(roteador, "r1", "oi");
    inserirInicio(roteador, "r2", "telemar");
    inserirInicio(roteador, "r3", "gvt");
    inserirInicio(roteador, "r4", "net");
    inserirInicio(roteador, "r5", "telemar");
    /////////////////
    do{
        cout << "\n-----Digite sua opção--------\n"
        << "0 - Sair\n"
        << "1 - Cadastra Roteador\n"
        << "2 - Cadastra Terminal\n"
        << "3 - Remove Roteador\n"
        << "4 - Remove Terminal\n"
        << "5 - Conecta Roteadores\n"
        << "6 - Desconecta Roteadores\n"
        << "7 - Frequencia Operadoras\n"
        << "8 - Enviar Pacotes de Dados\n"
        << "9 - Mostrar Terminais\n"
        << "10 - Mostrar Roteadores: ";
        cin >> opt;
        cin.ignore();
        switch(opt){
            case 0:
                return 0;
            case 1:
                do{
                    cout << "Digite o nome do roteador: ";
                    getline(cin, nome);
                }while(!validarString(nome) && !validarRoteador(roteador, nome));
                do{
                    cout << "Digite a operadora do roteador: ";
                    getline(cin, desc);
                }while(!validarString(desc) && !validarRoteador(roteador, desc));
                inserirInicio(roteador, nome, desc);
                break;
            case 2:
                if(roteador->tamanho > 0){
                    do{
                        cout << "Digite o nome do terminal: ";
                        getline(cin, nome);
                    }while(!validarString(nome));
                    do{
                        cout << "Digite a localização do terminal: ";
                        getline(cin, desc);
                    }while(!validarString(desc));
                    inserirInicio(terminal, nome, desc);
                    string con;
                    do{
                        cout << "Conecte-se com qual roteador: ";
                        getline(cin, con);
                    }while(!validarString(con));
                    No *busca = buscaRecursiva(roteador->inicio, con);
                    if(busca){
                        terminal->inicio->rot = busca;
                    }else{
                        cout << "Roteador não encontrado";
                    }
                }else{
                    cout << "Cadastre um roteador primeiro";
                }
                break;
            case 3:
                do{
                    cout << "Qual roteador deseja remover: ";
                    getline(cin, nome);
                }while(!validarString(nome));
                if(checkRemocaoRoteador(terminal->inicio->rot, nome)){
                    cout << "Roteador possui conexões";
                }else{
                    removeValor(roteador, nome);
                    cout << "Valor removido";
                }
                break;
            case 4:
                do{
                    cout << "Qual terminal deseja remover: ";
                    getline(cin, nome);
                }while(!validarString(nome));
                removeValor(terminal, nome);
                break;
            case 5:{
                cout << "Quais roteadores deseja conectar: ";
                getline(cin, nome);
                No *aux1 = buscaRecursiva(roteador->inicio, nome);
                getline(cin, nome);
                No *aux2 = buscaRecursiva(roteador->inicio, nome);
                if(aux1 == NULL || aux2 == NULL){
                    cout << "Valores não encontrados";
                }else{
                    insereRoteador(aux1, aux2);
                    insereRoteador(aux2, aux1);
                }
                break;}
            case 6:{
                cout << "Quais roteadores deseja desconectar: ";
                getline(cin, nome);
                No *aux1 = buscaRecursiva(roteador->inicio, nome);
                getline(cin, desc);
                No *aux2 = buscaRecursiva(roteador->inicio, desc);
                if(aux1 == NULL || aux2 == NULL){
                    cout << "Valores não encontrados";
                }else{
                    if(removeRoteador(aux1, aux2->nome)){
                        cout << "Roteador " << aux2->nome << " retirado de " << aux1->nome;
                    }else{
                        cout << "Não foi retirado";
                    }
                    cout << "\n";
                    if(removeRoteador(aux2, aux1->nome)){
                        cout << "Roteador " << aux1->nome << " retirado de " << aux2->nome;
                    }else{
                        cout << "Não foi retirado";
                    }
                }
                
                break;}
            case 7:
                do{
                    cout << "Quais operadoras deseja buscar: ";
                    getline(cin, nome);
                }while(!validarString(nome));
                cout << frequencia(roteador->inicio, nome, 0);
                break;
            case 8:{
                cout << "Enviar pacotes entre quais terminais: ";
                getline(cin, nome);
                No *aux1 = buscaRecursiva(terminal->inicio, nome);
                aux1 = buscaRecursiva(roteador->inicio, aux1->rot->nome);
                getline(cin, desc);
                No *aux2 = buscaRecursiva(terminal->inicio, desc);
                aux2 = buscaRecursiva(roteador->inicio, aux2->rot->nome);
                if(aux1 == NULL || aux2 == NULL){
                    cout << "Valores não encontrados";
                }else{
                    bool check = false;
                    if(enviaPacotes(aux1->rot, aux2) || aux1->nome == aux2->nome){
                        cout << "Pacotes Enviados\n";
                    }else{
                        cout << aux1->nome;
                        No *x = aux1->rot;
                        while(x){
                            cout << x->nome;
                            check = enviaPacotes(x, aux2->rot);
                            if(check){
                                break;
                            }
                            x = x->prox;
                        }
                        if(check){
                            cout << "Pacotes Enviados\n";
                        }else{
                            cout << "Não foi possivel enviar dados\n";
                        }
                    }
                }
                break;}
            case 9:
                imprimeInverso(terminal);
                break;
            case 10:
                imprime(roteador);
                break;
        }
    }while(opt != 0);
}
