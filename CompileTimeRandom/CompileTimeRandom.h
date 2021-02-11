#pragma once

#include <cstdint>

// all numbers are generated randomly at compile time. the internal state is pseudo
// remembered using the counter macro. the seed is based on time using the timestamp
// and time macro. additionally a custom random seed can be specified to fully rely

#ifndef DYNLEC_CUSTOM_RANDOM_SEED
#define DYNLEC_CUSTOM_RANDOM_SEED 0xbdac'f99b'3f7a'1bb4ULL
#endif

// just iterating over the macros will always result in same
// number because the internal state is only updated for each occurance
// of the following macros

// generates a random number seeded with time and the custom seed
#define DYC_RAND_NEXT (::Dynlec::CTRandomGeneratorValueSeeded<__COUNTER__>)
// generates a random number seeded with time and the custom seed between min and max ( [min, max[ )
#define DYC_RAND_NEXT_BETWEEN(min, max) (min + (::Dynlec::CTRandomGeneratorValueSeeded<__COUNTER__> % (max - min)))
// generates a random number seeded with time and the custom seed with a limit ( [0, limit[ )
#define DYC_RAND_NEXT_LIMIT(limit) DYC_RAND_NEXT_BETWEEN(0, limit)

namespace Dynlec
{
	// the random generator internal state is represented by
	// the CTRandomGeneratorRaw type with each of its values
	// x, y, z and c
	template <
		uint64_t x, 
		uint64_t y, 
		uint64_t z, 
		uint64_t c>
	class CTRandomGeneratorRaw
	{
		static_assert(y != 0, 
			"CompileTimeRandom can not be used with 'y' equals 0");
		static_assert(z != 0 || c != 0,
			"CompileTimeRandom can not be used with 'z' and 'c' equals 0");
	public:
		typedef CTRandomGeneratorRaw<
			6906969069ULL * x + 1234567ULL,
			((y ^ (y << 13)) ^ ((y ^ (y << 13)) >> 17)) ^ (((y ^ (y << 13)) ^ ((y ^ (y << 13)) >> 17)) << 43),
			z + ((z << 58) + c),
			((z + ((z << 58) + c)) >> 6) + (z + ((z << 58) + c) < ((z << 58) + c))> Next;

		constexpr static uint64_t Value = x + y + z;
	};

	// to prevent any accidental selection of invalid parameters
	// these values are omitted
	template <
		uint64_t x,
		uint64_t y,
		uint64_t z,
		uint64_t c>
	class CTRandomGeneratorRawSafe
		:
		public CTRandomGeneratorRaw<
			x, (y == 0) ? 1 : y, (z == 0 && c == 0) ? 1 : z, c>
	{
	};

	// CTRandomGenerator is used to quickly compute the nth iteration
	// of CTRandomGeneratorSafeRaw based on a single uint64_t seed
	template <uint64_t iterations, uint64_t seed>
	class CTRandomGenerator
	{
		friend CTRandomGenerator<iterations + 1, seed>;
		typedef typename CTRandomGenerator<iterations - 1, seed>::Current::Next Current;

	public:
		constexpr static uint64_t Value = Current::Value;
	};

	template <uint64_t seed>
	class CTRandomGenerator<0ULL, seed>
	{
		friend CTRandomGenerator<1ULL, seed>;

		typedef typename CTRandomGeneratorRawSafe<
			seed ^ 1066149217761810ULL,
			seed ^ 362436362436362436ULL,
			seed ^ 1234567890987654321ULL,
			seed ^ 123456123456123456ULL>::Next Current;

	public:
		constexpr static uint64_t Value = Current::Value;
	};

	template <uint64_t iteration, uint64_t seed>
	constexpr static uint64_t CTRandomGeneratorValue = CTRandomGenerator<iteration, seed>::Value;

	const uint64_t CTRandomTimeSeed = 
		CTRandomGeneratorValue<0, (__TIME__[0]) ^
		CTRandomGeneratorValue<0, (__TIME__[1]) ^
		CTRandomGeneratorValue<0, (__TIME__[3]) ^
		CTRandomGeneratorValue<0, (__TIME__[4]) ^
		CTRandomGeneratorValue<0, (__TIME__[6]) ^
		CTRandomGeneratorValue<0, (__TIME__[7])>>>>>> ^
		CTRandomGeneratorValue<0, (__TIMESTAMP__[0]) ^
		CTRandomGeneratorValue<0, (__TIMESTAMP__[1]) ^
		CTRandomGeneratorValue<0, (__TIMESTAMP__[2]) ^
		CTRandomGeneratorValue<0, (__TIMESTAMP__[4]) ^
		CTRandomGeneratorValue<0, (__TIMESTAMP__[5]) ^
		CTRandomGeneratorValue<0, (__TIMESTAMP__[6])>>>>>> ^
		CTRandomGeneratorValue<0, (__TIMESTAMP__[8]) ^
		CTRandomGeneratorValue<0, (__TIMESTAMP__[9]) ^
		CTRandomGeneratorValue<0, (__TIMESTAMP__[20]) ^
		CTRandomGeneratorValue<0, (__TIMESTAMP__[21]) ^
		CTRandomGeneratorValue<0, (__TIMESTAMP__[22]) ^
		CTRandomGeneratorValue<0, (__TIMESTAMP__[23])>>>>>>;

	const uint64_t CTRandomSeed = (DYNLEC_CUSTOM_RANDOM_SEED ^ CTRandomTimeSeed);

	template <uint64_t iteration>
	constexpr static uint64_t CTRandomGeneratorValueSeeded = CTRandomGeneratorValue<iteration, CTRandomSeed>;
}
