#include "PhylogenyTree.hpp"

PhylogenyTree::PhylogenyTree(const Animal& root_animal, std::vector<Animal> animals_to_add, std::vector<std::vector<int>>& animal_dist_matrix){

    // Construct min priority queue
    EdgeMinPqueue edge_pq = EdgeMinPqueue();
    for (const auto& animal : animals_to_add) {
        if (!(animal == root_animal)) edge_pq.emplace(root_animal, animal, animal_dist_matrix);
    }

    // Construct list of nodes and push_back root
    nodes = std::list<PhylogenyNode*>();
    PhylogenyNode* new_child = new PhylogenyNode(root_animal);
    nodes.push_back(new_child);

    // Add each animal to tree
    int num_not_added = animals_to_add.size() - 1;
    while (num_not_added > 0) {
        auto this_edge = edge_pq.top();

        if (animal_in_tree(this_edge.get_sink())) edge_pq.pop(); // Ignore edge if sink already in tree
        else {
            auto source_node = get_node(this_edge.get_source()); // Find Node with source animal
            PhylogenyNode* new_child = new PhylogenyNode(this_edge.get_sink()); // Make new child node for sink animal
            source_node->get_children().push_back(new_child); // Add sink animal to source animal's children list
            nodes.push_back(new_child); // Add sink animal to nodes
            for (const auto& animal : animals_to_add) {
                if (!(this_edge.get_sink() == animal)) edge_pq.emplace(this_edge.get_sink(), animal, animal_dist_matrix);
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

void PhylogenyTree::print_tree_rec(PhylogenyNode* node, int level, std::vector<std::string>& collect_children) {
    if (level == 0) collect_children.push_back(node->get_animal().get_name());
    else {
        for (auto child : node->get_children()) print_tree_rec(child, level - 1, collect_children);
    }
}

void PhylogenyTree::print_tree(int level) {
    std::string tabs = "";
    for(int i = 0; i < level; i++) tabs += "\t";
    std::cout << nodes.front()->get_animal().get_name() << std::endl;
    std::vector<std::string> collect_children;
    if (level != 0) {
        for (auto child : nodes.front()->get_children()) print_tree_rec(child, level - 1, collect_children);
    }
    std::sort(collect_children.begin(), collect_children.end());
    for (const auto child_name : collect_children) std::cout << tabs << child_name << std::endl;
}