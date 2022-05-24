// GraphColoring1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "for_file_output.h"


int main()
{
    int n, m, v1, v2;
    random_device rd;
    mt19937 g(rd());
    vector<string> files;
    auto cur_p = fs::current_path();
    fs::path dir{ "data" };
    fs::path pathtodata = cur_p / dir;
    files = filesindir(pathtodata);
    ofstream out("result.txt");
    for (int file = 0; file < files.size(); file++) {
        ifstream in(files[file]);
        in >> n >> m;
        vector<vector<int>> edges(n);//edges[vertex] contains all vertices agjacent to it
        for (int i = 0; i < m; i++) {
            in >> v1 >> v2;
            edges[v1].push_back(v2);
            edges[v2].push_back(v1);
        }
        vector<int> permutation;
        for (int i = 0; i < n; i++) {
            permutation.push_back(i);
        }
        int min_color = greedy_coloring(edges, permutation, n);//finding initial number of colors
        int col;
        //It is known that there exists a permutation which gives the true result for coloring 
        // So I simple create permutation for several times to find the best one
        // There are n! possible permutations but I don't have time for it so I use just n permutations
        for (int cnt = 0; cnt < n; cnt++) {
            shuffle(permutation.begin(), permutation.end(), g);
            col = greedy_coloring(edges, permutation, n);
            if (min_color > col) {
                min_color = col;
            }
        }
        cout << min_color;
        fill_result(min_color, out, files[file]);
        in.close();
    }
    out.close();
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
