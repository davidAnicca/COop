#include <stdio.h>
#include "repo.c"
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
}

void runAll(){
    repoTestAdd();
    repoTestDelete();
    repoTestModify();
    printf("tests end\n");
    return;
}