#include "MemcmpComparator.hpp"

#include <fstream>
#include <memory>

std::map<boost::filesystem::path, std::set<boost::filesystem::path>>
MemcmpComparator::compare(const std::forward_list<boost::filesystem::path>& group_a,
                          const std::forward_list<boost::filesystem::path>& group_b,
                          const size_t size) const
{
    std::forward_list<std::pair<boost::filesystem::path, std::ifstream>> ifs_a;
    std::forward_list<std::pair<boost::filesystem::path, std::ifstream>> ifs_b;
    
    for (const auto& file_a : group_a)
        ifs_a.push_front(std::make_pair<>(file_a, std::ifstream(file_a.string(), std::ios::binary)));
    for (const auto& file_b : group_b)
        ifs_b.push_front(std::make_pair<>(file_b, std::ifstream(file_b.string(), std::ios::binary)));
    
    const size_t block_size = std::min(size + 1, MAX_BLOCK_SIZE + (size % MAX_BLOCK_SIZE == 0));
    
    std::pair<std::unique_ptr<char[]>, size_t> memblock_a
    = std::make_pair(std::make_unique<char[]>(block_size), 0);
    std::pair<std::unique_ptr<char[]>, size_t> memblock_b
    = std::make_pair(std::make_unique<char[]>(block_size), 0);
    
    std::map<boost::filesystem::path, std::set<boost::filesystem::path>> equals;
    
    while (std::count_if(ifs_a.begin(), ifs_a.end(), [] (const auto& i) { return !i.second.eof(); })) {
        
        for (auto& if_a : ifs_a) {
            if_a.second.read(memblock_a.first.get(), block_size);
            memblock_a.second = if_a.second.gcount();
            
            for (auto& if_b : ifs_b) {
                if_b.second.read(memblock_b.first.get(), block_size);
                memblock_b.second = if_b.second.gcount();
                
                if (memblock_a.second == memblock_b.second &&
                    std::memcmp(memblock_a.first.get(), memblock_b.first.get(), memblock_a.second) == 0) {
                    
                    equals[if_a.first].insert(if_b.first);
                } else {
                    auto duplicates = equals[if_a.first];
                    if (auto it = duplicates.find(if_b.first); it != duplicates.end()) duplicates.erase(it);
                    if (duplicates.size() == 0) equals.erase(if_a.first);
                }
            }
        }
    }
    
    return equals;
}

