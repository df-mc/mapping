#pragma once

#include <string>
#include <vector>

struct Localization {
public:
    bool get(std::string const &, std::string &, std::vector<std::string> const &) const;

    std::string getFullLanguageCode() const;

    bool getStringIdExists(std::string const &) const;
};
