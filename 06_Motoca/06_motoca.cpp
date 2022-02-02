#include <iostream>
#include <sstream>

using namespace std;

struct Pessoa {
    string nome; 
    int idade;

    Pessoa(string nome = "", int idade = 0) { 
        this->nome = nome;
        this->idade = idade;
    }

    Pessoa(int idade) : Pessoa("", idade) {
    }

    friend ostream& operator<<(ostream& os, const Pessoa& p) {
        os << "Nome: " << p.nome << " Idade: " << p.idade;
        return os;
    }
};


struct Motoca {
    Pessoa* pessoa {nullptr}; 
    int tempo {0};
    int potencia {1};
    Motoca(int pot): potencia {pot} {
    }


    bool inserirPessoa(Pessoa * p) {
        if (this->pessoa != nullptr) {
            cout << "Motoca cheia" << endl;
            return false;
        }
        this->pessoa = p;
        return true;
    }

    string buzinar() {
        return "P" + std::string(this->potencia, 'e') + "m";
    }

    Pessoa * removerPessoa() {
        Pessoa * p = this->pessoa;
        this->pessoa = nullptr;
        return p;
    }

    void comprarTempo(int tempo) {
        this->tempo += tempo;
    }

    bool dirigir(int tempo) {
        if (this->pessoa == nullptr) {
            cout << "nao tem gente pra dirigir" << endl;
            return false;
        }
        if (tempo > this->tempo) {
            cout << "só conseguiu dirigir " << this->tempo << " minutos" << endl;
            this->tempo = 0;
            return true;
        }
        cout << "conseguiu dirigir " << this->tempo << " minutos" << endl;
        this->tempo -= tempo;
    }

    friend ostream& operator<<(ostream& os, const Motoca& m) {
        os << "T: " << m.tempo << " P: " << m.potencia;
        os << "[" << (m.pessoa == nullptr ? "vazio" : m.pessoa->nome) << "]";
        return os;
    }
};

int main() {
    Motoca motoca(1);
    while (true) {
        string line;
        getline(cin, line);
        stringstream ss(line);
        string cmd;
        ss >> cmd;
        if (cmd == "end") {
            break;
        } else if (cmd == "init") {
            int pot = 0;
            ss >> pot;
            motoca = Motoca(pot);
        } else if (cmd == "show") {
            cout << motoca << "\n";
        } else if (cmd == "inserir") {
            string nome {};
            int idade {};
            ss >> nome >> idade;
            Pessoa * pessoa = new Pessoa(nome, idade);  
            if(!motoca.inserirPessoa(pessoa))
                delete pessoa;
        } else if (cmd == "retirar") {
            Pessoa* pessoa = motoca.removerPessoa();
            if (pessoa != nullptr) {
                delete pessoa; 
            }
        } else {
            cout << "Comando nao existe\n";
        }
    }
}
