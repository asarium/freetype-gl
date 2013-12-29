
MACRO(DEMO _target _sources)
     add_executable(${_target} ${_sources})
     include_directories(${WINDOWS_DIR} ${GLUT_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIR_ft2build}
						${FREETYPE_INCLUDE_DIR_freetype2} ${ANT_TWEAK_BAR_INCLUDE_PATH} ${FREETYPE_GL_INCLUDE_DIRS})
     target_link_libraries(${_target} ${OPENGL_LIBRARY})
     target_link_libraries(${_target} ${GLEW_LIBRARY})
     target_link_libraries(${_target} freetype-gl)
     target_link_libraries(${_target} ${GLUT_LIBRARY})
     target_link_libraries(${_target} ${GLEW_LIBRARY})
     target_link_libraries(${_target} ${FREETYPE_LIBRARY})
	ADD_DEFINITIONS(-DUSE_GLEW)
     IF( MATH_LIBRARY )
         target_link_libraries(${_target} ${MATH_LIBRARY})
     ENDIF( MATH_LIBRARY )
    if(MSVC)
      # Compile demos as C++
      set_source_files_properties(${_sources} PROPERTIES LANGUAGE CXX)
    endif()

	IF(WIN32)
		ADD_CUSTOM_COMMAND(
			TARGET ${_target} POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different "${GLEW_DLL}"  "$<TARGET_FILE_DIR:${_target}>"
			COMMENT "copying glew dlls ..."
		)
		ADD_CUSTOM_COMMAND(
			TARGET ${_target} POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different "${GLUT_DLL}"  "$<TARGET_FILE_DIR:${_target}>"
			COMMENT "copying glut dlls ..."
		)
	ENDIF(WIN32)
ENDMACRO( DEMO )

IF(MSVC)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:LIBCMT")
ENDIF(MSVC)

DEMO( demo-texture          "demo-texture.c" )
DEMO( demo-font             "demo-font.c" )
DEMO( demo-benchmark        "demo-benchmark.c" )
DEMO( demo-console          "demo-console.c" )
DEMO( demo-cube             "demo-cube.c" )
DEMO( demo-glyph            "demo-glyph.c" )
DEMO( demo-cartoon          "demo-cartoon.c" )
DEMO( demo-outline          "demo-outline.c" )
DEMO( demo-lcd              "demo-lcd.c" )
DEMO( demo-gamma            "demo-gamma.c" )
DEMO( demo-ansi             "demo-ansi.c" )
DEMO( demo-subpixel         "demo-subpixel.c" )
DEMO( demo-make             "demo-makefont.c" )
DEMO( makefont              "makefont.c" )
DEMO( demo-distance-field   "demo-distance-field.c;edtaa3func.c")
DEMO( demo-distance-field-2 "demo-distance-field-2.c;edtaa3func.c")
DEMO( demo-distance-field-3 "demo-distance-field-3.c;edtaa3func.c")

IF (FONTCONFIG_FOUND)
   INCLUDE_DIRECTORIES( ${FONTCONFIG_INCLUDE_DIR} )
   DEMO( demo-markup      "demo-markup.c" )
   target_link_libraries(demo-markup ${FONTCONFIG_LIBRARY})
ENDIF (FONTCONFIG_FOUND)

IF (ANT_TWEAK_BAR_FOUND AND (NOT (WIN32 OR WIN64)) )  
 #DEMO( demo-atb-agg     "demo-atb-agg.c;markup.h;")
 FILE(WRITE ${CMAKE_SOURCE_DIR}/stdc_test.c
  "int main(void){return 0;}\n")
  EXECUTE_PROCESS(COMMAND ${CMAKE_C_COMPILER} -lstdc++ OUTPUT_VARIABLE out_res ERROR_VARIABLE err_res)
  string(FIND VAL"${err_res}" "main" substr_index ) 
  if(${substr_index} STRGREATER "0")
      message (STATUS "Found Libstdc++ needed by demo-atb-agg.c ." )

      add_executable(demo-atb-agg  demo-atb-agg.c) 
      target_link_libraries( demo-atb-agg freetype-gl)
      target_link_libraries( demo-atb-agg ${GLUT_LIBRARY})
      target_link_libraries( demo-atb-agg ${GLEW_LIBRARY})
      target_link_libraries( demo-atb-agg ${FREETYPE_LIBRARY})
      target_link_libraries( demo-atb-agg ${ANT_TWEAK_BAR_LIBRARY})
      # target_link_libraries( demo-atb-agg ${STDC_LIBRARY}) # Buggy Cmake can't find libstdc++
      # quirk: because of link order libstdc++ must be linked before libGLU
      target_link_libraries( demo-atb-agg "-lstdc++")
      target_link_libraries( demo-atb-agg ${OPENGL_LIBRARY})
      IF(MATH_LIBRARY)
        target_link_libraries( demo-atb-agg ${MATH_LIBRARY})
      ENDIF(MATH_LIBRARY) 
  else()
      message (STATUS "NOT FOUND: Libstdc++ is not installed. It is needed by demo-atb-agg.c" )
  endif()
  FILE(REMOVE ${CMAKE_SOURCE_DIR}/stdc_test.c)
ENDIF (ANT_TWEAK_BAR_FOUND AND (NOT (WIN32 OR WIN64)) )  

# Copy font and shaders into build directory for in-place testing
FILE(GLOB Fonts   "fonts/Vera.ttf"
                  "fonts/VeraMoBI.ttf"
                  "fonts/VeraMoBd.ttf"
                  "fonts/VeraMoIt.ttf"
                  "fonts/VeraMono.ttf"
                  "fonts/ObelixPro.ttf")
file(COPY ${Fonts}   DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/fonts)

FILE(GLOB Data   "data/256colors.txt")
file(COPY ${Data}   DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data)

FILE(GLOB Shaders "shaders/*.vert" "shaders/*.frag")
file(COPY ${Shaders} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shaders)
