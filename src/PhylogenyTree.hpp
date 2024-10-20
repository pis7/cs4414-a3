#pragma once
#include <queue>
#include <list>
#include <algorithm>
#include "Animal.hpp"

class PhylogenyTree {
public:

    class PhylogenyEdge {
    public:
        PhylogenyEdge(const Animal& source_, const Animal& sink_) : source(source_), sink(sink_), weight(source.distance(sink)) {}
        friend bool operator>(const PhylogenyEdge& a, const PhylogenyEdge& b) {return a.weight > b.weight;}
        Animal& get_source() {return source;}
        const Animal& get_sink() const {return sink;}
    private:
        Animal source;
        Animal sink;
        int weight;
    };

    typedef std::priority_queue<PhylogenyEdge, std::vector<PhylogenyEdge>, std::greater<PhylogenyEdge>> EdgeMinPqueue;

    PhylogenyTree(const Animal& root_animal, std::list<Animal> animals_to_add);

    class PhylogenyNode {
    public:
        PhylogenyNode(const Animal& animal_) : animal(animal_), children(std::list<PhylogenyNode>()) {}
        std::list<PhylogenyNode>& get_children() {return children;}
        const Animal& get_animal() const {return animal;}
    private:
        Animal animal;
        std::list<PhylogenyNode> children;
    };

private:
    std::list<PhylogenyNode> nodes;
    bool animal_in_tree(const Animal& animal) const;
    PhylogenyNode* get_node(const Animal& animal);
};