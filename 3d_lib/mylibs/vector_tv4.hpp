
union V4 {
	struct {
		T	x, y, z, w;
	};
	T		arr[4];
	
	VEC_ALWAYSINLINE T& operator[] (u32 i) {					return arr[i]; }
	constexpr VEC_ALWAYSINLINE T operator[] (u32 i) const {	return arr[i]; }
	
	VEC_ALWAYSINLINE V4 () {}
	VEC_ALWAYSINLINE constexpr V4 (T all):				x{all},	y{all},	z{all},	w{all} {}
	VEC_ALWAYSINLINE constexpr V4 (T x, T y, T z, T w):	x{x},	y{y},	z{z},	w{w} {}
	VEC_ALWAYSINLINE constexpr V4 (V2 v, T z, T w):		x{v.x},	y{v.y},	z{z},	w{w} {}
	VEC_ALWAYSINLINE constexpr V4 (V3 v, T w):			x{v.x},	y{v.y},	z{v.z},	w{w} {}
	
	VEC_ALWAYSINLINE constexpr V2 xy () const {			return V2(x,y) ;};
	VEC_ALWAYSINLINE constexpr V3 xyz () const {		return V3(x,y,z) ;};
	
#if !BOOLVEC
	VEC_INL V4& operator+= (V4 r) {						return *this = V4(x +r.x, y +r.y, z +r.z, w +r.w); }
	VEC_INL V4& operator-= (V4 r) {						return *this = V4(x -r.x, y -r.y, z -r.z, w -r.w); }
	VEC_INL V4& operator*= (V4 r) {						return *this = V4(x * r.x, y * r.y, z * r.z, w * r.w); }
	VEC_INL V4& operator/= (V4 r) {						return *this = V4(x / r.x, y / r.y, z / r.z, w / r.w); }
	
	#if FLTVEC
	VEC_INL constexpr operator u8v4() const;
	VEC_INL constexpr operator s64v4() const;
	VEC_INL constexpr operator s32v4() const;
	#endif
	#if INTVEC
	VEC_INL constexpr operator fv4() const {			return fv4((f32)x, (f32)y, (f32)z, (f32)w); }
	#endif
#endif
};

#if BOOLVEC
	VEC_INL constexpr bool all (V4 b) {				return b.x && b.y && b.z && b.w; }
	VEC_INL constexpr bool any (V4 b) {				return b.x || b.y || b.z || b.w; }
	
	VEC_INL constexpr V4 operator! (V4 b) {			return V4(!b.x,			!b.y,		!b.z,		!b.w); }
	VEC_INL constexpr V4 operator&& (V4 l, V4 r) {	return V4(l.x && r.x,	l.y && r.y,	l.z && r.z,	l.w && r.w); }
	VEC_INL constexpr V4 operator|| (V4 l, V4 r) {	return V4(l.x || r.x,	l.y || r.y,	l.z || r.z,	l.w || r.w); }
	VEC_INL constexpr V4 XOR (V4 l, V4 r) {			return V4(BOOL_XOR(l.x, r.x),	BOOL_XOR(l.y, r.y),	BOOL_XOR(l.z, r.z),	BOOL_XOR(l.w, r.w)); }
	
