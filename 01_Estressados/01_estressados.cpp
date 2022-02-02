#include <iostream>
#include <vector>

using namespace std;

bool existe(vector<int> vet, int valor){
  for(int i = 0; i < (int) vet.size(); i++)
      if(vet[i] == valor)
        return true;
return false;         
}

int contar(int num){
int cont = 0;
    vector <int> vet{-1, 60, 54, 76, 80};
    for (int i = 0; i < (int) vet.size(); i++){
       if (vet [i] == num)
           cont++;
    }
      return cont;
}

int procura (vector<int> vet, int valor){
  for(int i = 0; i < (int) vet.size(); i++)
  if(vet[i] == valor)
      return 1;
return -1;

}

int num = 0;
int valor = 0;

int procurar_valor_apos (vector<int> vet, int num, int pos){
   for(int i = pos; i < (int) vet.size(); i++)
       if(vet[i] == num){
          vet[i] = pos;
       }
        return pos;
}

int procurar_menor_pos(vector<int> vet){
  
int pos = 0;

  for( int i = 0; i < (int) vet.size(); i++)
      if(vet[i] < vet[pos]){
             pos = i;
      }
        return pos;
}

int procurar_melhor_se (vector<int> vet){

int melhor = 0;

  for( int i = 0; i < (int) vet.size(); i++){
     if (vet[i] > 0)
      melhor = vet[i];
  }
       return melhor;
}

int menor = 0;

int procurar_menor(vector<int> vet){
  for(int i = 0; i < (int) vet.size(); i++){
    if(vet[i] < menor)
     menor = vet[i];
  }
    return menor; 
}  

int procurar_menor_pos_apartir(vector<int> vet){

  int menor = -99;
  int pos = 0;

  for( int i = pos ; i < (int) vet.size(); i++){
          if(vet[i] < menor)
             vet[i] = menor; 
          }
            return menor;
}

string mais_homens_ou_mulheres(vector<int> vet){

   int homens = 0;
   int mulheres = 0;

  for( int i = 0; i < (int) vet.size(); i++){
       if (vet[i] > 0)
         homens++;
        else mulheres++;
      }
       if (mulheres > homens) {

          return "mulheres";

      } else if (mulheres == homens) {
          
            return "iguais";
      } else if (mulheres < homens) {
          
            return "homens";
      }
}

 string mais_homens_ou_mulheres_stress(vector<int> vet) {
  
  int n1 = 0;
  int n2 = 0;

  for( int i = 0; i < (int) vet.size(); i++){
       if(vet[i] > 0)
        n1 = vet[i];
        else n2 = abs(vet[i]);

      }       
       if(n1 > n2) {
         
        return "segunda";

      } else if(n1 < n2) {
            
        return "primeira";

      } else if(n1 == n2) {
              
          return "iguais";  
      }
}

string homens_sao_mais_estressados_que_mulheres(vector<int> vet){
  
  int n1;
  int n2;
  int h;
  int m;
  
  for( int i = 0; i < (int) vet.size(); i++){
       if(vet[i] > 0){
       
        n1 = vet[i];
         h++;

} else {

        n2 = abs(vet[i]);
        m++;
    }
}
    n1 = n1/h;
    n2 = n2/m;

      if(n1 > n2) {
      
      return "sim";

    } else if(n1 < n2) {

      return "nao";

    } else if(n1 == n2) {

      return "iguais";

    }
}

float calcular_stress_medio(vector<int> vet){

  float media = 0;

     for( int i = 0; i < (int) vet.size(); i++){
          media = abs(vet[i]);         
}
          media = media/vet.size();
              return media;
}

int main(){
    vector<int> exemplo = {10,1,2,-5,-5,-5};
    for (int i = 0; i < (int)exemplo.size(); i++) 
          cout<<exemplo[i]<<" ";
}

