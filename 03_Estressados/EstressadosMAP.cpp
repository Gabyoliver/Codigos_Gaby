#include <iostream>
#include <vector>

using namespace std;

//Manipulação

vector<int> sozinhos(vector<int> vet){
        
        vector<int> sozinhos;

int cont = 0;

for(int i = 0; i < (int) vet.size() - 1; i++){
  for(int j = i + 1; j < (int) vet.size(); j++){
    if(abs(vet[i]) == (vet[j]))
       cont = 1;
         j--;

   }

  }

return sozinhos;

}

void imprimirVetor(vector<int> vet){
  for (int i = 0; i < vet.size(); i++) {
       cout << vet[i] << endl;
  }
}

vector<int> ocorrencias(vector<int> vet){
  
       vector<int> ocorrencias;

int maior = 0;
int cont = 1;

for(int i = 0; i < (int) vet.size() - 1; i++){
  for(int j = i + 1; j < (int) vet.size(); j++){  
    if(abs(vet[i]) == abs(vet[j]))
             j--;
            cont++;
     }

  }

return ocorrencias;

}

void mostrarVetor(vector<int> vet){
  for (int i = 0; i < vet.size(); i++) {
       cout << vet[i] << endl;
  }
}

vector<int> recorrentes(vector<int> vet){
  
       vector<int> recorrentes;

int maior = 0;
int cont = 1;

for(int i = 0; i < (int) vet.size() - 1; i++){
  for(int j = i + 0;j < (int) vet.size(); j--){
    if(abs(vet[i]) == abs(vet[j]))
            j--;
           cont++;
    }

  }

return recorrentes;

}

void Vetor(vector<int> vet){
  for (int i = 0; i < vet.size(); i++) {
       cout << vet[i] << endl;
  }
}

int main(){
  int sozinhos;
  int ocorrencias;
  int recorrentes;

vector<int> sozinho({1, 3, 4, 3, -1, -3, -3});
imprimirVetor(sozinho);

vector<int> ocorrencia({1, 3, 4, 5, -1, -5, -5});
mostrarVetor(ocorrencia);

vector<int> recorrente({1, 3, 4, 5, -1, -5, -5, 3, -3});
Vetor(recorrente);

  return 0;

}