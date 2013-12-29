
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

SET(HEADERS  freetype-gl.h
			 vec234.h
			 opengl.h
			 markup.h
			 mat4.h
			 texture-atlas.h
			 texture-font.h
			 vertex-buffer.h
			 vertex-attribute.h
			 font-manager.h
			 text-buffer.h
			 shader.h
			 vector.h
			 platform.h
			 callbacks.h
			 ext_funcs.h
			 opengl_funcs.h)

SET( FREETYPE_GL_SRC mat4.c
                     texture-atlas.c
                     texture-font.c
                     vertex-buffer.c
                     vertex-attribute.c
                     font-manager.c
                     text-buffer.c
                     shader.c
                     vector.c
                     platform.c
					 callbacks.c
					 ext_funcs.c)

ADD_LIBRARY(freetype-gl STATIC ${FREETYPE_GL_SRC} ${HEADERS})

SET(FREETYPE_GL_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")

INSTALL(TARGETS freetype-gl
		ARCHIVE DESTINATION lib
		LIBRARY DESTINATION lib)

INSTALL(FILES ${HEADERS} DESTINATION include)
