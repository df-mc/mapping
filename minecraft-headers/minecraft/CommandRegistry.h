#pragma once

struct CommandRegistry{
	struct Symbol{
		int value;


		Symbol(int value) : value(value) {}

		Symbol(void);
		Symbol(size_t);
		Symbol(const CommandRegistry::Symbol &);
		CommandRegistry::Symbol & operator=(const CommandRegistry::Symbol &);
	};

	std::string describe(CommandRegistry::Symbol) const;
	std::string symbolToString(CommandRegistry::Symbol) const;
	bool isValid(CommandRegistry::Symbol) const;

};
