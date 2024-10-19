#pragma once

#include <string>

class Gene
{
public:
    Gene();
    Gene(const std::string &gene_);
    Gene(const std::string &gene_, int id_);
    std::string get_gene() const;
    int get_id() const;
    void set_id(int id_);
    friend bool operator<(const Gene& a, const Gene& b);
    friend bool operator==(const Gene& a, const Gene& b);
    static int distance(const Gene& a, const Gene& b);
private:
    std::string gene;
    int id;
    static const int COMMON_COST = 15;
    static const int DIFF_NUM_COST = 8;
    static const int ONLY_IN_ONE_COST = 25;
    static const int MIN_MATCH = 4;
    static const char CHAR_ARR[];
    static int simple_score(std::string g0, std::string g1);
    static int distance_recursive(std::string g0, std::string g1);
};