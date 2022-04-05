cmake_minimum_required(VERSION 3.17)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Werror -Wall -Wextra -Wpedantic -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wmissing-field-initializers -Wctor-dtor-privacy  -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wsign-promo -fsanitize=address,undefined -fno-sanitize-recover=all")

set(SOURCE_FILES
        image_processor.cpp

        sources/logger.cpp
        sources/filter.cpp

        sources/additional.cpp
        sources/exception.cpp
        sources/argparser.cpp

        sources/image_processing/image_holder.cpp
        sources/image_processing/image.cpp
        sources/image_processing/abstract_image.cpp

        sources/filters/crop.cpp
        sources/filters/edge_detection.cpp
        sources/filters/gauss_blur.cpp
        sources/filters/grayscale.cpp
        sources/filters/negative.cpp
        sources/filters/sharp.cpp
        sources/filters/bilateral.cpp)


add_executable(image_processor ${SOURCE_FILES} image_processor.cpp)

target_include_directories(image_processor PRIVATE sources)

set(CMAKE_PROJECT_ROOT "${CMAKE_SOURCE_DIR}/../../")
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_PROJECT_ROOT}/cmake")
include(${CMAKE_PROJECT_ROOT}/cmake/TestSolution.cmake)
find_package(Catch REQUIRED)

#set(TEST_FILES
#        tests/test_for_wo_main1.cpp
#        tests/test_for_wo_main2.cpp
#        )

# add_catch(test_image_processor ${SOURCE_FILES} ${TEST_FILES})
# target_include_directories(test_image_processor PRIVATE sources)