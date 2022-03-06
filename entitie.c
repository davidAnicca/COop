#include <string.h>

typedef struct Oferte{
    char tip[11];
    ///(teren, casa, apartament)
    int suprafata;
    char adresa[100];
    float pret;
} Oferta;

void setAdresa(Oferta *oferta, char adresa[]){
    strcpy(oferta->adresa, adresa);
}

void setTip(Oferta *oferta, char tipul[]){
    strcpy(oferta->tip, tipul);
}

int egali(Oferta oferta1, Oferta oferta2){
    return strcmp(oferta1.adresa, oferta2.adresa) == 0;
}

Oferta creaza(char tip[], int suprafata, char adresa[], float pret){
    ///creează o ofertă nouă folosind informațiile din param
    Oferta oferta;
    setTip(&oferta, tip);
    setAdresa(&oferta, adresa);
    oferta.suprafata = suprafata;
    oferta.pret = pret;
    return oferta;
}