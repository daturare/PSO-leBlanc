#ifndef swarm_h
#define swarm_h

#include "leBlanc.h"

struct Solution
{
    int vertex_amount;
    std::vector<std::vector<double>> variablesC;
    std::vector<std::vector<double>> variablesX;
    
    Solution(int v_amount)
        : vertex_amount(v_amount), variablesC(vertex_amount, std::vector<double>(vertex_amount)), variablesX(vertex_amount, std::vector<double>(vertex_amount)){
        }
};

struct CollectedData
{
    std::vector<double> best_swarm_value;
    std::vector<std::vector<std::vector<double>>> best_swarm_position;
};

double GetRandomNumber(double min, double max, std::size_t precision)
{
  double value;
  value = rand() % (int)pow(10, precision);
  value = min + (value / pow(10, precision)) * (max - min);
  return value;
}

struct Swarm
{
    int particles_amount;
    int vertex_amount;
    std::size_t precision;
    std::vector<std::vector<double>> lower_bound;
    std::vector<std::vector<double>> upper_bound;
    std::vector <Particle> particles_;
    std::vector <Solution> solutions_;
    double best_swarm_value = INF;
    std::vector<std::vector<double>> best_swarm_position;
    
    Swarm(int p_amount,int v_amount, std::vector<std::vector<double>>& lower, std::vector<std::vector<double>>& upper, std::size_t prec, double& e, Graph& graph)
           : particles_amount(p_amount), vertex_amount(v_amount), lower_bound(lower), upper_bound(upper), precision(prec)
        {
            std::vector <Particle> particles;
            std::vector <Solution> solutions;
            
            for(std::size_t i = 0; i < particles_amount; ++i){
                Particle particle (vertex_amount);
                Solution solution (vertex_amount);
                particles.push_back(particle);
                solutions.push_back(solution);
            }
      
            for(std::size_t k = 0; k < particles_amount; ++k){
                for(std::size_t i = 0; i < vertex_amount; ++i){
                    for(std::size_t j = 0; j < vertex_amount; ++j){
                        solutions[k].variablesC[i][j] = GetRandomNumber(lower_bound[i][j], upper_bound[i][j], precision);
                        particles[k].current_position[i][j] = solutions[k].variablesC[i][j];
                        particles[k].best_position[i][j] =  solutions[k].variablesC[i][j];
                        }
                    std::cout << std::endl;
                    }
                std::cout << std::endl;
                }
            for(std::size_t k = 0; k < particles_amount; ++k){
                solutions[k].variablesX = leBlanc(t0, d, upper_bound, e, graph);
            }
            solutions_ = solutions;
            particles_ = particles;
        }
};


#endif /* swarm_h */
