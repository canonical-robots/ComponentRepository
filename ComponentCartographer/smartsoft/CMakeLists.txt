#--------------------------------------------------------------------------
# Code generated by the SmartSoft MDSD Toolchain
# The SmartSoft Toolchain has been developed by:
#  
# Service Robotics Research Center
# University of Applied Sciences Ulm
# Prittwitzstr. 10
# 89075 Ulm (Germany)
#
# Information about the SmartSoft MDSD Toolchain is available at:
# www.servicerobotik-ulm.de
#
# This file is generated once. Modify this file to your needs. 
# If you want the toolchain to re-generate this file, please 
# delete it before running the code generator.
#--------------------------------------------------------------------------

CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

# find the SmartSoft CMake Macros (version 2 that uses CMake v3)
FIND_FILE(SMART_MACROS SmartMacros2.cmake PATHS $ENV{SMART_ROOT_ACE}/CMakeMacros /opt/smartSoftAce/CMakeMacros/)
INCLUDE(${SMART_MACROS})

# Create and configure a CMake project for a CommunicationObject
SMART_COMPONENT_PROJECT()

# find SmartSoft package
#FIND_SMARTSOFT(3.0)
#FIXME: generalize this
FIND_PACKAGE(AceSmartSoft PATHS $ENV{SMART_ROOT_ACE}/build)

# generte doxygen documentation
SMART_COMPONENT_GENERATE_DOC()

# automatically build CommunicationObject dependencies
SMART_COMPONENT_AUTOBUILD_DEPENDENCIES()

#################################################################################
## here you can put all your project-specific compiler configurations          ##
## using regular CMake commands (like FIND_PACKAGE, INCLUDE_DIRECTORIES, etc.) ##

# you can add additional external libraries using regular CMake commands, e.g.:
find_package(Boost REQUIRED COMPONENTS system iostreams)
find_package(PCL REQUIRED COMPONENTS common)
find_package(cartographer REQUIRED)
find_package(LuaGoogle REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)

FIND_PACKAGE( MRPT REQUIRED gui base maps)

MESSAGE("MRPT_VERSION: ${MRPT_VERSION}")
IF(MRPT_VERSION VERSION_LESS 1.3.0)
MESSAGE("OLD MRPT VERSION DETECTED ..")
add_definitions(-DWITH_OLD_MRPT_VERSION)
ENDIF()


include("${CARTOGRAPHER_CMAKE_DIR}/functions.cmake")
INCLUDE(${CMAKE_CURRENT_LIST_DIR}/src-gen/MixedPortIncludes.cmake)

# these are the regular includes (add your own includes, if needed)
INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_LIST_DIR}/src
  ${CMAKE_CURRENT_LIST_DIR}/src-gen
  ${CMAKE_CURRENT_LIST_DIR}/src-gen/params
  ${EIGEN3_INCLUDE_DIR}
  ${Boost_INCLUDE_DIRS}
  ${LUA_INCLUDE_DIR}
  ${PCL_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${MRPT_INCLUDE_DIRS}
)

# collect the toolchain-generated source-files
FILE(GLOB_RECURSE SRC ${CMAKE_CURRENT_LIST_DIR}/src/*.cc)
FILE(GLOB_RECURSE SRC_GEN ${CMAKE_CURRENT_LIST_DIR}/src-gen/*.cc)
FILE(GLOB_RECURSE SRC_GEN_PARAMS ${CMAKE_CURRENT_LIST_DIR}/src-gen/params/*.cc)

# collect your own (local) source-files here (if needed)
#FILE(GLOB_RECURSE USER_SRC ${CMAKE_CURRENT_LIST_DIR}/src/<your-sources>)

# create the executable using collected source-files
ADD_EXECUTABLE(${PROJECT_NAME} ${SRC} ${SRC_GEN} ${SRC_GEN_PARAMS} ${FURTHER_SRCS}) # add ${USER_SRC} (if needed)

# link your external libraries here (if there are any)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} cartographer ${Boost_LIBRARIES} ${PCL_LIBRARIES} ${OpenCV_LIBS} ${MRPT_LIBS})

INCLUDE(${CMAKE_CURRENT_LIST_DIR}/src-gen/MixedPortTargetConfigs.cmake)

#INSTALL(FILES ${PROJECT_SOURCE_DIR}/src-gen/${PROJECT_NAME}.ini.template DESTINATION etc)

## end user-code                                                               ##
#################################################################################

# SmartSoftKernel is one of the default dependencies for each component
TARGET_LINK_LIBRARIES(${PROJECT_NAME} AceSmartSoftKernel)

# automatically link to all dependent CommunicationObjects
SMART_COMPONENT_AUTOLINK_DEPENDENCIES()

# automatically install the component target
SMART_COMPONENT_AUTOINSTALL()
