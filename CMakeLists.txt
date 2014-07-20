project(image)

add_definitions("-D_CRT_SECURE_NO_DEPRECATE")

include_directories("src")

set(SRC_DIR "src/")
set(TEST_DIR "tests/")

set(IMAGE
	${SRC_DIR}/bmp.c
	${SRC_DIR}/transform.c
	${SRC_DIR}/matrix.c
	)
add_library(image SHARED ${IMAGE})

set(IMAGE_TEST
	${TEST_DIR}/bmp.c
	)
add_executable(bmp ${IMAGE_TEST})
target_link_libraries(bmp image)
