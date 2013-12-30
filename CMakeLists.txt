# =========================================================================
# Freetype GL - A C OpenGL Freetype engine
# Platform:    Any
# WWW:         http://code.google.com/p/freetype-gl/
# -------------------------------------------------------------------------
# Copyright 2011,2012 Nicolas P. Rougier. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#  1. Redistributions of source code must retain the above copyright notice,
#     this list of conditions and the following disclaimer.
#
#  2. Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY NICOLAS P. ROUGIER ''AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
# EVENT SHALL NICOLAS P. ROUGIER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
# INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# The views and conclusions contained in the software and documentation are
# those of the authors and should not be interpreted as representing official
# policies, either expressed or implied, of Nicolas P. Rougier.
# =========================================================================
CMAKE_MINIMUM_REQUIRED( VERSION 2.8.5 )
SET( CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules"
                       "${CMAKE_MODULE_PATH}" )

OPTION(freetype-gl_BUILD_DEMOS "Build the freetype-gl example programs" ON)
OPTION(USE_GLEW "Disable usage of GLEW" ON)

IF(freetype-gl_BUILD_DEMOS)
	SET(USE_GLEW ON)
ENDIF(freetype-gl_BUILD_DEMOS)

PROJECT(freetype-gl)

IF(MSVC)
	OPTION(MSVC_STATIC_RUNTIME "Link the static runtime for Visual Studio" OFF)
ENDIF(MSVC)

IF(MSVC AND MSVC_STATIC_RUNTIME)
	string(REPLACE "/MDd" "/MTd" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
	string(REPLACE "/MD" "/MT" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
	
	string(REPLACE "/MDd" "/MTd" CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
	string(REPLACE "/MD" "/MT" CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
	
	string(REPLACE "/MDd" "/MTd" CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")
	string(REPLACE "/MD" "/MT" CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")
	
	string(REPLACE "/MDd" "/MTd" CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL}")
	string(REPLACE "/MD" "/MT" CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL}")
	
	string(REPLACE "/MDd" "/MTd" CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO}")
	string(REPLACE "/MD" "/MT" CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO}")
ENDIF(MSVC AND MSVC_STATIC_RUNTIME)

# Get required and optional library
FIND_PACKAGE( OpenGL REQUIRED )
IF( WIN32 OR WIN64 )
	SET( WINDOWS_DIR
         ${CMAKE_CURRENT_SOURCE_DIR}/windows )
	SET( GLUT_INCLUDE_DIR
         ${CMAKE_CURRENT_SOURCE_DIR}/windows/glut )
	SET( GLUT_LIBRARY
         ${CMAKE_CURRENT_SOURCE_DIR}/windows/glut/glut32.lib )
    SET( GLEW_INCLUDE_DIR
         ${CMAKE_CURRENT_SOURCE_DIR}/windows/glew/include )
    SET( GLEW_LIBRARY
         ${CMAKE_CURRENT_SOURCE_DIR}/windows/glew/lib/glew32.lib )
	SET( FREETYPE_INCLUDE_DIRS
         ${CMAKE_CURRENT_SOURCE_DIR}/windows/freetype )
	SET( FREETYPE_INCLUDE_DIR_ft2build
         ${CMAKE_CURRENT_SOURCE_DIR}/windows/freetype )
	SET( FREETYPE_INCLUDE_DIR_freetype2
         ${CMAKE_CURRENT_SOURCE_DIR}/windows/freetype/freetype )
	SET( FREETYPE_LIBRARY
         ${CMAKE_CURRENT_SOURCE_DIR}/windows/freetype/freetype.lib )
	SET( ANT_TWEAK_BAR_INCLUDE_PATH
         ${CMAKE_CURRENT_SOURCE_DIR}/windows/AntTweakBar/include )
	SET( ANT_TWEAK_BAR_LIBRARY
         ${CMAKE_CURRENT_SOURCE_DIR}/windows/AntTweakBar/lib/AntTweakBar.lib )
    SET( VS789FIX_INCLUDE_DIR
         ${CMAKE_CURRENT_SOURCE_DIR}/windows/include )
    SET( ANT_TWEAK_BAR_FOUND "YES" )
	
	SET(GLEW_DLL ${WINDOWS_DIR}/glew/bin/glew32.dll)
	
	SET(GLUT_DLL ${WINDOWS_DIR}/glut/glut32.dll)
ELSE( WIN32 OR WIN64 )
    FIND_PACKAGE( GLUT REQUIRED )
    FIND_PACKAGE( Freetype REQUIRED )
    FIND_PACKAGE( GLEW REQUIRED )
    FIND_PACKAGE( FontConfig )
    FIND_LIBRARY( MATH_LIBRARY m )
    #FIND_LIBRARY( STDC_LIBRARY stdc++) #Buggy Cmake can't find libstdc++
    FIND_PACKAGE( AntTweakBar )
ENDIF( WIN32 OR WIN64 )

ADD_SUBDIRECTORY(src)

IF(freetype-gl_BUILD_DEMOS)
	ADD_SUBDIRECTORY(demos)
ENDIF(freetype-gl_BUILD_DEMOS)
