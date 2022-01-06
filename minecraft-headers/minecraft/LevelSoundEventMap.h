#include <string>

enum class LevelSoundEvent;

struct LevelSoundEventMap{
	static std::string& getName(LevelSoundEvent type);

	static LevelSoundEvent getId(std::string const& string);
};
