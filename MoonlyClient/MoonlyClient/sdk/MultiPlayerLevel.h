#pragma once

class MultiPlayerLevel {
public:
	uintptr_t firstEntity; //0x0008
	uint64_t listStart; //0x0050
	uint64_t listEnd; //0x0058
	uintptr_t endAddr; //0x0060

public:

	inline class Actor* get(size_t idx) {
		if (idx >= getListSize())
			return 0;
		return *reinterpret_cast<class Actor**>(listStart + (idx * sizeof(uintptr_t)));
	}

	inline size_t getListSize() {
		return (listEnd - listStart) / sizeof(uintptr_t);
	}
};