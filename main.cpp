#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int NO_LO_VI = 0, EMPECE_A_VER = 1, TERMINE_DE_VER = 2;

void dfs(int v, int p, vector<int> &estado, vector<int> &back_edges_inf_en, vector<int> &back_edges_sup_en, vector<vector<int>> &tree_edges, vector<pair<int,int>> &back_edges, vector<vector<int>> &m, vector<int> &padre) {
    estado[v] = EMPECE_A_VER;
    for (int u : m[v]) {
        if (estado[u] == NO_LO_VI) {
            padre[u] = v;
            tree_edges[v].push_back(u);
            dfs(u, v, estado, back_edges_inf_en, back_edges_sup_en, tree_edges, back_edges, m, padre);
        } else if (u != p) {
            if (estado[u] == EMPECE_A_VER){
                back_edges_inf_en[v]++;
                back_edges.push_back({v,u});
            }
            else // estado[u] == TERMINE_DE_VER
                back_edges_sup_en[v]++;

        }
    }
    estado[v] = TERMINE_DE_VER;
}


int cubren(int v, int p, vector<int> &memo, vector<vector<int>> &tree_edges, vector<int> &back_edges_inf_en, vector<int> &back_edges_sup_en) {
    if (memo[v] != -1) return memo[v];
    int res = 0;
    for (int hijo : tree_edges[v]) {
        if (hijo != p) {
            res += cubren(hijo, v, memo, tree_edges, back_edges_inf_en, back_edges_sup_en);
        }
    }
    res -= back_edges_sup_en[v];
    res += back_edges_inf_en[v];
    memo[v] = res;
    return res;
}

int main() {
    int cantCasos, cantBases, cantEnlaces, U, V;
    cin >> cantCasos;
    for(int i = 0; i<cantCasos; i++){
        cin >> cantBases >> cantEnlaces;
        vector<vector<int>> m(cantBases);
        for(int j = 0; j<cantEnlaces;j++){
            cin >> U >> V;
            m[U].push_back(V);
            m[V].push_back(U);
        }

        vector<pair<int,int>> importantes;
        vector<int> estado(cantBases, NO_LO_VI);
        vector<int> back_edges_inf_en(cantBases, 0);
        vector<int> back_edges_sup_en(cantBases, 0);
        vector<vector<int>> tree_edges(cantBases);
        vector<pair<int,int>> back_edges;
        vector<int> padre(cantBases);

        dfs(0,-1, estado, back_edges_inf_en, back_edges_sup_en, tree_edges, back_edges, m, padre);

        vector<int> memo(cantBases, -1);

        for(int k = 0; k < tree_edges.size(); k++){
            for(int l = 0; l < tree_edges[k].size(); l++){
                if(cubren(tree_edges[k][l], -1, memo, tree_edges, back_edges_inf_en, back_edges_sup_en) == 1){
                    if(tree_edges[k][l] < k){
                        importantes.push_back({tree_edges[k][l], k});
                    }
                    else{
                        importantes.push_back({k, tree_edges[k][l]});
                    }
                }
            }
        }
        if(importantes.size() == 0){
            cout<< 0 << endl;
        }
        if(importantes.size() > 0){
            for(int q = 0; q < back_edges.size(); q++){
                bool esImportante = false;
                int punta_inf = back_edges[q].first;
                int inicio  = back_edges[q].first;
                int punta_sup = back_edges[q].second;
                while(inicio != punta_sup && !esImportante){
                    if(cubren(inicio, -1, memo, tree_edges, back_edges_inf_en, back_edges_sup_en) == 1){
                        esImportante = true;
                        importantes.push_back({min(punta_inf,punta_sup), max(punta_inf,punta_sup)});
                    }
                    else{
                        inicio = padre[inicio];
                    }
                }
            }
            cout << importantes.size() << endl;
            sort(importantes.begin(), importantes.end());
            for(int u = 0; u < importantes.size(); u++){
                cout<< importantes[u].first << " " << importantes[u].second << endl;
            }
        }
    }
    return 0;
}

