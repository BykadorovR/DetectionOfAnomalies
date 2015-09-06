find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS}) 
foreach(SRCITEM ${SRC})

set (EXTSRC ${EXTSRC} ${PROJECT_SOURCE_DIR}/${SRCITEM})
endforeach()

add_executable(runTests src/test_main.cpp src/test_reader.cpp src/test_utils.cpp src/test_algorithms.cpp ${EXTSRC})
target_link_libraries(runTests ${GDCM_LIBRARIES})
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

