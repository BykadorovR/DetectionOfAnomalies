cmake_minimum_required(VERSION 3.4)
project(bones)
#########################################################
# FIND OPENGL
#########################################################
set (OpenCV_DIR "C:/Users/Roman/Desktop/Education/opencv/sources/build")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
#########################################################
# FIND GLUT
#########################################################
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)
#########################################################
# FIND OPENGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)
#########################################################
# FIND GDCM
#########################################################
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} /MDd")
FIND_PACKAGE(GDCM REQUIRED)
    IF(GDCM_FOUND)
        include(${GDCM_USE_FILE})
        message(STATUS ${GDCM_USE_FILE})
        set(GDCM_LIBRARIES gdcmMSFF gdcmCommon gdcmDSED gdcmDICT gdcmIOD)
    ELSE(GDCM_FOUND)
        MESSAGE(FATAL_ERROR "Cannot find GDCM, did you set GDCM_DIR?")
    ENDIF(GDCM_FOUND)


include_directories("include/")
set (SRC src/Reader.cpp src/Utils.cpp src/Detecting.cpp)
FILE(GLOB INCLUDE include/*.h) #Get all include files and make for them separate folder in visual studio 
add_executable(${PROJECT_NAME} ${SRC}  src/Main.cpp ${INCLUDE})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GDCM_LIBRARIES} ${OpenCV_LIBS})




