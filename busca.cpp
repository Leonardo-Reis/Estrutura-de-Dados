#include <iostream>

using namespace std;

//Árvore Binária de Busca

struct no {
    struct no * esq;
    int value;
    struct no * dir;
};

typedef struct no * noPtr;

void insere(noPtr *, int);
bool enderecoVazio(noPtr);
void listar(noPtr);
void printNo(noPtr);
bool buscar(noPtr, int);
noPtr buscarMaior(noPtr *);
noPtr buscarMenor(noPtr);
void remove(noPtr *, int);

int main() {
    noPtr raiz, maior, menor;
    int op, x, n, achei;

    raiz = NULL;

    do {
        cout << "1 para inserir, 2 listar, 3 buscar, 4 buscar menor, 5 remove: ";
        cin >> op;

        switch (op) {
            case 1:
                cout << "Digite um numero: ";
                cin >> x;
                insere(&raiz, x);
                break;
            case 2:
                listar(raiz);
                break;
            case 3:
                cout << "Digite um numero: ";
                cin >> n;
                achei = buscar(raiz, n);
                if (achei) cout << "Elemento encontrado!" << endl;
                else cout << "Elemento nao encontrado..." << endl;
                break;
            case 4:
                menor = buscarMenor(raiz);
                printNo(menor);
                break;
            case 5:
                cout << "Digite um numero: ";
                cin >> x;
                remove(&raiz, x);
                break;
        }
        cout << endl;
    } while (op != 0);

    return 0;
}

void insere(noPtr * p, int x) {
    if (enderecoVazio(*p)) {
        *p = new no;
        (*p)->value = x;
        (*p)->esq = NULL;
        (*p)->dir = NULL;
    } else {
        if (x < (*p)->value) {
            insere(&(*p)->esq, x);
        } else {
            insere(&(*p)->dir, x);
        }
    }
}

void remove(noPtr * p, int x) {
    noPtr aux;

    if (!enderecoVazio(*p)) {
        if ((*p)->value == x) {
            aux = *p;
            if ((*p)->dir == NULL) {
                *p = (*p)->esq;
            } else if ((*p)->esq == NULL) {
                *p = (*p)->dir;
            } else {
                aux = buscarMaior(&(*p)->esq);
                (*p)->value = aux->value;
            }
            delete aux;
        } else {
            if (x < (*p)->value) {
                remove(&(*p)->esq, x);
            } else {
                remove(&(*p)->dir, x);
            }
        }
    } else {
        cout << "Vazio" << endl;
    }
}

noPtr buscarMaior(noPtr * p) {
    noPtr t;

    t = *p;

    if (enderecoVazio((*p)->dir)) {
        *p = (*p)->esq;
        return t;
    } else {
        return buscarMaior(&(*p)->dir);
    }
}

noPtr buscarMenor(noPtr p) {
    if (enderecoVazio(p->esq)) {
        return p;
    } else {
        return buscarMenor(p->esq);
    }
}

bool buscar(noPtr p, int n) {
    bool achei = false;

    if (enderecoVazio(p)) {
        return 0;
    } else {
        if (p->value == n) {
            achei = true;
        } else if (n < p->value) {
            achei = buscar(p->esq, n);
        } else if (n > p->value) {
            achei = buscar(p->dir, n);
        }
    }
    return achei;
}

bool enderecoVazio(noPtr p) {
    if (p == NULL) return 1;
    else return 0;
}

void listar(noPtr p) {
    if (!enderecoVazio(p)) {
        listar(p->esq);
        printNo(p);
        listar(p->dir);
    } else {
        return;
    }
}

void printNo(noPtr p) {
    cout << "esq: " << p->esq << " value: " << p->value << " dir: " << p->dir << endl;
}

//g++ -o busca busca.cpp && busca
