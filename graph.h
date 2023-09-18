#pragma once
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>

struct graph;
struct graph_edge;
struct graph_node;

struct graph
{
    std::unordered_map<int, std::shared_ptr<graph_node>> nodes;
    std::unordered_set<std::shared_ptr<graph_edge>> edges;

    graph() = default;
    graph(const graph& g);
};

struct graph_edge
{
    int weight;
    std::weak_ptr<graph_node> from;
    std::weak_ptr<graph_node> to;
    
    graph_edge(int weight,  std::shared_ptr<graph_node> from,  std::shared_ptr<graph_node> to)
    : weight(weight), from(from), to(to){}
};

struct graph_node
{
    int value;
    int in;
    int out;

    std::vector<std::shared_ptr<graph_node>> nexts;
    std::vector<std::shared_ptr<graph_edge>> edges;

    graph_node() = default;
    graph_node(int value) : value(value), in(0), out(0){}

    bool operator==(const graph_node& other);
};