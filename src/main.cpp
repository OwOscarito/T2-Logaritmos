#include <vector>
#include <random>
#include <chrono>
#include <filesystem>
#include "cppcsv.h"
#include "trees.cpp"

std::vector<int> gen_secuence(int n, int min = 0, int max = INT_MAX) {
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

void experiment_1(std::vector<int> n_seq, std::string save_path) {
    CSVFile csv(save_path + "experiment_1.csv");
    csv.write_line("i", "BT time(s)", "BT avg time (s)", "ST time(s)", "ST avg time (s)");

    int insert_count = 0;
    int n = 100000;
    int m = 100 * n;
    
    std::vector<int> m_seq;
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
                binary_tree.find(insert_it);
                splay_tree.find(insert_it);
            }
            n += 100000;
        }
    }
}

int main(void) {
    std::vector<int> n_seq = gen_secuence(1000000, INT_MIN);
    std::cout << "Starting tests" << std::endl << std::endl;

    std::string save_path = "results/";
    std::filesystem::create_directories(save_path);

    experiment_1(n_seq, save_path);

    /*
    experiment_2(seq, save_path)
    experiment_3(seq, save_path)
    experiment_4(seq, save_path)
    */

    std::cout << "End of test" << std::endl;
}