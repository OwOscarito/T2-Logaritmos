#include <vector>
#include <random>
#include <chrono>
#include <filesystem>
#include "cppcsv.h"
#include "binary_tree.cpp"
#include "splay_tree.cpp"

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

void experiment_1(std::vector<int> n_seq, std::string save_path) {
    CSVFile bt_csv(save_path + "experiment_1.csv");
    bt_csv.write_line("i", "BT time(s)", "BT avg time (s)", "ST time(s)", "ST avg time (s)");

    int inserts = 1;
    int n = 100000;
    int m = 100 * n;
    
    std::vector<int> m_seq;
    m_seq.reserve(m);
    
    auto seq_it = n_seq.begin();
    NodeBT bin_tree(*seq_it);
    seq_it++;

    for(; seq_it != n_seq.end(); seq_it++, inserts++) {
        bin_tree.insert(*seq_it);
        inserts++;
        if (inserts == n) {
            std::cout << "finding m = " << m << "in n = " << n << std::endl;

            m 
            auto start_time = std::chrono::high_resolution_clock::now();
            for(auto find_it = seq.begin(); find_it != seq.end(); find_it++, inserts++) {
                
            }

            auto current_time = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> duration = current_time - start_time;
            float time_spent = duration.count();
            float avg_time_spent = time_spent/inserts;
            csv.write_line(inserts, time_spent, avg_time_spent);

            std::cout << "time spent = " << time_spent << std::endl;
            std::cout << "avg time per insert = " << avg_time_spent << std::endl;
            n += 100000;
        }
    }
}

int main(void) {
    std::vector<int> n_seq = gen_secuence(1000000, INT_MIN);
    std::cout << "Starting tests" << std::endl << std::endl;

    std::string save_path = "results/";
    std::filesystem::create_directories(save_path);

    experiment_1(seq, save_path);

    /*
    experiment_2(seq, save_path)
    experiment_3(seq, save_path)
    experiment_4(seq, save_path)
    */

    std::cout << "End of test" << std::endl;
}