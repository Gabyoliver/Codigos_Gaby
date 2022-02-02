#include <iostream>
#include <vector>

using namespace std;

//OPERAÇÕES COM FILTRAGEM

vector<int> clonar(vector<int> vet) {

    vector<int> clone;

    for (int i = 0; i < (int) vet.size(); i++){
      clone.push_back(vet[i]);
    }

    return clone;
    
}
vector<int> pegar_homens(vector<int> vet) {

    vector<int> homens;
    for (int i = 0; i < (int) vet.size(); i++){
      if(vet[i] > 0)
      homens.push_back(vet[i]);
    }
      return homens;
}

vector<int> pegar_calmos(vector<int> vet){
  
    vector<int> calmos;

    for (int i = 0; i < (int) vet.size(); i++){
      if(abs(vet[i]) < 10)
      calmos.push_back(vet[i]);
    }
    return calmos;
}

vector<int> pegar_mulheres_calmas(vector<int> vet) {

    vector<int> mulheres_calmas;

    for (int i = 0; i < (int) vet.size(); i++){
      if(vet[i] < 0)
      if(vet[i] >- 10)
      mulheres_calmas.push_back(vet[i]);
    }
      return mulheres_calmas;
}

int main () {
int clone;
int homens;
int calmos;
int mulheres_calmas;
           
        cout << clone  << endl;
        cout << homens  << endl;
        cout << calmos  << endl;
        cout << mulheres_calmas << endl;

    return 0;

}