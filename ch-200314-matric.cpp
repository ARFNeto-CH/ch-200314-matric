#define         _MAX_ALUNOS (12)

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>

using namespace std;

struct Aluno
{
    string  nome;
    float   media;
    string  matricula;
};

struct Turma
{
    vector<Aluno*>* alunos;
    string          nome;
    Turma(string, unsigned int);
    ~Turma();

    void lista_alunos();
};

bool compararPorMedia(Aluno, Aluno);
bool compararPorNome(Aluno, Aluno);

int md11(long int); // calcula digito verificador
Aluno* fabrica();
ostream& operator<<(ostream&, const Turma&);

int main(int argc, char** argv)
{
    srand(200314); // inicia gerador rand()

    Turma   turma_b("C++", 2);
    turma_b.lista_alunos();
    Turma   turma_c("java", 2);
    cout << turma_c;
    Turma   turma_d("Lazer II", 698);
    cout << turma_d;
    return 0;
}

bool compararPorMedia(Aluno a, Aluno b) {
    return a.media < b.media;
}

bool compararPorNome(Aluno a, Aluno b) {
    return a.nome < b.nome;
}

ostream& operator<<(ostream& out, const Turma& t)
{
    cout << "\nTurma '" << t.nome << "'  (" <<
        t.alunos->size() << ")\n" << endl;
    int seq = 0;
    for (auto a : *t.alunos)
    {
        seq = seq + 1;
        out << setw(2) << seq <<
            ":\tNome '" << a->nome <<
            "'\n\tMatricula '" << a->matricula <<
            "'\n\tMedia " << a->media <<
            endl << endl;
    };  // for()
    return out;
}	//	end operator<<()


int md11(long int matricula)
{
    int valor = matricula;
    int peso = 1;
    int soma = 0;

    while (valor > 0)
    {   peso = peso + 1;
        soma = soma + (valor % 10) * peso;
        valor = valor / 10;
    };  // while()
    soma = soma % 11;
    if (soma > 1) return (11 - soma);
    return 0;
};  // md11()


Aluno* fabrica()
{
    static unsigned int sequencia = 0;
    stringstream valor;
    int mat{ 0 };
    if (sequencia >= _MAX_ALUNOS) return NULL;
    Aluno* a = new Aluno; // o novo aluno
    sequencia = sequencia +  1;
    // cria um nome
    valor.str("");
    valor << "Nome-" << sequencia;
    a->nome = valor.str();
    // cria uma matricula
    valor.str("");
    mat = (rand() % 100000);
    valor << mat << "-" << md11(mat);
    a->matricula = valor.str();
    // cria uma media
    a->media = (float) (rand() % 100) + (float)(rand() % 10) / 10.f ;
    return a;
};  // fabrica()


Turma::Turma(string nome, unsigned int n_alunos) : nome(nome)
{
    alunos = new vector<Aluno*>;
    Aluno* novo;
    for (unsigned int i = 0; i < n_alunos; i += 1)
        if( (novo=fabrica()) != NULL )
            alunos->push_back(novo);
    cout << "Criada turma '" << nome << "' com "
        << alunos->size() << " alunos"
        << endl;
};  // Turma(string, unsigned int)


Turma::~Turma()
{
    cout << "Cancelando turma '" << nome << "'" << endl;
    for (auto aluno : *alunos)
        delete aluno;
    delete alunos;
};  // ~Turma()


void Turma::lista_alunos()
{
    cout << "\nTurma '" << nome << "'  (" <<
        alunos->size() << ")\n" << endl;
    int seq = 0;
    for (auto a : *alunos)
    {
        seq = seq + 1;
        cout << setw(2) << seq <<
            ":\tNome '" << a->nome <<
            "'\n\tMatricula '" << a->matricula <<
            "'\n\tMedia " << a->media <<
            endl << endl;
    };  // for()
};  // lista_alunos()
