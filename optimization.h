#ifndef optimization_h
#define optimization_h

double GetRandomNumber(double min, double max, std::size_t precision);

double ttf(std::vector<std::vector<double>>& variablesC, std::vector<std::vector<double>>& variablesX, Graph& graph, int vertex_amount) {
    double value = 0.;
    for(std::size_t i = 0; i < vertex_amount; ++i){
        for(std::size_t j = 0; j < graph.nodes[i].edges.size(); ++j){
            value += graph.nodes[i].edges[j].weight + 0.15*pow(variablesX[i][graph.nodes[i].edges[j].indexTo]/variablesC[i][graph.nodes[i].edges[j].indexTo], 4);
        }
    }
    return value;
}

double icf(std::vector<std::vector<double>>& variablesC, std::vector<std::vector<double>>& lower_bound, Graph& graph, int vertex_amount) {
    double value = 0.;
    for(std::size_t i = 0; i < vertex_amount; ++i){
        for(std::size_t j = 0; j < graph.nodes[i].edges.size(); ++j){
            value +=  0.0000001*pow(variablesC[i][graph.nodes[i].edges[j].indexTo] - lower_bound[i][graph.nodes[i].edges[j].indexTo], 2);
        }
    }
    return value;
}

void optimize (int& particles_amount, int& vertex_amount,  int& iterations_amount, Graph& graph, const std::vector<std::vector<std::size_t>>& d,
               const std::vector<std::vector<std::size_t>>& t0, std::vector<std::vector<double>>& lower_bound, std::vector<std::vector<double>>& upper_bound, double& e, std::size_t precision, double& c1, double& c2) {
    Swarm swarm(particles_amount, vertex_amount,lower_bound, upper_bound, precision, e, graph);
    CollectedData result;
    for(std::size_t i = 0; i < particles_amount; ++i){
        ttf(swarm.particles_[i].current_position, swarm.solutions_[i].variablesX, graph, vertex_amount);
        swarm.particles_[i].current_particle_value = ttf(swarm.particles_[i].current_position, swarm.solutions_[i].variablesX, graph, vertex_amount) + icf(swarm.particles_[i].current_position, lower_bound, graph, vertex_amount);
        swarm.particles_[i].best_particle_value = swarm.particles_[i].current_particle_value;
        swarm.particles_[i].best_position = swarm.particles_[i].current_position;
        if(swarm.particles_[i].current_particle_value <= swarm. best_swarm_value){
            swarm.best_swarm_value = swarm.particles_[i].current_particle_value;
            swarm.best_swarm_position = swarm.particles_[i].current_position;
        }
    }
    std::size_t iterations_counter = 0;

while(iterations_counter < iterations_amount){
   
    for(std::size_t k = 0; k < particles_amount; ++k){
        swarm.particles_[k].velocity_conversion(swarm.particles_[k].velocity, swarm.particles_[k].current_position, swarm.particles_[k].best_position, swarm.best_swarm_position, c1, c2, vertex_amount);
            swarm.particles_[k].position_conversion(swarm.particles_[k].velocity, swarm.particles_[k].current_position, lower_bound, upper_bound, vertex_amount);
    }
   
    for(std::size_t k = 0; k < particles_amount; ++k){
        swarm.solutions_[k].variablesX = leBlanc(t0, d, upper_bound, e, graph);
    }
    
    for(std::size_t i = 0; i < particles_amount; ++i){
       
        swarm.particles_[i].current_particle_value = ttf(swarm.particles_[i].current_position, swarm.solutions_[i].variablesX, graph, vertex_amount) + icf(swarm.particles_[i].current_position, lower_bound, graph, vertex_amount);
        std:: cout <<  swarm.particles_[i].current_particle_value <<std::endl;
        if(swarm.particles_[i].current_particle_value <= swarm.particles_[i].best_particle_value){
            swarm.particles_[i].best_particle_value = swarm.particles_[i].current_particle_value;
            swarm.particles_[i].best_position = swarm.particles_[i].current_position;
        }
        if(swarm.particles_[i].current_particle_value <= swarm.best_swarm_value){
            swarm.best_swarm_value = swarm.particles_[i].current_particle_value;
            swarm.best_swarm_position = swarm.particles_[i].current_position;
        }
    }
        ++iterations_counter;
        result.best_swarm_value.push_back(swarm.best_swarm_value);
        result.best_swarm_position.push_back(swarm.best_swarm_position);
        std:: cout <<iterations_counter << ' ' << "Best value:" << swarm. best_swarm_value << std::endl;
    }
    std::ofstream out;          // поток для записи
        out.open("/Users/daryakuznetsova/Desktop/BPSOQ/results.txt"); // окрываем файл для записи
        if(out.is_open()) {
            out << "Best function results from iteration 0 to " << iterations_amount-1 << ':' << std::endl;
            for (double i :  result.best_swarm_value)
                out << i << ' ';
            out << std::endl << std::endl;
            out << "Best particle position on each iteration." << std::endl;
            for(int k = 0; k < iterations_amount; ++k){
                out << "Iteration " << k << ':' <<std::endl;
                for(int i = 0; i < vertex_amount; ++i){
                    for(int j = 0; j < vertex_amount; ++j){
                        out << result.best_swarm_position[k][i][j] << ' ';
                    }
                    out << std::endl;
                }
                out << std::endl;
            }
        }
}
#endif /* optimization_h */
