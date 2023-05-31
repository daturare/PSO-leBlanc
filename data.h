#ifndef data_h
#define data_h

#include "graph.h"

int particles_amount = 20;
int vertex_amount = 24;
int iterations_amount = 150;
double c1 = 0.5;
double c2 = 0.5;
double e = 0.001;
std::size_t precision = 2;

std::vector<std::vector<std::size_t>> read_two_dim_value(const std::string& file_path){
    std::vector<std::vector<std::size_t>> mas;
    std::ifstream fin(file_path);
    if (fin){
        int x_count;
        int y_count;
        fin >> x_count >> y_count;

        for (std::size_t i = 0; i < x_count; i++) {
            std::vector<std::size_t> vec;
            for (std::size_t j = 0; j < y_count; j++) {
                std::size_t value;
                fin >> value;
                vec.push_back(value);
            }
            mas.push_back(vec);
        }
    }
    return mas;
}

std::vector<std::vector<double>> read_two_dim_value2(const std::string& file_path){
    std::vector<std::vector<double>> mas;
    std::ifstream fin(file_path);
    if (fin){
        int x_count;
        int y_count;
        fin >> x_count >> y_count;

        for (std::size_t i = 0; i < x_count; i++) {
            std::vector<double> vec;
            for (std::size_t j = 0; j < y_count; j++) {
                double value;
                fin >> value;
                vec.push_back(value);
            }
            mas.push_back(vec);
        }
    }
    return mas;
}


Graph graph = read_graph("/Users/daryakuznetsova/Desktop/BPSOQ/graph.txt");

const std::vector<std::vector<std::size_t>> t0  = read_two_dim_value("/Users/daryakuznetsova/Desktop/BPSOQ/graph.txt");

const std::vector<std::vector<std::size_t>> d = read_two_dim_value("/Users/daryakuznetsova/Desktop/BPSOQ/d.txt");

std::vector<std::vector<double>> upper_bound = read_two_dim_value2("/Users/daryakuznetsova/Desktop/BPSOQ/c1.txt");

std::vector<std::vector<double>> lower_bound = read_two_dim_value2("/Users/daryakuznetsova/Desktop/BPSOQ/c0.txt");



#endif 
