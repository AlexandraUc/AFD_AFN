#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

class Automat{
    char* cuvant;
    char* stariFinale;
    char** matriceAutomat; 
    char* drum;
    int tranzitii;
    bool ok;
public:
    Automat();
    Automat(char* cuvant, char matriceAutomat[][4], char* stariFinale, int tranzitii, char stareCurenta);
    Automat(const Automat& obj);

    Automat& operator = (const Automat& obj);

    const char* getCuvant() const {return cuvant;}
    const char* getStariFinale() const {return stariFinale;}
    const char* getDrum() const {return drum;}
    int getTranzitii () const {return tranzitii;}


    void setCuvant(char* cuvant);
    void setStariFinale(char* stariFinale);
    void setDrum(char* drum);
    void setTranzitiiMatrice(int tranzitii, char matriceAutomat[][4]);

    void afisareMatriceAutomat();
    void bkt(int k, char, char*);
    void verificaAcceptare() {if(this->ok == 0) cout << "Cuvant neacceptat\n";}

    ~Automat();
};

// Constructor fara parametri
Automat::Automat(){
    this->tranzitii = 0;
    this->ok = 0;
    this->cuvant = NULL;
    this->matriceAutomat = NULL;
    this->stariFinale = NULL;
    this->drum = NULL;
}

// Constructor parametrizat
Automat::Automat(char* cuvant, char matriceAutomat[][4], char* stariFinale, int tranzitii, char stareCurenta){
    this->cuvant = new char[strlen(cuvant) + 1];
    strcpy(this->cuvant, cuvant);

    this->tranzitii = tranzitii;
    this->matriceAutomat = new char*[tranzitii]; 
    for(int i = 0; i < this->tranzitii; i++){
        this->matriceAutomat[i] = new char[4];
        strcpy(this->matriceAutomat[i], matriceAutomat[i]);
    }

    this->stariFinale = new char[strlen(stariFinale) + 1];
    strcpy(this->stariFinale, stariFinale);

    this->drum = new char[strlen(cuvant) + 2];
    this->drum[0] = stareCurenta;
    this->drum[1] = '\0';
    this->ok = 0;
}

// Copy constructor
Automat::Automat(const Automat& obj){
    this->cuvant = new char[strlen(obj.cuvant) + 1];
    strcpy(this->cuvant, obj.cuvant);
    this->stariFinale = new char[strlen(obj.stariFinale) + 1];
    strcpy(this->stariFinale, obj.stariFinale);
    this->drum = new char[strlen(obj.cuvant) + 2];
    this->drum[0] = obj.drum[0];
    this->drum[1] = '\0';
    this->ok = obj.ok;
    this->tranzitii = obj.tranzitii;
    this->matriceAutomat = new char*[this->tranzitii];
    for(int i = 0; i < obj.tranzitii; i++){
        this->matriceAutomat[i] = new char[4];
        strcpy(this->matriceAutomat[i], obj.matriceAutomat[i]);
    }

}

// Operator =
Automat& Automat::operator = (const Automat& obj){
    if(this != &obj){
        this->cuvant = new char[strlen(obj.cuvant) + 1];
        strcpy(this->cuvant, obj.cuvant);
        this->stariFinale = new char[strlen(obj.stariFinale) + 1];
        strcpy(this->stariFinale, obj.stariFinale);
        this->drum = new char[strlen(obj.cuvant) + 2];
        this->drum[0] = obj.drum[0];
        this->drum[1] = '\0';
        this->ok = obj.ok;
        this->tranzitii = obj.tranzitii;
        this->matriceAutomat = new char*[this->tranzitii];
        for(int i = 0; i < obj.tranzitii; i++){
            this->matriceAutomat[i] = new char[4];
            strcpy(this->matriceAutomat[i], obj.matriceAutomat[i]);
        }
    }
    return *this;
}

// Setteri
void Automat::setCuvant(char* cuvant){
    this->cuvant = new char[strlen(cuvant) + 1];
    strcpy(this->cuvant, cuvant);
}

