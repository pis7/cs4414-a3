#include <unordered_map>

#include "Gene.hpp"

// default constructor
Gene::Gene() {
    this->gene = "";
    id = 0;
}

// string-only parameterized constructor
Gene::Gene(const std::string &gene_){
    this->gene = gene_;
    id = 0;
}

// string and int parameterized constructor
Gene::Gene(const std::string &gene_, int id_){
    this->gene = gene_;
    this->id = id_;
}

std::string Gene::get_gene() const {
    return gene;
}

int Gene::get_id() const {
    return id;
}

bool operator<(const Gene &a, const Gene &b)
{
   return a.get_gene() < b.get_gene();
}