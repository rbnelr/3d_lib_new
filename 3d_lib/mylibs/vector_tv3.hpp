
union V3 {
	struct {
		T	x, y, z;
	};
	T		arr[3];
	
	VEC_ALWAYSINLINE T& operator[] (u32 i) {					return arr[i]; }
	constexpr VEC_ALWAYSINLINE T operator[] (u32 i) const {	return arr[i]; }
	
	VEC_ALWAYSINLINE V3 () {}
	VEC_ALWAYSINLINE constexpr V3 (T all):				x{all},	y{all},	z{all} {}
	VEC_ALWAYSINLINE constexpr V3 (T x, T y, T z):		x{x},	y{y},	z{z} {}
	VEC_ALWAYSINLINE constexpr V3 (V2 v, T z):			x{v.x},	y{v.y},	z{z} {}
	
	VEC_ALWAYSINLINE constexpr V2 xy () const {			return V2(x,y); };
	
#if !BOOLVEC
	VEC_INL V3& operator+= (V3 r) {						return *this = V3(x +r.x, y +r.y, z +r.z); }
	VEC_INL V3& operator-= (V3 r) {						return *this = V3(x -r.x, y -r.y, z -r.z); }
	VEC_INL V3& operator*= (V3 r) {						return *this = V3(x * r.x, y * r.y, z * r.z); }
	VEC_INL V3& operator/= (V3 r) {						return *this = V3(x / r.x, y / r.y, z / r.z); }

	#if FLTVEC
	VEC_INL constexpr operator u8v3() const;
	VEC_INL constexpr operator s64v3() const;
	VEC_INL constexpr operator s32v3() const;
	#endif
	#if INTVEC
	VEC_INL constexpr operator fv3() const {			return fv3((f32)x, (f32)y, (f32)z); }
	#endif
#endif
};

#if BOOLVEC
	VEC_INL constexpr bool all (V3 b) {				return b.x && b.y && b.z; }
	VEC_INL constexpr bool any (V3 b) {				return b.x || b.y || b.z; }
	
	VEC_INL constexpr V3 operator! (V3 b) {			return V3(!b.x,			!b.y,		!b.z); }
	VEC_INL constexpr V3 operator&& (V3 l, V3 r) {	return V3(l.x && r.x,	l.y && r.y,	l.z && r.z); }
	VEC_INL constexpr V3 operator|| (V3 l, V3 r) {	return V3(l.x || r.x,	l.y || r.y,	l.z || r.z); }
	VEC_INL constexpr V3 XOR (V3 l, V3 r) {			return V3(BOOL_XOR(l.x, r.x),	BOOL_XOR(l.y, r.y),	BOOL_XOR(l.z, r.z)); }
	
