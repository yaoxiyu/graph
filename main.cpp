#include <memory>
#include <iostream>

#include "graph.h"
#include "graph_utils.h"
#include "graph_algorithm.h"


int arr1[][3] = {
    {1,2,1},
    {1,3,2},
    {1,4,3},
    {5,6,5},
    {2,5,6},
    {3,5,7},
    {4,6,8},
    {9,8,9},
    {6,8,10},
    {4,7,100},
    {7,8,1000},
};

int arr2[][3] = {
    {1,2,1},
    {1,3,2},
    {2,3,3},
    {2,4,4},
    {3,4,5},
};

void dijkstra1()
{
       
    auto g = gen_graph(arr1, 11, false);

    auto head = g.nodes[1];
    auto map = dijkstra(head);

    std::cout << "head: " << head.get()->value << std::endl;
    for (auto& pairs : map)
    {
        std::cout << "key: " << pairs.first.get()->value << std::endl;
        std::cout << "val: " << pairs.second << std::endl;
        std::cout << "-------" << std::endl;
    } 
}

void dijkstra2()
{
       
    auto g = gen_graph(arr2, 5, false);

    auto head = g.nodes[1];
    auto map = dijkstra(head);

    std::cout << "head: " << head.get()->value << std::endl;
    for (auto& pairs : map)
    {
        std::cout << "key: " << pairs.first.get()->value << std::endl;
        std::cout << "val: " << pairs.second << std::endl;
        std::cout << "-------" << std::endl;
    } 
}

int main()
{
    dijkstra1();
}


