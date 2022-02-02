#include <iostream>
#include <vector>

using namespace std;

// CONJUNTOS

vector<int> exclusivos(vector<int> vet){
  
    vector<int> exclusivos;

for (int i = 0; i < (int) vet.size() - 1; i++){
  for(int x = 0 + 1; i < (int) vet.size(); x++){
    if(vet[i] == vet[x])
             x++;
  }

 }

 return vet;

}

vector<int> diferentes(vector<int> vet){
  
    vector<int> diferentes;

 for (int i = 0; i < (int) vet.size() - 1; i++)
       vet[i] = abs(vet[i]); 
   for (int i = 0; i < (int) vet.size() - 1; i++){
     for (int x = 0 + 1; i < (int) vet.size(); i++){
       if(vet[i] == vet[x])
              x++;
        }
     }
     
     return vet;
}

vector<int> abandonados(vector<int> vet){
  
  vector <int> abandonados;

  for (int i = 0; i < (int) vet.size() - 1; i++){
     for (int x = 0 + 1; i < (int) vet.size(); i++){
       if(vet[i] == vet[x])
               x++;
    }

  }

  return vet;

} 

int main () {
int exclusivos;
int diferentes;
int abandonados;
           
        cout << exclusivos << endl;
        cout << diferentes << endl;
        cout << abandonados << endl;

  return 0;
  
}