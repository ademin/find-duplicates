#include "Finder.hpp"

#include "Aggregator.hpp"
#include "Filter.hpp"
#include "Comparator.hpp"

std::forward_list<std::map<boost::filesystem::path, std::set<boost::filesystem::path>>>
Finder::find(const boost::filesystem::path& path_a,
             const boost::filesystem::path& path_b, const std::shared_ptr<Comparator> comparator) const
{
    if (comparator == nullptr) throw std::invalid_argument("comparator");
    
    // First of all, filter all entries in the pathes and stick with regular files only;
    // Secondly, group the files by size. It makes sence to compare only between same sized files.
    auto aggregation_a = Aggregator().group_by(Filter().filter(path_a));
    auto aggregation_b = Aggregator().group_by(Filter().filter(path_b));
    
    std::forward_list<std::map<boost::filesystem::path, std::set<boost::filesystem::path>>> results;
    
    // For each same sized group of files in A, find same sized group of files in B and compare files between groups.
    for (const auto& group_a : aggregation_a) {
        if (auto group_b = aggregation_b.find(group_a.first); group_b != aggregation_b.end()) {
            results.push_front(comparator->compare(group_a.second, group_b->second, group_a.first));
        }
    }
    
    return results;
}
