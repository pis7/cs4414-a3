#include "Animal.hpp"

Animal::Animal() {
    this->name = "";
    this->latinName = "";
    this->imageFilename = "";
}

Animal::Animal(std::ifstream &file) {
    this->name = return_next_content(file);
    this->latinName = return_next_content(file);
    this->imageFilename = return_next_content(file);
    extract_genes(return_next_content(file));
}

void Animal::sort_genes() {
    std::sort(dna.begin(), dna.end(), 
        [](const Gene& a, const Gene& b) -> bool {
            return a.get_id() < b.get_id();
        }
    );
}

std::string Animal::return_next_content(std::ifstream& dat_file) {
    std::string this_line;
    std::getline(dat_file, this_line);

    size_t begin_ctnt = this_line.find('\"');
    if (begin_ctnt == std::string::npos) return "";
    size_t end_ctnt = this_line.find('\"', begin_ctnt + 1);
    if (end_ctnt == std::string::npos) return "";

    return this_line.substr(begin_ctnt + 1, end_ctnt - begin_ctnt - 1);
}

void Animal::extract_genes(std::string dna_str) {

    // generate segments
    size_t seg_start = dna_str.find("IAY", 0);
    size_t seg_end = 0;
    while (seg_start != std::string::npos) {
        seg_start += 3;
        seg_end = dna_str.find("TYI", seg_start);
        if (seg_end == std::string::npos) break;
        else {
            dna.emplace_back(dna_str.substr(seg_start, seg_end - seg_start));
        }
        seg_start = dna_str.find("IAY", seg_start);
    }
}

// return copy of dna vector so member genes not modified
std::vector<Gene> Animal::get_dna() const {
    return dna;
}

int Animal::get_id() const {
    return id;
}

void Animal::set_dna_gene_id(const Gene& set_gene, int id_) {
    for (auto& gene : dna) {
        if (gene == set_gene) gene.set_id(id_);
    }
}

void Animal::set_id(int id_) {
    this->id = id_;
}

std::string Animal::get_name() const {
    return name;
}

bool operator<(const Animal& a, const Animal& b) {
    return a.name < b.name;
};

bool Animal::is_sibling(const Animal& other) {
    for (const auto& gene_a : dna) {
        for (const auto& gene_b : other.get_dna()) {
            if (gene_a.get_gene() == gene_b.get_gene()) return true;
        }
    }

    return false;
}