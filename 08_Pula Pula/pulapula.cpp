#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <memory>

using namespace std;

class Children {
public:
    int idade;
    string nome;

    Children(int idade = 0, string nome = "") : idade(idade), nome(nome) {}
    friend ostream& operator<<(ostream& os, const Children& p) {
    os << "Nome: " << p.nome << " Idade: " << p.idade << endl;
    return os;
    }
};

class PulaPula {
    list <shared_ptr<Children>> fila;
    list <shared_ptr<Children>> Pulap;

public:
    PulaPula(int lugares) : fila(lugares, nullptr) {}

    void entrar(shared_ptr<Children> crianca) {
            fila.push_back(crianca);
    }

    void moverpulapula(int flag) {
        if (flag == 1) {
            Pulap.push_front(fila.back());
            fila.pop_back();
        }
    }

    void sair(int flag) {
        if (flag == 1) {
            fila.push_front(Pulap.back());
            Pulap.pop_back();
        }
    }
    shared_ptr<Children> remover(string nome, int lista) {
        if (lista == 1) {
            for (auto it = fila.begin(); it != fila.end(); it++) {
                if ((*it)->nome == nome) {
                    shared_ptr<Children> crianca = *it;
                    fila.erase(it);
                    return crianca;
                }
            }
        } else {
            for (auto it = Pulap.begin(); it != Pulap.end(); it++) {
                if ((*it)->nome == nome) {
                    shared_ptr<Children> crianca = *it;
                    Pulap.erase(it);
                    return crianca;
            }
        }
    }
    return nullptr;
}

    friend ostream& operator<<(ostream& os, const PulaPula& p) {
        os << "\n|  ";
        for (auto pessoa : p.fila) {
            if (pessoa != nullptr) {
                os << *pessoa << " ";
    }
}

    os << "|";
    os << " => ";

    os << "[ ";
    for (auto pessoa : p.Pulap) {
        if(pessoa != nullptr){
            os << *pessoa << " ";
    }
}
    os << "]";

    return os;
    }
};
    
    int main(){
        PulaPula fila(4);

        fila.entrar(make_shared<Children>(5, "Damon"));
        fila.entrar(make_shared<Children>(6, "Stefan"));
        fila.entrar(make_shared<Children>(7, "Elena"));
        fila.entrar(make_shared<Children>(8, "Caroline"));
        cout << fila << endl;

        fila.moverpulapula(1);
        cout << fila << endl;

        fila.sair(1);
        cout << fila << endl;

        fila.remover("Damon", 1);
        cout << fila << endl;

        return 0;
}