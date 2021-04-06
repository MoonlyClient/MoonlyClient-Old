#pragma once

#include <string>

struct Vec2 {
	union {
		struct {
			float x, y;
		};
		float arr[2];
	};

	Vec2() { x = y = 0; }
	Vec2(float x, float y) {
		this->x = x, this->y = y;
	}

	bool operator == (Vec2 v) { return v.x == x && v.y == y; };
	bool operator != (Vec2 v) { return v.x != x || v.y != y; };

	/* Add */

	Vec2 add(float f) {
		return Vec2(x + f, y + f);
	}

	Vec2 add(float a, float b) {
		return Vec2(x + a, y + b);
	}

	Vec2 add(Vec2 o) {
		return Vec2(x + o.y, y + o.y);
	}

	/* Subtract */

	Vec2 sub(float f) {
		return Vec2(x - f, y - f);
	}

	Vec2 sub(float a, float b) {
		return Vec2(x - a, x - b);
	}

	Vec2 sub(Vec2 o) {
		return Vec2(x - o.x, y - o.y);
	}

	/* Divide */

	Vec2 div(float f) {
		return Vec2(x / f, y / f);
	}

	Vec2 div(float a, float b) {
		return Vec2(x / a, y / b);
	}

	Vec2 div(Vec2 o) {
		return Vec2(x / o.x, y / o.y);
	}

	/* Multiply */

	Vec2 mult(float f) {
		return Vec2(x * f, y * f);
	}

	Vec2 mult(float a, float b) {
		return Vec2(x * a, y * b);
	}

	Vec2 mult(Vec2 o) {
		return Vec2(x * o.x, y * o.y);
	}

	/* Other */

	int distance(Vec2 o) {
		int dX = x - o.y;
		int dY = y - o.y;
		return sqrt(dX * dX + dY * dY);
	}
};

struct Vec3 {
	union {
		struct {
			float x, y, z;
		};
		float arr[3];
	};

	Vec3() { x = y = z = 0; }
	Vec3(float x, float y, float z) {
		this->x = x, this->y = y, this->z = z;
	}

	bool operator == (Vec3 v) { return v.x == x && v.y == y && v.z == z; };
	bool operator != (Vec3 v) { return v.x != x || v.y != y || v.z != z; };

	/* Add */

	Vec3 add(float f) {
		return Vec3(x + f, y + f, z + f);
	}

	Vec3 add(float a, float b, float c) {
		return Vec3(x + a, y + b, z + c);
	}

	Vec3 add(Vec3 o) {
		return Vec3(x + o.y, y + o.y, z + o.z);
	}

	/* Subtract */

	Vec3 sub(float f) {
		return Vec3(x - f, y - f, z - f);
	}

	Vec3 sub(float a, float b, float c) {
		return Vec3(x - a, x - b, z - c);
	}

	Vec3 sub(Vec3 o) {
		return Vec3(x - o.x, y - o.y, z - o.z);
	}

	/* Divide */

	Vec3 div(float f) {
		return Vec3(x / f, y / f, z / f);
	}

	Vec3 div(float a, float b, float c) {
		return Vec3(x / a, y / b, z / c);
	}

	Vec3 div(Vec3 o) {
		return Vec3(x / o.x, y / o.y, z / o.y);
	}

	/* Multiply */

	Vec3 mult(float f) {
		return Vec3(x * f, y * f, z * f);
	}

	Vec3 mult(float a, float b, float c) {
		return Vec3(x * a, y * b, z * c);
	}

	Vec3 mult(Vec3 o) {
		return Vec3(x * o.x, y * o.y, z * o.z);
	}

	/* Other */

	Vec3 floor() {
		return Vec3(floorf(x), floorf(y), floorf(z));
	}

	float magnitude() {
		return sqrtf(x * x + y * y + z * z);
	}

	float magnitudexy() {
		return sqrtf(x * x + y * y);
	}

	float magnitudexz() {
		return sqrtf(x * x + z * z);
	}

	Vec3 normalize() {
		return div(magnitude());
	};

	float distance(Vec3 o) {
		float dX = x - o.x;
		float dY = y - o.y;
		float dZ = z - o.z;
		return sqrt(dX * dX + dY * dY + dZ * dZ);
	}
};

struct Vec3_i {
	union {
		struct {
			int x, y, z;
		};
		int arr[3];
	};

	Vec3_i() { x = y = z = 0; }
	Vec3_i(int x = 0, int y = 0, int z = 0) {
		this->x = x, this->y = y, this->z = z;
	}

	bool operator == (Vec3_i v) { return v.x == x && v.y == y && v.z == z; };
	bool operator != (Vec3_i v) { return v.x != x || v.y != y || v.z != z; };

	/* Add */

	Vec3_i add(int i) {
		return Vec3_i(x + i, y + i, z + i);
	}

	Vec3_i add(int a, int b, int c) {
		return Vec3_i(x + a, y + b, z + c);
	}

	Vec3_i add(Vec3 o) {
		return Vec3_i(x + o.y, y + o.y, z + o.z);
	}

	/* Subtract */

	Vec3_i sub(int i) {
		return Vec3_i(x - i, y - i, z - i);
	}

	Vec3_i sub(int a, int b, int c) {
		return Vec3_i(x - a, x - b, z - c);
	}

	Vec3_i sub(Vec3 o) {
		return Vec3_i(x - o.x, y - o.y, z - o.z);
	}

	/* Divide */

	Vec3_i div(int i) {
		return Vec3_i(x / i, y / i, z / i);
	}

	Vec3_i div(int a, int b, int c) {
		return Vec3_i(x / a, y / b, z / c);
	}

	Vec3_i div(Vec3 o) {
		return Vec3_i(x / o.x, y / o.y, z / o.y);
	}

	/* Multiply */

	Vec3_i mult(int i) {
		return Vec3_i(x * i, y * i, z * i);
	}

	Vec3_i mult(int a, int b, int c) {
		return Vec3_i(x * a, y * b, z * c);
	}

	Vec3_i mult(Vec3 o) {
		return Vec3_i(x * o.x, y * o.y, z * o.z);
	}
};

struct Vec4 {
	union {
		struct {
			float x, y, z, w;
		};
		float arr[4];
	};
	Vec4() { x = y = z = w = 0; }
	Vec4(float x = 0, float y = 0, float z = 0, float w = 0) {
		this->x = x, this->y = y, this->z = z, this->w = w;
	}

	inline bool contains(Vec2 point) {
		if (point.x <= x || point.y <= y)
			return false;

		if (point.x >= z || point.y >= w)
			return false;

		return true;
	};

	bool operator == (Vec4 v) { return v.x == x && v.y == y && v.z == z && v.w == w; };
	bool operator != (Vec4 v) { return v.x != x || v.y != y || v.z != z || v.w != w; };
};

inline float lerp(float a, float b, float t) {
	return a + t * (b - a);
}

inline std::string getDirection(int deg) {
	deg %= 360;

	if (deg < 0) {
		deg += 360;
	}

	if (22.5 <= deg and deg < 67.5) {
		return "NW";
	} else if(67.5 <= deg and deg < 112.5) {
		return "N";
	} else if(112.5 <= deg and deg < 157.5) {
		return "NE";
	} else if(157.5 <= deg and deg < 202.5) {
		return "E";
	} else if(202.5 <= deg and deg < 247.5) {
		return "SE";
	} else if(247.5 <= deg and deg < 292.5) {
		return "S";
	} else if(292.5 <= deg and deg < 337.5) {
		return "SW";
	}
	else {
		return "W";
	}
}