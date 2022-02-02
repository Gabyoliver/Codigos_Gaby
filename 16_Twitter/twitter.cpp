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

               
            /*try {
                if (cmd == "addUsuario") {
                    string nome;
                    ss >> nome;
                    sistema.addUsuario(nome);
                } else if (cmd == "show") {
                    cout << sistema << endl;
                } else if (cmd == "seguir") {
                    string nome, other;
                    ss >> nome >> other;
                    sistema.getUsuario(nome)->seguir(sistema.getUsuario(other));
                } else if (cmd == "tweet") {
                    string nome, msg;
                    ss >> nome;
                    getline(ss, msg);
                    msg.erase(0, 1);
                    sistema.tweet(nome, msg);
                } else if (cmd == "retweet") {
                    string nome, msg;
                    int twId;
                    ss >> nome >> twId;
                    sistema.retweet(nome, twId);
                } else if (cmd == "like") {
                    string nome;
                    int twId;
                    ss >> nome >> twId;
                    sistema.getUsuario(nome)->like(twId);
                } else if (cmd == "deixarSeguir") {
                    string nome, other;
                    ss >> nome >> other;
                    sistema.getUsuario(nome)->deixarSeguir(other);
                } else if (cmd == "timeline") {
                    string nome;
                    ss >> nome;
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

        while(true) {
            vector<string> cmd = getcmd();
            if (cmd[0] == "addUsuario") {
                sistema.addUsuario(cmd[1]);
            } else if (cmd[0] == "seguir") {
                sistema.getUsuario(cmd[1])->seguir(sistema.getUsuario(cmd[2]));
            } else if (cmd[0] == "tweet") {
                sistema.tweet(cmd[1], cmd[2]);
            } else if (cmd[0] == "retweet") {
                sistema.retweet(cmd[1], stoi(cmd[2]));
            } else if (cmd[0] == "like") {
                sistema.getUsuario(cmd[1])->like(stoi(cmd[2]));
            } else if (cmd[0] == "deixarSeguir") {
                sistema.getUsuario(cmd[1])->deixarSeguir(cmd[2]);
            } else if (cmd[0] == "show") {
                cout << sistema << endl;
            } else if (cmd[0] == "removerUsuario") {
                sistema.removerUsuario
            }
            } else if (cmd[0] == "exit") {
                break;
            } else {
                cout << "Comando invalido" << endl;
            }
        } 
        return 0;
    }

       

            try{
                if (cmd == "addUsuario") {
                    sistema.addUsuario(param[1]);
                } else if (cmd == "seguir") {
                    sistema.getUsuario(param[1])->seguir(sistema.getUsuario(param[2]));
                } else if (cmd == "tweet") {
                    sistema.tweet(param[1], param[2]);
                } else if (cmd == "retweet") {
                    sistema.retweet(param[1], stoi(param[2]), param[3]);
                } else if (cmd == "removerUsuario") {
                    sistema.removerUsuario(param[1]);
                } else if (cmd == "like") {
                    sistema.getUsuario(param[1])->like(stoi(param[2]));
                } else if (cmd == "deixarSeguir") {
                    sistema.getUsuario(param[1])->deixarSeguir(param[2]);
                } else if (cmd == "deixarSeguirAll") {
                    sistema.getUsuario(param[1])->deixarSeguirAll();
                } else if (cmd == "rejectAll") {
                    sistema.getUsuario(param[1])->rejectAll();
                } else if (cmd == "exit") {
                    break;
                } else {
                    throw invalid_argument("Comando invalido");
                }
            } catch (invalid_argument &e) {
                cout << e.what() << endl;
            }
        }
        return 0;
    }

int main() {
    Controle sistema;

    while(true) {
        string cmd;
        cin >> cmd;
        if (cmd == "addUsuario") {
            string nome;
            cin >> nome;
            sistema.addUsuario(nome);
        } else if (cmd == "seguir") {
            string nome, nome2;
            cin >> nome >> nome2;
            sistema.getUsuario(nome)->seguir(sistema.getUsuario(nome2));
        } else if (cmd == "tweet") {
            string nome, msg;
            cin >> nome >> msg;
            sistema.tweet(nome, msg);
        } else if (cmd == "retweet") {
            string nome, msg;
            int twId;
            cin >> nome >> twId >> msg;
            sistema.retweet(nome, twId, msg);
        } else if (cmd == "removerUsuario") {
            string nome;
            cin >> nome;
            sistema.removerUsuario(nome);
        } else if (cmd == "like") {
            string nome;
            int twId;
            cin >> nome >> twId;
            sistema.getUsuario(nome)->like(twId);
        } else if (cmd == "deixarSeguir") {
            string nome, nome2;
            cin >> nome >> nome2;
            sistema.getUsuario(nome)->deixarSeguir(nome2);
        } else if (cmd == "deixarSeguirAll") {
            string nome;
            cin >> nome;
            sistema.getUsuario(nome)->deixarSeguirAll();
        } else if (cmd == "rejectAll") {
            string nome;
            cin >> nome;
            sistema.getUsuario(nome)->rejectAll();
        } else if (cmd == "get tweets") {
            string nome;
            cin >> nome;
            cout << sistema.getUsuario(nome)->getInbox();
        } else if (cmd == "get my tweets") {
            string nome;
            cin >> nome;
            for (auto t : sistema.getUsuario(nome)->getMyTweets()) {
                cout << *t << endl;
            }
        } else if (cmd == "get timeline") {
            string nome;
            cin >> nome;
            for (auto t : sistema.getUsuario(nome)->getInbox().getTimeline()) {
                cout << *t << endl;
            }
        } else if (cmd == "get seguidores") {
            string nome;
            cin >> nome;
            for (auto s : sistema.getUsuario(nome)->seguidores) {
                cout << s.first << endl;
            }
        } else if (cmd == "get seguindo") {
            string nome;
            cin >> nome;
            for (auto s : sistema.getUsuario(nome)->seguindos) {
                cout << s.first << endl;
            }
        } else if (cmd == "get tweets seguidos") {
            string nome;
            cin >> nome;
            for (auto s : sistema.getUsuario(nome)->seguidores) {
                cout << s.first << endl;
                for (auto t : sistema.getUsuario(s.first)->getInbox().getTimeline()) {
                    cout << *t << endl;
                }
            }
        } else if (cmd == "get tweets seguidores") {
            string nome;
            cin >> nome;
            for (auto s : sistema.getUsuario(nome)->seguidores) {
                cout << s.first << endl;
                for (auto t : sistema.getUsuario(s.first)->getInbox().getTimeline()) {
                    cout << *t << endl;
                }
            }
        } else if (cmd == "get tweets seguidos e seguidores") {
            string nome;
            cin >> nome;
            for (auto s : sistema.getUsuario(nome)->seguidores) {
                cout << s.first << endl;
                for (auto t : sistema.getUsuario(s.first)->getInbox().getTimeline()) {
                    cout << *t << endl;
                }
            }
            for (auto s : sistema.getUsuario(nome)->seguindos) {
                cout << s.first << endl;
                for (auto t : sistema.getUsuario(s.first)->getInbox().getTimeline()) {
                    cout << *t << endl;
                }
            }
        } else if (cmd == "get tweets seguidos e seguidores e meus tweets") {
            string nome;
            cin >> nome;
            for (auto s : sistema.getUsuario(nome)->seguidores) {
                cout << s.first << endl;
                for (auto t : sistema.getUsuario(s.first)->getInbox().getTimeline()) {
                    cout << *t << endl;
                }
            }
            for (auto s : sistema.getUsuario(nome)->seguindos) {
                cout << s.first << endl;
                for (auto t : sistema.getUsuario(s.first)->getInbox().getTimeline()) {
                    cout << *t << endl;
                }
            }
            for (auto t : sistema.getUsuario(nome)->getMyTweets()) {
                cout << *t << endl;
            }

    




class Message {
    int id;
    std::string username;
    std::string msg;
    std::set<std::string> likes;

public:
    Message(int id, std::string username, std::string msg) : id{id}, username{username}, msg{msg} {}
    
    int get_id() const {
        return this->id;
    }

    void like(std::string username) {
        likes.insert(username);
    }

    friend std::ostream& operator<<(std::ostream& os, const Message& msg) {
        os << msg.get_id() << ":" << msg.username << " (" << msg.msg << ")";
        if (msg.likes.size() > 0) {
            os << " [";
            bool flag = true;
            for (auto like : msg.likes) {
                if (flag) {
                    os << like;
                    flag = false;
                } else {
                    os << ", " << like;
                }
            }
            os << "]";
        }
        return os;
    }
};

class Inbox {
    std::map<int, Message*> unread;
    std::map<int, Message*> readed;

public:
    Inbox() {}

    std::vector<Message*> get_unread() {
        std::vector<Message*> unreadMsgs;
        for (auto msg : this->unread) {
            unreadMsgs.push_back(msg.second);
        }
        return unreadMsgs;
    }

    std::vector<Message*> get_readed() {
        std::vector<Message*> readedMsgs;
        for (auto msg : this->readed) {
            readedMsgs.push_back(msg.second);
        }
        return readedMsgs;
    }

    Message* get_tweet(int id) {
        auto it = readed.find(id);
        if (it != readed.end()) {
            return it->second;
        } else {
            throw std::runtime_error("fail: tweet nao existe");
        }
    }

    void store_unread(Message* tweet) {
        this->unread[tweet->get_id()] = tweet;
        this->readed[tweet->get_id()] = tweet;
    }

    void store_readed(Message* tweet) {
        this->readed[tweet->get_id()] = tweet;
    }

    friend std::ostream& operator<<(std::ostream& os, Inbox& inbox) {
        for (auto msg : inbox.get_readed()) {
            os << *msg << "\n";
        }
        return os;
    }
};

class User {
    std::string username;
    Inbox inbox;
    std::map<std::string, User*> followers;
    std::map<std::string, User*> following;

public:
    User(std::string username) : username{username} {}

    void follow(User* other) {
        auto it = following.find(other->username);
        if (it != following.end()) {
            throw std::runtime_error("fail: ja segue esse usuario");
        } else {
            following[other->username] = other;
            other->followers[username] = this;
        }
    }

    void unfollow(std::string username) {
        if (following.find(username) == following.end()) {
            throw std::runtime_error("fail: nao segue esse usuario");
        } else {
            auto other = following[username];
            following.erase(username);
            other->followers.erase(this->username);
        }
    }

    void like(int twId) {
        inbox.get_tweet(twId)->like(this->username);
    }

    Inbox& get_inbox() {
        return this->inbox;
    }

    void send_tweet(Message* msg) {
        inbox.store_readed(msg);
        for (auto& follower : this->followers) {
            follower.second->get_inbox().store_unread(msg);
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const User& user) {
        os << user.username << "\n";
        os << "  seguidos [";
        bool flag = true;
        for (auto f : user.following) {
            if (flag) {
                os << f.first;
                flag = false;
            } else {
                os << ", " << f.first;
            }
        }
        os << "]\n";

        os << "  seguidores [";
        flag = true;
        for (auto f : user.followers) {
            if (flag) {
                os << f.first;
                flag = false;
            } else {
                os << ", " << f.first;
            }
        }
        os << "]\n";
        return os;
    }
};

class Controller {
    std::map<std::string, std::shared_ptr<User>> users;
    std::map<int, std::shared_ptr<Message>> tweets;
    int next_tweet_id {0};

    std::shared_ptr<Message> create_msg(std::string username, std::string msg) {
        tweets[next_tweet_id] = std::make_shared<Message>(next_tweet_id, username, msg);
        next_tweet_id++;
        return tweets[next_tweet_id - 1];
    }

public:
    Controller() {}

    void add_user(std::string username) {
        auto it = users.find(username);
        if (it == users.end()) {
            users[username] = std::make_shared<User>(username);
        } else {
            throw std::runtime_error("fail: usuario ja existe");
        }
    }

    User* get_user(std::string username) {
        auto it = users.find(username);
        if (it != users.end()) {
            return it->second.get();
        } else {
            throw std::runtime_error("fail: usuario nao existe");
        }
    }

    void send_tweet(std::string username, std::string msg) {
        std::shared_ptr<Message> tweet = create_msg(username, msg);
        get_user(username)->send_tweet(tweet.get());
    }

    friend std::ostream& operator<<(std::ostream& os, Controller& ctrl) {
        for (auto user : ctrl.users) {
            os << *user.second << "\n";
        }
        return os;
    }
};

int main() {
    Controller system;

    while(true) {
        std::string line, cmd;
        std::cin >> cmd;
        getline(std::cin, line);
        std::stringstream ss(line);

        try {
            if (cmd == "end") {
                break;

            } else if (cmd == "add") {
                std::string username;
                ss >> username;
                system.add_user(username);

            } else if (cmd == "show") {
                std::cout << system;

            } else if (cmd == "follow") {
                std::string username, other;
                ss >> username >> other;
                system.get_user(username)->follow(system.get_user(other));

            } else if (cmd == "unfollow") {
                std::string username, other;
                ss >> username >> other;
                system.get_user(username)->unfollow(other);

            } else if (cmd == "twittar") {
                std::string username, msg;
                ss >> username;
                getline(ss, msg);
                msg.erase(0, 1);
                system.send_tweet(username, msg);

            } else if (cmd == "like") {
                std::string username;
                int twId;
                ss >> username >> twId;
                system.get_user(username)->like(twId);

            } else if (cmd == "unread") {
                std::string username;
                ss >> username;
                for (auto m : system.get_user(username)->get_inbox().get_unread()) {
                    std::cout << *m << "\n";
                }

            } else if (cmd == "timeline") {
                std::string username;
                ss >> username;
                std::cout << system.get_user(username)->get_inbox();
                
            } else {
                std::cout << "fail: comando invalido\n";
            }
        } catch (std::exception& e) {
            std::cout << e.what() << "\n";
        }
    }
    return 0;
}*/

