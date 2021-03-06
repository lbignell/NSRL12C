# $Id: CMakeLists.txt 68058 2013-03-13 14:47:43Z gcosmo $
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

############ Make your changes here ############ 
 
set(name NSRL12C)  # equivalent to "name := exampleN01" in G4 GNUmakefiles
set(useROOT true)        # use true or false


############ What's below should not need to be changed ############ 

set(mymain ${name}.cc )
set(myexe  ${name}    )
set(myproj ${name}_   )# any name as long as it is different from myexe

#----------------------------------------------------------------------------
# Setup the project
project(${myproj})

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

if(useROOT)
        #I added this line
        find_package(ROOT)
	#Below lines came with cmakefile.
	EXECUTE_PROCESS(COMMAND root-config --cflags OUTPUT_VARIABLE ROOT_CXX_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ROOT_CXX_FLAGS}")
endif(useROOT) 

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(${myexe} ${mymain} ${sources} ${headers})
if(useROOT)
	EXECUTE_PROCESS(COMMAND root-config --libs OUTPUT_VARIABLE ROOT_LD_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
	set(CMAKE_EXE_LINKER_FLAGS ${ROOT_LD_FLAGS})
	#I also added this line. ROOT_LIBRARIES is set by find_package(ROOT).
	set(ROOT_LIBRARIES ${ROOT_LIBRARIES})
endif(useROOT)
#And I modified this line...
target_link_libraries(${myexe} ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build B1. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(EDEPNSRL2014_SCRIPTS
  vis.mac
  run.mac
  )

#find_package(ROOT)
#include_directories(/usr/include/root/)

#foreach(_script ${EDEPNSRL2014_SCRIPTS})
#  configure_file(
#    ${PROJECT_SOURCE_DIR}/${_script}
#    ${PROJECT_BINARY_DIR}/${_script}
#    COPYONLY
#    )
#endforeach()

#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build this
# example standalone
#
add_custom_target(${myproj} DEPENDS ${myexe})

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS ${myexe} DESTINATION bin)


