#ifndef particle_h
#define particle_h

double GetRandomNumber(double min, double max, std::size_t precision);

struct Particle
{
    int vertex_amount;
    std::vector<std::vector<double>> current_position;
    std::vector<std::vector<double>> best_position;
    std::vector<std::vector<double>> velocity;
    double current_particle_value = 0.;
    double best_particle_value = INF;
    
    Particle(int v_amount)
    : vertex_amount(v_amount), best_position(vertex_amount, std::vector<double>(vertex_amount)), current_position(vertex_amount, std::vector<double>(vertex_amount)), velocity(vertex_amount, std::vector<double>(vertex_amount)){
        }
    
    std::vector<std::vector<double>> velocity_conversion(std::vector<std::vector<double>>& velocity,
         std::vector<std::vector<double>>& current_particle_position, std::vector<std::vector<double>>& best_particle_position,
         std::vector<std::vector<double>>& best_swarm_position,double& c1, double& c2, int vertex_amount){
        for(std::size_t i = 0; i < vertex_amount; ++i){
            for(std::size_t j = 0; j < vertex_amount; ++j){
                velocity[i][j] += GetRandomNumber(0, 1, 2)*c1*(best_particle_position[i][j] - current_particle_position[i][j]) + GetRandomNumber(0, 1, 2)*c2*(best_swarm_position[i][j] - current_particle_position[i][j]);
            }
        }
        return velocity;
    }
    
    std::vector<std::vector<double>> position_conversion(std::vector<std::vector<double>>& velocity, std::vector<std::vector<double>>& position, std::vector<std::vector<double>>& lower_bound, std::vector<std::vector<double>>& upper_bound,int& vertex_amount){
        for(std::size_t i = 0; i < vertex_amount; ++i){
            for(std::size_t j = 0; j < vertex_amount; ++j){
                position[i][j] += velocity[i][j];
                if(position[i][j] < lower_bound[i][j]){
                    position[i][j] = lower_bound[i][j];
                }
                if(position[i][j] > upper_bound[i][j]){
                    position[i][j] = upper_bound[i][j];
                }
            }
        }
        return position;
    }
    
};

#endif /* particle_h */
