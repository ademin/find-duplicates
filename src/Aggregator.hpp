#pragma once

#include <map>
#include <forward_list>

#include <boost/filesystem.hpp>

struct Aggregator
{
public:
    using Aggregation = std::map<size_t, std::forward_list<boost::filesystem::path>>;
    
    Aggregator::Aggregation group_by(const std::forward_list<boost::filesystem::path>& path) const; // Size
};
