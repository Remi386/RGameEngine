#pragma once
#include <iostream>
#include <unordered_map>
#include <cassert>

#if defined(_DEBUG) or defined(DEBUG) or defined(DEBUG_)
	#define DEBUG_BUILD
#endif

#define assertm(exp, msg) assert(((void)msg, exp))

class Game;

enum DebugLVL : int8_t {
	rCRITICAL = 0,
	rIMPORTANT,
	rWARNING,
	rCOMMON,
	rMINOR,
	rSPAM
};

class Debug {

	friend Game;

private:
	static inline DebugLVL VERBOSE_LEVEL = DebugLVL::rSPAM;

#ifdef DEBUG_BUILD

	static inline std::ostream NullStream = std::ostream(nullptr);
	static inline std::unordered_map<std::string, std::ostream*> debugStreams;

	/// <summary>
	/// (Game class calls it in Init method)
	/// To specify verbose level change game.ini file
	/// </summary>
	/// <param name="newDebugLVL"></param>
	static void setDebugLevel(DebugLVL newDebugLVL)
	{
		VERBOSE_LEVEL = newDebugLVL;
	}

public:
	static void setDebugOutputStream(const std::string& streamName, std::ostream& stream)
	{
		if (!debugStreams.contains(streamName))
			debugStreams[streamName] = &stream;
	}

	/// <summary>
	/// Stream for debug output
	/// </summary>
	/// <param name="int">argument controls the level of output information</param>
	/// <param name="string">StreamName specifies output stream, cout by default</param>
	static std::ostream& Out(DebugLVL VerboseLevel, const std::string& StreamName = "")
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

	static void Assert(bool condition, DebugLVL VerboseLevel,
					   std::string_view message, const std::string& StreamName = "", 
					   int error_code = 0)
	{
		if (!condition) {
			Debug::Out(VerboseLevel, StreamName) << message << std::endl;
			if (error_code != 0) {
				std::exit(error_code);
			}
		}
	}

#else

	static void setDebugLevel(DebugLVL newDebugLVL)
	{}

public:
	static void setDebugOutputStream(const std::string& streamName, std::ostream& stream)
	{}

	class RNullDebug
	{
	public:
		template<typename Type>
		RNullDebug& operator<<(const Type&) { return *this; }

		// overload for std::endl support
		RNullDebug& operator<<(std::ostream& (*pManip)(std::ostream&)) { return *this; }

	};

	static RNullDebug Out(int VerboseLevel, const std::string& StreamName = "")
	{
		return RNullDebug();
	}

	static void Assert(bool condition, DebugLVL VerboseLevel,
					   std::string_view message, const std::string& StreamName = "",
					   int error_code = 0)
	{}

#endif // DEBUG_BUILD

}; //Debug