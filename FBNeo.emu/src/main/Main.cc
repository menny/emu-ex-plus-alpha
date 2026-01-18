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

#include <emuframework/EmuSystemInlines.hh>
#include <emuframework/EmuAppInlines.hh>

extern "C"
{
	#include <fbneo/burn/burnint.h>
	#include <fbneo/burn/burn.h>
}

import imagine;

namespace EmuEx
{

constexpr SystemLogger log{"FBNeo.emu"};
const char *EmuSystem::creditsViewStr = CREDITS_INFO_STRING "(c) 2025\nMenny Even Danan\n\nFBNeo (c) FBNeo Team\nwww.fbn.com";
bool EmuSystem::handlesGenericIO = true;
bool EmuSystem::canRenderRGBA8888 = false;
bool EmuSystem::hasRectangularPixels = false;
bool EmuApp::needsGlobalInstance = true;

FBNeoApp::FBNeoApp(ApplicationInitParams initParams, ApplicationContext &ctx):
	EmuApp{initParams, ctx}, fbNeoSystem{ctx} {}

FBNeoSystem::FBNeoSystem(ApplicationContext ctx):
	EmuSystem{ctx}
{
	// Initialize FBNeo
}

const char *EmuSystem::shortSystemName() const
{
	return "FBNeo";
}

const char *EmuSystem::systemName() const
{
	return "FinalBurn Neo (CPS1/2/3)";
}

static bool hasCPSExtension(std::string_view name)
{
	return false; // archives handled by EmuFramework
}

EmuSystem::NameFilterFunc EmuSystem::defaultFsFilter = hasCPSExtension;

void FBNeoSystem::reset(EmuApp &, ResetMode mode)
{
	assume(hasContent());
	// Reset FBNeo emulation
}

void FBNeoSystem::loadContent(IO &io, EmuSystemCreateParams params, OnLoadProgressDelegate onLoadProgress_)
{
	onLoadProgress = onLoadProgress_;
	// Load ROM and initialize FBNeo
}

void FBNeoSystem::runFrame(EmuSystemTaskContext task, EmuVideo *video, EmuAudio *audio)
{
	// Run one frame of emulation
}

FS::FileString FBNeoSystem::stateFilename(int slot, std::string_view name) const
{
	return IG::format<FS::FileString>("{}.0{}.sta", name, saveSlotCharUpper(slot));
}

size_t FBNeoSystem::stateSize()
{
	return saveStateSize;
}

void FBNeoSystem::readState(EmuApp &app, std::span<uint8_t> buff)
{
	// Load save state
}

size_t FBNeoSystem::writeState(std::span<uint8_t> buff, SaveStateFlags flags)
{
	// Save state
	return saveStateSize;
}

bool FBNeoSystem::readConfig(ConfigType type, MapIO &io, unsigned key)
{
	if(type == ConfigType::MAIN)
	{
		switch(key)
		{
			case CFGKEY_REGION: return readOptionValue(io, optionRegion);
			case CFGKEY_DIAGNOSTIC_INPUT: return readOptionValue(io, optionDiagnosticInput);
		}
	}
	return false;
}

void FBNeoSystem::writeConfig(ConfigType type, FileIO &io)
{
	if(type == ConfigType::MAIN)
	{
		writeOptionValueIfNotDefault(io, optionRegion);
		writeOptionValueIfNotDefault(io, optionDiagnosticInput);
	}
}

void FBNeoSystem::closeSystem()
{
	// Cleanup FBNeo
}

void FBNeoSystem::clearInputBuffers(EmuInputView &view)
{
	// Clear input state
}

void FBNeoSystem::handleInputAction(EmuApp *app, InputAction a)
{
	// Handle input
}

SystemInputDeviceDesc FBNeoSystem::inputDeviceDesc(int idx) const
{
	static constexpr std::array gamepadComponents
	{
		InputComponentDesc{"D-Pad", dpadKeyInfo, InputComponent::dPad, LB2DO},
		InputComponentDesc{"Face Buttons", faceKeyInfo, InputComponent::button, RB2DO},
		InputComponentDesc{"Select", {&centerKeyInfo[0], 1}, InputComponent::button, LB2DO},
		InputComponentDesc{"Start", {&centerKeyInfo[1], 1}, InputComponent::button, RB2DO},
		InputComponentDesc{"Select/Start", centerKeyInfo, InputComponent::button, CB2DO, {.altConfig = true}},
		InputComponentDesc{"Turbo Buttons", turboFaceKeyInfo, InputComponent::button, RB2DO, {.altConfig = true}},
		InputComponentDesc{"Combos", comboKeyInfo, InputComponent::button, RB2DO, {.altConfig = true}},
	};

	static constexpr SystemInputDeviceDesc gamepadDesc{"Gamepad", gamepadComponents};

	return gamepadDesc;
}

void FBNeoSystem::configAudioRate(FrameRate outputFrameRate, int outputRate)
{
	// Configure audio output rate
}

std::span<const AspectRatioInfo> FBNeoSystem::aspectRatioInfos()
{
	static constexpr AspectRatioInfo aspectRatios[]
	{
		{"4:3 (Original)", {4, 3}},
		EMU_SYSTEM_DEFAULT_ASPECT_RATIO_INFO_INIT
	};
	return aspectRatios;
}

void FBNeoSystem::renderFramebuffer(EmuVideo &video)
{
	// Render framebuffer to video output
}

void FBNeoSystem::onOptionsLoaded()
{
	// Apply loaded options
}

bool FBNeoSystem::resetSessionOptions(EmuApp &app)
{
	optionRegion.reset();
	optionDiagnosticInput.reset();
	return true;
}

void FBNeoSystem::loadBackupMemory(EmuApp &app)
{
	// Load EEPROM/NVRAM
}

void FBNeoSystem::onFlushBackupMemory(EmuApp &app, BackupMemoryDirtyFlags flags)
{
	// Save EEPROM/NVRAM
}

WallClockTimePoint FBNeoSystem::backupMemoryLastWriteTime(const EmuApp &app) const
{
	return appContext().fileUriLastWriteTime(eepromFileIO.uri());
}

FS::FileString FBNeoSystem::contentDisplayNameForPath(IG::CStringView path) const
{
	return FS::fileString(FS::basename(path));
}

}
