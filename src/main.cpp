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

int powi(int base, int exp) {
    int result = 1;
    for (;;) {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }
    return result;
}

const double CONST_C = 1/1.64493;

double prob_fun(int i) {
    return CONST_C/powi(i+1, 2);
}

void experiment_1(std::vector<uint> n_seq, std::string save_path) {
    std::cout << "Experiment 1" << std::endl;

    CSVFile csv(save_path + "experiment_1.csv");
    csv.write_line("i", "BT time(ns)", "BT avg time (ns)", "ST time(ns)", "ST avg time (ns)");

    int insert_count = 0;
    int n = 100000;
    int m = 100 * n;

    std::vector<uint> m_seq;

    BinaryTree binary_tree;
    SplayTree splay_tree;

    for (auto &&insert_it : n_seq) {
        binary_tree.insert(insert_it);
        splay_tree.insert(insert_it);
        insert_count++;

        // Cada 100,000 elementos, ejecutar el bloque de búsqueda
        if (insert_count == n) {
            std::cout << "checkpoint n = " << n << std::endl;
            // Preparar m_seq con M/N copias de cada elemento en n_seq
            m_seq.reserve(m);
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
            auto duration_bt = std::chrono::duration_cast<std::chrono::nanoseconds>( end_bt - start_bt);

            // Medición de tiempo para SplayTree
            auto start_st = std::chrono::high_resolution_clock::now();
            for (const auto &find_val : m_seq) {
                splay_tree.find(find_val);
            }
            auto end_st = std::chrono::high_resolution_clock::now();
            auto duration_st = std::chrono::duration_cast<std::chrono::nanoseconds>( end_st - start_st);

            // Calcular tiempos promedio y guardar en CSV
            double avg_time_bt = duration_bt.count() / (double)m;
            double avg_time_st = duration_st.count() / (double)m;
            std::cout << "avg_time_bt = " << avg_time_bt << std::endl;
            std::cout << "avg_time_st = "<< avg_time_st << std::endl << std::endl;
            csv.write_line(insert_count, duration_bt.count(), avg_time_bt, duration_st.count(), avg_time_st);

            // Limpiar m_seq y preparar para el siguiente bloque
            m_seq.clear();
            n += 100000;
            m = 100 * n;
        }
    }
}


void experiment_2(std::vector<uint> n_seq, std::string save_path) {
    std::cout << "Experiment 2" << std::endl;

    CSVFile csv(save_path + "experiment_2.csv");
     csv.write_line("i", "BT time(ns)", "BT avg time (ns)", "ST time(ns)", "ST avg time (ns)");

    BinaryTree binary_tree;
    SplayTree splay_tree;

    int insert_count = 0;
    int n = 100000;
    int m = 100 * n;

    std::vector<uint> m_seq;

    for (auto &&insert_it : n_seq) {
        binary_tree.insert(insert_it);
        splay_tree.insert(insert_it);
        insert_count++;

        // Cada 100,000 elementos, ejecutar el bloque de búsqueda
        if (insert_count == n) {
            std::cout << "checkpoint n = " << n << std::endl;

            m_seq.reserve(m);
            // Crear el arreglo M
            for (int i = 0; i < 1000000; ++i) {
                int copies = prob_fun(i) * m;
                for (int j = 0; j < copies; ++j) {
                    m_seq.push_back(n_seq[i]);
                }
            }

            // Medición de tiempo para BinaryTree
            auto start_bt = std::chrono::high_resolution_clock::now();
            for (auto &&find_it : m_seq) {
                binary_tree.find(find_it);
            }
            auto end_bt = std::chrono::high_resolution_clock::now();
            auto duration_bt = std::chrono::duration_cast<std::chrono::nanoseconds>( end_bt - start_bt);

            // Medición de tiempo para SplayTree
            auto start_st = std::chrono::high_resolution_clock::now();
            for (auto &&find_it : m_seq) {
                splay_tree.find(find_it);
            }
            auto end_st = std::chrono::high_resolution_clock::now();
            auto duration_st = std::chrono::duration_cast<std::chrono::nanoseconds>(end_st - start_st);

            // Calcular tiempos promedio y guardar en CSV
            double avg_time_bt = duration_bt.count() / (double)m;
            double avg_time_st = duration_st.count() / (double)m;
            std::cout << "avg_time_bt = " << avg_time_bt << std::endl;
            std::cout << "avg_time_st = "<< avg_time_st << std::endl << std::endl;
            csv.write_line(insert_count, duration_bt.count(), avg_time_bt, duration_st.count(), avg_time_st);

            // Limpiar m_seq y preparar para el siguiente bloque
            m_seq.clear();
            n += 100000;
            m = 100 * n;
        }
    }
}


