#include <iostream>
#include <vector>

using namespace std;

//ACESSO

vector<int> inverter_com_copia(vector<int> vet){
   
	vector<int> inverter;
    
     for (int i = (int) vet.size() - 1; i >= 0; i--){
        inverter.push_back(vet[i]);
  }
       
  return inverter;
  
}

vector<int> inverter_inplace(vector<int> vet){

     vector<int> invertido;

int aux;
int valor_f = 0;
  
  for (int i = (int) vet.size(); i--;){
    for (int j = (int) vet.size(); j--;){
      valor_f = vet[i];
         vet[i] = aux;
      if (i == 0) invertido[0] = valor_f; 

    }
        
  }

return invertido;

}

int sortear(vector<int>& vet){

  int valor = rand()%(vet.size()+1);

  return vet[valor];

}

vector<int> embaralhar(vector<int> vet){
   
    vector<int> vetor;

    for (int i = 0; i < vet.size(); i++){
		int j = rand() % vet.size();
		int temp = vet[i];
		vet[i] = vet[j];
		vet[j] = temp;
	}
  
  return vet;
  
}

vector<int> ordenar(vector<int> vet){

   vector<int> ordenar_vetor;

int aux;

for (int i = 0; i < ordenar_vetor.size(); i++){
  if (ordenar_vetor[i] > ordenar_vetor[i + 1]){
        ordenar_vetor[i] = ordenar_vetor[i + 1];
            ordenar_vetor[i + 1] = aux;
    }

  }
    
  return ordenar_vetor;
  
}

int main(){
  int inverter;
  int inverter_inplace;
  int sortear;
  int embaralhar;
  int ordenar_vetor;

  cout << inverter << endl;
  cout << inverter_inplace << endl;
  cout << sortear << endl;
  cout << embaralhar << endl;
  cout << ordenar_vetor << endl;

	return 0;
}