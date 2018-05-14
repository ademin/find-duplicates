#include "Filter.hpp"

std::forward_list<boost::filesystem::path> Filter::filter(const boost::filesystem::path& path) const
{
    std::forward_list<boost::filesystem::path> files;
    
    for (const auto& it : boost::filesystem::recursive_directory_iterator{path}) {
        if (boost::filesystem::is_regular_file(it.path())) files.push_front(it.path());
    }
    
    return files;
}
