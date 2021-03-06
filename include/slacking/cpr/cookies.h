#ifndef CPR_COOKIES_H
#define CPR_COOKIES_H

#include <initializer_list>
#include <map>
#include <sstream>
#include <string>

#include "util.h"

namespace cpr {

class Cookies {
  public:
    Cookies() {}
    Cookies(const std::initializer_list<std::pair<const std::string, std::string>>& pairs);
    Cookies(const std::map<std::string, std::string>& map) : map_{map} {}

    std::string& operator[](const std::string& key);
    std::string GetEncoded() const;

  private:
    std::map<std::string, std::string> map_;
};


Cookies::Cookies(const std::initializer_list<std::pair<const std::string, std::string>>& pairs)
        : map_{pairs} {}

std::string Cookies::GetEncoded() const {
    std::stringstream stream;
    for (const auto& item : map_) {
        stream << cpr::util::urlEncode(item.first) << "=";
        // special case version 1 cookies, which can be distinguished by
        // beginning and trailing quotes
        if (!item.second.empty() && item.second.front() == '"' && item.second.back() == '"') {
            stream << item.second;
        } else {
            stream << cpr::util::urlEncode(item.second);
        }
        stream << "; ";
    }
    return stream.str();
}

std::string& Cookies::operator[](const std::string& key) {
    return map_[key];
}

} // namespace cpr

#endif
