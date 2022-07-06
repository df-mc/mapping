#pragma once

struct CommandRegistry {
    struct Symbol {
        int value;

        Symbol(int value) : value(value) {}

        Symbol(void);

        Symbol(size_t);

        Symbol(const CommandRegistry::Symbol &);

        CommandRegistry::Symbol &operator=(const CommandRegistry::Symbol &);
    };

    void forEachNonTerminal(std::function<void(CommandRegistry::Symbol)>) const;

    std::string describe(CommandRegistry::Symbol) const;

    bool isValid(CommandRegistry::Symbol) const;
};
