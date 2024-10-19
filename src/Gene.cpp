#include <unordered_map>
#include <cmath>

#include "Gene.hpp"

const char Gene::CHAR_ARR[] = "AITY";

// default constructor
Gene::Gene() {
    this->gene = "";
    id = 0;
}

// string-only parameterized constructor
Gene::Gene(const std::string &gene_){
    this->gene = gene_;
    id = 0;
}

// string and int parameterized constructor
Gene::Gene(const std::string &gene_, int id_){
    this->gene = gene_;
    this->id = id_;
}

std::string Gene::get_gene() const {
    return gene;
}

int Gene::get_id() const {
    return id;
}

void Gene::set_id(int id_) {
    this->id = id_;
}

bool operator<(const Gene &a, const Gene &b) {
    if (a.gene.size() != b.gene.size()) {
        return a.gene.size() < b.gene.size();
    } else {
        return a.gene < b.gene;
    }
}

bool operator==(const Gene &a, const Gene &b) {
    return a.gene == b.gene;
}

int Gene::simple_score(std::string g0, std::string g1) {
    std::unordered_map<char, int> g0_chars;
    std::unordered_map<char, int> g1_chars;

    // Initialize char maps to 0
    for (auto c : CHAR_ARR) {
        if (c != '\0') {
            g0_chars[c] = 0;
            g1_chars[c] = 0;
        }
    }

    // Obtain character counts
    for (size_t i = 0; i < g0.length(); i++) {
        g0_chars[g0[i]]++;
    }

    for (size_t i = 0; i < g1.length(); i++) {
        g1_chars[g1[i]]++;
    }

    // Calculate total cost
    int total_cost = 0;
    int larger_num;
    int num_common;

    for (auto c : CHAR_ARR) {
        if (g0_chars[c] == 0 || g1_chars[c] == 0) {
            total_cost += g0_chars[c] != 0 ? g0_chars[c] * Gene::ONLY_IN_ONE_COST : g1_chars[c] * Gene::ONLY_IN_ONE_COST;
        } else {
            larger_num = std::max(g0_chars[c], g1_chars[c]);
            num_common = std::min(g0_chars[c], g1_chars[c]);
            total_cost += num_common * Gene::COMMON_COST + (larger_num - num_common) * Gene::DIFF_NUM_COST;
        }
    }

    return total_cost;
}

int Gene::distance_recursive(std::string g0, std::string g1) {
    
    // Find match if it exists
    int match_length = 0;
    size_t g0_i, g1_i;
    for (g0_i = 0; g0_i < g0.length() - MIN_MATCH; g0_i++) {
        for (g1_i = 0; g1_i < g1.length() - MIN_MATCH; g1_i++) {

            // If found match
            if (g0.substr(g0_i, g0_i + MIN_MATCH) == g1.substr(g1_i, g1_i + MIN_MATCH)) {
                match_length = MIN_MATCH;

                // Check if match can grow (don't grow if already at end of either gene)
                for (size_t k = 0; k < std::min(g0.length(), g1.length()); k++) {
                    if (g0_i + MIN_MATCH + k < g0.length() && g1_i + MIN_MATCH + k < g1.length()
                        && g0[g0_i + MIN_MATCH + k] == g1[g1_i + MIN_MATCH + k]) match_length++;
                }

                break;
            }
        }
    }

    // Create left and right sides for g0 and g1
    std::string g0_l, g0_r, g1_l, g1_r;
    if (match_length == 0) {
        return simple_score(g0, g1);
    } else if (g0_i + match_length == g0.length() && g1_i + match_length == g1.length()) {
        return simple_score(g0.substr(0, g0_i), g1.substr(0, g1_i));
    } else {
        g0_l = g0.substr(0, g0_i);
        g0_r = g0.substr(g0_i + match_length);
        g1_l = g1.substr(0, g1_i);
        g1_r = g1.substr(g1_i + match_length);
    }

    return simple_score(g0_l, g1_l) + std::min(distance_recursive(g0_r, g1_r), distance_recursive(g1_r, g0_r));
}

int Gene::distance(const Gene& a, const Gene& b) {
    std::string g0 = a.get_gene();
    std::string g1 = b.get_gene();

    // Trim prefixes
    int prefix_length = 0;
    size_t min_length = std::min(g0.length(), g1.length());
    for (size_t i = 0; i < min_length; i++) {
        if (g0[i] == g1[i]) prefix_length++;
    }
    g0 = g0.substr(prefix_length);
    g1 = g1.substr(prefix_length);

    // Trim suffixes
    int suffix_length = 0;
    min_length = std::min(g0.length(), g1.length());
    for (size_t i = 0; i < min_length; i++) {
        if (g0[g0.length() - i - 1] == g1[g1.length() - i - 1]) suffix_length++;
        else break;
    }
    g0 = g0.substr(0, g0.length() - suffix_length);
    g1 = g1.substr(0, g1.length() - suffix_length);

    // Make sure shorter string (or alphabetically smaller string) is first
    if (!(g0.length() < g1.length()) && !(g0.length() == g1.length() && g0 < g1)) {
        std::string temp;
        temp = g0;
        g0 = g1;
        g1 = temp;
    }

    return std::min(distance_recursive(g0, g1), distance_recursive(g1, g0));
}