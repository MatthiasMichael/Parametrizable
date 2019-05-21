CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

PROJECT( Parametrizable )

INCLUDE(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
CONAN_BASIC_SETUP()

FIND_PACKAGE( Qt5Core )
FIND_PACKAGE( Qt5Gui )
FIND_PACKAGE( Qt5Widgets )

SET( CMAKE_AUTOMOC ON)

SET( BUILD_EXAMPLES ON CACHE BOOL "Build example projects.")

INCLUDE_DIRECTORIES(
	../include/
	${CMAKE_CURRENT_BINARY_DIR}
)

ADD_LIBRARY ( ${PROJECT_NAME}
	../include/GenericParameter.h
	../include/GenericParameterWidget.h
	../include/GenericVisualComponent.h
	../include/Parametrizable.h
	../src/GenericParameter.cpp
	../src/GenericParameterWidget.cpp
	../src/GenericVisualComponent.cpp
	../src/Parametrizable.cpp
)

TARGET_LINK_LIBRARIES( ${PROJECT_NAME}
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
)

SET_PROPERTY( TARGET ${PROJECT_NAME} PROPERTY FOLDER "Algorithms")

IF( BUILD_EXAMPLES )
	ADD_SUBDIRECTORY( ../example ${CMAKE_CURRENT_BINARY_DIR}/example )
ENDIF()