#else
	VEC_INL constexpr BV4 operator < (V4 l, V4 r) {	return BV4(l.x  < r.x,	l.y  < r.y,	l.z  < r.z,	l.w  < r.w); }
	VEC_INL constexpr BV4 operator<= (V4 l, V4 r) {	return BV4(l.x <= r.x,	l.y <= r.y,	l.z <= r.z,	l.w <= r.w); }
	VEC_INL constexpr BV4 operator > (V4 l, V4 r) {	return BV4(l.x  > r.x,	l.y  > r.y,	l.z  > r.z,	l.w  > r.w); }
	VEC_INL constexpr BV4 operator>= (V4 l, V4 r) {	return BV4(l.x >= r.x,	l.y >= r.y,	l.z >= r.z,	l.w >= r.w); }
	VEC_INL constexpr BV4 operator== (V4 l, V4 r) {	return BV4(l.x == r.x,	l.y == r.y,	l.z == r.z,	l.w == r.w); }
	VEC_INL constexpr BV4 operator!= (V4 l, V4 r) {	return BV4(l.x != r.x,	l.y != r.y,	l.z != r.z,	l.w != r.w); }
	VEC_INL constexpr V4 select (BV4 c, V4 l, V4 r) {
		return V4(	c.x ? l.x : r.x,	c.y ? l.y : r.y,	c.z ? l.z : r.z,	c.w ? l.w : r.w );
	}
	
	VEC_INL constexpr bool equal (V4 l, V4 r) {		return l.x == r.x && l.y == r.y && l.z == r.z && l.w == r.w; }

	VEC_INL int smallest_comp (V4 v) {
		int a = smallest_comp(v.xy());
		int b = smallest_comp(V2(v.z, v.w));
		return v[a] <= v[b] ? a : b;
	}
	VEC_INL int biggest_comp (V4 v) {
		int a = biggest_comp(v.xy());
		int b = biggest_comp(V2(v.z, v.w));
		return v[a] >= v[b] ? a : b;
	}

	VEC_INL constexpr V4 operator+ (V4 v) {			return v; }
	VEC_INL constexpr V4 operator- (V4 v) {			return V4(-v.x, -v.y, -v.z, -v.w); }

	VEC_INL constexpr V4 operator+ (V4 l, V4 r) {	return V4(l.x +r.x, l.y +r.y, l.z +r.z, l.w +r.w); }
	VEC_INL constexpr V4 operator- (V4 l, V4 r) {	return V4(l.x -r.x, l.y -r.y, l.z -r.z, l.w -r.w); }
	VEC_INL constexpr V4 operator* (V4 l, V4 r) {	return V4(l.x * r.x, l.y * r.y, l.z * r.z, l.w	* r.w); }
	VEC_INL constexpr V4 operator/ (V4 l, V4 r) {	return V4(l.x / r.x, l.y / r.y, l.z / r.z, l.w / r.w); }
	#if INTVEC
	VEC_INL constexpr V4 operator% (V4 l, V4 r) {	return V4(l.x % r.x, l.y % r.y, l.z % r.z, l.w % r.w); }
	#endif

	VEC_INL constexpr T dot(V4 l, V4 r) {			return l.x*r.x + l.y*r.y + l.z*r.z + l.w*r.w; }

	VEC_INL V4 abs(V4 v) {							return V4(math::abs(v.x), math::abs(v.y), math::abs(v.z), math::abs(v.w)); }
	VEC_INL T max_component(V4 v) {					return math::max(math::max(v.x, v.y), math::max(v.z, v.w)); }

	VEC_INL constexpr V4 MIN (V4 l, V4 r) {			return select(l <= r, l, r); }
	VEC_INL constexpr V4 MAX (V4 l, V4 r) {			return select(r >= l, r, l); }
	
	VEC_INL constexpr V4 clamp (V4 val, V4 l=0, V4 h=1)	{	return MIN( MAX(val,l), h ); }
	
	#if FLTVEC
	VEC_INL constexpr V4 lerp (V4 a, V4 b, V4 t) {								return (a * (V4(1) -t)) +(b * t); }
	VEC_INL constexpr V4 map (V4 x, V4 in_a, V4 in_b) {							return (x -in_a)/(in_b -in_a); }
	VEC_INL constexpr V4 map (V4 x, V4 in_a, V4 in_b, V4 out_a, V4 out_b) {		return lerp(out_a, out_b, map(x, in_a, in_b)); }
	
	VEC_INL T length (V4 v) {						return sqrt(v.x*v.x +v.y*v.y +v.z*v.z +v.w*v.w); }
	VEC_INL T length_sqr (V4 v) {					return v.x*v.x +v.y*v.y +v.z*v.z +v.w*v.w; }
	VEC_INL T distance (V4 a, V4 b) {				return length(b -a); }
	VEC_INL V4 normalize (V4 v) {					return v / V4(length(v)); }
	
	VEC_INL constexpr V4 to_deg (V4 v) {			return v * RAD_TO_DEG; }
	VEC_INL constexpr V4 to_rad (V4 v) {			return v * DEG_TO_RAD; }

	VEC_INL V4 mymod (V4 val, V4 range) {			return V4(	math::mymod(val.x, range.x),	math::mymod(val.y, range.y),	math::mymod(val.z, range.z),	math::mymod(val.w, range.w) ); }
	
	VEC_INL V4 floor (V4 v) {						return V4(math::floor(v.x),	math::floor(v.y),	math::floor(v.z),	math::floor(v.w)); }
	VEC_INL V4 ceil (V4 v) {						return V4(math::ceil(v.x),	math::ceil(v.y),	math::ceil(v.z),	math::ceil(v.w)); }
	VEC_INL V4 round (V4 v) {						return V4(math::round(v.x),	math::round(v.y),	math::round(v.z),	math::round(v.w)); }

	VEC_INL V4 pow (V4 v, V4 e) {					return V4(math::pow(v.x,e.x),	math::pow(v.y,e.y),	math::pow(v.z,e.z),	math::pow(v.w,e.w)); }
	#endif
#endif
