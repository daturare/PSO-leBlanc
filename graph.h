#ifndef graph_h
#define graph_h

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <optional>
#include <stack>
#include <map>
#include <cmath>
#include <stdlib.h>
#include <time.h>

const auto INF = std::numeric_limits<int>::max();

struct Edge{
    double weight;
    std::size_t indexTo;
};

struct Node{
    int id;
    std::vector<Edge> edges;

    std::size_t prevIndex;
    double weight;
    bool visited;
};

struct Graph{
    std::vector<Node> nodes;

    void clear(){
        nodes.clear();
    }

    void clear_edges(){
        for (auto& node : nodes){
            node.edges.clear();
        }
    }

    void init_start_values(){
        for (auto& node : nodes){
            node.weight = INF;
            node.visited = false;
            node.prevIndex = INF;
        }
    }

};

bool read_nodes(std::istream& istream, std::size_t nodes_count, Graph& graph_out){
    graph_out.nodes.clear();

    for (std::size_t i = 0; i < nodes_count; i++){
        decltype(Node::id) id;
        istream >> id;
        graph_out.nodes.push_back({ id });
    }

    return true;
}

bool read_edges(std::istream& istream, std::size_t edges_count, Graph& graph_out) {
    graph_out.clear_edges();

    for (std::size_t i = 0; i < edges_count; i++) {
        int start_id, end_id;
        double weight;

        istream >> start_id >> end_id;
        istream >> weight;

        auto& nodes_ref = graph_out.nodes;

        auto start_iter = std::find_if(nodes_ref.begin(), nodes_ref.end(), [start_id](const auto& node) { return node.id == start_id; });
        auto end_iter = std::find_if(nodes_ref.begin(), nodes_ref.end(), [end_id](const auto& node) { return node.id == end_id; });

        if (start_iter == nodes_ref.end() || end_iter == nodes_ref.end()) {
            graph_out.clear_edges();

            return false;
        }
        std::size_t index = (end_iter - nodes_ref.begin());
        (*start_iter).edges.push_back(Edge{ weight, index });
    }

    return true;
}

Graph read_graph(const std::string& file_path){
    Graph graph;
    std::ifstream fin(file_path);
    if (fin){
        std::size_t node_count;
        int edge_count;

        fin >> node_count >> edge_count;

        if (read_nodes(fin, node_count, graph)){
            read_edges(fin, edge_count, graph);
        }
    }
    return graph;
}

std::vector<std::size_t> convert_graph_to_path(Graph& graph, std::size_t start_index, std::size_t end_index){
    std::vector<std::size_t> result;
    std::stack<std::size_t> tmp_path;
    std::size_t current_node = end_index;
    while (current_node != INF){
        tmp_path.push(current_node);
        current_node = graph.nodes[current_node].prevIndex;
    }
    while (!tmp_path.empty()){
        result.push_back(tmp_path.top());
        tmp_path.pop();
    }
    return result;
}

#endif /* gragh_h */
