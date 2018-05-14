#pragma once

#include "Comparator.hpp"

struct MemcmpComparator : Comparator
{
    std::map<boost::filesystem::path, std::set<boost::filesystem::path>>
    compare(const std::forward_list<boost::filesystem::path>& group_a,
            const std::forward_list<boost::filesystem::path>& group_b,
            const size_t size) const override;
private:
    static constexpr size_t MAX_BLOCK_SIZE = 100*1024*1024; // 100Mb
};

