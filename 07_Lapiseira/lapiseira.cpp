#include <iostream>
#include <algorithm>

using namespace std;

struct Grafite {
  float calibre {0.0};
  string dureza {"HB"};
  int tamanho {0};
  
  Grafite(float calibre = 0, string dureza = "", int tamanho = 0):
  calibre{calibre}, dureza{dureza}, tamanho{tamanho} {

  }

  friend ostream& operator<<(ostream& os, const Grafite& grafite){
    os << "Calibre: " << grafite.calibre << "mm. ";
    os << "Dureza: " << grafite.dureza << ". ";
    os << "Tamanho: " << grafite.tamanho << "mm\n ";
    return os;
  }

}; 

struct Lapiseira {
  float calibre;
  Grafite* grafite;
  Lapiseira(float calibre, Grafite* grafite = nullptr):
     calibre{calibre}, grafite{grafite} {

  }
  
  bool inserirGrafite(Grafite* grafite){
    if(this->grafite != nullptr){
      cout << "Ja tem grafite \n";
      return false;
    }
      if(grafite->calibre != this->calibre){
        cout << "Calibre incompativel\n";
        return false;
      }
      this->grafite = grafite;
      return true;
  }
  
  Grafite* removerGrafite(){
    if(this->grafite == nullptr){
      cout << "Nao tem grafite\n";
      return nullptr;
    }
    return exchange(this->grafite, nullptr);
  }
};

int main(){
  Grafite grafite(0.5, "HC", 10);

  Lapiseira lapiseira(0.5, &grafite);
  lapiseira.grafite->tamanho -= 5; 

  cout << grafite.tamanho << endl;
  cout << lapiseira.grafite->tamanho << endl;

  return 0;
}