#pragma once

#include <queue>
#include <list>
#include <iostream>

#include "Animal.hpp"

class PhylogenyTree {
public:

    class PhylogenyEdge {
    public:
        PhylogenyEdge(const Animal& source_, const Animal& sink_) : source(source_), sink(sink_), weight(source.distance(sink)) {}
        friend bool operator>(const PhylogenyEdge& a, const PhylogenyEdge& b) {
            if (a.weight == b.weight) return a.sink > b.sink;
            else return a.weight > b.weight;
        }
        Animal& get_source() {return source;}
        const Animal& get_sink() const {return sink;}
    private:
        Animal source;
        Animal sink;
        int weight;
    };

    class PhylogenyNode {
    public:
        PhylogenyNode(const Animal& animal_) : animal(animal_), children(std::list<PhylogenyNode*>()) {}
        std::list<PhylogenyNode*>& get_children() {return children;}
        const Animal& get_animal() const {return animal;}
    private:
        Animal animal;
        std::list<PhylogenyNode*> children;
    };

    typedef std::priority_queue<PhylogenyEdge, std::vector<PhylogenyEdge>, std::greater<PhylogenyEdge>> EdgeMinPqueue;
    PhylogenyTree(const Animal& root_animal, std::vector<Animal> animals_to_add);
    ~PhylogenyTree();
    void print_tree(int level);
private:
    std::list<PhylogenyNode*> nodes;
    bool animal_in_tree(const Animal& animal) const;
    PhylogenyNode* get_node(const Animal& animal);
    void print_tree_rec(PhylogenyNode* node, int level, std::string tabs);
};