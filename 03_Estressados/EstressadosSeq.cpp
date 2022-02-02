#include <iostream>
#include <vector>

using namespace std;

//Sequências

int times(vector<int> vet){

int qtdtimes = 0;
int cont = 0;
int contador = 0;

for(int i = 0; i < (int) vet.size(); i++){
   
        if(vet[i] < 0){
         contador++;
         cont--;
        if(vet[i] > 0){
         contador++;
         cont++;
      }
    }
  }
  
  return contador;
}

int maiortime(vector<int> vet){

  int contador = 1;
  int cont = 0;
  int maior = 0;

for(int i = 0; i < (int) vet.size(); i++){
         if(vet[i] < 0){
           contador++;
         if(vet[i] > 0){
           contador++;
        maior = max(maior,contador);
      }
    }
  }

return maior;
}

int sozinho(vector<int> vet){

  int qtdsozinhos = 0;
  int contador = 0;
  int cont = 0;

for(int i = 0; i < (int) vet.size(); i++){
 
        if(vet[i] > 0){
          cont = 10;
        if(vet[i] < 0){
          cont = -10;
        if(i == 0) {
        if(vet[i + 1] > 0 and vet[i] <0)
                contador++;
        if(vet[i + 1] < 0 and vet[i] > 0)
                contador++;
        }
      }
    }
  }

 return contador;
}

void imprimirVetor(vector<int> vetor) {
  for (int i = 0; i < vetor.size(); i++) {
     cout << vetor[i] << endl;
  }
}

int main(){

int qtdtimes = times({28, 26, 1, 6, 39});
      cout << times << endl;
  
int maior = maiortime({-5, 3, -1, 15, 1, -99, 11, 1});
      cout << maior << endl;

int qtdsozinhos = sozinho({-5, -3, -1, -15, -1, -99, -11, -1, -7});
      cout << qtdsozinhos << endl;


 return 0;

}