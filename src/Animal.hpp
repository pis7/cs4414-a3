#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "Gene.hpp"

class Animal
{
public:
    Animal();
    Animal(std::ifstream& file);
    void sort_genes();
    std::vector<Gene> get_dna() const;
    int get_id() const;
    void set_id(int id_);
    void set_dna_gene_id(const Gene& set_gene, int id_);
    std::string get_name() const;
    friend bool operator<(const Animal& a, const Animal& b);
    bool is_sibling(const Animal& other);
private:
    std::string name;
    std::string latinName;
    std::filesystem::path imageFilename;
    std::vector<Gene> dna;
    int id;

    std::string return_next_content(std::ifstream& dat_file);
    void extract_genes(std::string dna_str);
};