#pragma once

#pragma pack(push, 1)

struct Vec2i;

struct Vec2;
struct Vec3;
struct Vec4;

#define FLOAT_EQ_MARGIN 0.0000001

struct Vec2i {
    union {
        struct {
            s32 x, y;
        };
        s32 _[2];
    };

    Vec2i operator-() const { return {-x, -y}; }

    Vec2i operator+(Vec2i other) const { return {other.x + x, y + other.y}; }

    Vec2i operator-(Vec2i other) const { return {x - other.x, y - other.y}; }

    Vec2i operator*(s32 scaler) const { return {x * scaler, y * scaler}; }

    Vec2i operator/(s32 scaler) const { return {x / scaler, y / scaler}; }

    void operator+=(Vec2i other) {
        x += other.x;
        y += other.y;
    }

    void operator-=(Vec2i other) {
        x -= other.x;
        y -= other.y;
    }

    void operator*=(s32 scaler) { *this = (*this) * scaler; }

    void operator/=(s32 scaler) { *this = (*this) / scaler; }

    bool operator==(Vec2i other) {
        return x == other.x && y == other.y;
    }
};

s32 dot(Vec2i a, Vec2i b) { return a.x * b.x + a.y * b.y; }

s32 length_squared(Vec2i a) { return dot(a, a); }

real length(Vec2i a) { return sqrt((real) length_squared(a)); }

struct Vec2 {
    union {
        struct {
            real x, y;
        };
        real _[2];
    };

    Vec2 operator-() const { return {-x, -y}; }

    Vec2 operator+(Vec2 other) const { return {other.x + x, y + other.y}; }

    Vec2 operator-(Vec2 other) const { return {x - other.x, y - other.y}; }

    Vec2 operator*(real scaler) const { return {x * scaler, y * scaler}; }

    Vec2 operator/(real scaler) const {
        real divisor = 1.0f / scaler;
        return {x * divisor, y * divisor};
    }

    void operator+=(Vec2 other) {
        x += other.x;
        y += other.y;
    }

    void operator-=(Vec2 other) {
        x -= other.x;
        y -= other.y;
    }

    void operator*=(real scaler) { *this = (*this) * scaler; }

    void operator/=(real scaler) { *this = (*this) / scaler; }

    bool operator==(Vec2 other) {
        return (x - other.x) * (x - other.x) < FLOAT_EQ_MARGIN &&
               (y - other.y) * (y - other.y) < FLOAT_EQ_MARGIN;
    }
};

real dot(Vec2 a, Vec2 b) { return a.x * b.x + a.y * b.y; }

real length_squared(Vec2 a) { return a.x * a.x + a.y * a.y; }

real length(Vec2 a) { return sqrt(length_squared(a)); }

Vec2 normalize(Vec2 a) {
    // This can be faster if the length is close to one.
    return a / length(a);
}

Vec2 hadamard(Vec2 a, Vec2 b) { return {a.x * b.x, a.y * b.y}; }

Vec2 inverse(Vec2 a) { return {(real) 1.0 / a.x, (real) 1.0 / a.y}; }

Vec2 rotate_ccw(Vec2 p) { return {-p.y, p.x}; }

Vec2 rotate(Vec2 p, real angle) {
    real s = sin(-angle);
    real c = cos(-angle);
    return {p.x * c - p.y * s, p.x * s + p.y * c};
}

real angle(Vec2 p) {
    real angle = atan2(p.y, p.x);
    if (isnan(angle)) return SIGN(p.y) * -PI;
    return angle;
}

struct Vec3 {
    union {
        struct {
            real x, y, z;
        };
        real _[3];
    };

    Vec3 operator-() { return {-x, -y, -z}; }

    Vec3 operator+(Vec3 other) {
        return {x + other.x, y + other.y, z + other.z};
    }

    Vec3 operator-(Vec3 other) {
        return {x - other.x, y - other.y, z - other.z};
    }

    Vec3 operator*(real scaler) { return {x * scaler, y * scaler, z * scaler}; }

