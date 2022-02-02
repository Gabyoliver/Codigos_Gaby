#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Pessoa {
    private:
        string nome;
        int idade;

    public:
        Pessoa(string nome, int idade) {
            this->nome = nome;
            this->idade = idade;
        }

        string getNome() {
            return nome;
        }

        int getIdade() {
            return idade;
        }

    friend ostream& operator<<(ostream& os, Pessoa& pessoa) {
        os << pessoa.nome << " " << pessoa.idade;
        return os;
    }
};

class Agenda {
    private:
        vector<Pessoa> pessoas;

        int procurarPessoa(string nome) {
            for (int i = 0; i < (int)pessoas.size(); i++) {
                if (pessoas[i].getNome() == nome) {
                    return i;
                }
            }
            return -1;
        }

    public:
        Agenda () {}
        void addPessoa(Pessoa pessoa) {
            this->pessoas.push_back(pessoa);
            sort(pessoas.begin(), pessoas.end(), [](Pessoa p1, Pessoa p2) {
                if(p1.getNome() < p2.getNome()) {
                return p1.getNome() < p2.getNome();
                } else {
                return p1.getIdade() < p2.getIdade();
            }
        });
    }

    Pessoa* getPessoa(string nome) {
        int index = procurarPessoa(nome);
        if (index != -1) {
            return &pessoas[index];
        }
        return nullptr;
    }

    void removePessoa(string nome) {
        int index = procurarPessoa(nome);
        if (index != -1) {
            pessoas.erase(pessoas.begin() + index);
        return;
        }
    }

    vector <Pessoa> search (string nome) {
        vector <Pessoa> result;
        for (int i = 0; i < (int)pessoas.size(); i++) {
            if (pessoas[i].getNome().find(nome) != string::npos) {
                result.push_back(pessoas[i]);
            }
        }
        return result;
    }

    friend ostream& operator<<(ostream& os, Agenda& agenda) {
        for (int i = 0; i < (int)agenda.pessoas.size(); i++) {
            os << agenda.pessoas[i] << endl;
        }
        return os;
    }
};

int main() {
    Agenda agenda;
    Pessoa pessoa1("Joao", 20);
    Pessoa pessoa2("Maria", 25);
    Pessoa pessoa3("Jose", 30);
    Pessoa pessoa4("Pedro", 40);

    agenda.addPessoa(pessoa1);
    agenda.addPessoa(pessoa2);
    agenda.addPessoa(pessoa3);
    agenda.addPessoa(pessoa4);

    cout << agenda << endl;

    Pessoa* pessoa = agenda.getPessoa("Jose");
    if (pessoa != nullptr) {
        cout << "Pessoa encontrada: " << *pessoa << endl;
    } else {
        cout << "Pessoa nao encontrada" << endl;
    }

    agenda.removePessoa("Maria");
    cout << agenda << endl;

    vector <Pessoa> result = agenda.search("a");
    for (int i = 0; i < (int)result.size(); i++) {
        cout << result[i] << endl;
    }

    return 0;
    
}
    