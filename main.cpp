#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void robustos(vector<vector<int>> m){
    vector<vector<bool>> noUsado(m.size(),vector<bool>(m.size(),true));
    vector<pair<int,int>> res;
    for(int i = 0; i< m.size(); i++){
        if(m[i].size() == 2){
            pair<int,int> par1 = {min(i,m[i][0]), max(i,m[i][0])};
            pair<int,int> par2 = {min(i,m[i][1]), max(i,m[i][1])};
            if(noUsado[par1.first][par1.second]){
                res.push_back(par1);
                noUsado[par1.first][par1.second] = false;
            }
            if(noUsado[par2.first][par2.second]){
                res.push_back(par2);
                noUsado[par2.first][par2.second] = false;
            }
        }
    }
    sort(res.begin(),res.end());
    cout << res.size() << endl;
    for(int k = 0; k< res.size();k++){
        cout<< res[k].first << " " << res[k].second << endl;
    }
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


        robustos(m);
    }
    return 0;
}
