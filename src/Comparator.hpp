#pragma once

#include <forward_list>
#include <map>
#include <set>

#include <boost/filesystem.hpp>

struct Comparator
{
    virtual std::map<boost::filesystem::path, std::set<boost::filesystem::path>>
    compare(const std::forward_list<boost::filesystem::path>& group_a,
            const std::forward_list<boost::filesystem::path>& group_b,
            const size_t size) const = 0;
};
