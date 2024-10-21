#include <functional>

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

int main(int argc, char *argv[])
{

    // Confirm correct argyments
    if (argc != 3) {
        std::cerr << "Invalid number of program arguments!" << std::endl;
        return -1;
    }

    // Get all .dat files
    auto file_vec = find_all_files(
        ".", 
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


    // Print out all genes
    for (const auto& gene : all_genes) {
        std::cout << "G" << gene.get_id() << "=" << gene.get_gene() << std::endl; 
    }

    std::cout << std::endl;

    // Print out gene comparison matrix
    for (size_t r = 0; r < all_genes.size() + 1; r++) {
        for (size_t c = 0; c < all_genes.size(); c++) {
            if (r == 0) { // Print column names on first row
                std::cout << "G" << c << '\t';
            } else {
                std::cout << all_genes[r - 1].distance(all_genes[c]) << '\t';
            }
            if (c == all_genes.size() - 1) std::cout << std::endl;
        }
    }

    std::cout << std::endl;

    // Print out all animals
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

    std::cout << std::endl;

    // Print out animal comparison matrix
    for (size_t r = 0; r < animals.size() + 1; r++) {
        for (size_t c = 0; c < animals.size(); c++) {
            if (r == 0) { // Print column names on first row
                std::cout << "S" << c << '\t';
            } else {
                std::cout << animals[r - 1].distance(animals[c]) << '\t';
            }
            if (c == animals.size() - 1) std::cout << std::endl;
        }
    }

    std::cout << std::endl;

    // Construct and print tree
    PhylogenyTree phy_tree(animals[atoi(argv[1])], animals);
    phy_tree.print_tree(atoi(argv[2]));

    return 0;
}