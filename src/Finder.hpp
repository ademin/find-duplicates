#pragma once

#include <map>
#include <set>
#include <forward_list>

#include <boost/filesystem.hpp>

#include "Comparator.hpp"

struct Finder
{
    std::forward_list<std::map<boost::filesystem::path, std::set<boost::filesystem::path>>>
    find(const boost::filesystem::path& path_a,
         const boost::filesystem::path& path_b, const std::shared_ptr<Comparator> comparator) const;
};
