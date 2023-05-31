#ifndef leBlanc_h
#define leBlanc_h

std::vector<std::vector<double>> GetFlowVector(Graph& graph, const std::size_t vertex_amount, const std::vector<std::vector<std::size_t>>& d){
    std::vector<std::vector<double>> x(vertex_amount, std::vector<double>(vertex_amount));
    
    for(std::size_t i = 0; i < vertex_amount; ++i){
        for(std::size_t j = 0; j < vertex_amount; ++j){
            if(i != j){
                auto p = find_path_Dijkstra(graph, i, j);
                for(std::size_t l = 0; l < p.size() - 1; ++l){
                    x[p[l]][p[l+1]] = x[p[l]][p[l+1]] + d[i][j];
                }
                /*for(int i : p){
                    std::cout << i << ' ';
                }
                std::cout << std::endl;*/
            }
        }
    }
    return x;
}

std::vector<std::vector<double>> leBlanc(const std::vector<std::vector<std::size_t>>& t0, const std::vector<std::vector<std::size_t>>& d, const std::vector<std::vector<double>>& c1, const double& e, Graph graph){
    std::size_t vertex_amount = d.size();
    bool stop = false;
    std::vector<std::vector<double>> x1 = GetFlowVector(graph, vertex_amount, d);
    std::size_t iteration_num = 0;
    
    while(stop!=true){
        std::vector<std::vector<double>> t1(vertex_amount, std::vector<double>(vertex_amount));
        for(std::size_t i = 0; i < vertex_amount; ++i){
            for(std::size_t j = 0; j < vertex_amount; ++j){
                if(c1[i][j] != 0){
                    t1[i][j] = t0[i][j] * (1 + 0.15*(pow(x1[i][j]/c1[i][j], 4)));
                }
            }
        }
       
        auto graph1 = graph;
        for(std::size_t i = 0; i < vertex_amount; ++i){
            for(std::size_t j = 0; j < graph1.nodes[i].edges.size(); ++j){
                graph1.nodes[i].edges[j].weight = t1[i][graph1.nodes[i].edges[j].indexTo];
            }
        }
        std::vector<std::vector<double>> y = GetFlowVector(graph1, vertex_amount, d);
        std::vector<std::vector<float>> ccalc(vertex_amount, std::vector<float>(vertex_amount));
        for(std::size_t i = 0; i < vertex_amount; ++i){
            for(std::size_t j = 0; j < vertex_amount; ++j){
                if(c1[i][j]!=0){
                    ccalc[i][j] = 1/pow(c1[i][j],4);
                }
            }
        }
        
        double h = 0.001;
        std::vector<double> l;
        double counter = 0.;
        while(counter < 1){
            l.push_back(counter);
            counter+=h;
        }
        double dfi = 0.;
        double dfi_plus_one = 0.;
        float lambda = 0.5;
        for(std::size_t l_count = 0; l_count < l.size( ) - 1; ++l_count){
            for(std::size_t i = 0; i < vertex_amount; ++i){
                for(std::size_t j = 0; j < vertex_amount; ++j){
                    dfi += (t0[i][j]*(y[i][j]-x1[i][j]) + 0.15*t0[i][j]*ccalc[i][j]*(pow((x1[i][j]+l[l_count]*(y[i][j]-x1[i][j])),4)*(y[i][j]-x1[i][j])));
                    dfi_plus_one += (t0[i][j]*(y[i][j]-x1[i][j]) + 0.15*t0[i][j]*ccalc[i][j]*(pow((x1[i][j]+l[l_count+1]*(y[i][j]-x1[i][j])),4)*(y[i][j]-x1[i][j])));
                }
            }
            if((dfi<0&&dfi_plus_one<0)||(dfi>0&&dfi_plus_one>0)){
                lambda = h*l_count + h/2;
                l_count = l.size() + 1;
            } else {
                lambda = 0.5;
            }
        }
        std::vector<std::vector<double>> x2 (vertex_amount, std::vector<double>(vertex_amount));
        for(std::size_t i = 0; i < vertex_amount; ++i){
            for(std::size_t j = 0; j < vertex_amount; ++j){
                x2[i][j] = x1[i][j] + lambda * (y[i][j]-x1[i][j]);
            }
        }
        std::vector<std::vector<double>> dif_val (vertex_amount, std::vector<double>(vertex_amount));
        std::vector<double> max_el;
        for(std::size_t i = 0; i < vertex_amount; ++i){
            for(std::size_t j = 0; j < vertex_amount; ++j){
                if(x1[i][j]!=0){
                    dif_val[i][j] = abs((x2[i][j]-x1[i][j])/x1[i][j]);
                }
            }
            max_el.push_back(*max_element(dif_val[i].begin(), dif_val[i].end()));
        }
        if(*max_element(max_el.begin(), max_el.end())<e){
            stop = true;
        } else {
            stop = false;
            x1 = x2;
            ++iteration_num;
        }
        double result = 0.;
        for(int i = 0; i < vertex_amount; ++i){
            for(int j = 0; j < vertex_amount; ++j){
                result += t0[i][j]*x1[i][j] + t0[i][j]*0.03*ccalc[i][j]*pow(x1[i][j],5);
            }
        }
    }
    return x1;
}

#endif /* leBlanc_h */
