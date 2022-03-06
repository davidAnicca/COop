#include "entitie.c"

typedef struct lst{
    Oferta oferte[100];
    int n;
}Lista;

Lista lista;

int add(Oferta oferta){
    ///adaugă o oferta in repo
    ///returneaza 1 dacă oferta s-a adăugat. 0 altfel
    for(int i = 0; i < lista.n; i++){
         if(egali(oferta, lista.oferte[i]))
             return 0;
    }
    lista.oferte[lista.n] = oferta;
    lista.n++;
    return 1;
}

int delete(Oferta oferta){
    ///sterge oferta din repo
    ///returneză 1 dacă oferta s-a șters, 0 dacă ea nu există
    for(int i = 0; i < lista.n; i++){
        if(egali(oferta, lista.oferte[i])){
            for(int j = i; j < lista.n-1; j++)
                lista.oferte[i] = lista.oferte[i+1];
            lista.n--;
            return 1;
        }
    }
    return 0;
}

int modify(Oferta oferta){
    ///modifica oferta dată cu noile informatii
    ///returneaza 1 daca s-a facut modificarea
    ///0 dacă oferta nu a putut fi găsită
    for(int i = 0; i < lista.n; i++){
        if(egali(oferta, lista.oferte[i])){
            lista.oferte[i] = oferta;
            return 1;
        }
    }
    return 0;
}

void emptyList(){
    //golește lista de oferte
    while(lista.n>0) {
        if(lista.n == 1){
            lista.n = 0;
            return;
        }
        for (int i = 0; i < lista.n - 1; i++)
            lista.oferte[i] = lista.oferte[i+1];
        lista.n--;
    }
}

Oferta cauta(char adresa[]){
    Oferta oferta;
    setAdresa(&oferta, adresa);
    for(int i = 0; i < lista.n; i++)
        if(egali(lista.oferte[i], oferta))
            return lista.oferte[i];
    Oferta vida;
    setAdresa(&vida, "vida");
    return vida;
}