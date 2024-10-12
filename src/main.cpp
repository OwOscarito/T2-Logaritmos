#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <filesystem>
#include "cppcsv.h"

std::vector<int> generate_secuence(int n, int min = 0, int max = INT32_MAX) {
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

int main(void){
    std::vector<int> seq = generate_secuence(pow(2, 24));
    std::cout << "Starting tests" << std::endl << std::endl;

    std::string save_path = "results/";
    std::filesystem::create_directories(save_path);

    for(int c = 2; c <= 6 ; c++) {
        int c_max = pow(2, c);
        std::cout << "Insertion using c_max = " << c_max << std::endl << std::endl;

        CSVFile csv(save_path + "c_max " + std::to_string(c_max) +".csv");
        csv.write_line("i", "I/Os","avg I/Os per ins", "time (ms)", "fill %");

        int count = 1;
        int i = 10; 
        int n = pow(2, i);
        
        auto start_time = std::chrono::high_resolution_clock::now();
        for(auto it = seq.begin(); it != seq.end(); it++, count++) {
            if (count == n) {
                auto current_time = std::chrono::high_resolution_clock::now();
                std::chrono::duration<float> duration = current_time - start_time;
                float delta_time = duration.count();
                csv.write_line(i, delta_time);

                std::cout << "reached = 2^" << i << std::endl;
                std::cout << "time spent = " << delta_time << std::endl;

                i++;
                n = pow(2, i);
            }
        }
    }
    std::cout << "End of test" << std::endl;
}