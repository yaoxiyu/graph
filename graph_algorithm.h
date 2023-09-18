#pragma once
#include<vector>
#include<unordered_map>
#include<memory>

struct graph;
struct graph_node;
struct graph_edge;

// no direct
std::vector<int> bfs(graph g);

// no direct
std::vector<int> dfs(graph g);

// direct
std::vector<int> topo(graph g);

// no direct
std::vector<graph_edge> kruskal(graph g);

// no direct
std::vector<graph_edge> prim(graph g);

// no direct
std::unordered_map<std::shared_ptr<graph_node>,int> dijkstra(std::shared_ptr<graph_node> head);