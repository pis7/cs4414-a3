#include <list>
#include <functional>
#include <iostream>
#include "PhylogenyTree.hpp"

// From Sagar's wc++
std::vector<std::filesystem::path> find_all_files(
    const std::filesystem::path &dir, std::function<bool(const std::string &)> pred)
{
    std::list<std::filesystem::path> files_to_sweep;
    // Iterate recursively to find all files that satisfy pred
    for (auto &entry : std::filesystem::recursive_directory_iterator(dir))
    {
        if (entry.is_regular_file())
        {
            std::filesystem::path cur_file = entry.path();
            std::string type(cur_file.extension());
            if (pred(type))
            {
                files_to_sweep.push_back(std::move(cur_file));
            }
        }
    }
    return std::vector<std::filesystem::path>(std::make_move_iterator(files_to_sweep.begin()), std::make_move_iterator(files_to_sweep.end()));
}

int main(int argc, char *argv[]) {

    // Confirm correct argyments
    if (argc != 3) {
        std::cerr << "Invalid number of program arguments!" << std::endl;
        return -1;
    }

    // Get all .dat files
    auto file_vec = find_all_files(
        "SpeciesData", 
        [](const std::string& str) -> bool {
            return (str.size() >= 4 && str.substr(str.size() - 4) == ".dat");
        }
    );

    // Create and fill animals vector
    std::vector<Animal> animals;
    for (const auto& file_path : file_vec) {
        std::ifstream dat_file(file_path);
        if (dat_file.is_open()) animals.emplace_back(dat_file);
        else std::cerr << "Unable to open dat file!" << std::endl;
    }
    
    // Sort all animals in alphabetical order by name and assign id's
    int animal_id = 0;
    std::sort(animals.begin(), animals.end());
    for (auto& animal : animals) {
        animal.set_id(animal_id++);
    }

    // Push back all animals' genes onto all_genes vector (no duplicates)
    std::vector<Gene> all_genes;
    for(const auto& animal : animals){
        for(auto gene : animal.get_dna()) {
            Gene::unique_push_back(all_genes, gene);
        }
    }

    // Sort all genes in ascending length order (lexicographic second)
    std::sort(all_genes.begin(), all_genes.end());

    // ID genes according to order
    int gene_id = 0;
    for (auto& gene : all_genes) {
        gene.set_id(gene_id);
        for (auto& animal : animals) {
            animal.set_dna_gene_id(gene, gene_id);
        }
        gene_id++;
    }

    // Sort genes vector in each animal once overall order has been determined
    for (auto& animal : animals) {
        animal.sort_genes();
    }


}