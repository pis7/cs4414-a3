#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

class Gene {
public:
    Gene() : gene(""), id(0) {}
    Gene(const std::string &gene_) : gene(gene_), id(0) {}
    Gene(const std::string &gene_, int id_) : gene(gene_), id(id_) {}
    std::string get_gene() const {return gene;}
    int get_id() const {return id;}
    void set_id(int id_) {id = id_;}
    static void unique_push_back(std::vector<Gene>& gene_arr, const Gene& gene);
    friend bool operator<(const Gene &a, const Gene &b) {
        if (a.gene.size() != b.gene.size()) {
            return a.gene.size() < b.gene.size();
        } else {
            return a.gene < b.gene;
        }
    }
    friend bool operator==(const Gene &a, const Gene &b) {
        return a.gene == b.gene;
    }
    int distance(const Gene& other) const;
private:
    std::string gene;
    int id;
    static const int COMMON_COST = 15;
    static const int DIFF_NUM_COST = 8;
    static const int ONLY_IN_ONE_COST = 25;
    static const int MIN_MATCH = 4;
    static const char CHAR_ARR[];
    int simple_score(std::string g0, std::string g1) const;
    int distance_recursive(std::string g0, std::string g1) const;
};