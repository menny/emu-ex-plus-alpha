#pragma once

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

#include <emuframework/EmuOptions.hh>
#include <emuframework/EmuSystem.hh>
#include <imagine/io/FileIO.hh>

extern "C"
{
	#include <fbneo/burn/burnint.h>
}

namespace EmuEx::Controls
{
static const unsigned joystickKeys = 19;
}

namespace EmuEx
{

enum FBNeoConfigKey
{
	CFGKEY_DIP_SWITCHES = 275,
	CFGKEY_REGION = 276,
	CFGKEY_DIAGNOSTIC_INPUT = 277
};

class FBNeoSystem final: public EmuSystem
{
public:
	static constexpr auto pixFmt = IG::PixelFmtRGB565;
	static constexpr int FBResX = 512; // Max CPS resolution width
	static constexpr int FBResY = 512; // Max CPS resolution height
	size_t saveStateSize{};
	FileIO eepromFileIO;
	uint16_t screenBuff[FBResX * FBResY] __attribute__ ((aligned (8))){};
	EmuSystem::OnLoadProgressDelegate onLoadProgress{};
	Property<uint8_t, CFGKEY_REGION,
		PropertyDesc<uint8_t>{.defaultValue = 0}> optionRegion;
	Property<bool, CFGKEY_DIAGNOSTIC_INPUT> optionDiagnosticInput;
	static constexpr FrameRate fbNeoFrameRate{60.}; // CPS standard frame rate

	FBNeoSystem(ApplicationContext ctx);
	PixmapView videoPixmap()
	{
		// FBNeo renders to variable resolution based on game
		// Will be updated per-frame based on actual game resolution
		return {{{384, 224}, pixFmt}, screenBuff, {FBResX, IG::PixmapView::Units::PIXEL}};
	}

	// required API functions
	void loadContent(IO &, EmuSystemCreateParams, OnLoadProgressDelegate);
	[[gnu::hot]] void runFrame(EmuSystemTaskContext task, EmuVideo *video, EmuAudio *audio);
	FS::FileString stateFilename(int slot, std::string_view name) const;
	std::string_view stateFilenameExt() const { return ".sta"; }
	size_t stateSize();
	void readState(EmuApp &, std::span<uint8_t> buff);
	size_t writeState(std::span<uint8_t> buff, SaveStateFlags = {});
	bool readConfig(ConfigType, MapIO &, unsigned key);
	void writeConfig(ConfigType, FileIO &);
	void reset(EmuApp &, ResetMode mode);
	void clearInputBuffers(EmuInputView &view);
	void handleInputAction(EmuApp *, InputAction);
	SystemInputDeviceDesc inputDeviceDesc(int idx) const;
	FrameRate frameRate() const { return fbNeoFrameRate; }
	void configAudioRate(FrameRate outputFrameRate, int outputRate);
	static std::span<const AspectRatioInfo> aspectRatioInfos();

	// optional API functions
	void closeSystem();
	void renderFramebuffer(EmuVideo &);
	void onOptionsLoaded();
	bool resetSessionOptions(EmuApp &);
	void loadBackupMemory(EmuApp &);
	void onFlushBackupMemory(EmuApp &, BackupMemoryDirtyFlags);
	WallClockTimePoint backupMemoryLastWriteTime(const EmuApp &) const;
	FS::FileString contentDisplayNameForPath(IG::CStringView path) const;
};

using MainSystem = FBNeoSystem;

}

constexpr EmuEx::EmuSystem::BackupMemoryDirtyFlags EEPROM_DIRTY_BIT = IG::bit(0);
