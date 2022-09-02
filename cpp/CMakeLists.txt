cmake_minimum_required(VERSION 3.13)

project(RedEyeFiltering)

set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(SOURCES main.cpp
            Solution.h
            utils/CommonDefines.h
            utils/EyePatterns.h
            utils/FileParser.h
            utils/FunctionTracer.h
            utils/Image.h
            utils/Image.cpp
            utils/SolutionEvaluator.h)

add_executable(red_eye_filtering ${SOURCES})
