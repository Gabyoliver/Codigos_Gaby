#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <memory>
#include <stdexcept>
#include <algorithm>

using namespace std;

class IMedico;

class IPaciente {
public:
   virtual void addMedico(IMedico* medico) = 0;
   virtual string getDiagnostico() = 0;
   virtual string getId() = 0;
   virtual vector <IMedico*> getMedicos() = 0;
   virtual void removeMedico(IMedico* medico) = 0;
   virtual string toString() = 0;
   virtual ~IPaciente(){}
};

class IMedico {
public:
   virtual void addPaciente(IPaciente* paciente) = 0;
   virtual string getClasse() = 0;
    virtual string getId() = 0;
   virtual vector <IPaciente*> getPacientes() = 0;
   virtual void removePaciente(IPaciente* paciente) = 0;
   virtual string toString() = 0;
   virtual ~IMedico(){}
};

class Paciente : public IPaciente {
private:
   string id;
   string diagnostico;
   vector <IMedico*> medicos;
public:
    Paciente(string id, string diagnostico) : id(id), diagnostico(diagnostico) {}
    
    string toString() override {
        stringstream ss;
        int size = 1;

        ss << "Paciente: " << this->getId() << " : " << this->getDiagnostico() << " Meds[";
        for(auto medico : this->getMedicos()) {
            if(size < (int) this->getMedicos().size()) {
                ss << medico->getId() << ", ";
            } else {
                ss << medico->getId();
            }
            size++;
        }
        ss << "]";
        return ss.str();
    }
    void addMedico(IMedico* medico) {
        medicos.push_back(medico);
    }
    string getDiagnostico() {
        return diagnostico;
    }
    string getId() {
        return id;
    }
    vector <IMedico*> getMedicos() {
        return medicos;
    }
    void removeMedico(IMedico* medico) {
        auto it = find(medicos.begin(), medicos.end(), medico);
        if (it != medicos.end()) {
            medicos.erase(it);
        }
    }
};

class Medico : public IMedico {
protected:
    string id;
    string classe;
    vector <IPaciente*> pacientes;
public:
    Medico(string id, string classe) : id(id), classe(classe) {}
    string toString() override {
        stringstream ss;
        int size = 1;

        ss << "Medico: " << this->getId() << " : " << this->getClasse() << " Pacs[";
        for(auto paciente : this->getPacientes()) {
            if(size < (int) this->getPacientes().size()) {
                ss << paciente->getId() << ", ";
            } else {
                ss << paciente->getId();
            }
            size++;
        }
        ss << "]";
        return ss.str();
    }
    void addPaciente(IPaciente* paciente) {
        pacientes.push_back(paciente);
    }
    string getClasse() {
        return classe;
    }
    string getId(){
        return id;
    }
    vector <IPaciente*> getPacientes() {
        return pacientes;
    }
    void removePaciente(IPaciente* paciente) {
        auto it = find(pacientes.begin(), pacientes.end(), paciente);
        if (it != pacientes.end()) {
            pacientes.erase(it);
        }
    }
};

class Hospital {
    private:
        map <string, shared_ptr<IMedico>> medicos;
        map <string, shared_ptr<IPaciente>> pacientes;
    public:
        Hospital() {}

    void addMedico(shared_ptr<IMedico> medico) {
        if(this->medicos.find(medico->getId()) == this->medicos.end()) {
             medicos[medico->getId()] = medico;
        } else {
            throw invalid_argument("Medico ja existe");
        }
    }

    void addPaciente(shared_ptr<IPaciente> paciente) {
        if(this->pacientes.find(paciente->getId()) == this->pacientes.end()) {
            pacientes[paciente->getId()] = paciente;
        } else {
            throw invalid_argument("Paciente ja existe");
        }
    }

    void removeMedico(string id) {
        if(this->medicos.find(id) != this->medicos.end()) {
            this->medicos.erase(id);
        } else {
            throw invalid_argument("Medico nao existe");
        }
    }

    void removePaciente(string id) {
        if(this->pacientes.find(id) != this->pacientes.end()) {
            this->pacientes.erase(id);
        } else {
            throw invalid_argument("Paciente nao existe");
        }
    }

    string showAll() {
        stringstream ss;
        ss << "Hospital: " << endl;
        for(auto medico : this->medicos) {
            ss << medico.second->toString() << endl;
        }
        for(auto paciente : this->pacientes) {
            ss << paciente.second->toString() << endl;
        }
        return ss.str();
    }

    void vincular(string medicoId , string pacienteId) {
        if(this->medicos.find(medicoId) == this->medicos.end() && this->pacientes.find(pacienteId) == this->pacientes.end()) {
            throw invalid_argument("Medico ou Paciente nao existe");
        } else {
           auto pacientesMedico = this->pacientes[pacienteId].get()->getMedicos();
           if(find(pacientesMedico.begin(), pacientesMedico.end(), this->medicos[medicoId].get()) != pacientesMedico.end()) {
            throw invalid_argument("Paciente ja esta vinculado a esse medico");
           } else {
               for(auto medico : this->pacientes[pacienteId].get()->getMedicos()) {
                   if(medico->getClasse() == this->medicos[medicoId]->getClasse()) {
                       throw invalid_argument("Ja existe um medico com essa classe" + this->medicos[medicoId]->getClasse());
                   }
               }
                this->medicos[medicoId].get()->addPaciente(this->pacientes[pacienteId].get());
                this->pacientes[pacienteId].get()->addMedico(this->medicos[medicoId].get());     
           }
        }
    }

    void desvincular(string medicoId , string pacienteId) {
        this->medicos[medicoId]->removePaciente(this->pacientes[pacienteId].get());
        this->pacientes[pacienteId]->removeMedico(this->medicos[medicoId].get());
    }
};

int main(){
    Hospital hospital;
    while(true){
        string line;
        getline(cin, line);
        stringstream ss(line);
        string command;
        ss >> command;
        if(command == "addMedico"){
            string id, classe;
            ss >> id >> classe;
            shared_ptr<IMedico> medico = make_shared<Medico>(id, classe);
            hospital.addMedico(medico);
        } else if(command == "addPaciente"){
            string id, classe;
            ss >> id >> classe;
            shared_ptr<IPaciente> paciente = make_shared<Paciente>(id, classe);
            hospital.addPaciente(paciente);
        } else if(command == "removeMedico"){
            string id;
            ss >> id;
            hospital.removeMedico(id);
        } else if(command == "removePaciente"){
            string id;
            ss >> id;
            hospital.removePaciente(id);
        } else if(command == "vincular"){
            string medicoId, pacienteId;
            ss >> medicoId >> pacienteId;
            try {
                hospital.vincular(medicoId, pacienteId);
            } catch(invalid_argument& e) {
                cout << e.what() << endl;
            }
        } else if(command == "desvincular"){
            string medicoId, pacienteId;
            ss >> medicoId >> pacienteId;
            try {
                hospital.desvincular(medicoId, pacienteId);
            } catch(invalid_argument& e) {
                cout << e.what() << endl;
            }
        } else if(command == "showAll"){
            cout << hospital.showAll() << endl;
        } else if(command == "exit"){
            break;
        } else {
            cout << "Comando invalido" << endl;
        }
    }
    return 0;
}
