#include "PhylogenyTree.hpp"

PhylogenyTree::PhylogenyTree(const Animal& root_animal, std::list<Animal> animals_to_add){

    // Construct min priority queue
    EdgeMinPqueue pq = EdgeMinPqueue();
    for (const auto& animal : animals_to_add) pq.emplace(root_animal, animal);

    // Construct list of nodes and push_back root
    nodes = std::list<PhylogenyNode>();
    nodes.emplace_back(root_animal);

    // Add each animal to tree
    int num_not_added = animals_to_add.size();
    while (num_not_added > 0) {
        auto this_edge = pq.top();

        if (animal_in_tree(this_edge.get_sink())) pq.pop(); // Ignore edge if sink already in tree
        else { // Add sink to source node's children, update minpqueue edges and count
            auto source_node = get_node(this_edge.get_source());
            source_node->get_children().emplace_back(this_edge.get_sink());
            for (const auto& animal : animals_to_add) {
                if (this_edge.get_sink().get_name() != animal.get_name()) pq.emplace(this_edge.get_sink(), animal);
            }
            num_not_added--;
        }
    }
}

bool PhylogenyTree::animal_in_tree(const Animal& animal) const {
    for (auto& node : nodes) {
        if (node.get_animal().get_name() == animal.get_name()) return true;
    }
    return false;
}

PhylogenyTree::PhylogenyNode* PhylogenyTree::get_node(const Animal& animal) {
    for (auto& node : nodes) {
        if (node.get_animal().get_name() == animal.get_name()) return &node;
    }
    return nullptr;
}