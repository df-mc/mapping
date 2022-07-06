#pragma once

#include <map>
#include <memory>
#include "HashedString.h"
#include "Recipe.h"

struct Recipes {
    std::map<HashedString, std::map<std::string, std::shared_ptr<Recipe>, std::less<std::string>, std::allocator<std::pair<std::string const, std::shared_ptr<Recipe>>>>, struct std::less<HashedString>, std::allocator<struct std::pair<HashedString const, std::map<std::string, std::shared_ptr<Recipe>, std::less<std::string>, std::allocator<std::pair<std::string const, std::shared_ptr<Recipe>>>>>>> const & getRecipesAllTags() const;
};
