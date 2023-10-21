project(CustomPath)

set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

set(HEADERS
    ${HEADER_DIR}/c_path.h
)

set(SOURCES
    ${SOURCE_DIR}/c_path.cpp
)

add_library(${PROJECT_NAME}
    STATIC
        ${HEADERS}
        ${SOURCES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${HEADER_DIR}>
)

if (CMAKE_VERSION VERSION_GREATER 3.8)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
else()
    set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
endif()
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED on)