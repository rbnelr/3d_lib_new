
union V2 {
	struct {
		T	x, y;
	};
	T		arr[2];
	
	VEC_ALWAYSINLINE T& operator[] (u32 i) {					return arr[i]; }
	constexpr VEC_ALWAYSINLINE T operator[] (u32 i) const {	return arr[i]; }
	
	VEC_ALWAYSINLINE V2 () {}
	VEC_ALWAYSINLINE constexpr V2 (T all):				x{all},	y{all} {}
	VEC_ALWAYSINLINE constexpr V2 (T x, T y):			x{x},	y{y} {}
	
#if !BOOLVEC
	VEC_INL V2& operator+= (V2 r) {						return *this = V2(x +r.x, y +r.y); }
	VEC_INL V2& operator-= (V2 r) {						return *this = V2(x -r.x, y -r.y); }
	VEC_INL V2& operator*= (V2 r) {						return *this = V2(x * r.x, y * r.y); }
	VEC_INL V2& operator/= (V2 r) {						return *this = V2(x / r.x, y / r.y); }
	
	#if FLTVEC
	VEC_INL constexpr operator u8v2() const;
	VEC_INL constexpr operator s64v2() const;
	VEC_INL constexpr operator s32v2() const;
	#endif
	#if INTVEC
	VEC_INL constexpr operator fv2() const {			return fv2((f32)x, (f32)y); }
	#endif
#endif
};

#if BOOLVEC
	VEC_INL constexpr bool all (V2 b) {				return b.x && b.y; }
	VEC_INL constexpr bool any (V2 b) {				return b.x || b.y; }
	
	VEC_INL constexpr V2 operator! (V2 b) {			return V2(!b.x,			!b.y); }
	VEC_INL constexpr V2 operator&& (V2 l, V2 r) {	return V2(l.x && r.x,	l.y && r.y); }
	VEC_INL constexpr V2 operator|| (V2 l, V2 r) {	return V2(l.x || r.x,	l.y || r.y); }
	VEC_INL constexpr V2 XOR (V2 l, V2 r) {			return V2(BOOL_XOR(l.x, r.x),	BOOL_XOR(l.y, r.y)); }
	
#else
	VEC_INL constexpr BV2 operator < (V2 l, V2 r) {	return BV2(l.x  < r.x,	l.y  < r.y); }
	VEC_INL constexpr BV2 operator<= (V2 l, V2 r) {	return BV2(l.x <= r.x,	l.y <= r.y); }
	VEC_INL constexpr BV2 operator > (V2 l, V2 r) {	return BV2(l.x  > r.x,	l.y  > r.y); }
	VEC_INL constexpr BV2 operator>= (V2 l, V2 r) {	return BV2(l.x >= r.x,	l.y >= r.y); }
	VEC_INL constexpr BV2 operator== (V2 l, V2 r) {	return BV2(l.x == r.x,	l.y == r.y); }
	VEC_INL constexpr BV2 operator!= (V2 l, V2 r) {	return BV2(l.x != r.x,	l.y != r.y); }
	VEC_INL constexpr V2 select (BV2 c, V2 l, V2 r) {
		return V2(	c.x ? l.x : r.x,	c.y ? l.y : r.y );
	}
	
	VEC_INL constexpr bool equal (V2 l, V2 r) {		return l.x == r.x && l.y == r.y; }
	
	VEC_INL constexpr int smallest_comp (V2 v) {	return v.x <= v.y ? 0 : 1; }
	VEC_INL constexpr int biggest_comp (V2 v) {		return v.x >= v.y ? 0 : 1; }

	VEC_INL constexpr V2 operator+ (V2 v) {			return v; }
	VEC_INL constexpr V2 operator- (V2 v) {			return V2(-v.x, -v.y); }
	
	VEC_INL constexpr V2 operator+ (V2 l, V2 r) {	return V2(l.x +r.x, l.y +r.y); }
	VEC_INL constexpr V2 operator- (V2 l, V2 r) {	return V2(l.x -r.x, l.y -r.y); }
	VEC_INL constexpr V2 operator* (V2 l, V2 r) {	return V2(l.x * r.x, l.y * r.y); }
	VEC_INL constexpr V2 operator/ (V2 l, V2 r) {	return V2(l.x / r.x, l.y / r.y); }
	#if INTVEC
	VEC_INL constexpr V2 operator% (V2 l, V2 r) {	return V2(l.x % r.x, l.y % r.y); }
	#endif
	
	VEC_INL constexpr T dot (V2 l, V2 r) {			return l.x*r.x + l.y*r.y; }

	VEC_INL V2 abs (V2 v) {							return V2(math::abs(v.x), math::abs(v.y)); }
	VEC_INL T max_component (V2 v) {				return math::max(v.x, v.y); }

	VEC_INL constexpr V2 MIN (V2 l, V2 r) {			return select(l <= r, l, r); }
	VEC_INL constexpr V2 MAX (V2 l, V2 r) {			return select(r >= l, r, l); }

	VEC_INL constexpr V2 clamp (V2 val, V2 l=0, V2 h=1) {	return MIN( MAX(val,l), h ); }
	
	#if FLTVEC
	VEC_INL constexpr V2 lerp (V2 a, V2 b, V2 t) {								return (a * (V2(1) -t)) +(b * t); }
	VEC_INL constexpr V2 map (V2 x, V2 in_a, V2 in_b) {							return (x -in_a)/(in_b -in_a); }
	VEC_INL constexpr V2 map (V2 x, V2 in_a, V2 in_b, V2 out_a, V2 out_b) {		return lerp(out_a, out_b, map(x, in_a, in_b)); }
	
	VEC_INL T length (V2 v) {						return sqrt(v.x*v.x +v.y*v.y); }
	VEC_INL T length_sqr (V2 v) {					return v.x*v.x +v.y*v.y; }
	VEC_INL T distance (V2 a, V2 b) {				return length(b -a); }
	VEC_INL V2 normalize (V2 v) {					return v / V2(length(v)); }
	
	VEC_INL constexpr V2 to_deg (V2 v) {			return v * RAD_TO_DEG; }
	VEC_INL constexpr V2 to_rad (V2 v) {			return v * DEG_TO_RAD; }
	
	VEC_INL V2 mymod (V2 val, V2 range) {			return V2(	math::mymod(val.x, range.x),	math::mymod(val.y, range.y) ); }

	VEC_INL V2 floor (V2 v) {						return V2(math::floor(v.x),		math::floor(v.y)); }
	VEC_INL V2 ceil (V2 v) {						return V2(math::ceil(v.x),		math::ceil(v.y)); }
	VEC_INL V2 round (V2 v) {						return V2(math::round(v.x),		math::round(v.y)); }

	VEC_INL V2 pow (V2 v, V2 e) {					return V2(math::pow(v.x,e.x),	math::pow(v.y,e.y)); }
	#endif
#endif
