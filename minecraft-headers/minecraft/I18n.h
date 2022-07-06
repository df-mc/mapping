#pragma once

#include <string>
#include "Localization.h"

struct I18n {
public:
    static void chooseLanguage(std::string const &);

    static std::vector<std::unique_ptr<Localization>> mLanguages;
};
