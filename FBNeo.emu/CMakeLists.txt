cmake_minimum_required(VERSION 4.1)

project(
	FBNeo.emu
	DESCRIPTION "FinalBurn Neo CPS1/CPS2/CPS3 emulator"
	HOMEPAGE_URL "https://www.explusalpha.com/"
)

include(emuFrameworkUtils.cmake)
printConfigInfo()
configureAppTarget(fbneoemu)
addPkgConfigDepMultiConfig(fbneoemu emuframework)
addCxxModules(fbneoemu emuex imagine)
evalPkgConfigFlags(fbneoemu all)
target_compile_definitions(fbneoemu PRIVATE
	$<$<COMPILE_LANGUAGE:C,CXX>:LSB_FIRST>
)
target_compile_options(fbneoemu PRIVATE
	$<$<COMPILE_LANGUAGE:C,CXX>:-Wno-sign-compare -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable>
	$<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-declarations>
)
add_subdirectory(src)
