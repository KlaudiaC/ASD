// Klaudia C 20.12.2016

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

double d(pair<double, double> a, pair<double, double> b){ // odleglosc miedzy wierzcholkami
    double x = a.first - b.first;
    double y = a.second - b.second;
    return sqrt(x * x + y * y);
}

int main(){
    int z; // liczba zestawow
    cin >> z;

    while(z--){
        int N; // liczba wysp
        cin >> N;

        vector<pair<double, double> > xy(1); // wspolrzedne stolicy (czyli (0, 0)) sa dodawane od razu
        for(int n = 1; n <= N + 1; n++){ // wspolrzedne wysp i portu
            double x, y;
            cin >> x >> y;
            xy.push_back(make_pair(x, y));
        }

        vector<double> t(N + 2); // tablica minimalnych odleglosci
        vector<int> p(N + 2); // tablica krawedzi

        t[0] = d(xy[0], xy[1]); // odleglosc miedzy stolica i pierwsza wyspa
        p[1] = 0;
        for(int n = 2; n < N + 2; n++){
            pair<double, int> mint(t[0] + d(xy[0], xy[n]), 0); // minimalny koszt

            for(int i = 0; i < n - 1; i++){
                mint = min(mint, make_pair(t[i] + d(xy[i], xy[n]), i));
                t[i] += d(xy[n - 1], xy[n]); // rozszerzenie sciezki
            }
            t[n - 1] = mint.first;
            p[n] = mint.second;
        }

        vector<int> A, B; // stosy sciezek port-stolica (A jest krotsze od B)
        int a = N; // oraz a < b
        int b = N + 1;

        while(a != b){
            B.push_back(b);
            if(a < b - 1) // sprawdzenie warunku a < b
                b--;
            else{ // zamiana indeksow i stosow w celu zachowania zalozen
                b = p[b];
                swap(a, b);
                A.swap(B);
            }
        }
        if(A.size() == 0 || A.back() != 1) // ustalenie, czy sciezka stolica-port jest w A
            A.swap(B);

        vector<int> C; // stos wynikowy z cyklem
        C.push_back(0); // stolica (poczatek trasy)
        for(int i = A.size() - 1; i >= 0; i--)
            C.push_back(A[i]); // przepisanie sciezki stolica-port
        for(int i = 0; i < B.size(); i++)
            C.push_back(B[i]); // oraz sciezki port-stolica
        C.push_back(0); // stolica (koniec trasy)

        double dc(0.0), da(0.0); // dlugosc calej trasy i trasy stolica-port
        string sc; // zapis drogi
        for(int i = 0; i < C.size() - 1; i++){
            if(C[i] == N + 1) // jesli pokonalismy droge do portu, to ja zapisujemy
                da = dc;
            dc += d(xy[C[i]], xy[C[i + 1]]);
            if(C[i] == 0)
                sc += 'S'; // stolica
            else if(C[i] == N + 1)
                sc += 'P'; // port
            else
                sc += ((char) 'a' + C[i] - 1); // wyspa
        }
        sc += 'S'; // punkt koncowy
        cout << setprecision(2) << fixed << dc << "=" << da << "+" << dc - da << ":" << sc << endl;
    }
}
