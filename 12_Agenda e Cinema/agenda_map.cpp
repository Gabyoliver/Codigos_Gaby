#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

class Fone {
    private:
        string id;
        string numero;
    
    public:
      Fone(string id, string numero) : id{id}, numero{numero}{}

      friend ostream &operator<<(ostream& os, const Fone& fone){
            
            os << fone.getId() << ":" << fone.getNumero();

            return os;

        }

        static bool validate(string numero){
            for(int i = 0; i < (int) numero.length(); i++){
                if((numero[i] < 48  && numero[i] != 40 && numero[i] != 41 && numero[i] != 46) || numero[i] > 57){
                    return false;
                }
            }

            return true;
        }

        string getId() const{
            return this->id;
        }

        string getNumero() const{
            return this->numero;
        }

        void setId(string id){
            this->id = id;
        }

        void setNumero(string numero){
            this->numero = numero;
        }


};


class Contato{
    private:
        string nome;
        vector<Fone> fones;

    protected:
        string prefixo = "-";

    public:
        Contato(){

        }

        Contato(string nome, vector<Fone> fones) : nome{nome}, fones{fones} {}

        friend ostream &operator<<(ostream& os, Contato& contato){
            os << contato.prefixo << " " << contato.nome;

            if(!contato.fones.empty()){
                for(int i = 0; i < (int) contato.fones.size(); i++){
                    os << " [" << i << ":" << contato.fones[i] << "]";
                }
            }

            return os;
        }

        string getNome(){
            return this->nome;
        }

        vector<Fone> getFones(){
            return this->fones;
        }
        
        void setNome(string nome){
            this->nome = nome;
        }

        void addFone(Fone fone){
            if(Fone::validate(fone.getNumero())){
                this->fones.push_back(fone);
            }else{
                cout << "Numero invalido" << endl;
            }
        }

        void rmFone(int id){
            if(this->fones.empty()){
                cout << "Sem telefones para remover" << endl;

            }else if(id < 0 || id > (int) this->fones.size() - 1){
                cout << "Id invalido" << endl;

            }else{
                this->fones.erase(this->fones.begin() + id);
            }
        }

};


class Agenda{
    private:
        std::map<std::string, Contato> contatos;
    
    public:
        Agenda(){

        }

        friend ostream& operator<<(ostream& os, Agenda agenda){
            for(auto contato : agenda.contatos){
                os << contato.second << '\n';
            }

            return os;
        }

        void addContato(Contato contato){
            auto it = contatos.find(contato.getNome());

            if(it != contatos.end()){
                for(Fone fone : contato.getFones()){
                    contatos[contato.getNome()].addFone(fone);
                }
                
            }else{
                if(contato.getFones().size() > 0){
                    contatos[contato.getNome()] = contato;
                }else{
                    cout << "Sem telefones" << endl;
                }
            }
        }

        Contato* getContato(string nome){
            auto it = contatos.find(nome);

            if(it != contatos.end()){
                return &it->second;
            }else{
                return nullptr;
            }
        }

        void rmContact(string nome){
            auto it = contatos.find(nome);

            if(it != contatos.end()){
                contatos.erase(it);
            }else{
                cout << "Contato nao encontrado" << endl;
            }
        }

        vector<Contato> search(string pattern){
            vector<Contato> result;

            for(auto& [id, contato] : this->contatos){
                stringstream ss;
                ss << contato << endl;

                string text = ss.str();

                if(text.find(pattern) != string::npos){
                    result.push_back(contato);
                }
            }

            return result;
        }

        map<string, Contato> getContatos(){
            return this->contatos;
        }
};

void controle(Agenda *agenda, string comando, string nome, string numero){
    if(comando == "add"){
        Contato contato(nome, vector<Fone>());
        contato.addFone(Fone(nome, numero));
        agenda->addContato(contato);
    }else if(comando == "rm"){
        agenda->rmContact(nome);
    }else if(comando == "search"){
        vector<Contato> result = agenda->search(nome);

        if(result.size() > 0){
            for(Contato contato : result){
                cout << contato << endl;
            }
        }else{
            cout << "Nenhum contato encontrado" << endl;
        }
    }else if(comando == "list"){
        cout << *agenda << endl;
    }
}

int main(){
    Agenda agenda;

    string comando;
    string nome;
    string numero;

    while(cin >> comando){
        if(comando == "end"){
            break;
        }

        cin >> nome;

        if(comando == "add" || comando == "rm" || comando == "search"){
            cin >> numero;
        }

        controle(&agenda, comando, nome, numero);
    }

    return 0;

}
    