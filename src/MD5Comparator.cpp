#include "MD5Comparator.hpp"

#include <map>
#include <array>

#include <boost/iostreams/device/mapped_file.hpp>

#include <openssl/md5.h>

std::map<boost::filesystem::path, std::set<boost::filesystem::path>>
MD5Comparator::compare(const std::forward_list<boost::filesystem::path>& group_a,
                       const std::forward_list<boost::filesystem::path>& group_b,
                       const size_t size) const
{
    std::map<boost::filesystem::path, std::set<boost::filesystem::path>> equals;
    
    std::map<std::array<unsigned char, MD5_DIGEST_LENGTH>, boost::filesystem::path> a; // std::unordered_map is also possible here
    
    if (size == 0) for (const auto& file_b : group_b) equals[*group_a.begin()].insert(file_b); // It isn't possible to map zero-length files
    else {
        
        for (const auto& file_a : group_a) {
            auto md5 = std::array<unsigned char, MD5_DIGEST_LENGTH>();
            boost::iostreams::mapped_file_source mf(file_a);
            MD5(reinterpret_cast<const unsigned char*>(mf.data()), mf.size(), md5.data());
            a[md5] = file_a;
        }
        
        for (const auto& file_b : group_b) {
            auto md5 = std::array<unsigned char, MD5_DIGEST_LENGTH>();
            boost::iostreams::mapped_file_source mf(file_b);
            MD5(reinterpret_cast<const unsigned char*>(mf.data()), mf.size(), md5.data());
            
            if (auto it = a.find(md5); it != a.end()) equals[it->second].insert(file_b);
        }
    }
    
    return equals;
}
