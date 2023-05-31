#ifndef dijkstra_h
#define dijkstra_h

std::vector<std::size_t> find_path_Dijkstra(Graph& graph, std::size_t start_index, std::size_t end_index){
    graph.init_start_values();
    std::multimap<int, std::size_t> min_weigth_map;
    graph.nodes[start_index].weight = 0;
    min_weigth_map.insert({ 0, start_index });
    while (!min_weigth_map.empty())
    {
        auto [current_weight, current_index] = *(min_weigth_map.begin());
        min_weigth_map.erase(min_weigth_map.begin());
        if (graph.nodes[current_index].visited)
        {
            continue;
        }

        graph.nodes[current_index].visited = true;
     
        for (std::size_t i = 0; i < graph.nodes[current_index].edges.size() ; ++i)
        {
            std::size_t index_to = graph.nodes[current_index].edges[i].indexTo;
            int edged_weight = graph.nodes[current_index].edges[i].weight;
            if (!graph.nodes[index_to].visited)
            {
                if (current_weight + edged_weight < graph.nodes[index_to].weight )
                {
                    graph.nodes[index_to].weight = current_weight + edged_weight;
                    graph.nodes[index_to].prevIndex = current_index;
                    min_weigth_map.insert({ graph.nodes[index_to].weight, index_to });
                }
            }
        }
    }
    return convert_graph_to_path(graph, start_index, end_index);
}

#endif /* dijkstra_h */
