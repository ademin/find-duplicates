#include "ComparatorFactory.hpp"

#include "MemcmpComparator.hpp"
#include "MD5Comparator.hpp"

std::shared_ptr<Comparator> ComparatorFactory::create(const std::string &type)
{
    std::shared_ptr<Comparator> comparator;
    
    if (type == "cmp") comparator = std::make_shared<MemcmpComparator>();
    if (type == "md5") comparator = std::make_shared<MD5Comparator>();
    
    return comparator;
}
