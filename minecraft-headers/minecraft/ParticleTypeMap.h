#include <string>
#include <vector>

enum class ParticleType;

struct ParticleTypeMap{
	static std::string& getParticleName(ParticleType type);

	static std::vector<std::pair<std::string, ParticleType>> getParticleNameTypeList(void);

	static ParticleType getParticleTypeId(std::string& name);
};
