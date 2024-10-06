#include <list>
#include <vector>
#include <functional>
#include <iostream>

#include "Animal.hpp"

// from Sagar's wc++
std::vector<std::filesystem::path> find_all_files(
    const std::filesystem::path &dir, std::function<bool(const std::string &)> pred)
{
    std::list<std::filesystem::path> files_to_sweep;
    // iterate recursively to find all files that satisfy pred
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

void unique_push_back(std::vector<Gene>& gene_arr, const Gene& gene) {
    if (std::find(gene_arr.begin(), gene_arr.end(), gene) == gene_arr.end()) gene_arr.push_back(gene);
}


int main(int argc, char *argv[])
{

    // confirm correct argyments
    if (argc != 2) {
        std::cerr << "Invalid number of program arguments!" << std::endl;
        return -1;
    }

    // get all .dat files
    auto file_vec = find_all_files(
        std::string(argv[1]), 
        [](const std::string& str) -> bool {
            return (str.size() >= 4 && str.substr(str.size() - 4) == ".dat");
        }
    );

    // create and fill animals vector
    std::vector<Animal> animals;
    for (const auto& file_path : file_vec) {
        std::ifstream dat_file(file_path);
        if (dat_file.is_open()) animals.emplace_back(dat_file);
        else std::cerr << "Unable to open dat file!" << std::endl;
    }
    
    // sort all animals in alphabetical order by name and assign id's
    int animal_id = 0;
    std::sort(animals.begin(), animals.end());
    for (auto& animal : animals) {
        animal.set_id(animal_id++);
    }

    // push back all animals' genes onto all_genes vector (no duplicates)
    std::vector<Gene> all_genes;
    for(const auto& animal : animals){
        for(auto gene : animal.get_dna()) {
            unique_push_back(all_genes, gene);
        }
    }

    // sort all genes in ascending length order (lexicographic second)
    std::sort(all_genes.begin(), all_genes.end());

    // id genes according to order
    int gene_id = 0;
    for (auto& gene : all_genes) {
        gene.set_id(gene_id);
        for (auto& animal : animals) {
            animal.set_dna_gene_id(gene, gene_id);
        }
        gene_id++;
    }

    // sort genes vector in each animal once overall order has been determined
    for (auto& animal : animals) {
        animal.sort_genes();
    }


    // print out all genes
    for (const auto& gene : all_genes) {
        std::cout << "G" << gene.get_id() << "=" << gene.get_gene() << std::endl; 
    }

    std::cout << std::endl;

    // print out all animals
    for (const auto& animal : animals) {
        std::cout << "S" << animal.get_id() << "=" << animal.get_name() <<": Genes [";

        int size = animal.get_dna().size();
        int count = 0;
        for (const auto& gene : animal.get_dna()) {
            ++count;
            std::cout << gene.get_id();
            if (count != size) std::cout << ", ";
        }

        std::cout << "]" << std::endl;
    }

    return 0;
}