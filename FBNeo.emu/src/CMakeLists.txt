target_include_directories(fbneoemu PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/fbneo"
	"${CMAKE_CURRENT_SOURCE_DIR}/fbneo/burn"
	"${CMAKE_CURRENT_SOURCE_DIR}/fbneo/cpu/m68k"
	"${CMAKE_CURRENT_SOURCE_DIR}/fbneo/cpu/z80"
)

# Main integration sources
target_sources(fbneoemu PRIVATE
	main/Main.cc
	main/input.cc
)

# FBNeo burn core
target_sources(fbneoemu PRIVATE
	fbneo/burn/burn.cpp
	fbneo/burn/burn_sound.cpp
	fbneo/burn/burn_sound_c.cpp
	fbneo/burn/burn_memory.cpp
	fbneo/burn/burn_pal.cpp
	fbneo/burn/burn_bitmap.cpp
	fbneo/burn/burn_gun.cpp
	fbneo/burn/burn_led.cpp
	fbneo/burn/burn_shift.cpp
	fbneo/burn/burn_sha1.cpp
	fbneo/burn/cheat.cpp
	fbneo/burn/debug_track.cpp
	fbneo/burn/hiscore.cpp
	fbneo/burn/load.cpp
	fbneo/burn/timer.cpp
	fbneo/burn/tilemap_generic.cpp
	fbneo/burn/tiles_generic.cpp
	fbneo/burn/vector.cpp
)

# CPS drivers
target_sources(fbneoemu PRIVATE
	fbneo/burn/drv/capcom/cps.cpp
	fbneo/burn/drv/capcom/d_cps1.cpp
	fbneo/burn/drv/capcom/d_cps2.cpp
	fbneo/burn/drv/capcom/cps2_crpt.cpp
	fbneo/burn/drv/capcom/cps_config.cpp
	fbneo/burn/drv/capcom/cps_draw.cpp
	fbneo/burn/drv/capcom/cps_mem.cpp
	fbneo/burn/drv/capcom/cps_obj.cpp
	fbneo/burn/drv/capcom/cps_pal.cpp
	fbneo/burn/drv/capcom/cps_run.cpp
	fbneo/burn/drv/capcom/cps_rw.cpp
	fbneo/burn/drv/capcom/cps_scr.cpp
	fbneo/burn/drv/capcom/cpsr.cpp
	fbneo/burn/drv/capcom/cpsrd.cpp
	fbneo/burn/drv/capcom/cpst.cpp
	fbneo/burn/drv/capcom/ctv.cpp
	fbneo/burn/drv/capcom/ctv_make.cpp
	fbneo/burn/drv/capcom/kabuki.cpp
	fbneo/burn/drv/capcom/fcrash_snd.cpp
	fbneo/burn/drv/capcom/sf2mdt_snd.cpp
	fbneo/burn/drv/capcom/ps.cpp
	fbneo/burn/drv/capcom/ps_m.cpp
	fbneo/burn/drv/capcom/ps_z.cpp
	fbneo/burn/drv/capcom/qs.cpp
	fbneo/burn/drv/capcom/qs_c.cpp
	fbneo/burn/drv/capcom/qs_z.cpp
)

# Sound chips
target_sources(fbneoemu PRIVATE
	fbneo/burn/snd/burn_ym2151.cpp
	fbneo/burn/snd/ym2151.c
	fbneo/burn/snd/msm6295.cpp
)

# Devices
target_sources(fbneoemu PRIVATE
	fbneo/burn/devices/eeprom.cpp
	fbneo/burn/devices/timekpr.cpp
)

# CPU cores
target_sources(fbneoemu PRIVATE
	fbneo/cpu/m68k/m68kcpu.c
	fbneo/cpu/m68k/m68kdasm.c
	fbneo/cpu/z80/z80.cpp
	fbneo/cpu/z80/z80daisy.cpp
)
