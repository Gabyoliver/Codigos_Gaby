#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

class Conta {
protected:
    int id;
    string clienteId;
    float balanco{0.00};
    string tipo{""}; // Corrente ou Poupança
public:
    Conta(int id, string clienteId) : id(id), clienteId(clienteId) {};

    float getBalanco() const {
        return balanco;
    }

    string getClienteId() const {
        return clienteId;
    }

    int getId() {
        return id;
    }

    string getTipo() const {
        return tipo;
    }

    virtual void depositar(float valor) {
        balanco += valor;
    }

    virtual void monthlyUpdate() {}

    virtual void transferir(Conta &conta, float valor) {
        if(valor > balanco) {
            throw invalid_argument("Saldo insuficiente");
        }
        balanco -= valor;
        conta.depositar(valor);
    }

    virtual void sacar(float valor) {
        if(valor > balanco) {
            throw invalid_argument("Saldo insuficiente");
        }
        balanco -= valor;
    }

    friend ostream& operator<<(ostream& os, Conta* conta) {
        os << conta->getId() << " : " << conta->getClienteId() << " : "; 
        os << fixed << setprecision(2) << conta->getBalanco();
        os << " : " << conta->getTipo() << endl;
        return os;
    }
};
    class ContaPoupanca : public Conta {
    public:
        ContaPoupanca(int id, string clienteId) : Conta(id, clienteId) {
            tipo = "Poupança";
        }

        virtual void monthlyUpdate() {
            balanco += balanco * 0.01;
        }
    };

    class ContaCorrente : public Conta {
    public:
        ContaCorrente(int id, string clienteId) : Conta(id, clienteId) {
            tipo = "Corrente";
        }

        virtual void monthlyUpdate() {
            balanco -= 20;
        }
    };

    class Cliente {
        vector<shared_ptr<Conta>> contas;
        string clienteId;
    public:
        Cliente(string clienteId = "", int id = 0) : clienteId(clienteId) {

            this->addConta(shared_ptr<Conta>(new ContaCorrente(id, clienteId)));
            this->addConta(shared_ptr<Conta>(new ContaPoupanca(id, clienteId)));
    }

    void addConta(shared_ptr<Conta> conta) {
        contas.push_back(conta);
    }

    friend ostream& operator<<(ostream& os, Cliente* cliente) {
       auto contas = cliente->getConta();
       os << cliente->clienteId << "[" << endl;
         for(int i = 0; i < (int) contas.size(); i++) {
             if(i != (int) contas.size() - 1)
                 os << contas[i]->getId() << ", ";
              else 
                 os << contas[i]->getId() << "]" << endl;
             }
            return os;
        }

    vector<shared_ptr<Conta>> getConta() const {
        return contas;
    }

    string getClienteId() const {
        return clienteId;
    }

    void setConta(vector<shared_ptr<Conta>> contas) {
        this->contas = contas;
    }

    void setClienteId(string clienteId) {
        this->clienteId = clienteId;
    }
}; 

    class Banco {
       map<int, shared_ptr<Conta>> contas;
       map<string, shared_ptr<Cliente>> clientes;

       Conta* getConta(int id) {
           return this->contas[id].get();
       }

       void existeConta(int id) {
           if(this->contas.find(id) == this->contas.end()) 
               throw invalid_argument("Conta não existe");
        }
public:
    Banco() {};

    void addConta(string clienteId){
        for(auto conta : clientes) {
            if(conta.first == clienteId)
                throw invalid_argument("Conta já existe");
        }

        int size {(int) contas.size()};

        auto cliente {make_shared<Cliente>(clienteId, size)};
        clientes.insert({clienteId, cliente});

        auto contas = cliente->getConta();
        for(int i{0}; i < (int) contas.size(); i++) {
            this->contas.insert({contas[i]->getId(), contas[i]});
            size++;
        }
    }
    
    void depositar(int id, float valor) {
        auto conta = getConta(id);
        if((int)this->contas.size() <= id)
            throw invalid_argument("Conta não existe");
        else
            conta->depositar(valor);
    }

    void monthlyUpdate() {
        for(auto conta : contas) {
            conta.second->monthlyUpdate();
        }
    }

    void transferir(int contaOrigem, int contaDestino, float valor) {
        existeConta(contaOrigem);
        existeConta(contaDestino);
        auto conta = getConta(contaOrigem);
        
        conta->transferir(*getConta(contaDestino), valor);
    }

    void sacar(int id, float valor) {
        existeConta(id);
        auto conta = getConta(id);

        conta->sacar(valor);
    }

    friend ostream& operator<<(ostream& os, Banco* banco) {
        os << "Clientes: " << endl;

        for(auto cliente : banco->clientes) {
            os << cliente.second << endl;
        }

        os << "Contas: " << endl;

        for(auto conta : banco->contas) {
            os << conta.second << endl;
        }
        return os;
    }
};

int main() {
    Banco* banco = new Banco();
    while (true){
        string cmd;
        cin >> cmd;
        if (cmd == "add"){
            string clienteId;
            cin >> clienteId;
            banco->addConta(clienteId);
        }
        else if (cmd == "depositar"){
            int id;
            float valor;
            cin >> id >> valor;
            banco->depositar(id, valor);
        }
        else if (cmd == "transferir"){
            int contaOrigem, contaDestino;
            float valor;
            cin >> contaOrigem >> contaDestino >> valor;
            banco->transferir(contaOrigem, contaDestino, valor);
        }
        else if (cmd == "sacar"){
            int id;
            float valor;
            cin >> id >> valor;
            banco->sacar(id, valor);
        }
        else if (cmd == "monthlyUpdate"){
            banco->monthlyUpdate();
        }
        else if (cmd == "show"){
            cout << banco << endl;
        }
        else if (cmd == "exit"){
            break;
        }
        else{
            cout << "Comando inválido" << endl;
        }
    }
    delete banco;
    return 0;
}
