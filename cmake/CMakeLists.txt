CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

PROJECT( Parametrizable )

FIND_PACKAGE( Qt5Core )
FIND_PACKAGE( Qt5Gui )
FIND_PACKAGE( Qt5Widgets )

INCLUDE( $ENV{RTCV_CMAKE_MACROS_DIR}/cmakeMacros.txt )
MODIFY_COMPILER_FLAGS()
SET_CMAKE_POLICIES()
CONAN_SETUP()

SET( CMAKE_AUTOMOC ON)

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
	#../conanfile.py
)

TARGET_LINK_LIBRARIES( ${PROJECT_NAME}
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
)

SET_PROPERTY( TARGET ${PROJECT_NAME} PROPERTY FOLDER "Algorithms")