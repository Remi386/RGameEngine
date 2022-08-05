#pragma once
#include <iostream>
#include <unordered_map>
#include <cassert>

#if defined(_DEBUG) or defined(DEBUG) or defined(DEBUG_)
	#define DEBUG_BUILD
#endif

#define assertm(exp, msg) assert(((void)msg, exp))

enum DebugLVL : int8_t {
	rCRITICAL = 0,
	rIMPORTANT,
	rWARNING,
	rCOMMON,
	rMINOR,
	rSPAM
};

inline DebugLVL VERBOSE_LEVEL = DebugLVL::rCRITICAL;

namespace Debug {

#ifdef DEBUG_BUILD

	inline std::ostream NullStream(nullptr);
	inline std::unordered_map<std::string, std::ostream*> debugStreams;

	/// <summary>
	/// SHOULD NOT CALL (Game class calls it in Init method)
	/// To specify verbose level change game.ini file
	/// </summary>
	/// <param name="newDebugLVL"></param>
	inline void setDebugLevel(DebugLVL newDebugLVL)
	{
		VERBOSE_LEVEL = newDebugLVL;
	}

	inline void setDebugOutputStream(std::string streamName, std::ostream& stream)
	{
		if (!debugStreams.contains(streamName))
			debugStreams[streamName] = &stream;
	}

	/// <summary>
	/// Stream for debug output
	/// </summary>
	/// <param name="int">argument controls the level of output information</param>
	/// <param name="string">StreamName specifies output stream, cout by default</param>
	inline std::ostream& Out(DebugLVL VerboseLevel, std::string StreamName = "")
	{
		assertm(int8_t(VerboseLevel) <= int8_t(DebugLVL::rSPAM) &&
			    int8_t(VerboseLevel) >= int8_t(DebugLVL::rCRITICAL),
			    "Argument 'VerboseLevel' should be between rCRITICAL and rSPAM DebugLVL enum");

		if (int8_t(VerboseLevel) > int8_t(VERBOSE_LEVEL))
			return NullStream;
		else if (debugStreams.contains(StreamName))
			return *debugStreams[StreamName];
		else
			return std::cout;
	}

#else

	inline void setDebugLevel(DebugLVL newDebugLVL)
	{}

	inline void setDebugOutputStream(std::string streamName, std::ostream& stream)
	{}

	class RNullDebug
	{
	public:
		template<typename Type>
		RNullDebug& operator<<(const Type&) { return *this; }

		// overload for std::endl support
		RNullDebug& operator<<(std::ostream& (*pManip)(std::ostream&)) { return *this; }

	};

	inline RNullDebug Out(int VerboseLevel, std::string StreamName = "")
	{
		return RNullDebug();
	}

#endif // DEBUG_BUILD

} //DebugNS