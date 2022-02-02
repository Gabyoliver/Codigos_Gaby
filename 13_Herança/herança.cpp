#include <iostream>

using namespace std;

class Animal {
public:
    bool animal_vivo;
protected:
    string marca {"animal"};
public:
        Animal() : animal_vivo(true) {
            cout << marca << "Animal criado" << endl;
        }
        
        friend ostream& operator<<(ostream& os, const Animal& animal) {
            os << animal.marca << ":" << (animal.animal_vivo ? "vivo" : "morto") << endl;
            return os;
        }

        bool estaVivo() {
            return animal_vivo;
        }

        virtual void comer() {
            cout << marca << " está comendo" << endl;
        }

        virtual void morrer() {
            animal_vivo = false;
        }

};

class Mamifero : public Animal {
private:
    string corPelo {"preto"};
protected:
    string tipoPelo {"cabelo"};
public:
        Mamifero() {
            cout << marca << "Mamifero criado" << endl;
        }

        ~Mamifero() {
        }

        virtual void comer() {
            cout << marca << "Mamifero comendo" << endl;
        }

        virtual void dormir() {
            cout << marca << "Mamifero dormindo" << endl;
        }

        virtual void morrer() {
            cout << marca << "Mamifero morreu" << endl;
        }

        bool estaVivo() {
            return estaVivo();
        }

        friend ostream& operator<<(ostream& os, const Mamifero& mamifero) {
            os << mamifero.marca << ":" << (mamifero.animal_vivo ? "vivo" : "morto") << endl;
            return os;
        }
};

class Cachorro : public Mamifero {
private:
    string raca {"cachorro"};
public:
        Cachorro() {
            cout << marca << "Cachorro criado" << endl;
        }

        ~Cachorro() {
        }

        void comer() {
            cout << marca << "Cachorro comendo" << endl;
        }

        void dormir() {
            cout << marca << "Cachorro dormindo" << endl;
        }

        void morrer() {
            animal_vivo = false;
            cout << marca << "Cachorro morreu" << endl;
        }

        bool estaVivo() {
            return animal_vivo;
        }

        friend ostream& operator<<(ostream& os, const Cachorro& cachorro) {
            os << cachorro.raca << ":" << (cachorro.animal_vivo ? "vivo" : "morto") << endl;
            return os;
        }
}; 

int main(){
    Animal animal;
    Mamifero mamifero;
    Cachorro cachorro;

    cout << animal << mamifero << cachorro << endl;

    animal.comer();
    mamifero.comer();
    cachorro.comer();

    animal.morrer();
    mamifero.morrer();
    cachorro.morrer();

    cout << animal << endl;
    
    return 0;
}