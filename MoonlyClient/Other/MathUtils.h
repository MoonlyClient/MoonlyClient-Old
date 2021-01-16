#pragma once

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