    Vec3 operator/(real scaler) {
        real divisor = 1.0f / scaler;
        Vec3 result = {x * divisor, y * divisor, z * divisor};
        return result;
    }

    void operator+=(Vec3 other) {
        x += other.x;
        y += other.y;
        z += other.z;
    }

    void operator-=(Vec3 other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
    }

    void operator*=(real scaler) { *this = (*this) * scaler; }

    void operator/=(real scaler) { *this = (*this) / scaler; }

    bool operator==(Vec3 other) {
        return (x - other.x) * (x - other.x) < FLOAT_EQ_MARGIN &&
               (y - other.y) * (y - other.y) < FLOAT_EQ_MARGIN &&
               (z - other.z) * (z - other.z) < FLOAT_EQ_MARGIN;
    }
};

real dot(Vec3 a, Vec3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

Vec3 cross(Vec3 a, Vec3 b) {
    return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x};
}

real length_cubed(Vec3 a) {
    return a.x * a.x * a.x + a.y * a.y * a.y + a.z * a.z * a.z;
}

real length_squared(Vec3 a) { return a.x * a.x + a.y * a.y + a.z * a.z; }

real length(Vec3 a) { return sqrt(length_squared(a)); }

Vec3 normalize(Vec3 a) { return a / length(a); }

struct Vec4 {
    union {
        struct {
            real x, y, z, w;
        };
        real _[4];
    };

    Vec4 operator-() { return {-x, -y, -z, -w}; }

    Vec4 operator+(Vec4 other) {
        return {x + other.x, y + other.y, z + other.z, w + other.w};
    }

    Vec4 operator-(Vec4 other) {
        return {x - other.x, y - other.y, z - other.z, w - other.w};
    }

    Vec4 operator*(real scaler) {
        return {x * scaler, y * scaler, z * scaler, w * scaler};
    }

    Vec4 operator/(real scaler) {
        real divisor = 1.0f / scaler;
        return {x * divisor, y * divisor, z * divisor, w * divisor};
    }

    void operator+=(Vec4 other) {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
    }

    void operator-=(Vec4 other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w += other.w;
    }

    void operator*=(real scaler) { *this = (*this) * scaler; }

    void operator/=(real scaler) { *this = (*this) / scaler; }

    bool operator==(Vec4 other) {
        return (x - other.x) * (x - other.x) < FLOAT_EQ_MARGIN &&
               (y - other.y) * (y - other.y) < FLOAT_EQ_MARGIN &&
               (z - other.z) * (z - other.z) < FLOAT_EQ_MARGIN &&
               (w - other.w) * (w - other.w) < FLOAT_EQ_MARGIN;
    }
};

