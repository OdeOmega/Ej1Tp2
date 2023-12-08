#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

const int INF = 1e9+1;

struct GRAFO {
    vector<int> padre_de;
    vector<int> nivel_de;
    vector<int> nivel_minimo_alcanzado;
    vector<vector<int>> aristas;

    GRAFO(int cantBases) :
    padre_de(cantBases,-1),
    nivel_de(cantBases, INF),
    aristas(cantBases),
    nivel_minimo_alcanzado(cantBases, INF){}
};

void dfs(int v, int padre, pair<int,int> ignorar, GRAFO &grafo){
    grafo.padre_de[v] = padre;
    grafo.nivel_de[v] = grafo.nivel_de[padre] + 1;
    grafo.nivel_minimo_alcanzado[v] = grafo.nivel_de[v];
    for(int i = 0; i < grafo.aristas[v].size(); i++){
        int posible_hijo_de_v = grafo.aristas[v][i];
        if(make_pair(v,posible_hijo_de_v) != ignorar && make_pair(posible_hijo_de_v, v) != ignorar){
            if(grafo.padre_de[posible_hijo_de_v] == -1){
                dfs(posible_hijo_de_v, v, ignorar, grafo);
                grafo.nivel_minimo_alcanzado[v] = min(grafo.nivel_minimo_alcanzado[v],grafo.nivel_minimo_alcanzado[posible_hijo_de_v]);
            }
            else if(grafo.padre_de[v] != posible_hijo_de_v && grafo.nivel_de[posible_hijo_de_v] < grafo.nivel_de[v]){
                grafo.nivel_minimo_alcanzado[v] = min(grafo.nivel_minimo_alcanzado[v],grafo.nivel_de[posible_hijo_de_v]);
            }
        }
    }


}

int main() {
    int cantCasos, cantBases, cantEnlaces, U, V;
    cin >> cantCasos;
    for(int i = 0; i<cantCasos; i++){
        cin >> cantBases >> cantEnlaces;
        GRAFO grafo(cantBases);
        vector<pair<int,int>> aristas_a_ignorar;
        for(int j = 0; j<cantEnlaces;j++){
            cin >> U >> V;
            grafo.aristas[U].push_back(V);
            grafo.aristas[V].push_back(U);
            aristas_a_ignorar.push_back({U,V});
        }
        vector<pair<int,int>> importantes;
        for(int j = 0; j < aristas_a_ignorar.size(); j++){
            grafo.padre_de = vector<int>(cantBases,-1);
            grafo.nivel_de = vector<int>(cantBases, INF);
            grafo.nivel_minimo_alcanzado = vector<int>(cantBases,INF);
            grafo.nivel_de[0] = 0;
            dfs(0,0,aristas_a_ignorar[j],grafo);
            for(int k = 0; k < cantBases; k++){
                if(grafo.nivel_minimo_alcanzado[k] > grafo.nivel_de[grafo.padre_de[i]]){
                    importantes.push_back({min(aristas_a_ignorar[j].first,aristas_a_ignorar[j].second), max(aristas_a_ignorar[j].first,aristas_a_ignorar[j].second)});
                    k = cantBases;
                }
            }
            int a = 0;
        }
        sort(importantes.begin(), importantes.end());
        cout << importantes.size() << endl;
        for(int w = 0; w < importantes.size(); w++){
            cout << importantes[w].first << " " << importantes[w].second << endl;
        }


    }
    return 0;
}
