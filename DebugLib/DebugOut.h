#pragma once
#include <iostream>

#if defined(_DEBUG) or defined(DEBUG) or defined(DEBUG_)
	#define DEBUG_BUILD
#endif

#define LOW_VERBOSE 5
#define WEAK_VERBOSE 4
#define MID_VERBOSE 3
#define STRONG_VERBOSE 2
#define MAX_VERBOSE 1
#define NO_VERBOSE 0

#define VERBOSE_LEVEL MAX_VERBOSE

#ifdef DEBUG_BUILD
	
namespace DebugNS {

	inline std::ostream* debugStream = &std::cout;
	inline std::ostream NullStream(nullptr);

	inline void setDebugOutputStream(std::ostream& stream)
	{
		DebugNS::debugStream = &stream;
	}

	template<int VerboseLevel>
	inline std::ostream& debugOut()
	{
		static_assert(VerboseLevel >= NO_VERBOSE && VerboseLevel <= LOW_VERBOSE,
			"Template argument 'VerboseLevel should be between NO_VERBOSE and MAX_VERBOSE macro");

		if constexpr (VerboseLevel > VERBOSE_LEVEL)
			return DebugNS::NullStream;
		else
			return *DebugNS::debugStream;
	}

	#define rDebugImpl(verbLevel) debugOut<verbLevel>()

} // DebugNS 

#else

namespace DebugNS {

	inline void setDebugOutputStream(std::ostream&)
	{}

	class RNullDebug
	{
	public:
		template<typename Type>
		inline RNullDebug& operator<<(const Type&) { return *this; }

		// overload for std::endl support
		RNullDebug& operator<<(std::ostream& (*pManip)(std::ostream&)) { return *this; }

	};

	#define rDebugImpl(_verbLevel) RNullDebug()

} // DebugNS 

#endif // DEBUG_BUILD

namespace DebugNS {

	/// <summary>
	/// Macro for debug output
	/// </summary>
	/// <param name="int">argument controls the level of output information</param>
	#define rDebug(verbLevel) rDebugImpl(verbLevel)
}