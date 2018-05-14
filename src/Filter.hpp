#pragma once

#include <forward_list>

#include <boost/filesystem.hpp>

struct Filter
{
    std::forward_list<boost::filesystem::path> filter(const boost::filesystem::path& path) const;
};
