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
private:
    std::string gene;
    int id;
};