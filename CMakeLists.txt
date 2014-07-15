project(imgconv)

add_definitions("-D_CRT_SECURE_NO_DEPRECATE")

set(SRC_DIR "src/")

set(READIMG_LIST
	${SRC_DIR}/bmp.c
	)

add_executable(bmp ${READIMG_LIST})