void experiment_3(std::vector<uint> n_seq, std::string save_path) {
    std::cout << "Experiment 3" << std::endl;

    CSVFile csv(save_path + "experiment_3.csv");
     csv.write_line("i", "BT time(ns)", "BT avg time (ns)", "ST time(ns)", "ST avg time (ns)");

    // Ordenar el arreglo A
    std::sort(n_seq.begin(), n_seq.end());

    int insert_count = 0;
    int n = 100000;
    int m = 100 * n;

    std::vector<uint> m_seq;

    BinaryTree binary_tree;
    SplayTree splay_tree;

    for (auto &&insert_it : n_seq) {
        binary_tree.insert(insert_it);
        splay_tree.insert(insert_it);
        insert_count++;

        // Cada 100,000 elementos, ejecutar el bloque de búsqueda
        if (insert_count == n) {
            std::cout << "checkpoint n = " << n << std::endl;
            // Preparar m_seq con M/N copias de cada elemento en n_seq
            m_seq.reserve(m);
            for (auto &val : n_seq) {
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
            auto duration_bt = std::chrono::duration_cast<std::chrono::nanoseconds>( end_bt - start_bt);

            // Medición de tiempo para SplayTree
            auto start_st = std::chrono::high_resolution_clock::now();
            for (const auto &find_val : m_seq) {
                splay_tree.find(find_val);
            }
            auto end_st = std::chrono::high_resolution_clock::now();
            auto duration_st = std::chrono::duration_cast<std::chrono::nanoseconds>( end_st - start_st);

            // Calcular tiempos promedio y guardar en CSV
            double avg_time_bt = duration_bt.count() / (double)m;
            double avg_time_st = duration_st.count() / (double)m;
            std::cout << "avg_time_bt = " << avg_time_bt << std::endl;
            std::cout << "avg_time_st = "<< avg_time_st << std::endl << std::endl;
            csv.write_line(insert_count, duration_bt.count(), avg_time_bt, duration_st.count(), avg_time_st);

            // Limpiar m_seq y preparar para el siguiente bloque
            m_seq.clear();
            n += 100000;
            m = 100 * n;
        }
    }
}

void experiment_4(std::vector<uint> n_seq, std::string save_path) {
    std::cout << "Experiment 4" << std::endl;

    CSVFile csv(save_path + "experiment_4.csv");
     csv.write_line("i", "BT time(ns)", "BT avg time (ns)", "ST time(ns)", "ST avg time (ns)");


    int insert_count = 0;
    int n = 100000;
    int m = 100 * n;

    std::vector<uint> C;
    std::vector<uint> m_seq;

    BinaryTree binary_tree;
    SplayTree splay_tree;

    for (auto &&insert_it : n_seq) {
        binary_tree.insert(insert_it);
        splay_tree.insert(insert_it);
        insert_count++;

        // Cada 100,000 elementos, ejecutar el bloque de búsqueda
        if (insert_count == n) {
            std::cout << "checkpoint n = " << n << std::endl;
            C.reserve(n);
            std::copy(n_seq.begin(), n_seq.begin() + n, std::back_inserter(C));
            m_seq.reserve(m);
            // Crear el arreglo M
            for (int i = 0; i < n; ++i) {
                int copies = prob_fun(i) * m;
                for (int j = 0; j < copies; ++j) {
                    m_seq.push_back(n_seq[i]);
                }
            }

            // Medición de tiempo para BinaryTree
            auto start_bt = std::chrono::high_resolution_clock::now();
            for (auto &&find_it : m_seq) {
                binary_tree.find(find_it);
            }
            auto end_bt = std::chrono::high_resolution_clock::now();
            auto duration_bt = std::chrono::duration_cast<std::chrono::nanoseconds>( end_bt - start_bt);

            // Medición de tiempo para SplayTree
            auto start_st = std::chrono::high_resolution_clock::now();
            for (auto &&find_it : m_seq) {
                splay_tree.find(find_it);
            }
            auto end_st = std::chrono::high_resolution_clock::now();
            auto duration_st = std::chrono::duration_cast<std::chrono::nanoseconds>( end_st - start_st);

            // Calcular tiempos promedio y guardar en CSV
            double avg_time_bt = duration_bt.count() / (double)m;
            double avg_time_st = duration_st.count() / (double)m;
            std::cout << "avg_time_bt = " << avg_time_bt << std::endl;
            std::cout << "avg_time_st = "<< avg_time_st << std::endl << std::endl;
            csv.write_line(insert_count, duration_bt.count(), avg_time_bt, duration_st.count(), avg_time_st);

            // Limpiar m_seq y preparar para el siguiente bloque
            m_seq.clear();
            n += 100000;
            m = 100 * n;
        }
    }
}

void test(void) {
    std::vector<uint> A = gen_secuence(10, 0, 100);
    BinaryTree bt;
    SplayTree st;
    for (auto &&it : A) {
        bt.insert(it);
        st.insert(it);
    }
    bt.print();
    st.print();
}

int main(void) {
    int n_len = 1000000;
    std::vector<uint> n_seq = gen_secuence(n_len, INT_MIN);
    std::cout << "Starting tests" << std::endl << std::endl;

    std::string save_path = "results/";
    std::filesystem::create_directories(save_path);

    experiment_1(n_seq, save_path);
    experiment_2(n_seq, save_path);
    experiment_3(n_seq, save_path);
    experiment_4(n_seq, save_path);

    std::cout << "End of test" << std::endl;
}