#pragma once

#include "Comparator.hpp"

struct MD5Comparator : Comparator
{
    std::map<boost::filesystem::path, std::set<boost::filesystem::path>>
    compare(const std::forward_list<boost::filesystem::path>& group_a,
            const std::forward_list<boost::filesystem::path>& group_b,
            const size_t size) const override;
};
