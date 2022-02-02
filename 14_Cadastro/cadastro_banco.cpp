#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>


using namespace std;

class Conta {
protected:
    int id;
    string clienteId;
    float balanco{0.00};
    string tipo{""}; // Corrente ou Poupança
public:
    Conta(int id = 0, string clienteId = "") : id(id), clienteId(clienteId) {};
   
    int getId() {
        return id;
    }

    float getBalanco() const {
        return balanco;
    }
    string getTipo() const {
        return tipo;
    }
    string getClienteId() const {
        return clienteId;
    }

    virtual void deposito (float valor) {
        balanco += valor;
}

    virtual void atualizacaoMensal () {}

    virtual void transferencia (Conta &destino, float valor) {
        balanco -= valor;
        destino.balanco += valor;
}

    friend ostream& operator<<(ostream& os, Conta* conta) {
        os << conta->getId() << ":" << conta->getClienteId() << ":";
        os << conta->getBalanco() << ":" << conta->getTipo() << endl;
        return os;
    }
};

class ContaCorrente : public Conta {
public:
    ContaCorrente(int id = 0, string clienteId = "") : Conta(id, clienteId) {
        tipo = "Corrente";
    }
    
    virtual void atualizacaoMensal(){
        balanco -= 20;
    } 

}; 

class ContaPoupanca : public Conta {
public:
    ContaPoupanca(int id = 0, string clienteId = "") : Conta(id, clienteId) {
        tipo = "Poupança";
    }
    virtual void atualizacaoMensal(){
        balanco += balanco * 0.01;
    }

};

class Cliente {
private:
    string clienteId;
    vector<shared_ptr<Conta>> conta;
public:
    Cliente(string clienteId = "", int id = 0) : clienteId{clienteId} {
        this->adicionaConta(make_shared<ContaCorrente>(id, clienteId));
        this->adicionaConta(make_shared<ContaPoupanca>((id + 1), clienteId));    
    }
    void adicionaConta(shared_ptr<Conta> conta){
        this->conta.push_back(conta);
    }

    friend ostream& operator<<(ostream& os, const Cliente* cliente) {
        os << cliente->clienteId << ":" << endl;
        for (auto conta : cliente->conta) {
            os << conta << endl;
        }
        return os;
    }

    vector<shared_ptr<Conta>> getContas() const {
        return conta;
    }

    string getCliente() const {
        return clienteId;
    }

    void setConta(shared_ptr<Conta> conta) {
        this->conta.push_back(conta);
    }

    void setClienteId(string clienteId) {
        this->clienteId = clienteId;
    }

};

class Banco {
    map<string, shared_ptr<Cliente>> clientes;
    map<int, shared_ptr<Conta>> conta;

    Conta* getConta(int id) {
        return this->conta[id].get();
    }

    void existe(int conta) {
        if ((int) this->conta.size() <= conta)
            throw invalid_argument("Conta não existe");
        }
    
public:
    Banco() {};

    void adicionaCliente(string clienteId) {
        for(auto conta : clientes) {
            if(conta.first == clienteId) {
                throw invalid_argument("Conta já existe");
            }
        }
        
        clientes.insert(pair<string, shared_ptr<Cliente>>(clienteId, make_shared<Cliente>(clienteId)));

    }
    
    void deposito(int idConta, float valor) {
        auto conta = getConta(idConta);
        if(conta == nullptr) {
            throw invalid_argument("Conta não existe");
        } else {
            conta->deposito(valor);
        }
    }

    void atualizacaoMensal() {
        for (auto conta : conta) {
            conta.second->atualizacaoMensal();
        }
    }

    void transferencia(int idOrigem, int idDestino, float valor) {
        existe(idOrigem);
        existe(idDestino);
        auto conta = getConta(idOrigem);

        conta->transferencia( *(this->conta[idDestino]), valor);
    }

    void saque(int id, float valor) {
        existe(id);
        auto conta = getConta(id);

        conta->transferencia( *(this->conta[id]), valor);

    }

    friend ostream& operator<<(ostream& os, const Banco* banco) {
        os << "Clientes: " << endl;
        for (auto cliente : banco->clientes) {
            os << "-" << (cliente.second) << endl;
        }
            os << "Contas: " << endl;
        for (auto conta : banco->conta) {
            int{0};
            os << (conta.second) << endl;
        }
        return os;
    }
};


int main() {
    Banco* banco = new Banco();

     while (true){
        string line, cmd;
        cin >> cmd;
        getline(cin, line);
        stringstream ss(line);

     try {
         if (cmd == "adicionaConta") {
            string tipo;
            string clienteId;
            int id;
            ss >> clienteId >> id;
        } else if (cmd == "adicionaCliente") {
            string clienteId;
            ss >> clienteId;
            banco->adicionaCliente(clienteId);
        } else if (cmd == "deposito") {
            int idConta;
            float valor;
            ss >> idConta >> valor;
            banco->deposito(idConta, valor);
        } else if (cmd == "atualizacaoMensal") {
            banco->atualizacaoMensal();
        } else if (cmd == "transferencia") {
            int idOrigem, idDestino;
            float valor;
            ss >> idOrigem >> idDestino >> valor;
            banco->transferencia(idOrigem, idDestino, valor);
        } else if (cmd == "saque") {
            int id;
            float valor;
            ss >> id >> valor;
            banco->saque(id, valor);
        } else if (cmd == "fim") {
            break;
        } else {
            throw invalid_argument("Comando inválido");
        }
    } catch (invalid_argument& e) {
        cout << e.what() << endl;
    }
}

    delete banco;

    return 0;
}

       