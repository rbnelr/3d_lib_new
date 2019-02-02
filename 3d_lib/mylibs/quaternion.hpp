
union QUAT {
	struct {
		T	x, y, z, w;
	};
	T		arr[4];

	VEC_ALWAYSINLINE QUAT () {}
	VEC_ALWAYSINLINE constexpr QUAT (T x, T y, T z, T w):	x{x},	y{y},	z{z}, w{w} {}
	VEC_ALWAYSINLINE constexpr QUAT (V3 v, T w):			x{v.x},	y{v.y},	z{v.z}, w{w} {}

	VEC_ALWAYSINLINE constexpr V3 xyz () const {	return V3(x,y,z); };

	static VEC_INL constexpr QUAT ident () {		return QUAT(0,0,0, 1); }
	static VEC_INL constexpr QUAT nan () {			return QUAT(QNAN,QNAN,QNAN,QNAN); }

	VEC_INL QUAT& operator*= (QUAT r);
};

VEC_INL M3 convert_to_m3 (QUAT q) {
	M3 ret;

	T xx = q.x * q.x;
	T yy = q.y * q.y;
	T zz = q.z * q.z;
	T xz = q.x * q.z;
	T xy = q.x * q.y;
	T yz = q.y * q.z;
	T wx = q.w * q.x;
	T wy = q.w * q.y;
	T wz = q.w * q.z;

	ret.arr[0] = V3(	1 -(2 * (yy +zz)),		// y z 
		2 * (xy +wz),	// yx zw
		2 * (xz -wy) ); // zx yw

	ret.arr[1] = V3(	    2 * (xy -wz),	// xy zw
		1 -(2 * (xx +zz)),		// x z
		2 * (yz +wx) ); // zy xw

	ret.arr[2] = V3(	    2 * (xz +wy),	// xz yw
		2 * (yz -wx),	// yz xw
		1 -(2 * (xx +yy)) );	// x y

	return ret;
}

VEC_INL HM convert_to_hm (QUAT q) { return HM(convert_to_m3(q)); }

VEC_INL V3 operator* (QUAT q, V3 v) { // not tested

	V3 l_vec = q.xyz();
	V3 uv = cross(l_vec, v);
	V3 uuv = cross(l_vec, uv);

	return v + (uv * q.w +uuv) * 2;
}

VEC_INL QUAT operator* (QUAT l, QUAT r) {
	return QUAT(	(l.w * r.x) +(l.x * r.w) +(l.y * r.z) -(l.z * r.y),
		(l.w * r.y) +(l.y * r.w) +(l.z * r.x) -(l.x * r.z),
		(l.w * r.z) +(l.z * r.w) +(l.x * r.y) -(l.y * r.x),
		(l.w * r.w) -(l.x * r.x) -(l.y * r.y) -(l.z * r.z) );
}
VEC_INL QUAT& QUAT::operator*= (QUAT r) {
	return *this = *this * r;
}

VEC_INL QUAT conjugate (QUAT q) { // not tested
	return QUAT(-q.xyz(), q.w);
}

VEC_INL QUAT inverse (QUAT q) { // not tested
	QUAT conj = conjugate(q);

	V4 qv = V4(q.x,q.y,q.z,q.w);
	T d = dot(qv, qv);

	return QUAT(	conj.x / d,
		conj.y / d,
		conj.z / d,
		conj.w / d );
}

VEC_INL fquat rotateQ (V3 axis, T ang) {
	auto res = sin_cos(ang / 2.0f);
	return fquat( axis * V3(res.s), res.c );
}
VEC_INL fquat rotateQ_X (T ang) {
	return rotateQ(V3(+1, 0, 0), ang);
}
VEC_INL fquat rotateQ_Y (T ang) {
	return rotateQ(V3( 0,+1, 0), ang);
}
VEC_INL fquat rotateQ_Z (T ang) {
	return rotateQ(V3( 0, 0,+1), ang);
}
