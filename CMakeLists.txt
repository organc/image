project(image)

add_definitions("-D_CRT_SECURE_NO_DEPRECATE")

include_directories("src")

set(SRC_DIR "src/")
set(TEST_DIR "tests/")

set(READIMG_LIST
	${SRC_DIR}/bmp.c
	${TEST_DIR}/bmp.c
	)

add_executable(bmp ${READIMG_LIST})

