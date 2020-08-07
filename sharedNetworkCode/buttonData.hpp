#pragma once

#define SET_BIT(number, bit, loc) (number) ^= (-(unsigned long)(bit) ^ (number)) & (1UL << (loc))
#define GET_BIT(number, loc) ((number) >> (loc)) & 1U

#include "include/zpp.hpp"
#include <cstdint>

// Buttons enum (coencides with the index of the bit in the input struct)
// Also used to identify the button everywhere else in the program
enum Btn : uint8_t {
	A,
	B,
	X,
	Y,
	L,
	R,
	ZL,
	ZR,
	SL,
	SR,
	DUP,
	DDOWN,
	DLEFT,
	DRIGHT,
	PLUS,
	MINUS,
	HOME,
	CAPT,
	LS,
	RS,
	BUTTONS_SIZE,
};

enum FrameState : uint8_t {
	RAN,
	SAVESTATE,
};

// Controller data that will be packed into the array and will be recieved from
// the switch
struct ControllerData : public zpp::serializer::polymorphic {
	// Button data stored with bitflags in 3 bytes
	// 20 flags need to be stored
	uint32_t buttons = 0;
	// Joystick values
	// https://switchbrew.github.io/libnx/structHiddbgHdlsState.html
	// Range -30000 to 30000
	int16_t LS_X = 0;
	int16_t LS_Y = 0;
	int16_t RS_X = 0;
	int16_t RS_Y = 0;
	// Gyroscope and Accelerometer data, all floats
	float ACCEL_X = 0;
	float ACCEL_Y = 0;
	float ACCEL_Z = 0;
	float GYRO_X  = 0;
	float GYRO_Y  = 0;
	float GYRO_Z  = 0;
	float ANGLE_X = 0;
	float ANGLE_Y = 0;
	float ANGLE_Z = 0;
	// State of the frame, mostly for the editor
	uint8_t frameState = 0;

	friend zpp::serializer::access;
	template <typename Archive, typename Self> static void serialize(Archive& archive, Self& self) {
		// clang-format off
			archive(self.buttons,
				self.LS_X, self.LS_Y, self.RS_X, self.RS_Y,
				self.ACCEL_X, self.ACCEL_Y, self.ACCEL_Z,
				self.GYRO_X, self.GYRO_Y, self.GYRO_Z,
				self.ANGLE_X, self.ANGLE_Y, self.ANGLE_Z,
				self.frameState);
		// clang-format on
	}
};

// Not button data, but the memory info
// Mirrors libnx MemoryInfo
/*
struct GameMemoryInfo {
	uint64_t addr;            ///< Base address.
	uint64_t size;            ///< Size.
	uint32_t type;            ///< Memory type (see lower 8 bits of \ref MemoryState).
	uint32_t attr;            ///< Memory attributes (see \ref MemoryAttribute).
	uint32_t perm;            ///< Memory permissions (see \ref Permission).
	uint32_t device_refcount; ///< Device reference count.
	uint32_t ipc_refcount;    ///< IPC reference count.
	uint32_t padding;         ///< Padding.

	friend zpp::serializer::access;
	template <typename Archive, typename Self> static void serialize(Archive& archive, Self& self) {
		// clang-format off
			archive(self.addr, self.size, self.type,
				self.attr, self.perm, self.device_refcount,
				self.ipc_refcount, self.padding);
		// clang-format on
	}
};
*/