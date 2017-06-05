// Klaudia C - 10.11.2016

#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>
using namespace std;

struct Node{
    char key;
    Node *left, *right;
    int size; // liczba przodkow
};

struct Result{
    int height; // wysokosc drzewa
    int size; // liczba wierzcholkow
    int leavesCount; // liczba lisci
    long long permCount; // liczba permutacji
};

long long newton(long long n, long long k){
    if(k > n - k) // chcemy zasze miec k jako mniejsza liczbe
        k = n - k;
    long long l = 1, m = 1; // licznik i miankownik

    while(k){
        l *= (n--); // domnazam licznik i mianownik dopoki nie zejde z k do 0
        m *= (k--);
    }
    return l/m;
}

void addTree(Node *&v, char val){ // tworzenie  (pod)drzewa od danego wskaznika referencji
    if(v == NULL){ // dotarcie za liscie
        v = new Node; // dajemy tam nowy wezel
        v -> key = val;
        v -> left = v -> right = NULL;
    }
    if(v -> key == val) // powtorzony element
        return;
    addTree((val < v -> key)? v -> left: v -> right, val); // zejscie do odpowiedniego potomka
}

void deleteTree(Node *&v){ // usuwanie calego drzewa
    if(v == NULL)
        return;
    deleteTree(v -> left);
    deleteTree(v -> right);
    delete v;
    v = NULL;
}

Result go(Node *v){
    Result res;
    res.height = 0;
    res.size = 0;
    res.leavesCount = 0;
    res.permCount = 1;

    if(v == NULL)
        return res;
    Result resLeft = go(v -> left), resRight = go(v -> right); // obliczanie kazdego poddrzewa oddzielnie
    res.height = max(resLeft.height, resRight.height) + 1; // zwiekszenie wysokosci
    res.size = resLeft.size + resRight.size + 1;
    res.leavesCount = resLeft.leavesCount + resRight.leavesCount;
    if(res.height == 1) // jesli jestesmy w lisciu
        res.leavesCount++; // to go dodajemy
    res.permCount = resLeft.permCount * resRight.permCount * newton(res.size - 1, resLeft.size); // odejmujemy podwojny korzen
    return res;
}

void printFirstTree(Node *v){ // wypisanie pierwszej permutacji drzewa
    if(v == NULL)
        return;
    cout << v -> key;
    printFirstTree(v -> left);
    printFirstTree(v -> right);
}

void printLastTree(Node *v){ // wypisanie ostatniej permutacji drzewa
    if(v == NULL)
        return;
    cout << v -> key;
    printLastTree(v -> right);
    printLastTree(v -> left);
}

int main(){
    int Z; // liczba zestawow

    cin >> Z;
    for(int z = 0; z < Z; z++){
        Node *root = NULL;
        string word; // zbior liter do drzewa

        cin >> word;
        for(int i = 0; i < word.size(); i++){
            if(isupper(word[i]))
                addTree(root, word[i]);
        }
        Result res = go(root);
        cout << res.height - 1 << ',' << res.leavesCount << ',' << res.permCount << ',';
        printFirstTree(root);
        cout << ',';
        printLastTree(root);
        cout << endl;
        deleteTree(root);
    }
}
