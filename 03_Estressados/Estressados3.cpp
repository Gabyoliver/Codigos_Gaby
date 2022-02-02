#include <iostream>
#include <vector>

using namespace std;

//Alteração

int remove(vector<int> vet, int pessoa){

  int i = 0;

for(int i = 0; i < (int) vet.size(); i++){
       if(vet[i] == pessoa){
               i++;
       }
  }
}

int insert(vector<int> vet, int pessoa, int posição){

       vector <int> inserir;

for(int i = 0; i < (int) vet.size(); i++){
  
       if(vet[i] == posição){
  
       inserir.push_back(pessoa);
       inserir.push_back(vet[i]);
    }
  }
}

int dance(vector<int> vet){

  int cont = 1;

for(int i = 0; i < (int) vet.size(); i++){
  if(abs(vet[i]) == abs(vet[i + 1])){
    i--;
    cont++;
  }
}
}

int main(){
 
 int remove;
 int insert;
 int dance;
      
      cout << remove << endl;
      cout << insert << endl;
      cout << dance << endl;

 return 0;

}