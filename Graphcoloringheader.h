#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <random>

using namespace std;
//generation of random uniform distribution using mersenne twister
namespace MyRandom {
    mt19937 mersenne{ static_cast<mt19937::result_type>(time(nullptr)) };
}
int getRandomNumber(int min_num, int max_num) {
    uniform_int_distribution die{ min_num,max_num };
    return die(MyRandom::mersenne);
}

//edge struct
struct edge {
    int v1, v2;
};

// functions for checking subproducts
template<class T>
void show1d_matrix(vector<T>& V) {
    int N = V.size();
    for (int i = 0; i < N; i++) {
        cout << V[i] << " ";
    }
    cout << endl;
}



// creating individual for population
vector<int> create_individual(int& n, int& count_of_col) {
    vector<int> individual(n);
    for (int i = 0; i < n; i++) {
        individual[i] = getRandomNumber(0, count_of_col); // maybe using without - 1 just add 1 in the answer
    }
    return individual;
}
//creating population
vector<vector<int>> create_population(int& pop_size, int& cols, int& n) {
    vector<vector<int>> population;
    vector<int> individual;
    for (int i = 0; i < pop_size; i++) {
        individual = create_individual(n, cols);
        population.push_back(individual);
    }
    return population;
}

//fitness function to analyse which individual is better and will go to the next generation
int fitness_function(vector<edge>& edges, vector<int>& individual, int& m) {
    int penalty = 0;
    int u, v;
    for (int i = 0; i < m; i++) {
        u = edges[i].v1;
        v = edges[i].v2;
        if (individual[u] == individual[v])
            penalty++;
    }
    return penalty;
}

//Selects best individuals for next generation;
vector<vector<int>> tournament_selection(vector<vector<int>>& population, int& pop_size, vector<edge>& edges, int& m) {
    int f1, f2;
    vector<vector<int>> new_population;
    for (int cnt = 0; cnt < 2; cnt++) {
        for (int i = 0; i < pop_size - 1; i++) {
            f1 = fitness_function(edges, population[i], m);
            f2 = fitness_function(edges, population[i + 1], m);
            if (f1 < f2) {
                new_population.push_back(population[i]);
            }
            else {
                new_population.push_back(population[i + 1]);
            }
        }
    }
    return new_population;
}

//small function for one process in crossover
void change_vectors(vector<int>& v1, vector<int>& v2, int& pos) {
    int tmp;
    int n = v1.size();
    for (int i = pos; i < n; i++) {
        tmp = v1[i];
        v1[i] = v2[i];
        v2[i] = tmp;
    }
}
//function which is helpful to create new population
void crossover(vector<vector<int>>& population, int& pop_size, int& n) {
    int pos;
    for (int i = 0; i < pop_size; i += 2) {
        pos = getRandomNumber(0, n - 1);
        change_vectors(population[i], population[i + 1], pos);
    }
}

//Mutation function for speeding up the process selects random vertex and changes its color with probability of 2%
void Mutation(vector<vector<int>>& population, int& pop_size, int& num_of_colors, int& n) {
    int K, col, pos;
    for (int i = 0; i < pop_size; i++) {
        K = getRandomNumber(1, 10);
        if (K <= 2) {
            col = getRandomNumber(0, num_of_colors);
            pos = getRandomNumber(0, n - 1);
            population[i][pos] = col;
        }
    }
}
// function for finding best individual in population
pair<int, int> Best(vector<vector<int>>& population, int& pop_size, int& m, vector<edge>& edges) {
    int best_fit = fitness_function(edges, population[0], m);
    int index = 0;
    int fit;
    for (int i = 1; i < pop_size; i++) {
        fit = fitness_function(edges, population[i], m);
        if (best_fit > fit) {
            best_fit = fit;
            index = i;
        }
    }
    return make_pair(best_fit, index);
}

//function for finding suitable individual for k-coloring of given graph
pair<int, int> finding_suited_individual_for_coloring(int& num_of_colors, vector<vector<int>>& population, int& pop_size, vector<edge>& edges, int& m, int& n) {
    int generation = 0;
    int best_fitness = n;
    pair<int, int> cur_best;
    while (generation <= 500 && best_fitness != 0) {
        population = tournament_selection(population, pop_size, edges, m);
        crossover(population, pop_size, n);
        Mutation(population, pop_size, num_of_colors, n);
        cur_best = Best(population, pop_size, m, edges);
        if (cur_best.first < best_fitness) {
            best_fitness = cur_best.first;
        }
        generation += 1;
    }
    return make_pair(best_fitness, cur_best.second);
}

//function for finding min number of colors
int find_min_num_col(vector<edge>& edges, int& n, int& m, int& cols) {
    int best_fit = 0;
    int pop_size = 20;
    vector<vector<int>> population;
    pair<int, int> res;
    population = create_population(pop_size, cols, n);
    res = finding_suited_individual_for_coloring(cols, population, pop_size, edges, m, n);
    best_fit = res.first;
    int index = res.second;
    cols--;
    while (cols >= 0 && best_fit != 0) {
        population = create_population(pop_size, cols, n);
        res = finding_suited_individual_for_coloring(cols, population, pop_size, edges, m, n);
        best_fit = res.first;
        if (best_fit == 0) {
            index = res.second;
        }
    }

    //show1d_matrix<int>(population[index]);
    if (best_fit == 0) return cols;
    else return cols + 1;
}