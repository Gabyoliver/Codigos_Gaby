#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

struct Grafite {
    float calibre;
    string dureza;
    int tamanho;

    Grafite(float calibre=0, string dureza="", int tamanho=0) : calibre(calibre), dureza(dureza), tamanho(tamanho) {}

    friend ostream &operator<<(ostream &os, const Grafite &lapiseira) {
        os << "Grafite: " << lapiseira.calibre << ", " << lapiseira.dureza << ", " << lapiseira.tamanho << "." << endl;
        return os;
    }

    int desgastesfolha(){
        if(this->dureza == "HB"){ 
            return 1;
    }
        else if(this->dureza == "2B"){ 
            return 2;
    }
        else if(this->dureza == "4B"){ 
            return 4;
    }
        else if(this->dureza == "6B"){ 
            return 6;
    }
        else{ 
            return 0;
    }
}
};

struct Lapiseira{
    float calibre;
    vector<Grafite> grafite;

    Lapiseira(float calibre=0): calibre(calibre){}

    friend ostream &operator<<(ostream &os, const Lapiseira &lapiseira){
        os << "Calibre: " << lapiseira.calibre << "\n";
        if(lapiseira.grafite.empty()){ os << "Grafite: null\n"; }
        else{  
            for(int i=0; i<(int)lapiseira.grafite.size(); i++){
                os << lapiseira.grafite[i];
            }
        }
        return os;
    }

    bool inserir_grafite(Grafite &grafite){
        if(grafite.calibre != this->calibre){
            cout << "Calibre incompativel" << endl;
            return true;
        }
        if((int)this->grafite.size() == 4){
            cout << "Grafite completo" << endl;
            return true;
        }
        this->grafite.push_back(grafite);
        return true;
    }

    vector<Grafite> remover_grafite(int i){
        if(this->grafite.empty()){
            cout << "Grafite vazio" << endl;
            return this->grafite;
        }
        vector<Grafite> grafite_aux = this->grafite;
        this->grafite.erase(this->grafite.begin()+i);
        return grafite_aux;
    }

    void escreverfolhas(int folhas){
        int aux = 0;
        
        if(this->grafite.empty()){
            cout << "O grafite não foi inserido" << endl;
        }
        else{
            for(int i=0; i<(int)this->grafite.size(); i++){
                while(this->grafite[i].tamanho > 0 && folhas > 0){
                    this->grafite[i].tamanho -= this->grafite[i].desgastesfolha();
                    if(this->grafite[i].tamanho >= 0){
                        folhas--;
                        aux++;
                    }
                    if(this->grafite[i].tamanho <= 0){
                        this->grafite.erase(this->grafite.begin()+i);
                    }
                }
            }
            if(folhas > 0 && this->grafite.empty()){
                cout << "O grafite acabou" << endl;
                cout << "Folhas escritas: " << aux << endl;
            }
        }
    }
};

int main(){
    Lapiseira lapiseira;
    Grafite grafite;
    int opcao, folhas;
    float calibre;

    cout << "Insira o calibre da lapiseira: ";
    cin >> calibre;
    lapiseira.calibre = calibre;

    do{
        cout << "1 - Inserir grafite\n2 - Remover grafite\n3 - Escrever folhas\n4 - Sair\n";
        cin >> opcao;
        switch(opcao){
            case 1:
                cout << "Insira o calibre do grafite: ";
                cin >> calibre;
                grafite.calibre = calibre;
                cout << "Insira a dureza do grafite: ";
                cin >> grafite.dureza;
                cout << "Insira o tamanho do grafite: ";
                cin >> grafite.tamanho;
                lapiseira.inserir_grafite(grafite);
                break;
            case 2:
                cout << "Insira o grafite a ser removido: ";
                cin >> calibre;
                lapiseira.remover_grafite(calibre);
                break;
            case 3:
                cout << "Insira a quantidade de folhas: ";
                cin >> folhas;
                lapiseira.escreverfolhas(folhas);
                break;
            case 4:
                break;
            default:
                cout << "Opcao invalida" << endl;
        }

    }while(opcao != 4);

    return 0;
}