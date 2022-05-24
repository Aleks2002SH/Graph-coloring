#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

//functions for checking tempopary results
template<class T>
void show2d_matrix(vector<vector<T>>& M, int N) {
    for (int i = 0; i < N; i++)
    {
        int K = M[i].size();
        for (int j = 0; j < K; j++) {
            cout << M[i][j] << " ";
        }
        cout << endl;
    }
}
template<class T>
void show_1dmatrix(vector<T>& V) {
    int N = V.size();
    for (int i = 0; i < N; i++) {
        cout << V[i] << " ";
    }
    cout << endl;
}

//greedy algorithm for graph coloring
int greedy_coloring(vector<vector<int>>& edges, vector<int>& permutation, int& n) {
    set<int> used_colors;//to count used colors
    vector<int> coloring(n, -1);// coloring of graph for current permutation
    int v;
    coloring[permutation[0]] = 0;//first vertex of permutation is always colored in min color number
    used_colors.insert(0);
    for (int i = 1; i < n; i++) {
        v = permutation[i];
        vector<bool> colors(n, true);//for checking of available colors
        for (int j = 0; j < edges[v].size(); j++) {
            if (coloring[edges[v][j]] != -1) {
                colors[coloring[edges[v][j]]] = false;
            }
        }
        vector<bool>::iterator it = find(colors.begin(), colors.end(), true);//finding not used by neighbors of current vertex color
        int dist = distance(colors.begin(), it);
        coloring[v] = dist;//coloring vertex
        used_colors.insert(dist);//pushing color in set
    }
    return used_colors.size();
}