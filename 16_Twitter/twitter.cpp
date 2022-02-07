#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <sstream>

using namespace std;

class Tweet {
    int id;
    string nome;
    string msg;
    set<string> likes;
public:
    Tweet(int id, string nome, string msg) : id(id), nome(nome), msg(msg) {}

    int getId() const {
        return id;
    }

    void Like(const string nome) {
         likes.insert(nome); 
    }

    friend ostream& operator<<(ostream& os, const Tweet& tweet) {
        os  << tweet.id << " : " << tweet.nome << "(" << tweet.msg << ")";

        if(!tweet.likes.empty()) {
            os << " [ ";
            for(const auto& like : tweet.likes) {
                os << like << " ";
            }
            os << "]";
        }
        return os;
    }
};

class Inbox {
public:
    map<int, Tweet*> alltweets;
    map<int, Tweet*> unread;
public:
    Inbox() {}

    void Add(Tweet* tweet) {
        alltweets[tweet->getId()] = tweet;
        unread[tweet->getId()] = tweet;
    }

    void lidas(Tweet* msg) {
        alltweets.insert(pair<int, Tweet*>(msg->getId(), msg));
    }

    vector<Tweet*> getnaolidas() {
        vector<Tweet*> msgnaolidas;
        for(auto& tweet : unread) {
            msgnaolidas.push_back(tweet.second);
            alltweets.insert(pair<int, Tweet*>(tweet.first, tweet.second));
        }
        unread.clear();
        return msgnaolidas;
    }

    vector<Tweet*> getAll() {
        vector<Tweet*> alltweetsvector;
        for(auto& tweet : alltweets) {
            alltweetsvector.push_back(tweet.second);
        }
        return alltweetsvector;
    }

    Tweet* getTweet(int id) {
        auto it = alltweets.find(id);
        if(it == alltweets.end()) {
           throw "Tweet não encontrado";
        }
        return it->second; 
    }

    void toString() {
        for(auto& tweet : this->getnaolidas()) {
            cout << *tweet << endl;
        }

        if(this->getnaolidas().empty()) {
            for(auto& tweet : this->getAll()) {
                cout << *tweet << endl;
            }
        }

        cout << endl;
    }
};

class Usuario{
    string nome;
    Inbox inbox;
    map<string, Usuario*> seguidores;
    map<string, Usuario*> seguindo;
public:
    Usuario(string nome) : nome(nome) {}

    void seguir(Usuario* other) {
        if(seguindo.find(other->nome) == seguindo.end()) {
            seguindo.insert(pair<string, Usuario*>(other->nome, other));
            other->seguidores.insert(pair<string, Usuario*>(nome, this));
        }
    }

    void deixarDeSeguir(string nome) {
      auto it = seguindo.find(nome);
      if(it == seguindo.end()) {
        throw runtime_error("Usuário não existe");
      }
      auto it2 = seguidores.find(nome);
      it->second->seguidores.erase(it2);
        seguindo.erase(it); 
    }

    void like(int twId) {
       Tweet* tweet = inbox.getTweet(twId);
       if(tweet == nullptr) {
           throw runtime_error("Tweet não existe");
       }
         tweet->Like(nome); 
    }

    Inbox& getInbox() {
        return inbox;
    }

    void sendTweet(Tweet* tweet) {
        inbox.Add(tweet);
        for(auto& seguidor : seguidores) {
            seguidor.second->getInbox().Add(tweet);
        }
    }

    void toString() {
        cout << nome << endl;
        cout << " seguidos: [" << endl;
        for(auto& seguindo : seguindo) {
            cout << seguindo.first << " " << endl;
        }
        cout << "]" << endl;

        cout << " seguidores: [ " << endl;
        for(auto& seguidores : seguidores) {
            cout << seguidores.first << " " << endl;
        }
        cout << "]" << endl;
    }
};

class Controller {
    map<string, shared_ptr<Usuario>> usuarios;
    map<int, shared_ptr<Tweet>> tweets;
    int nextTweetId = 0;

    Tweet* createTweet(string nome, string msg) {
        Tweet* tweet = new Tweet(nextTweetId, nome, msg);
        tweets.insert(pair<int, shared_ptr<Tweet>>(nextTweetId, shared_ptr<Tweet>(tweet)));
        nextTweetId++;
        return tweet;
    }

public:
    Controller() {}

    void addUsuario(string nome) {
        if(usuarios.find(nome) != usuarios.end()) {
            throw runtime_error("Usuário já existe");
        }
        usuarios.insert(pair<string, shared_ptr<Usuario>>(nome, make_shared<Usuario>(nome)));
    }

    Usuario* getUsuario(string nome) {
        auto it = usuarios.find(nome);
        if(it == usuarios.end()) {
            throw runtime_error("Usuário não existe");
        }
        return it->second.get();
    }

    void sendTweet(string nome, string msg) {
        Usuario* usuario = getUsuario(nome);
        Tweet* tweet = new Tweet(nextTweetId, nome, msg);
        usuario->sendTweet(tweet);
    }

    void toString() {
        for(auto& usuario : usuarios) {
            usuario.second->toString();
        }
        cout << endl;
    }
};

int main() {
    try {
        Controller controller;

        cout << "addUsuario" << endl;

        controller.addUsuario("joao");
        controller.addUsuario("maria");
        controller.addUsuario("pedro");
        
        controller.toString();

        cout << "sendTweet" << endl;

        controller.sendTweet("joao", "oi");
        controller.sendTweet("maria", "tudo bem?");
        controller.sendTweet("pedro", "como vai?");

        controller.toString();

        cout << "seguir" << endl;
        
        controller.getUsuario("joao")->seguir(controller.getUsuario("maria"));
        controller.getUsuario("maria")->seguir(controller.getUsuario("pedro"));
        controller.getUsuario("pedro")->seguir(controller.getUsuario("joao"));

        controller.toString();

        cout << "like" << endl;

        controller.getUsuario("joao")->like(1);
        controller.getUsuario("maria")->like(2);
        controller.getUsuario("pedro")->like(3);

        controller.getUsuario("joao")->getInbox().toString();
        controller.getUsuario("maria")->getInbox().toString();
        controller.getUsuario("pedro")->getInbox().toString();

        controller.toString();

        cout << "deixarDeSeguir" << endl;

        controller.getUsuario("joao")->deixarDeSeguir("maria");
        controller.getUsuario("maria")->deixarDeSeguir("pedro");
        controller.getUsuario("pedro")->deixarDeSeguir("joao");

        controller.toString();

    } catch(exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}
