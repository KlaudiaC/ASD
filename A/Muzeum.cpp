// Klaudia C - 04.11.2016

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

priority_queue<pair<int, pair<int, int> >, vector<pair<int, pair<int, int> > >, greater<pair<int, pair<int, int> > > > heap; // kolejka: <typ, kontener, porzadek>
vector<vector<int> > s; // sale
vector<vector<int> > par; // lista poprzednikow
vector<vector<int> > dis; // odleglosci

const int INF = 1000000000; // nieskonczonosc
const char intToChar[4] = {'N', 'W', 'S', 'E'}; // kierunki

void preDijkstra(int M, int N){
    dis.clear(); // resize nie tyka wczesniejszych wartosci, wiec trzeba wyczyscic
    dis.resize(M, vector<int>(N, INF)); // wszystkie odleglosci na starcie to inf
    par.clear();
    par.resize(M, vector<int>(N));
}

void Dijkstra(int M, int N){
    while(heap.size() > 0){ // poki jest cos w kopcu
        pair<int, pair<int, int> > p = heap.top();
        int x = p.second.first, y = p.second.second;
        int d = dis[x][y]; // odleglosc miedzy wierzcholkami

        heap.pop();
        if(d < p.first)
            continue;
        d += s[x][y]; // wydluzamy krawedz do kolejnego wierzcholka
        if(x > 0){ // w gore
            if(dis[x - 1][y] > d){ // relaksacja
                heap.push(make_pair(dis[x - 1][y] = d, make_pair(x - 1, y)));
                // par[x - 1][y] = 0; // ustalenie kierunku
            }
        }
        if(x < M - 1){ // w dol
            if(dis[x + 1][y] > d){
                heap.push(make_pair(dis[x + 1][y] = d, make_pair(x + 1, y)));
                // par[x + 1][y] = 2;
            }
        }
        if(y > 0){ // w lewo
            if(dis[x][y - 1] > d){
                heap.push(make_pair(dis[x][y - 1] = d, make_pair(x, y - 1)));
                // par[x][y - 1] = 1;
            }
        }
        if(y < N - 1){ // w prawo
            if(dis[x][y + 1] > d){
                heap.push(make_pair(dis[x][y + 1] = d, make_pair(x, y + 1)));
                // par[x][y + 1] = 3;
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false); // dla przyspieszenia wylaczam synchronizacje wejscia/wyjscia
    int Z, M, N, K;

    cin >> Z; // liczba zestawow
    for(int z = 0; z < Z; z++){
        vector<vector<int> > disIn; // odleglosci od wejscia
        vector<vector<int> > disOut; // odleglosci od wyjscia
        vector<vector<int> > parIn; // poprzednicy do wejscia
        vector<vector<int> > parOut; // poprzednicy do wyjscia

        cin >> M >> N; // wiersze i kolumny
        s.clear();
        s.resize(M);
        for(int m = 0; m < M; m++){
            s[m].resize(N); // kazdy wiersz dotaje kolumny
            for(int n = 0; n < N; n++){
                cin >> s[m][n]; // wartosci sal
            }
        }

        preDijkstra(M, N); // drogi od wejscia
        dis[M - 1][0] = 0; // wejscie
        heap.push(make_pair(0, make_pair(M - 1, 0)));
        Dijkstra(M, N);
        disIn.swap(dis);
        parIn.swap(par);

        preDijkstra(M, N); // drogi od wyjscia
        dis[0][N - 1] = 0; // wyjscie
        heap.push(make_pair(0, make_pair(0, N - 1)));
        Dijkstra(M, N);
        disOut.swap(dis);
        parOut.swap(par);

        cin >> K; // zestawy sal promocyjnych
        for(int k = 0; k < K; k++){
            int a, b;
            string res;

            cin >> a >> b;
            a--, b--; // bo indeksujemy od 0
            cout << disIn[a][b] - s[a][b] << ", " << disOut[a][b] << endl;
            /*
            for(int x = a, y = b; x != M - 1 || y != 0; ((parIn[x][y]&1)?y:x) -= (parIn[x][y]&2) - 1) // ustalenie kierunku po bitach:
                res += intToChar[parIn[x][y]]; // pierwszy bit to wspolrzedna, drugi jest kierunkiem na wskazanej osi
            reverse(res.begin(), res.end()); // odwracamy, aby bylo od wejscia
            cout << ", " << res;
            res.clear();

            for(int x = a, y = b; x != 0 || y != N - 1; ((parOut[x][y]&1)?y:x) -= (parOut[x][y]&2) - 1)
                res += intToChar[parOut[x][y]^2]; // w druga strone, wiec xorujemy
            cout << ", " << res << endl;
            */
        }
    }
}
