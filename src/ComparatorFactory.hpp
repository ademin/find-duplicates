#pragma once

#include "Comparator.hpp"

#include <memory>

struct ComparatorFactory
{
    static std::shared_ptr<Comparator> create(const std::string& type);
};
