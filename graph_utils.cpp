#include "graph_utils.h"
#include <iostream>
#include "graph.h"

void print_graph(const graph& g)
{
	std::cout << "Graph: " << std::endl;
    for (auto& node : g.nodes)
    {
        std::cout << "value:";
        std::cout << node.first << std::endl;
        std::cout << "in:";
        std::cout << node.second->in << std::endl;
        for (auto& edge : g.edges)
        {
            if (edge.get()->to.lock() == node.second)
            {
                std::cout << edge.get()->from.lock().get()->value << ",";
            }
        }
        std::cout << std::endl;
        std::cout << "out:";
        std::cout << node.second->out << std::endl;
        std::cout << "next:";
        for (auto& n : node.second.get()->nexts)
        {
            std::cout << n.get()->value << ",";
        }
        std::cout << std::endl;
        std::cout << "--------------" << std::endl;
    }
}

void print_node(const graph& g, const graph_node& n)
{
    for (auto& node : g.nodes)
    {
        if (node.first != n.value)
        {
            continue;
        }
        std::cout << "value:";
        std::cout << node.first << std::endl;
        std::cout << "in:";
        std::cout << node.second->in << std::endl;
        for (auto& edge : g.edges)
        {
            if (edge.get()->to.lock().get()->value == node.second.get()->value)
            {
                std::cout << edge.get()->to.lock().get()->value << ",";
            }
        }
        std::cout << std::endl;
        std::cout << "out:";
        std::cout << node.second->out << std::endl;
        std::cout << "next:";
        for (auto& n : node.second.get()->nexts)
        {
            std::cout << n.get()->value << ",";
        }
        std::cout << std::endl;
        std::cout << "--------------" << std::endl;
    }
}

void print_edge(const std::unordered_set<std::shared_ptr<graph_edge>>& edges)
{
    for (auto& edge : edges)
    {
        std::cout << "from:";
        std::cout << edge.get()->from.lock()->value << std::endl;
        std::cout << "to:";
        std::cout << edge.get()->to.lock()->value << std::endl;
        std::cout << "weight:";
        std::cout << edge->weight << std::endl;
        std::cout << std::endl;
        std::cout << "--------------" << std::endl;
    }
}

void print_edge(const std::vector<std::shared_ptr<graph_edge>>& edges)
{
    for (auto& edge : edges)
    {
        std::cout << "from:";
        std::cout << edge.get()->from.lock()->value << std::endl;
        std::cout << "to:";
        std::cout << edge.get()->to.lock()->value << std::endl;
        std::cout << "weight:";
        std::cout << edge.get()->weight << std::endl;
        std::cout << std::endl;
        std::cout << "--------------" << std::endl;
    }
}

graph gen_graph(int arr[][3], const int len, const bool direct)
{
    graph g;
    for (int i = 0; i < len; ++i)
    {
        int from = arr[i][0];
        int to = arr[i][1];
        int weight = arr[i][2];
        auto fromIter = g.nodes.find(from);
        auto toIter = g.nodes.find(to);
        if (fromIter == g.nodes.end())
        {
            g.nodes[from] = std::make_shared<graph_node>(from);
        }
        if (toIter == g.nodes.end())
        {
            g.nodes[to] = std::make_shared<graph_node>(to);
        }

        auto fromNode = g.nodes[from];
        auto toNode = g.nodes[to];
        auto edge = std::make_shared<graph_edge>(weight, fromNode, toNode);
        fromNode->nexts.push_back(toNode);
        fromNode->out++;
        toNode->in++;
        fromNode->edges.push_back(edge);
        g.edges.insert(edge);
        if (!direct)
        {
            auto edge1 = std::make_shared<graph_edge>(weight, toNode, fromNode);
            toNode->nexts.push_back(fromNode);
            toNode->out++;
            fromNode->in++;
            toNode->edges.push_back(edge1);
            g.edges.insert(edge1);
        }
    }
    return g;
}


