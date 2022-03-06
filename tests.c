#include <stdio.h>
#include "service.c"
#include <assert.h>

void repoTestAdd(){
    Oferta ofertaDeAdaugat;
    setAdresa(&ofertaDeAdaugat, "adresa");
    add(ofertaDeAdaugat);
    int added = 0;
    for(int i = 0; i < lista.n; i++){
        if(egali(ofertaDeAdaugat, lista.oferte[i]))
            added = 1;
    }
    assert(added==1);
    add(ofertaDeAdaugat);
    added = 0;
    for(int i = 0; i < lista.n; i++){
        if(egali(ofertaDeAdaugat, lista.oferte[i]))
            added++;
    }
    assert(added==1);
}

void repoTestDelete(){
    Oferta ofertaDeSters;
    setAdresa(&ofertaDeSters, "adresa");
    assert(delete(ofertaDeSters)==1);
    assert(delete(ofertaDeSters)==0);
    int added = 0;
    for(int i = 0; i < lista.n; i++){
        if(egali(ofertaDeSters, lista.oferte[i]))
            added++;
    }
    assert(added==0);
}

void repoTestModify(){
    Oferta ofertaDeModificat;
    setAdresa(&ofertaDeModificat, "adresa");
    ofertaDeModificat.pret = 12;
    ofertaDeModificat.suprafata = 100;
    setTip(&ofertaDeModificat, "b");
    assert(modify(ofertaDeModificat) == 0);
    add(ofertaDeModificat);
    Oferta alta;
    setAdresa(&alta, "adresa");
    alta.pret = 15;
    setTip(&alta, "a");
    alta.suprafata = 15;
    assert(modify(alta) == 1);
    for(int i = 0; i < lista.n; i++){
        if(egali(ofertaDeModificat, lista.oferte[i])){
            assert(alta.pret == lista.oferte[i].pret);
        }
    }
    for(int i = 0; i < lista.n; i++){
        if(egali(ofertaDeModificat, lista.oferte[i])){
            assert(alta.suprafata == lista.oferte[i].suprafata);
        }
    }
    for(int i = 0; i < lista.n; i++){
        if(egali(ofertaDeModificat, lista.oferte[i])){
            assert(strcmp(alta.tip, lista.oferte[i].tip)==0);
        }
    }
    assert(delete(ofertaDeModificat)==1);
}

void testEmpty(){
    emptyList();
    assert(lista.n == 0);
}


///services tests

void servicesAdd(){
    assert(stringEgal(srvAdd("nimicbun", 1, "a", 12),
                      "tip invalid. nu s-a efectual adaugarea"));
    assert(stringEgal("s-a adaugat", srvAdd("casa", 12, "adresa", 12)));
    assert(stringEgal("oferta exista deja. nu s-a efectuat adaugarea", srvAdd("casa", 12, "adresa", 12)));
}

void servicesDelete(){
    assert(stringEgal("s-a sters", srvDelete("adresa")));
    for(int i = 0; i < lista.n; i++)
        assert(!egali(lista.oferte[i], creaza("casa", 12, "adresa", 12)));
    assert(stringEgal("oferta nu exista. nu s-a efectuat stergere", srvDelete("adresa")));
}

float myabs(float a) {
    return a >= 0 ? a : -a;
}

void servicesModPrice(){
    srvAdd("casa", 12, "adresa", 15.0);
    assert(stringEgal("s-a modificat pretul", srvModifyPrice("adresa", 3.14)));
    for(int i = 0; i < lista.n; i++){
        if(egali(lista.oferte[i], creaza("casa", 12, "adresa", 0))){
            assert(myabs(lista.oferte[i].pret-3.14)<0.01);
        }
    }
    assert(stringEgal("nu exista. nu s-a efectuat modificarea", srvModifyPrice("in", 3.14)));
}

void servicesModSurface(){
    assert(stringEgal("s-a modificat suprafata", srvModifySurface("adresa", 100)));
    for(int i = 0; i < lista.n; i++){
        if(egali(lista.oferte[i], creaza("casa", 12, "adresa", 0))){
            assert(lista.oferte[i].suprafata == 100);
        }
    }
    assert(stringEgal("nu exista. nu s-a efectuat modificarea", srvModifySurface("in", 3.14)));
}

void servicesModType(){
    assert(stringEgal("tip invalid. nu s-a efectuat modificarea", srvModifyType("adresa", "prostie")));
    assert(stringEgal("s-a modificat tipul", srvModifyType("adresa", "apartament")));
    for(int i = 0; i < lista.n; i++){
        if(egali(lista.oferte[i], creaza("casa", 12, "adresa", 0))){
            assert(stringEgal(lista.oferte[i].tip, "apartament"));
        }
    }
    assert(stringEgal("nu exista. nu s-a efectuat modificarea", srvModifyType("in", "apartament")));
}

void runAll(){
    repoTestAdd();
    repoTestDelete();
    repoTestModify();

    servicesAdd();
    servicesDelete();
    servicesModPrice();
    servicesModSurface();
    servicesModType();

    testEmpty();
    printf("tests end\n");
    return;
}