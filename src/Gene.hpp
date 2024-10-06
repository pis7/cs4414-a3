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

private:
    std::string gene;
    int id;
};