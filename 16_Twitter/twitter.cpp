#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <memory>
#include <stdexcept>
#include <sstream>
#include <iterator>

using namespace std;

class Tweet {
public:
    int id;
    string msg;
    string usuario;
    set<string>likes;
    Tweet *retweet;
public:
    Tweet(int id, string msg, string usuario) : id(id), msg(msg), usuario(usuario) {};

    int getId() {
        return id;
    }

    string getMsg() {
        return msg;
    }

    friend ostream& operator<<(ostream& os, const Tweet& t) {
        os << "Tweet: " << t.id << " - " << t.msg << " - " << t.usuario << endl;
        return os;
    }

    void like(string usuario) {
        likes.insert(usuario);
    }

    void setRetweet(Tweet *rt) {
        retweet = rt;
    }

    bool deleted{false};

    void setDeleted() {
        deleted = true;
    }

    bool isDeleted() {
        return deleted;
    }
};

class Inbox {
    map<int, Tweet*> timeline;
    map<int, Tweet*> myTweets;
public:
    void addTweet(Tweet *t) {
        timeline[t->getId()] = t;
    }
    
    vector<Tweet*> getTimeline() {
        vector<Tweet*> tweets;
        for (auto t : timeline) {
            tweets.push_back(t.second);
        }
        return tweets;
    }

    friend ostream& operator<<(ostream& os, const Inbox& i) {
        for (auto t : i.timeline) {
            os << *t.second << endl;
        }
        return os;
    }

    Tweet* getTweet(int id) {
        return timeline[id];
    }

    void removeTweet(string& nome) {
        for (auto t : timeline) {
            if (t.second->usuario == nome) {
                t.second->setDeleted();
            }
        }
    }

    void myTweet(Tweet *t) {
        myTweets[t->getId()] = t;
    }

    vector<Tweet*> getMyTweets() {
        vector<Tweet*> tweets;
        for (auto t : myTweets) {
            tweets.push_back(t.second);
        }
        return tweets;
    }
};

class Usuario {
    string nome;
    Inbox inbox;
    map<string, Usuario*> seguidores;
    map<string, Usuario*> seguindos;
public:
    Usuario (string nome) : nome(nome) {};

    friend ostream& operator<<(ostream& os, const Usuario& u) {
        os << u.nome << endl;
        os << u.inbox;
        return os;
    }

    void seguir(Usuario * other) {
        seguidores[other->nome] = other;
        other->seguindos[nome] = this;
    }

    Inbox& getInbox() {
        return inbox;
    }

    void tweet(Tweet *t) {
        inbox.addTweet(t);
        for (auto s : seguidores) {
            s.second->getInbox().addTweet(t);
        }
    }

    void deixarSeguir(string& nome) {
        seguidores.erase(nome);
        seguindos.erase(nome);
    }

    void like(int twId) {
        inbox.getTweet(twId)->like(nome);
    }

    void deixarSeguirAll();
    void rejectAll();
};

class Controle {
public:
    int nextTweetId { 0 };
    map<string, shared_ptr<Usuario>> usuarios;
    map<int, shared_ptr<Tweet>> tweets;
public:
    void addUsuario(string nome) {
        usuarios[nome] = make_shared<Usuario>(nome);
    }

    friend ostream& operator<<(ostream& os, const Controle& c) {
        for (auto u : c.usuarios) {
            os << *u.second << endl;
        }
        return os;
    }
private:
    Tweet* criarTweet(string nome, string msg) {
        Tweet *t = new Tweet(nextTweetId, msg, nome);
        tweets[nextTweetId] = make_shared<Tweet>(*t);
        nextTweetId++;
        return t;
    }
public:
    Usuario* getUsuario(string nome) {
        return usuarios[nome].get();
    }

    void tweet(string nome, string msg) {
        Usuario *u = getUsuario(nome);
        Tweet *t = criarTweet(nome, msg);
        u->tweet(t);
    }

    void retweet(string nome, int twId) {
        Usuario *u = getUsuario(nome);
        Tweet *t = u->getInbox().getTweet(twId);
        Tweet *rt = new Tweet(nextTweetId, t->getMsg(), nome);
        rt->setRetweet(t);
        tweets[nextTweetId] = make_shared<Tweet>(*rt);
        nextTweetId++;
        u->tweet(rt);
    }

    void removerUsuario(string nome) {
        usuarios.erase(nome);
    }
};

    int main () {
        Controle sistema;

        while(true) {
            try {
                string cmd;
                cin >> cmd;
                if (cmd == "addUsuario") {
                    string nome;
                    cin >> nome;
                    sistema.addUsuario(nome);
                } else if (cmd == "removerUsuario") {
                    sistema.removerUsuario(cmd);
                } else if (cmd == "seguir") {
                    string nome, nome2;
                    cin >> nome >> nome2;
                    sistema.getUsuario(nome)->seguir(sistema.getUsuario(nome2));
                } else if (cmd == "tweet") {
                    string nome, msg;
                    cin >> nome >> msg;
                    sistema.tweet(nome, msg);
                } else if (cmd == "retweet") {
                    string nome, nome2;
                    int twId;
                    cin >> nome >> nome2 >> twId;
                    sistema.retweet(nome, twId);
                } else if (cmd == "like") {
                    string nome;
                    int twId;
                    cin >> nome >> twId;
                    sistema.getUsuario(nome)->like(twId);
                } else if (cmd == "deixarSeguir") {
                    string nome, nome2;
                    cin >> nome >> nome2;
                    sistema.getUsuario(nome)->deixarSeguir(nome2);
                } else if (cmd == "show") {
                    cout << sistema << endl;
                } else if (cmd == "timeline") {
                    string nome;
                    cin >> nome;
                    cout << sistema.getUsuario(nome)->getInbox() << endl;
                } else if (cmd == "end") {
                    break;
                } else {
                    cout << "Comando invalido" << endl;
                } 
            } catch (exception& e) {
                cout << e.what() << endl;
            }
        }
        return 0;
    }

               
           
