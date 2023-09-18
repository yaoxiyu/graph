#include "graph.h"
#include "graph_algorithm.h"
#include <queue>
#include <stack>
#include <unordered_set>
#include <memory>

std::vector<int> bfs(graph g)
{
    std::vector<int> result;
    if (g.nodes.begin() == g.nodes.end())
    {
        return result;
    }
    std::shared_ptr<graph_node> head = g.nodes.begin()->second;
    std::queue<std::shared_ptr<graph_node>> queue;
    std::unordered_set<std::shared_ptr<graph_node>> set;
    queue.push(head);
    set.insert(head);
    while(!queue.empty())
    {
        auto node = queue.front();
        result.push_back(node.get()->value);
        queue.pop();
        for (auto& next : node.get()->nexts)
        {
            if (set.find(next) == set.end())
            {
                continue;
            }
            queue.push(next);
            set.insert(next);
        }
    }

    return result;
}

std::vector<int> dfs(graph g)
{
    std::vector<int> result;
    if (g.nodes.begin() == g.nodes.end())
    {
        return result;
    }
    std::shared_ptr<graph_node> head = g.nodes.begin()->second;
    std::stack<std::shared_ptr<graph_node>> stack;
    std::unordered_set<std::shared_ptr<graph_node>> set;
    stack.push(head);
    set.insert(head);
    result.push_back(head.get()->value);
    while(!stack.empty())
    {
        auto node = stack.top();
        stack.pop();
        for (auto& next : node.get()->nexts)
        {
            if (set.find(next) == set.end())
            {
                continue;
            }
            stack.push(node);
            stack.push(next);
            set.insert(next);
            result.push_back(next.get()->value);
            break;
        }
    }

    return result;
}

std::vector<int> topo(graph g)
{
    std::unordered_set<int> set;
    std::vector<int> result;
    auto begin = g.nodes.begin();
    auto end = g.nodes.end();
    while (begin != end)
    {
        if (set.find(begin->first) != set.end() || begin->second.get()->in > 0)
        {
            begin++;
            continue;
        }
        for (auto& edge : begin->second.get()->edges)
        {
            edge.get()->to.lock().get()->in--;
        }
        set.insert(begin->first);
        result.push_back(begin->first);
        begin = g.nodes.begin();
        end = g.nodes.end();
    }
    return result;
}

std::shared_ptr<graph_node> getMinDistanceAndUnselectedNode(
    std::unordered_map<std::shared_ptr<graph_node>,int> distance_map,
    std::unordered_set<std::shared_ptr<graph_node>> selected_nodes)
{
    std::shared_ptr<graph_node> minNode = nullptr;
    int minDistance = INT32_MAX;
    for(auto& pairs : distance_map)
    {
        auto node = pairs.first;
        int distance = pairs.second;
        if (selected_nodes.find(node) == selected_nodes.end() && distance < minDistance)
        {
            minNode = node;
            minDistance = distance;
        }
    }
    return minNode;
}

std::unordered_map<std::shared_ptr<graph_node>,int> dijkstra(std::shared_ptr<graph_node> head)
{
    std::unordered_map<std::shared_ptr<graph_node>,int> distance_map;
    std::unordered_set<std::shared_ptr<graph_node>> selected_nodes;
    distance_map[head] = 0;
    auto min_node = getMinDistanceAndUnselectedNode(distance_map, selected_nodes);
    while(min_node != nullptr)
    {
        int distance = distance_map[min_node];
        for (auto& edge : min_node.get()->edges)
        {
            auto to_node = edge.get()->to.lock();
            if (distance_map.find(to_node) == distance_map.end())
            {
                distance_map[to_node] = distance + edge.get()->weight;
            }
            else
            {
                distance_map[to_node] = 
                    distance + edge.get()->weight < distance_map[to_node] ? 
                        distance + edge.get()->weight : distance_map[to_node];
            }
            
        }
        selected_nodes.insert(min_node);
        min_node = getMinDistanceAndUnselectedNode(distance_map, selected_nodes);
    }
    return distance_map;
}
