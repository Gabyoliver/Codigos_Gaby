#include <iostream>
#include <list>
#include <vector>
#include <memory>
#include <map>

using namespace std;

class Client{
    public:
        string id;
        int fone;

        Client(string id = "", int fone = 0) : id(id), fone(fone) {}

        friend ostream& operator<<(ostream& os, const Client& c){
            os << "Cliente: " << c.id << " - " << c.fone << endl;
            return os;
        }
};

class Cinema{
    map<int, shared_ptr <Client>> cadeiras;
public:
    Cinema(int quantidade_cadeiras){
        for(int i = 0; i < quantidade_cadeiras; i++){
            cadeiras[i] = nullptr;
        }
    }

    bool reserva(const shared_ptr<Client>& cliente, int numero_cadeiras){
        for(size_t i = 0; i < cadeiras.size(); i++){
            if(this->cadeiras[i] != nullptr && this->cadeiras[i]->id == cliente->id){
                cout << "Cliente ja esta reservando" << endl;
                return false;
            }
        }
        if(this->cadeiras[numero_cadeiras] != nullptr){
            cout << "Nao ha cadeiras disponiveis" << endl;
            return false;
        }
        if(this->cadeiras[numero_cadeiras] == nullptr){
            this->cadeiras[numero_cadeiras] = cliente;
            cout << "Reserva realizada com sucesso" << endl;
            return true;
        }
        return false;
    }

    bool cancelar(const shared_ptr<Client>& cliente, int numero_cadeiras){
        for(size_t i = 0; i < cadeiras.size(); i++){
            if(this->cadeiras[i] != nullptr && this->cadeiras[i]->id == cliente->id){
                this->cadeiras[numero_cadeiras] = nullptr;
                cout << "Reserva cancelada com sucesso" << endl;
                return true;
            }
        }
        cout << "Cliente nao esta reservando" << endl;
        return false;
    }

    friend ostream& operator<<(ostream& os, const Cinema& c){
        os << "[";
        for(size_t i = 0; i < c.cadeiras.size(); i++){
            auto cadeiras = c.cadeiras;
            os << " ";
            if(cadeiras[i] != nullptr){
                os << *(cadeiras[i]);
            }else{
                os << "-";    
            }
                os << " ";
        }
        os << "]" << endl;
        return os;
    }
};

    int main(){
        Cinema c(10);
        cout << c;

        shared_ptr<Client> cliente1(new Client("Joao", 123456789));
        shared_ptr<Client> cliente2(new Client("Maria", 987654321));
        shared_ptr<Client> cliente3(new Client("Jose", 987654321));
        c.reserva(cliente1, 1);
        c.reserva(cliente2, 2);
        c.reserva(cliente3, 3);
        c.cancelar(cliente1, 1);

        cout << c;
        return 0;
    }


