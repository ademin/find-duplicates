#include "Aggregator.hpp"

Aggregator::Aggregation Aggregator::group_by(const std::forward_list<boost::filesystem::path>& files) const
{
    std::map<size_t, std::forward_list<boost::filesystem::path>> aggregation;
    
    for (const auto& file : files) {
        aggregation[boost::filesystem::file_size(file)].push_front(file);
    }
    
    return aggregation;
}