real dot(Vec4 a, Vec4 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

real length_squared(Vec4 a) {
    return a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w;
}

real length(Vec4 a) { return sqrt(length_squared(a)); }

Vec4 normalize(Vec4 a) { return a / length(a); }

Vec3 V3(Vec2 v) { return {v.x, v.y, 0.0f}; }

Vec4 V4(Vec2 v, real x4 = 1.0f) { return {v.x, v.y, 0.0f, x4}; }

Vec2 V2(Vec3 v) { return {v.x, v.y}; }

Vec4 V4(Vec3 v, real x4 = 1.0f) {
    return {
        v.x,
        v.y,
        v.z,
    };
}

Vec2 V2(Vec4 v) { return {v.x, v.y}; }

Vec3 V3(Vec4 v) { return {v.x, v.y, v.z}; }

Vec2 V2(real x, real y) { return {x, y}; }

Vec3 V3(real x, real y, real z) { return {x, y, z}; }

Vec4 V4(real x, real y, real z, real w) { return {x, y, z, w}; }

#ifdef _EXAMPLE_
////
// <h3>Vec2</h3>
// A 2d vector, each element can be accessed indivisually (x, y) or through the
// _[n], where n is the component you want to access. All vector oprations
// return a new vector, thus you don't have to care about modifying old valus. <br>
// Overloaded operators:
// <ul>
// 		<li>uniary -, negates the compoents of the vector</li>
// 		<li>binary -, subtracts the components of the two vectors</li>
// 		<li>binary +, adds the components the of two vectors</li>
// 		<li>binary *, multiplies the vector by a scalar</li>
// 		<li>binary /, divides the vector by a scalar</li>
// 		<li>binary ==, Checks if the numbers are equal to a cirtain margin</li>
// </ul>
struct Vec2;
// The other functions that can be used on a Vec2 are.<br>
// <hr>
// a dot b, component wise multiplication and addition.
real dot(Vec2 a, Vec2 b);
// |a|*|a|
real length_squared(Vec2 a);
// |a|
real length(Vec2 a);
// a / |a|
Vec2 normalize(Vec2 a);
// Component wise multiplication.
Vec2 hadamard(Vec2 a, Vec2 b);
// 1.0 / a
Vec2 inverse(Vec2 a);
// {-y, x}
Vec2 rotate_ccw(Vec2 p);
// Rotates the vector "p" by "angle"
Vec2 rotate(Vec2 p, real angle);
// Returns the angle of "p" relative to the x-axis.
real angle(Vec2 p);
// <br>
// Constructs a new Vec2, can be used as default argument.
Vec2 V2(real x, real y);
// Padds out a V3 with zeroes, returning {x, y, 0}
Vec3 V3(Vec2 a);
// Padds out a V4 with appropriate lements, {x, y, 0, x4}
Vec4 V4(Vec2 a, x4=1.0);
////

////
// <h3>Vec3</h3>
// A 3d vector, each element can be accessed indivisually (x, y, z) or through the
// _[n], where n is the component you want to access. All vector oprations
// return a new vector, thus you don't have to care about modifying old valus. <br>
// Overloaded operators:
// <ul>
// 		<li>uniary -, negates the compoents of the vector</li>
// 		<li>binary -, subtracts the components of the two vectors</li>
// 		<li>binary +, adds the components the of two vectors</li>
// 		<li>binary *, multiplies the vector by a scalar</li>
// 		<li>binary /, divides the vector by a scalar</li>
// 		<li>binary ==, Checks if the numbers are equal to a cirtain margin</li>
// </ul>
struct Vec3;
// The other functions that can be used on a Vec3 are.<br>
// <hr>
// a dot b, component wise multiplication and addition.
real dot(Vec3 a, Vec3 b);
// Returns a vector perpendicular to "a" and "b".
Vec3 cross(Vec3 a, Vec3 b) {
// |a|
real length(Vec3 a);
// |a|*|a|
real length_squared(Vec3 a);
// |a|*|a|*|a|
real length_squared(Vec3 a);
// a / |a|
Vec3 normalize(Vec3 a);
// <br>
// Cuts the last value, returning {x, y}
Vec2 V2(Vec3 a);
// Creates a new Vec3.
Vec3 V3(real x, real y, real z);
// Padds out a V4 with appropriate lements, {x, y, z, x4}
Vec4 V4(Vec2 a, x4=1.0);
////

////
// <h3>Vec4</h3>
// A 4d vector, each element can be accessed indivisually (x, y, z, w) or through the
// _[n], where n is the component you want to access. All vector oprations
// return a new vector, thus you don't have to care about modifying old valus. <br>
// Overloaded operators:
// <ul>
// 		<li>uniary -, negates the compoents of the vector</li>
// 		<li>binary -, subtracts the components of the two vectors</li>
// 		<li>binary +, adds the components the of two vectors</li>
// 		<li>binary *, multiplies the vector by a scalar</li>
// 		<li>binary /, divides the vector by a scalar</li>
// 		<li>binary ==, Checks if the numbers are equal to a cirtain margin</li>
// </ul>
struct Vec3;
// The other functions that can be used on a Vec4 are.<br>
// <hr>
// a dot b, component wise multiplication and addition.
real dot(Vec4 a, Vec4 b);
// |a|*|a|
real length_squared(Vec4 a);
// |a|
real length(Vec4 a);
// a / |a|
Vec4 normalize(Vec4 a);
// <br>
// Creates a new Vec4.
Vec4 V4(real x, real y, real z);
////

#endif

#pragma pack(pop)