#else
	VEC_INL constexpr BV3 operator < (V3 l, V3 r) {	return BV3(l.x  < r.x,	l.y  < r.y,	l.z  < r.z); }
	VEC_INL constexpr BV3 operator<= (V3 l, V3 r) {	return BV3(l.x <= r.x,	l.y <= r.y,	l.z <= r.z); }
	VEC_INL constexpr BV3 operator > (V3 l, V3 r) {	return BV3(l.x  > r.x,	l.y  > r.y,	l.z  > r.z); }
	VEC_INL constexpr BV3 operator>= (V3 l, V3 r) {	return BV3(l.x >= r.x,	l.y >= r.y,	l.z >= r.z); }
	VEC_INL constexpr BV3 operator== (V3 l, V3 r) {	return BV3(l.x == r.x,	l.y == r.y,	l.z == r.z); }
	VEC_INL constexpr BV3 operator!= (V3 l, V3 r) {	return BV3(l.x != r.x,	l.y != r.y,	l.z != r.z); }
	VEC_INL constexpr V3 select (BV3 c, V3 l, V3 r) {
		return V3(	c.x ? l.x : r.x,	c.y ? l.y : r.y,	c.z ? l.z : r.z );
	}
	
	VEC_INL constexpr bool equal (V3 l, V3 r) {		return l.x == r.x && l.y == r.y && l.z == r.z; }

	VEC_INL constexpr int smallest_comp (V3 v) {	return v.x <= v.y && v.x <= v.z ? 0 : (v.y <= v.z ? 1 : 2); }
	VEC_INL constexpr int biggest_comp (V3 v) {		return v.x >= v.y && v.x <= v.z ? 0 : (v.y >= v.z ? 1 : 2); }

	VEC_INL constexpr V3 operator+ (V3 v) {			return v; }
	VEC_INL constexpr V3 operator- (V3 v) {			return V3(-v.x, -v.y, -v.z); }

	VEC_INL constexpr V3 operator+ (V3 l, V3 r) {	return V3(l.x +r.x, l.y +r.y, l.z +r.z); }
	VEC_INL constexpr V3 operator- (V3 l, V3 r) {	return V3(l.x -r.x, l.y -r.y, l.z -r.z); }
	VEC_INL constexpr V3 operator* (V3 l, V3 r) {	return V3(l.x * r.x, l.y * r.y, l.z * r.z); }
	VEC_INL constexpr V3 operator/ (V3 l, V3 r) {	return V3(l.x / r.x, l.y / r.y, l.z / r.z); }
	#if INTVEC
	VEC_INL constexpr V3 operator% (V3 l, V3 r) {	return V3(l.x % r.x, l.y % r.y, l.z % r.z); }
	#endif
	
	VEC_INL constexpr T dot(V3 l, V3 r) {			return l.x*r.x + l.y*r.y + l.z*r.z; }

	VEC_INL constexpr V3 cross(V3 l, V3 r) {
		return V3(l.y*r.z - l.z*r.y, l.z*r.x - l.x*r.z, l.x*r.y - l.y*r.x);
	}

	VEC_INL V3 abs(V3 v) {							return V3(math::abs(v.x), math::abs(v.y), math::abs(v.z)); }
	VEC_INL T max_component(V3 v) {					return math::max(math::max(v.x, v.y), v.z); }

	VEC_INL constexpr V3 min (V3 l, V3 r) {			return select(l <= r, l, r); }
	VEC_INL constexpr V3 max (V3 l, V3 r) {			return select(r >= l, r, l); }
	
	VEC_INL constexpr V3 clamp (V3 val, V3 l=0, V3 h=1) {	return min( max(val,l), h ); }
	
#if FLTVEC
	VEC_INL constexpr V3 lerp (V3 a, V3 b, V3 t) {								return (a * (V3(1) -t)) +(b * t); }
	VEC_INL constexpr V3 map (V3 x, V3 in_a, V3 in_b) {							return (x -in_a)/(in_b -in_a); }
	VEC_INL constexpr V3 map (V3 x, V3 in_a, V3 in_b, V3 out_a, V3 out_b) {		return lerp(out_a, out_b, map(x, in_a, in_b)); }
	
	VEC_INL T length (V3 v) {						return sqrt(v.x*v.x +v.y*v.y +v.z*v.z); }
	VEC_INL T length_sqr (V3 v) {					return v.x*v.x +v.y*v.y +v.z*v.z; }
	VEC_INL T distance (V3 a, V3 b) {				return length(b -a); }
	VEC_INL V3 normalize (V3 v) {					return v / V3(length(v)); }
	
	VEC_INL constexpr V3 to_deg (V3 v) {			return v * RAD_TO_DEG; }
	VEC_INL constexpr V3 to_rad (V3 v) {			return v * DEG_TO_RAD; }

	VEC_INL V3 mymod (V3 val, V3 range) {			return V3(	math::mymod(val.x, range.x),	math::mymod(val.y, range.y),	math::mymod(val.z, range.z) ); }
	
	VEC_INL V3 floor (V3 v) {						return V3(math::floor(v.x),	math::floor(v.y),	math::floor(v.z)); }
	VEC_INL V3 ceil (V3 v) {						return V3(math::ceil(v.x),	math::ceil(v.y),	math::ceil(v.z)); }
	VEC_INL V3 round (V3 v) {						return V3(math::round(v.x),	math::round(v.y),	math::round(v.z)); }

	VEC_INL V3 pow (V3 v, V3 e) {					return V3(math::pow(v.x,e.x),	math::pow(v.y,e.y),	math::pow(v.z,e.z)); }
	#endif
#endif
