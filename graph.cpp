#include "graph.h"
#include <iostream>

graph::graph(const graph& g)
{
    for (auto& edge : g.edges)
    {
        std::shared_ptr<graph_node> from = nullptr;
        std::shared_ptr<graph_node> to = nullptr;
        if (edge){
            auto edge_from = edge.get()->from.lock();
            auto edge_to = edge.get()->to.lock();
            auto edge_weight = edge.get()->weight;
            if (edge_from)
            {
                auto node = edge_from.get();
                auto value = node->value;
                if (this->nodes.find(value) != this->nodes.end())
                {
                    from = std::make_shared<graph_node>(value);
                    from.get()->in = node->in;
                    from.get()->out = node->out;
                    this->nodes[value] = std::move(from);
                }
                else
                {
                    from = this->nodes[value];
                }
            }
            if (edge_to)
            {
                auto node = edge_to.get();
                auto value = node->value;
                if (this->nodes.find(value) != this->nodes.end())
                {
                    to = std::make_shared<graph_node>(value);
                    to.get()->in = node->in;
                    to.get()->out = node->out;
                    this->nodes[value] = std::move(from);
                }
                else
                {
                    to = this->nodes[value];
                }
            }
            auto new_edge = std::make_shared<graph_edge>(edge_weight, from, to);
            this->edges.insert(std::move(new_edge));
        }
    }
    for (auto& edge : this->edges)
    {
        auto& from = edge.get()->from;
        auto& to = edge.get()->to;
        from.lock().get()->nexts.push_back(to.lock());
        from.lock().get()->edges.push_back(edge);
    }
}

bool graph_node::operator==(const graph_node &other)
{
    return this->value == other.value;
}
