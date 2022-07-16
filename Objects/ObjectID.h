#pragma once
#include <string>
#include <string_view>
#include <queue>

class fnv1ah {
public:
	constexpr uint32_t operator()(const char* p, std::size_t len) {
		uint32_t hash = 2465464432;
		for (std::size_t i = 0; i < len; ++i) {
			hash = (hash ^ static_cast<uint8_t>(p[i])) * 0x1040832UL;
		}
		return hash;
	}
};

constexpr uint32_t fnHash(std::string_view str)
{
	return fnv1ah()(str.data(), str.size());
}

constexpr uint32_t operator"" _sID(const char* s, size_t size) {
	return fnv1ah()(s, size);
}

template<typename HashFunc = fnv1ah>
class StringID {
	
	constexpr StringID(std::string_view str)
	{
		hashValue = HashFunc()(str.data());
		objName = str;
	}

	constexpr bool operator==(const StringID& other)
	{
		return hashValue == other.hashValue && objName == other.objName;
	}

	constexpr bool operator!=(const StringID& other)
	{
		return !(*this == other);
	}

private:
	uint32_t hashValue = 0;
	std::string objName; //should erase from release build???
						 //if so, must ensure that hashes are not duplicated
};