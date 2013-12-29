
INCLUDE_DIRECTORIES( ${GLUT_INCLUDE_DIR}
                     ${OPENGL_INCLUDE_DIRS}
                     ${FREETYPE_INCLUDE_DIRS}
                     ${CMAKE_CURRENT_SOURCE_DIR}
                     ${VS789FIX_INCLUDE_DIR})
					 
IF(USE_GLEW)
	INCLUDE_DIRECTORIES(${GLEW_INCLUDE_DIR})
	ADD_DEFINITIONS(-DUSE_GLEW)
ELSE(USE_GLEW)
	INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/external)
ENDIF(USE_GLEW)

IF(MSVC)
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
ENDIF(MSVC)

SET( FREETYPE_GL_SRC freetype-gl.h
                     vec234.h
                     opengl.h
                     markup.h
                     mat4.c             mat4.h
                     texture-atlas.c    texture-atlas.h
                     texture-font.c     texture-font.h
                     vertex-buffer.c    vertex-buffer.h
                     vertex-attribute.c vertex-attribute.h
                     font-manager.c     font-manager.h
                     text-buffer.c      text-buffer.h
                     shader.c           shader.h
                     vector.c           vector.h
                     platform.c         platform.h
					 callbacks.c		callbacks.h
					 ext_funcs.c		ext_funcs.h
					 opengl_funcs.h)
					 
ADD_LIBRARY( freetype-gl STATIC ${FREETYPE_GL_SRC} )

SET(FREETYPE_GL_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")
