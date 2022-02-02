#include <iostream>
#include <vector>

using namespace std;

//Proximidade

int numerobrigas(vector<int> vet){

int brigas = 0;

for(int i = 0; i < (int) vet.size(); i++){
       if(abs(vet[i]) > 50 && abs(vet[i + 1]) > 30 && abs(vet[i - 1]) > 30){
                    brigas++;
  }

}

 return brigas;
 
}

vector<int> apaziguados(vector<int> vet){
        
        vector<int> apaziguado;

for(int i = 0; i < (int) vet.size(); i++){
  if(abs(vet[i]) > 80 && abs(vet[i + 1]) > 10 && abs(vet[i - 1]) > 10){
        
 }

}

return apaziguado;

}

void mostrarVetor(vector<int> vet){
  for (int i = 0; i < vet.size(); i++) {
       cout << vet[i] << endl;
  }
}

int main(){
  
int brigas = numerobrigas({50, 98, 31, -51, 31, -99});
      cout << brigas << endl;

vector<int> apaziguado({83, -4, 65, 8, -99, 12});
      mostrarVetor(apaziguado);

 return 0;

}