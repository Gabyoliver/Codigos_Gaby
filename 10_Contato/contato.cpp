#include <iostream>
#include <vector>
#include <memory>
#include <list>

using namespace std;

class Fone {
    string id;
    string numero;

public:
    Fone(string id = "", string numero = "") : id(id), numero(numero) {}

    bool validate(string numero) {
        for(int i = 0; i < (int)numero.size(); i++) {
            if(numero[i] >= '0' || numero[i] <= '9' || numero[i] == '+' || numero[i] == '-' || numero[i] == '(' || numero[i] == ')') {
                return true;
            }
        }

        return false;
    }
    
    friend ostream& operator<<(ostream& os, const Fone& fone) {
        os << "(" << fone.id << ") " << fone.numero;
        return os;
    }

    string getId() {
        return id;
    }

    string getNumero() {
        return numero;
    }
};

class Contato {
    string nome;
    list<Fone> fones;
public:
    Contato(string nome = "") : nome(nome) {}

    void addFone(Fone fone) {
        fones.push_back(fone);
        cout << "Fone adicionado: " << fone << endl;
    }

    void rmFone (int cont = -1) {
        int cont2 = 0;
        for(auto it = fones.begin(); it != fones.end(); it++) {
            if(cont2 == cont) {
                fones.erase(it);
                cout << "Fone removido: " << *it << endl;
                break;
            }
            cont2++;
        }
    }

    friend ostream& operator<<(ostream& os, const Contato& contato) {
        os << contato.nome << endl;
        for(auto it = contato.fones.begin(); it != contato.fones.end(); it++) {
            os << *it << endl;
        }
        return os;
    }

    string getNome() {
        return nome;
    }

    list<Fone> getFones() {
        return fones;
    }
};

    int main() {
        Contato contato("Gabrielly Oliveira");
        contato.addFone(Fone("Celular", "98888-8888"));
        contato.addFone(Fone("Casa", "8888-8888"));
        contato.addFone(Fone("Trabalho", "8888-8888"));
        contato.rmFone(1);
        cout << contato;
        return 0;
    }

   