void Automat::setStariFinale(char* stariFinale){
    this->stariFinale = new char[strlen(stariFinale) + 1];
    strcpy(this->stariFinale, stariFinale);
}

void Automat::setDrum(char* drum){
    this->drum = new char[strlen(drum) + 1];
    strcpy(this->drum, drum);
}

void Automat::setTranzitiiMatrice(int tranzitii, char matriceAutomat[][4]){
    this->tranzitii = tranzitii;
    this->matriceAutomat = new char*[tranzitii];
    for(int i = 0; i < tranzitii; i++){
        this->matriceAutomat[i] = new char[4];
        strcpy(this->matriceAutomat[i], matriceAutomat[i]);
    }
}

// Afiseaza matricea
void Automat::afisareMatriceAutomat(){
    for(int i = 0; i < this->tranzitii; i++){
        for(int j = 0; j < 3; j++)
            cout << this->matriceAutomat[i][j] << ' ';
        cout << endl;
    }
}

// Metoda Backtracking pentru verificarea acceptarii unui cuvant
void Automat::bkt(int k, char, char*){
    for(int i = 0; i < this->tranzitii; i++){
        if(this->drum[k] == this->matriceAutomat[i][0] && this->cuvant[k] == this->matriceAutomat[i][1]){
            this->drum[k+1] = this->matriceAutomat[i][2];
            if(k == strlen(this->cuvant) - 1){
                for(int j = 0; j < strlen(this->stariFinale); j++)
                    if(this->matriceAutomat[i][2] == this->stariFinale[j]){
                        if(this->ok == 0)
                            cout << "Cuvant acceptat\n";
                        this->ok = 1;
                        this->drum[strlen(this->cuvant) + 1] = '\0';
                        for(int l = 0; l < strlen(this->drum); l++)
                            cout << this->drum[l] << ' ';
                        cout << endl;
                    }
            }
            else
                if(k < strlen(this->cuvant) - 1){
                    bkt(k+1, this->matriceAutomat[i][2], this->drum);
                }
        }
    }
}

// Destructor
Automat::~Automat(){
    if(this->cuvant != NULL){
        delete[] this->cuvant;
        this->cuvant = NULL;
    }
    if(this->stariFinale != NULL){
        delete[] this->stariFinale;
        this->stariFinale = NULL;
    }
    if(this->drum != NULL){
        delete[] this->drum;
        this->drum = NULL;
    }
    for(int i = 0; i < this->tranzitii; i++)
        if(this->matriceAutomat[i] != NULL){
            delete[] this->matriceAutomat[i];
            this->matriceAutomat[i] = NULL;
        }
    if(this->matriceAutomat != NULL){
        delete[] this->matriceAutomat;
        this->matriceAutomat = NULL;
    }
}

int main(){
    // Format fisier: cuvant, nr stari, card alfabet, stare initiala, nr stari finale, stari finale, tranzitii
    ifstream f("in.txt");

    char cuvant[300], stareCurenta;
    int nrStari, cardAlfabet, nrStariFinale;

    f >> cuvant >> nrStari >> cardAlfabet >> stareCurenta >> nrStariFinale;

    int n = cardAlfabet*nrStari*nrStari;
    char matriceAutomat[n][4], stariFinale[nrStariFinale];
    for(int i = 0; i < nrStariFinale; i++)
        f >> stariFinale[i]; 
    stariFinale[nrStariFinale] = '\0';

    int tranzitii = 0;
    while(f >> matriceAutomat[tranzitii][0] >> matriceAutomat[tranzitii][1] >> matriceAutomat[tranzitii][2]){
        matriceAutomat[tranzitii][3] = '\0'; 
        tranzitii++;
    }

    Automat a(cuvant, matriceAutomat, stariFinale, tranzitii, stareCurenta);

    char dummy1;
    char* dummy2;

    a.bkt(0, dummy1, dummy2);
    a.verificaAcceptare();

    f.close();
    return 0;
}