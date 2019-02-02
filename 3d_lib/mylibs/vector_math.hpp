#pragma once
#include "basic_typedefs.hpp"
#include "math.hpp"
#include "preprocessor_stuff.hpp" // for BOOL_XOR

namespace vector_math {
	using namespace basic_typedefs;
	using namespace math;

	#if 0 // debug
		#define constexpr 
		#define VEC_ALWAYSINLINE inline
		#define VEC_INL inline
	#else
		#define VEC_ALWAYSINLINE FORCEINLINE // to prevent tons of small functions in debug mode
		#define VEC_INL inline
	#endif

	union u8v2;
	union u8v3;
	union u8v4;
	union s32v2;
	union s32v3;
	union s32v4;
	union s64v2;
	union s64v3;
	union s64v4;

	// boolean vectors
	#define T	bool
	#define V2	bv2
	#define V3	bv3
	#define V4	bv4
	#define BOOLVEC	1

	#include "vector_tv2.hpp"
	#include "vector_tv3.hpp"
	#include "vector_tv4.hpp"

	#undef T
	#undef V2
	#undef V3
	#undef V4
	#undef BOOLVEC

	#define BOOLVEC	0
	#define BV2	bv2
	#define BV3	bv3
	#define BV4	bv4

	// float vectors
	#define FLTVEC 1

	#define T	f32
	#define V2	fv2
	#define V3	fv3
	#define V4	fv4

	#include "vector_tv2.hpp"
	#include "vector_tv3.hpp"
	#include "vector_tv4.hpp"

	#undef T
	#undef V2
	#undef V3
	#undef V4

	// double float vectors
	#define T	f64
	#define V2	dv2
	#define V3	dv3
	#define V4	dv4

	#include "vector_tv2.hpp"
	#include "vector_tv3.hpp"
	#include "vector_tv4.hpp"

	#undef T
	#undef V2
	#undef V3
	#undef V4

	#undef FLTVEC

	// integer vectors
	#define INTVEC	1

	#define T	s32
	#define V2	s32v2
	#define V3	s32v3
	#define V4	s32v4

	#include "vector_tv2.hpp"
	#include "vector_tv3.hpp"
	#include "vector_tv4.hpp"

	#undef T
	#undef V2
	#undef V3
	#undef V4

	#define T	s64
	#define V2	s64v2
	#define V3	s64v3
	#define V4	s64v4

	#include "vector_tv2.hpp"
	#include "vector_tv3.hpp"
	#include "vector_tv4.hpp"

	#undef T
	#undef V2
	#undef V3
	#undef V4

	#define T	u8
	#define V2	u8v2
	#define V3	u8v3
	#define V4	u8v4

	#include "vector_tv2.hpp"
	#include "vector_tv3.hpp"
	#include "vector_tv4.hpp"

	#undef T
	#undef V2
	#undef V3
	#undef V4

	#undef INTVEC

	#undef BOOLVEC
	#undef BV2
	#undef BV3
	#undef BV4

	// 
	VEC_INL constexpr fv2::operator u8v2() const {	return u8v2((u8)x, (u8)y); }
	VEC_INL constexpr fv3::operator u8v3() const {	return u8v3((u8)x, (u8)y, (u8)z); }
	VEC_INL constexpr fv4::operator u8v4() const {	return u8v4((u8)x, (u8)y, (u8)z, (u8)w); }

	VEC_INL constexpr fv2::operator s32v2() const {	return s32v2((s32)x, (s32)y); }
	VEC_INL constexpr fv3::operator s32v3() const {	return s32v3((s32)x, (s32)y, (s32)z); }
	VEC_INL constexpr fv4::operator s32v4() const {	return s32v4((s32)x, (s32)y, (s32)z, (s32)w); }

	VEC_INL constexpr fv2::operator s64v2() const {	return s64v2((s64)x, (s64)y); }
	VEC_INL constexpr fv3::operator s64v3() const {	return s64v3((s64)x, (s64)y, (s64)z); }
	VEC_INL constexpr fv4::operator s64v4() const {	return s64v4((s64)x, (s64)y, (s64)z, (s64)w); }

	// matricies
	#define T	f32
	#define V2	fv2
	#define V3	fv3
	#define V4	fv4
	#define M2	fm2
	#define M3	fm3
	#define M4	fm4
	#define HM	fhm

	#include "matricies.hpp"

	// quaternion
	#define QUAT fquat

	#include "quaternion.hpp"

	#undef T
	#undef V2
	#undef V3
	#undef V4
	#undef M2
	#undef M3
	#undef M4

	#undef constexpr 
	#undef VEC_ALWAYSINLINE
	#undef VEC_INL

	//
}
