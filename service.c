#include "repo.c"



typedef struct Services{
    Repo *repo;
}Service;

Service createService(Repo *repo){
    Service service;
    service.repo = repo;
    return service;
}

int stringEgal(char prim[], char altul[]){
    ///verifică dacă două stringuri sunt egale
    return strcmp(prim, altul) == 0;
}

int validateType(char tip[]){
    return stringEgal("teren", tip) || stringEgal("casa", tip) || stringEgal("apartament", tip);
}

int srvAdd(Service srv, char tip[], int suprafata, char adresa[], float pret){
    ///adaugă o oferta
    ///returneaza mesajul "s-a adaugat" dacă s-a putut adăuga
    ///altfel returnează un mesaj de eroare
    if(!validateType(tip))
        return -1;
    Oferta ofertaDeAdaugat = creaza(tip, suprafata, adresa, pret);
    if(add(srv.repo, ofertaDeAdaugat) == 1){
        return 1;
    }else{
        return 0;
    }
}

int srvDelete(Service srv, char adresa[]){
    Oferta ofertaDeSters = creaza("tip", 0, adresa, 0);
    if(delete(srv.repo, ofertaDeSters) == 1)
        return 1;
    return 0;
}

int srvModifyPrice(Service srv, char adresa[], float pretNou){
    Oferta oferta = creaza("tip", 0, adresa, 0);
    Oferta gasita = cauta(*srv.repo, adresa);
    if(!egali(oferta, gasita))
        return 0;

    setTip(&oferta, gasita.tip);
    oferta.suprafata = gasita.suprafata;

    //!!
    oferta.pret = pretNou;
    modify(srv.repo, oferta);
    return 1;
}

int srvModifySurface(Service srv, char adresa[], int suprafataNoua){
    Oferta oferta = creaza("tip", 0, adresa, 0);
    Oferta gasita = cauta(*srv.repo, adresa);
    if(!egali(oferta, gasita))
        return 0;

    setTip(&oferta, gasita.tip);
    oferta.pret = gasita.pret;

    //!!
    oferta.suprafata = suprafataNoua;//modificarea
    modify(srv.repo, oferta);
    return 1;
}

int srvModifyType(Service srv, char adresa[], char tip[]){
    if(!validateType(tip))
        return -1;
    Oferta oferta = creaza("tip", 0, adresa, 0);
    Oferta gasita = cauta(*srv.repo, adresa);
    if(!egali(oferta, gasita))
        return 0;

    oferta.suprafata = gasita.suprafata;
    oferta.pret = gasita.pret;
    //!!
    setTip(&oferta, tip); //modificarea
    modify(srv.repo, oferta);
    return 1;
}