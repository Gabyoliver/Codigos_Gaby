#include <iostream>
#include <map>
#include <sstream>
#include <string>

using namespace std;

class Medico;

class Paciente {
public:
    string nome;
    string diagnostico;
    map<string, Medico*> medicos;
public:
    Paciente(string nome, string diagnostico) : nome(nome), diagnostico(diagnostico) {};

    void addMedico(Medico * medico);

    void removerMedico(string nome);

    string getDiagnostico() {
        return this->diagnostico;
    }

    string getNome() {
        return this->nome;
    }

    string getMedicos() {
        stringstream ss;
        for(auto it = medicos.begin(); it != medicos.end(); it++) {
            ss << it->first << " ";
        }
        return ss.str();
    }

    friend ostream& operator<<(ostream& os, Paciente& paciente) {
        os << "Paciente: " << paciente.nome << endl;
        os << "Diagnostico: " << paciente.diagnostico << endl;
        os << "Medicos: " << paciente.getMedicos() << endl;
        return os;
    }
};

class Medico {
public:
    string nome;
    string especialidade;
    map<string, Paciente*> pacientes;
public:
    Medico(string nome, string especialidade) : nome(nome), especialidade(especialidade) {};

    void addPaciente(Paciente* paciente);

    void removerPaciente(string nome);

    string getEspecialidade() {
        return this->especialidade;
    }

    string getNome() {
        return this->nome;
    }

    string getPacientes() {
        stringstream ss;
        for(auto it = pacientes.begin(); it != pacientes.end(); it++) {
            ss << it->first << " ";
        }
        return ss.str();
    }

    friend ostream& operator<<(ostream& os, Medico& medico) {
        os << "Medico: " << medico.getNome() << endl;
        os << "Especialidade: " << medico.getEspecialidade() << endl;
        os << "Pacientes: " << medico.getPacientes() << endl;
        return os;
    }
};

void Paciente :: addMedico(Medico* medico) {
    this->medicos[medico->getNome()] = medico;
}

void Paciente :: removerMedico(string nome) {
    auto it = this->medicos.find(nome);
    if(it != this->medicos.end()) {
        this->medicos.erase(it);
    }
}

void Medico :: addPaciente(Paciente* paciente) {
    this->pacientes[paciente->getNome()] = paciente;
}

void Medico :: removerPaciente(string nome) {
    auto it = this->pacientes.find(nome);
    if(it != this->pacientes.end()) {
        this->pacientes.erase(it);
    }
}

class Hospital {
public:
    map<string, Paciente*> pacientes;
    map<string, Medico*> medicos;
public:
    Hospital() {};

    void addPaciente(Paciente * paciente) {
        this->pacientes[paciente->getNome()] = paciente;
    }

    void addMedico(Medico * medico) {
        this->medicos[medico->getNome()] = medico;
    }

    void removerPaciente(string nome) {
        auto it = this->pacientes.find(nome);
        if(it != this->pacientes.end()) {
            this->pacientes.erase(it);
        }
    }

    void removerMedico(string nome) {
        auto it = this->medicos.find(nome);
        if(it != this->medicos.end()) {
            this->medicos.erase(it);
        }
    }

    void vincular(string nomePaciente, string nomeMedico) {
        this->medicos[nomeMedico]->addPaciente(this->pacientes[nomePaciente]);
        this->pacientes[nomePaciente]->addMedico(this->medicos[nomeMedico]);
    }

    void desvincular(string nomePaciente, string nomeMedico) {
        this->medicos[nomeMedico]->removerPaciente(nomePaciente);
        this->pacientes[nomePaciente]->removerMedico(nomeMedico);
    }

    friend ostream& operator<<(ostream& os, Hospital& hospital) {
        os << "Hospital" << endl;
        os << "Pacientes: " << endl;
        for(auto it = hospital.pacientes.begin(); it != hospital.pacientes.end(); it++) {
            os << it->second << endl;
        }
        os << "Medicos: " << endl;
        for(auto it = hospital.medicos.begin(); it != hospital.medicos.end(); it++) {
            os << it->second << endl;
        }
        return os;
    }
};

    int main() {
        Hospital hospital;
        while(true) {
            string comando;
            cin >> comando;
            if(comando == "addPaciente") {
                string nome, diagnostico;
                cin >> nome >> diagnostico;
                Paciente * paciente = new Paciente(nome, diagnostico);
                hospital.addPaciente(paciente);
            } else if(comando == "addMedico") {
                string nome, especialidade;
                cin >> nome >> especialidade;
                Medico * medico = new Medico(nome, especialidade);
                hospital.addMedico(medico);
            } else if(comando == "vincular") {
                string nomePaciente, nomeMedico;
                cin >> nomePaciente >> nomeMedico;
                hospital.vincular(nomePaciente, nomeMedico);
            } else if(comando == "desvincular") {
                string nomePaciente, nomeMedico;
                cin >> nomePaciente >> nomeMedico;
                hospital.desvincular(nomePaciente, nomeMedico);
            } else if(comando == "fim") {
                break;
            }
        }
    }


   