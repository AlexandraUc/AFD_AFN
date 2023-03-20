#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

int main(){
    // Format fisier f: nr stari, card alfabet, stare initiala, nr stari, finale, stari finale, tranzitii
    ifstream f("in2.txt"); 
    ifstream f2("cuvant.txt");

    char cuvant[300], stareCurenta;
    cuvant[0] = '-';
    cuvant[1] = '\0';
    string drum = "";
    int nrStari, cardAlfabet, nrStariFinale;
    f2 >> cuvant;
    f >> nrStari >> cardAlfabet >> stareCurenta >> nrStariFinale;

    char matriceAutomat[nrStari*cardAlfabet][4], stariFinale[nrStariFinale];
    drum += stareCurenta;

    for(int i = 0; i < nrStariFinale; i++)
        f >> stariFinale[i]; 
    stariFinale[nrStariFinale] = '\0';

    int tranzitii = 0;
    while(f >> matriceAutomat[tranzitii][0] >> matriceAutomat[tranzitii][1] >> matriceAutomat[tranzitii][2]){
        matriceAutomat[tranzitii][3] = '\0'; 
        tranzitii++;
    }

    int l;
    for(l = 0; l < strlen(cuvant); l++){
        for(int i = 0; i < tranzitii; i++)
            if(matriceAutomat[i][0] == stareCurenta && cuvant[l] == matriceAutomat[i][1]){
                stareCurenta = matriceAutomat[i][2];
                drum = drum + ' ' + stareCurenta;
                break;
            }
    }
    
    if(l == strlen(cuvant)){
        int i = 0;
        while(i < nrStariFinale){
            if(stariFinale[i] == stareCurenta){
                cout << "Cuvant acceptat\n" << drum << endl;
                break;
            }
            i++;
        }
        if(i == nrStariFinale)
            cout << "Cuvant neacceptat\n"; 
    }
    else    
        cout << "Cuvant neacceptat\n";
    f.close();
    f2.close();
    return 0;
}