#include "repo.c"

Oferta creaza(char tip[], int suprafata, char adresa[], float pret){
    ///creează o ofertă nouă folosind informațiile din param
    Oferta oferta;
    setTip(&oferta, tip);
    setAdresa(&oferta, adresa);
    oferta.suprafata = suprafata;
    oferta.pret = pret;
    return oferta;
}



int stringEgal(char prim[], char altul[]){
    ///verifică dacă două stringuri sunt egale
    return strcmp(prim, altul) == 0;
}

int validateType(char tip[]){
    return stringEgal("teren", tip) || stringEgal("casa", tip) || stringEgal("apartament", tip);
}

char *srvAdd(char tip[], int suprafata, char adresa[], float pret){
    ///adaugă o oferta
    ///returneaza mesajul "s-a adaugat" dacă s-a putut adăuga
    ///altfel returnează un mesaj de eroare
    if(!validateType(tip))
        return "tip invalid. nu s-a efectual adaugarea";
    Oferta ofertaDeAdaugat = creaza(tip, suprafata, adresa, pret);
    if(add(ofertaDeAdaugat) == 1){
        return "s-a adaugat";
    }else{
        return "oferta exista deja. nu s-a efectuat adaugarea";
    }
}

char *srvDelete(char adresa[]){
    Oferta ofertaDeSters = creaza("tip", 0, adresa, 0);
    if(delete(ofertaDeSters) == 1)
        return "s-a sters";
    return "oferta nu exista. nu s-a efectuat stergere";
}

char *srvModifyPrice(char adresa[], float pretNou){
    Oferta oferta = creaza("tip", 0, adresa, 0);
    Oferta gasita = cauta(adresa);
    if(!egali(oferta, gasita))
        return "nu exista. nu s-a efectuat modificarea";

    setTip(&oferta, gasita.tip);
    oferta.suprafata = gasita.suprafata;

    //!!
    oferta.pret = pretNou;
    modify(oferta);
    return "s-a modificat pretul";
}

char *srvModifySurface(char adresa[], int suprafataNoua){
    Oferta oferta = creaza("tip", 0, adresa, 0);
    Oferta gasita = cauta(adresa);
    if(!egali(oferta, gasita))
        return "nu exista. nu s-a efectuat modificarea";

    setTip(&oferta, gasita.tip);
    oferta.pret = gasita.pret;

    //!!
    oferta.suprafata = suprafataNoua;//modificarea
    modify(oferta);
    return "s-a modificat suprafata";
}

char *srvModifyType(char adresa[], char tip[]){
    if(!validateType(tip))
        return "tip invalid. nu s-a efectuat modificarea";
    Oferta oferta = creaza("tip", 0, adresa, 0);
    Oferta gasita = cauta(adresa);
    if(!egali(oferta, gasita))
        return "nu exista. nu s-a efectuat modificarea";

    oferta.suprafata = gasita.suprafata;
    oferta.pret = gasita.pret;
    //!!
    setTip(&oferta, tip); //modificarea
    modify(oferta);
    return "s-a modificat tipul";
}