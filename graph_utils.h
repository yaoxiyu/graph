#pragma once
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>

struct graph;
struct graph_edge;
struct graph_node;

void print_graph(const graph& g);

void print_node(const graph& g, const graph_node& n);

void print_edge(const std::unordered_set<std::shared_ptr<graph_edge>>& edges);

void print_edge(const std::vector<std::shared_ptr<graph_edge>>& edges);

graph gen_graph(int arr[][3], const int len, const bool direct=true);