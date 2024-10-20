#pragma once

#include <string>

class Gene {
public:
    Gene();
    Gene(const std::string &gene_);
    Gene(const std::string &gene_, int id_);
    std::string get_gene() const;
    int get_id() const;
    void set_id(int id_);
    static void unique_push_back(std::vector<Gene>& gene_arr, const Gene& gene);
    friend bool operator<(const Gene& a, const Gene& b);
    friend bool operator==(const Gene& a, const Gene& b);
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