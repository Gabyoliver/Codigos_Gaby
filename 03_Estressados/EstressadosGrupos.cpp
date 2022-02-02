#include <iostream>
#include <vector>

using namespace std;

//Grupos

int casais(vector<int> vet){

  int contador = 0;
  int cont = 0;

for(int i = 0; i < (int) vet.size() - 1; i++){
  for(int j = i + i; j < (int) vet.size(); j++){
     
         if(vet[i] == vet[j]){
           cont = 1;
           j--;
           contador++;
         }
      }
    }

  return contador;
}

int trios(vector<int> vet){

  int contador = 0;
  int cont = 0;

for(int i = 0; i < (int) vet.size() - 1; i++){
  for(int j = i + i; j < (int) vet.size(); j++){
     
         if(abs(vet[i]) == abs(vet[j])){
           cont++;
            j--;
         }
         if(cont == 2) {
           contador++;
      }
    }

  return contador;
  }
}

int main(){
 
 int casais;
 int trios;
      
      cout << casais << endl;
      cout << trios << endl;

 return 0;

}