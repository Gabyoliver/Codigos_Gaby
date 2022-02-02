#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Pessoa {
public:
    string nome;
    int idade;

    Pessoa (std::string nome = "", int idade = 0) : nome(nome), idade(idade) {}
    friend std::ostream& operator<<(std::ostream& os, const Pessoa& p) {
        os << p.nome << ":" << p.idade;
        return os;
    }
};

class Sala {
    vector<Pessoa> cadeiras;
public:
    Sala(int n_cadeiras = 0) {
        for (int i = 0; i < n_cadeiras; i++) {
            cadeiras.push_back(Pessoa());
        }
    }

    void adicionaPessoa(Pessoa pessoa) {
        cadeiras.push_back(pessoa);
    }

    void removePessoa() {
        cadeiras.pop_back();
    }

    int getNumeroPessoas() {
        return cadeiras.size();
    }

    friend std::ostream& operator<<(std::ostream& os, const Sala& s) {
        os << "Sala: " << s.cadeiras.size() << " pessoas" << endl;
        for (auto pessoa : s.cadeiras) {
            os << pessoa << endl;
        }
        return os;
    }

    bool temLugar() {
        return cadeiras.size() < cadeiras.capacity();
    }

    bool temPessoa() {
        return cadeiras.size() > 0;
    }
};

    int main(){
        Sala sala(1);
        sala.adicionaPessoa(Pessoa("Gaby", 20));
        sala.adicionaPessoa(Pessoa("Livia", 25));
        sala.adicionaPessoa(Pessoa("Joelson", 30));
        sala.adicionaPessoa(Pessoa("Cut cut", 35));
        sala.adicionaPessoa(Pessoa("Damon", 40));
        sala.adicionaPessoa(Pessoa("Stefan", 45));
        sala.adicionaPessoa(Pessoa("Elena", 50));
        sala.adicionaPessoa(Pessoa("Caroline", 55));
        sala.adicionaPessoa(Pessoa("Gustavo", 55));
        
        cout << sala << endl;

        sala.removePessoa();
        cout << sala << endl;

        return 0;
    }