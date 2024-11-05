#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <filesystem>
#include <algorithm>
#include <cstdint>
#include "cppcsv.h"
#include "trees.cpp"




typedef unsigned int uint;

std::vector<uint> gen_secuence(int n, uint min = 0, uint max = UINT_MAX) {
    std::vector<uint> secuence;
    secuence.reserve(n);

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<uint> distr(min, max); // define the range
    for (int i = 0; i < n; i++) {
        int x = distr(gen);
        secuence.push_back(x);
    }
    return secuence;
}

std::vector<int> gen_find_secuence(int n, int min = 0, int max = INT_MAX) {
    std::vector<int> secuence;
    secuence.reserve(n);

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<int> distr(min, max); // define the range
    for (int i = 0; i < n; i++) {
        int x = distr(gen);
        secuence.push_back(x);
    }
    return secuence;
}

void experiment_1(std::vector<uint> n_seq, std::string save_path) {
    CSVFile csv(save_path + "experiment_1.csv");
    csv.write_line("i", "BT time(s)", "BT avg time (s)", "ST time(s)", "ST avg time (s)");

    int insert_count = 0;
    int n = 100000;
    int m = 100 * n;
    
    std::vector<uint> m_seq;
    m_seq.reserve(m);
    
    BinaryTree binary_tree;
    SplayTree splay_tree;

    for(auto &&insert_it: n_seq) {
        binary_tree.insert(insert_it);
        splay_tree.insert(insert_it);
        insert_count++;
        if (insert_count == n) {
            std::cout << "finding m = " << m << "in n = " << n << std::endl;
            // preparar m

            // buscar
            for(auto &&find_it: m_seq) {
                binary_tree.find(find_it);
                splay_tree.find(find_it);
            }
            n += 100000;
        }
    }
}


void experiment_v1(std::vector<uint> n_seq, std::string save_path) {
    CSVFile csv(save_path + "experiment_v1.csv");
    csv.write_line("i", "BT time(s)", "BT avg time (s)", "ST time(s)", "ST avg time (s)");

    int insert_count = 0;
    int n = 100000;
    int m = 100 * n;

    std::vector<uint> m_seq;
    m_seq.reserve(m);

    BinaryTree binary_tree;
    SplayTree splay_tree;

    for (auto &&insert_it : n_seq) {
        binary_tree.insert(insert_it);
        splay_tree.insert(insert_it);
        insert_count++;

        // Cada 100,000 elementos, ejecutar el bloque de búsqueda
        if (insert_count == n) {
            // Preparar m_seq con M/N copias de cada elemento en n_seq
            for (const auto &val : n_seq) {
                for (int i = 0; i < m / n; ++i) {
                    m_seq.push_back(val);
                }
            }
            std::shuffle(m_seq.begin(), m_seq.end(), std::mt19937{std::random_device{}()});

            // Medición de tiempo para BinaryTree
            auto start_bt = std::chrono::high_resolution_clock::now();
            for (const auto &find_val : m_seq) {
                binary_tree.find(find_val);
            }
            auto end_bt = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration_bt = end_bt - start_bt;

            // Medición de tiempo para SplayTree
            auto start_st = std::chrono::high_resolution_clock::now();
            for (const auto &find_val : m_seq) {
                splay_tree.find(find_val);
            }
            auto end_st = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration_st = end_st - start_st;

            // Calcular tiempos promedio y guardar en CSV
            double avg_time_bt = duration_bt.count() / m;
            double avg_time_st = duration_st.count() / m;
            csv.write_line(insert_count, duration_bt.count(), avg_time_bt, duration_st.count(), avg_time_st);

            // Limpiar m_seq y preparar para el siguiente bloque
            m_seq.clear();
            n += 100000;
        }
    }
}




void test(std::vector<uint> n_seq){
    CSVFile csv("test.csv");
    csv.write_line("i", "time(s)", "avg time (s)");

    int n = 10;
    int m = 10;
    
    std::vector<uint> m_seq;
    m_seq.reserve(m);
    std::copy(n_seq.begin(), n_seq.end(), back_inserter(m_seq)); 

    BinaryTree binary_tree;
    SplayTree splay_tree;

    for(auto &&insert_it: n_seq) {
        binary_tree.insert(insert_it);
        splay_tree.insert(insert_it);
        std::cout << "inserted = " << insert_it << std::endl;
    }
    std::cout << "binary tree" << std::endl;
    binary_tree.print();
    std::cout << "splay tree" << std::endl;
    splay_tree.print();
    std::cout << "finding m = " << m << " in n = " << n << std::endl;
     // reparar m

    // buscar
    for(auto &&find_it: m_seq) {
        binary_tree.find(find_it);
        splay_tree.find(find_it);
    }
}

int main(void) {
    std::vector<uint> n_seq = gen_secuence(10, INT_MIN);
    std::cout << "Starting tests" << std::endl << std::endl;

    std::string save_path = "results/";
    std::filesystem::create_directories(save_path);

    test(n_seq);


    /*
    experiment_1(n_seq, save_path);
    experiment_2(seq, save_path)
    experiment_3(seq, save_path)
    experiment_4(seq, save_path)
    */

    std::cout << "End of test" << std::endl;
}