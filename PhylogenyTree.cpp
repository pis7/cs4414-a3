#include "PhylogenyTree.hpp"

PhylogenyTree::PhylogenyTree(const Animal& root_animal, std::vector<Animal> animals_to_add){

    // Construct min priority queue
    EdgeMinPqueue pq = EdgeMinPqueue();
    for (const auto& animal : animals_to_add) {
        if (!(animal == root_animal)) pq.emplace(root_animal, animal);
    }

    // Construct list of nodes and push_back root
    nodes = std::list<PhylogenyNode*>();
    PhylogenyNode* new_child = new PhylogenyNode(root_animal);
    nodes.push_back(new_child);

    // Add each animal to tree
    int num_not_added = animals_to_add.size() - 1;
    while (num_not_added > 0) {
        auto this_edge = pq.top();

        if (animal_in_tree(this_edge.get_sink())) pq.pop(); // Ignore edge if sink already in tree
        else {
            auto source_node = get_node(this_edge.get_source()); // Find Node with source animal
            PhylogenyNode* new_child = new PhylogenyNode(this_edge.get_sink()); // Make new child node for sink animal
            source_node->get_children().push_back(new_child); // Add sink animal to source animal's children list
            nodes.push_back(new_child); // Add sink animal to nodes
            for (const auto& animal : animals_to_add) {
                if (!(this_edge.get_sink() == animal)) pq.emplace(this_edge.get_sink(), animal);
            }
            num_not_added--;
        }
    }
}

PhylogenyTree::~PhylogenyTree() {
    for (auto node : nodes) delete node;
}

bool PhylogenyTree::animal_in_tree(const Animal& animal) const {
    for (const auto node : nodes) {
        if (node->get_animal() == animal) return true;
    }
    return false;
}

PhylogenyTree::PhylogenyNode* PhylogenyTree::get_node(const Animal& animal) {
    for (auto node : nodes) {
        if (node->get_animal() == animal) return node;
    }
    return nullptr;
}

void PhylogenyTree::print_tree_rec(PhylogenyNode* node, int level, std::string tabs) {
    if (level == 0) std::cout << tabs << node->get_animal().get_name() << std::endl;
    else {
        for (auto child : node->get_children()) print_tree_rec(child, level - 1, tabs);
    }
}

void PhylogenyTree::print_tree(int level) {
    std::string tabs = "";
    for(int i = 0; i < level; i++) tabs += "\t";
    std::cout << nodes.front()->get_animal().get_name() << std::endl;
    if (level != 0) {
        for (auto child : nodes.front()->get_children()) print_tree_rec(child, level - 1, tabs);
    }
}