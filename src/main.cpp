#include <iostream>
#include <exception>

#include "Finder.hpp"
#include "MemcmpComparator.hpp"
#include "MD5Comparator.hpp"

#include "ComparatorFactory.hpp"

#include "Aggregator.hpp"

int main(int argc, char* argv[])
{
    int result = 0;
    
    try {
        
        if (argc != 4) throw std::invalid_argument("Invalid argc");
        boost::filesystem::path path_a = argv[1];
        boost::filesystem::path path_b = argv[2];
        if (!boost::filesystem::exists(path_a)) throw std::invalid_argument("Invalid argv[1]");
        if (!boost::filesystem::exists(path_b)) throw std::invalid_argument("Invalid argv[1]");
        if (!boost::filesystem::is_directory(path_a)) throw std::invalid_argument("Invalid argv[2]");
        if (!boost::filesystem::is_directory(path_b)) throw std::invalid_argument("Invalid argv[2]");
        if (auto cmp = std::string(argv[3]); cmp != "cmp" && cmp != "md5") throw std::invalid_argument("Invalid argv[4]");
        
        auto results = Finder().find(path_a, path_b, ComparatorFactory::create(std::string(argv[3])));

        for (const auto& result : results) {
            for (const auto& files : result) {
                std::cout << "File " << files.first << " has duplicates: ";
                for (const auto& duplicate : files.second) {
                    std::cout << duplicate << ", ";
                }
                std::cout << std::endl;
            }
        }

    } catch (std::invalid_argument e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        result = -1;
    } catch (std::exception e) {
        std::cerr << "Unknown exception caught" << e.what() << std::endl;
        result = -1;
    }
    
    return result;
}
