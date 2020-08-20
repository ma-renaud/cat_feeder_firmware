SET(STM_COMMON_COMPILE_FLAGS "-mcpu=cortex-m0 -mthumb -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -fno-stack-protector -Wall -Wextra")

SET(CMAKE_C_FLAGS_DEBUG "${COMMON_FLAGS} -Og -g3 -ffreestanding -DDEBUG" CACHE INTERNAL "c compiler flags debug")
SET(CMAKE_CXX_FLAGS_DEBUG "${COMMON_FLAGS} -Og -g3 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -DDEBUG" CACHE INTERNAL "cxx compiler flags debug")
SET(CMAKE_ASM_FLAGS_DEBUG "-g3" CACHE INTERNAL "asm compiler flags debug")

SET(CMAKE_C_FLAGS_RELEASE "${COMMON_FLAGS} -O3 -g " CACHE INTERNAL "c compiler flags release")
SET(CMAKE_CXX_FLAGS_RELEASE "${COMMON_FLAGS} -O3 -g -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics" CACHE INTERNAL "cxx compiler flags release")
SET(CMAKE_ASM_FLAGS_RELEASE "-g" CACHE INTERNAL "asm compiler flags release")