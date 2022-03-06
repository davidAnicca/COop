#include <stdio.h>
#include "service.c"
#include <assert.h>

void repoTestAdd(Repo *lista){
    Oferta ofertaDeAdaugat;
    setAdresa(&ofertaDeAdaugat, "adresa");
    add(lista, ofertaDeAdaugat);
    int added = 0;
    for(int i = 0; i < lista->n; i++){
        if(egali(ofertaDeAdaugat, lista->oferte[i]))
            added = 1;
    }
    assert(added==1);
    assert(add(lista, ofertaDeAdaugat)==0);
    added = 0;
    for(int i = 0; i < lista->n; i++){
        if(egali(ofertaDeAdaugat, lista->oferte[i]))
            added++;
    }
    assert(added==1);
}

void repoTestDelete(Repo *lista){
    Oferta ofertaDeSters;
    setAdresa(&ofertaDeSters, "adresa");
    assert(delete(lista, ofertaDeSters)==1);
    assert(delete(lista, ofertaDeSters)==0);
    int added = 0;
    for(int i = 0; i < lista->n; i++){
        if(egali(ofertaDeSters, lista->oferte[i]))
            added++;
    }
    assert(added==0);
}

void repoTestModify(Repo *lista){
    Oferta ofertaDeModificat;
    setAdresa(&ofertaDeModificat, "adresa");
    ofertaDeModificat.pret = 12;
    ofertaDeModificat.suprafata = 100;
    setTip(&ofertaDeModificat, "b");
    assert(modify(lista, ofertaDeModificat) == 0);
    add(lista, ofertaDeModificat);
    Oferta alta;
    setAdresa(&alta, "adresa");
    alta.pret = 15;
    setTip(&alta, "a");
    alta.suprafata = 15;
    assert(modify(lista, alta) == 1);
    for(int i = 0; i < lista->n; i++){
        if(egali(ofertaDeModificat, lista->oferte[i])){
            assert(alta.pret == lista->oferte[i].pret);
        }
    }
    for(int i = 0; i < lista->n; i++){
        if(egali(ofertaDeModificat, lista->oferte[i])){
            assert(alta.suprafata == lista->oferte[i].suprafata);
        }
    }
    for(int i = 0; i < lista->n; i++){
        if(egali(ofertaDeModificat, lista->oferte[i])){
            assert(strcmp(alta.tip, lista->oferte[i].tip)==0);
        }
    }
    assert(delete(lista, ofertaDeModificat)==1);
}

void testEmpty(Repo *lista){
    emptyList(lista);
    assert(lista->n == 0);
}


///services tests

void servicesAdd(Service srv){
    assert(srvAdd(srv, "nimicbun", 1, "a", 12) == -1);
    assert(srvAdd(srv, "casa", 12, "adresa", 12) == 1);
    assert(srvAdd(srv, "casa", 12, "adresa", 12) == 0);
}

void servicesDelete(Repo *lista, Service srv){
    assert(srvDelete(srv, "adresa") == 1);
    for(int i = 0; i < lista->n; i++)
        assert(!egali(lista->oferte[i], creaza("casa", 12, "adresa", 12)));
    assert(srvDelete(srv, "adresa") == 0);
}

float myabs(float a) {
    return a >= 0 ? a : -a;
}

void servicesModPrice(Repo *lista, Service srv){
    srvAdd(srv, "casa", 12, "adresa", 15.0);
    assert(srvModifyPrice(srv, "adresa", 3.14) == 1);
    for(int i = 0; i < lista->n; i++){
        if(egali(lista->oferte[i], creaza("casa", 12, "adresa", 0))){
            assert(myabs(lista->oferte[i].pret-3.14)<0.01);
        }
    }
    assert(srvModifyPrice(srv, "in", 3.14) == 0);
}

void servicesModSurface(Repo *lista, Service srv){
    assert(srvModifySurface(srv, "adresa", 100) == 1);
    for(int i = 0; i < lista->n; i++){
        if(egali(lista->oferte[i], creaza("casa", 12, "adresa", 0))){
            assert(lista->oferte[i].suprafata == 100);
        }
    }
    assert(srvModifySurface(srv, "in", 3.14) == 0);
}

void servicesModType(Repo *lista, Service srv){
    assert(srvModifyType(srv, "adresa", "prostie") == -1);
    assert(srvModifyType(srv, "adresa", "apartament") == 1);
    for(int i = 0; i < lista->n; i++){
        if(egali(lista->oferte[i], creaza("casa", 12, "adresa", 0))){
            assert(stringEgal(lista->oferte[i].tip, "apartament"));
        }
    }
    assert(srvModifyType(srv, "in", "apartament") == 0);
}

///srv tests functionalitati



void runAll(){
    Repo repo = createRepo();
    repoTestAdd(&repo);
    repoTestDelete(&repo);
    repoTestModify(&repo);

    Service srv = createService(&repo);
    servicesAdd(srv);
    servicesDelete(&repo, srv);
    servicesModPrice(&repo, srv);
    servicesModSurface(&repo, srv);
    servicesModType(&repo, srv);

    testEmpty(&repo);
    printf("tests end\n");
    return;
}