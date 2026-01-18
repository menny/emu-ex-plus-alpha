/*  This file is part of FBNeo.emu.

	FBNeo.emu is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	FBNeo.emu is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with FBNeo.emu.  If not, see <http://www.gnu.org/licenses/> */

#include "MainSystem.hh"
#include "MainApp.hh"

import emuex;
import imagine;

namespace EmuEx
{

const int EmuSystem::maxPlayers = 2;

enum class FBNeoKey : KeyCode
{
	Up = 1,
	Right = 4,
	Down = 2,
	Left = 3,
	A = 5,
	B = 6,
	C = 7,
	D = 8,
	E = 9,
	F = 10,
	Select = 11,
	Start = 12,
	Diagnostic = 13
};

constexpr auto dpadKeyInfo = makeArray<KeyInfo>
(
	FBNeoKey::Up,
	FBNeoKey::Right,
	FBNeoKey::Down,
	FBNeoKey::Left
);

constexpr auto centerKeyInfo = makeArray<KeyInfo>
(
	FBNeoKey::Select,
	FBNeoKey::Start
);

constexpr auto faceKeyInfo = makeArray<KeyInfo>
(
	FBNeoKey::A,
	FBNeoKey::B,
	FBNeoKey::C,
	FBNeoKey::D,
	FBNeoKey::E,
	FBNeoKey::F
);

constexpr auto turboFaceKeyInfo = turbo(faceKeyInfo);

constexpr std::array comboKeyInfo{KeyInfo{std::array{FBNeoKey::A, FBNeoKey::B, FBNeoKey::C}}};

constexpr auto gpKeyInfo = concatToArrayNow<dpadKeyInfo, centerKeyInfo, faceKeyInfo, turboFaceKeyInfo, comboKeyInfo>;
constexpr auto gp2KeyInfo = transpose(gpKeyInfo, 1);

std::span<const KeyCategory> FBNeoApp::keyCategories()
{
	static constexpr std::array categories
	{
		KeyCategory{"Gamepad", gpKeyInfo},
		KeyCategory{"Gamepad 2", gp2KeyInfo, 1},
	};
	return categories;
}

std::string_view FBNeoApp::systemKeyCodeToString(KeyCode c)
{
	switch(FBNeoKey(c))
	{
		case FBNeoKey::Up: return "Up";
		case FBNeoKey::Right: return "Right";
		case FBNeoKey::Down: return "Down";
		case FBNeoKey::Left: return "Left";
		case FBNeoKey::A: return "A";
		case FBNeoKey::B: return "B";
		case FBNeoKey::C: return "C";
		case FBNeoKey::D: return "D";
		case FBNeoKey::E: return "E";
		case FBNeoKey::F: return "F";
		case FBNeoKey::Select: return "Select";
		case FBNeoKey::Start: return "Start";
		case FBNeoKey::Diagnostic: return "Diagnostic";
		default: return "";
	}
}

std::span<const KeyConfigDesc> FBNeoApp::defaultKeyConfigs()
{
	using namespace IG::Input;

	static constexpr std::array pcKeyboardMap
	{
		KeyMapping{FBNeoKey::Up, Keycode::UP},
		KeyMapping{FBNeoKey::Right, Keycode::RIGHT},
		KeyMapping{FBNeoKey::Down, Keycode::DOWN},
		KeyMapping{FBNeoKey::Left, Keycode::LEFT},
		KeyMapping{FBNeoKey::A, Keycode::Z},
		KeyMapping{FBNeoKey::B, Keycode::X},
		KeyMapping{FBNeoKey::C, Keycode::C},
		KeyMapping{FBNeoKey::D, Keycode::V},
		KeyMapping{FBNeoKey::E, Keycode::B},
		KeyMapping{FBNeoKey::F, Keycode::N},
		KeyMapping{FBNeoKey::Select, Keycode::SPACE},
		KeyMapping{FBNeoKey::Start, Keycode::ENTER},
	};

	static constexpr std::array genericGamepadMap
	{
		KeyMapping{FBNeoKey::Up, Keycode::UP},
		KeyMapping{FBNeoKey::Right, Keycode::RIGHT},
		KeyMapping{FBNeoKey::Down, Keycode::DOWN},
		KeyMapping{FBNeoKey::Left, Keycode::LEFT},
		KeyMapping{FBNeoKey::A, Keycode::GAME_A},
		KeyMapping{FBNeoKey::B, Keycode::GAME_B},
		KeyMapping{FBNeoKey::C, Keycode::GAME_X},
		KeyMapping{FBNeoKey::D, Keycode::GAME_Y},
		KeyMapping{FBNeoKey::E, Keycode::GAME_L1},
		KeyMapping{FBNeoKey::F, Keycode::GAME_R1},
		KeyMapping{FBNeoKey::Select, Keycode::GAME_SELECT},
		KeyMapping{FBNeoKey::Start, Keycode::GAME_START},
	};

	return genericKeyConfigs<pcKeyboardMap, genericGamepadMap>();
}

bool FBNeoApp::allowsTurboModifier(KeyCode c)
{
	switch(FBNeoKey(c))
	{
		case FBNeoKey::A ... FBNeoKey::F:
			return true;
		default:
			return false;
	}
}

AssetDesc FBNeoApp::vControllerAssetDesc(KeyInfo key) const
{
	static constexpr struct VirtualControllerAssets
	{
		AssetDesc dPad{AssetFileID::gamepadOverlay, {.size = {96, 96}}},
		a{AssetFileID::a, {.size = {48, 48}}},
		b{AssetFileID::b, {.size = {48, 48}}},
		c{AssetFileID::c, {.size = {48, 48}}},
		d{AssetFileID::d, {.size = {48, 48}}},
		e{AssetFileID::e, {.size = {48, 48}}},
		f{AssetFileID::f, {.size = {48, 48}}},
		select{AssetFileID::select, {.size = {64, 32}}},
		start{AssetFileID::start, {.size = {64, 32}}},
		combo{AssetFileID::abc, {.size = {80, 48}}},
		blank{AssetFileID::blank};
	} virtualControllerAssets;

	if(key[0] == 0)
		return virtualControllerAssets.dPad;
	switch(FBNeoKey(key[0]))
	{
		case FBNeoKey::A: return virtualControllerAssets.a;
		case FBNeoKey::B: return virtualControllerAssets.b;
		case FBNeoKey::C: return virtualControllerAssets.c;
		case FBNeoKey::D: return virtualControllerAssets.d;
		case FBNeoKey::E: return virtualControllerAssets.e;
		case FBNeoKey::F: return virtualControllerAssets.f;
		case FBNeoKey::Select: return virtualControllerAssets.select;
		case FBNeoKey::Start: return virtualControllerAssets.start;
		default: return virtualControllerAssets.blank;
	}
}

}
