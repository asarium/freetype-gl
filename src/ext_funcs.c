/* ============================================================================
* Freetype GL - A C OpenGL Freetype engine
* Platform:    Any
* WWW:         http://code.google.com/p/freetype-gl/
* ----------------------------------------------------------------------------
* Copyright 2011,2012 Nicolas P. Rougier. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
*  1. Redistributions of source code must retain the above copyright notice,
*     this list of conditions and the following disclaimer.
*
*  2. Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in the
*     documentation and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY NICOLAS P. ROUGIER ''AS IS'' AND ANY EXPRESS OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
* EVENT SHALL NICOLAS P. ROUGIER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
* THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* The views and conclusions contained in the software and documentation are
* those of the authors and should not be interpreted as representing official
* policies, either expressed or implied, of Nicolas P. Rougier.
* ============================================================================
*/

#ifndef USE_GLEW

#include "opengl.h"
#include "ext_funcs.h"

PFNGLDELETEBUFFERSPROC glDeleteBuffers = NULL;
PFNGLGENBUFFERSPROC glGenBuffers = NULL;
PFNGLBINDBUFFERPROC glBindBuffer = NULL;
PFNGLBUFFERDATAPROC glBufferData = NULL;
PFNGLBUFFERSUBDATAPROC glBufferSubData = NULL;

PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = NULL;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = NULL;

PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = NULL;
PFNGLBLENDCOLORPROC glBlendColor = NULL;
PFNGLUSEPROGRAMPROC glUseProgram = NULL;
PFNGLUNIFORM1FPROC glUniform1i = NULL;
PFNGLUNIFORM3FPROC glUniform3f = NULL;

PFNGLCREATESHADERPROC glCreateShader = NULL;
PFNGLSHADERSOURCEPROC glShaderSource = NULL;
PFNGLCOMPILESHADERPROC glCompileShader = NULL;
PFNGLGETSHADERIVPROC glGetShaderiv = NULL;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = NULL;
PFNGLDELETESHADERPROC glDeleteShader = NULL;
PFNGLCREATEPROGRAMPROC glCreateProgram = NULL;
PFNGLATTACHSHADERPROC glAttachShader = NULL;
PFNGLLINKPROGRAMPROC glLinkProgram = NULL;
PFNGLGETPROGRAMIVPROC glGetProgramiv = NULL;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = NULL;
PFNGLDELETEPROGRAMPROC glDeleteProgram = NULL;

#define FUNCTION_CASE(upper, lower) case FUNC_GL_##upper: \
										(lower) = (PFNGL##upper##PROC) function_ptr; \
										break

void ftgl_init_gl_func(opengl_func_t func, void* function_ptr)
{
	switch (func)
	{
		FUNCTION_CASE(DELETEBUFFERS, glDeleteBuffers);
		FUNCTION_CASE(GENBUFFERS, glGenBuffers);
		FUNCTION_CASE(BINDBUFFER, glBindBuffer);
		FUNCTION_CASE(BUFFERDATA, glBufferData);
		FUNCTION_CASE(BUFFERSUBDATA, glBufferSubData);

		FUNCTION_CASE(GETATTRIBLOCATION, glGetAttribLocation);
		FUNCTION_CASE(ENABLEVERTEXATTRIBARRAY, glEnableVertexAttribArray);
		FUNCTION_CASE(VERTEXATTRIBPOINTER, glVertexAttribPointer);

		FUNCTION_CASE(GETUNIFORMLOCATION, glGetUniformLocation);
		FUNCTION_CASE(BLENDCOLOR, glBlendColor);
		FUNCTION_CASE(USEPROGRAM, glUseProgram);
		FUNCTION_CASE(UNIFORM1F, glUniform1i);
		FUNCTION_CASE(UNIFORM3F, glUniform3f);

		FUNCTION_CASE(CREATESHADER, glCreateShader);
		FUNCTION_CASE(SHADERSOURCE, glShaderSource);
		FUNCTION_CASE(COMPILESHADER, glCompileShader);
		FUNCTION_CASE(GETSHADERIV, glGetShaderiv);
		FUNCTION_CASE(GETSHADERINFOLOG, glGetShaderInfoLog);
		FUNCTION_CASE(DELETESHADER, glDeleteShader);
		FUNCTION_CASE(CREATEPROGRAM, glCreateProgram);
		FUNCTION_CASE(ATTACHSHADER, glAttachShader);
		FUNCTION_CASE(LINKPROGRAM, glLinkProgram);
		FUNCTION_CASE(GETPROGRAMIV, glGetProgramiv);
		FUNCTION_CASE(GETPROGRAMINFOLOG, glGetProgramInfoLog);
		FUNCTION_CASE(DELETEPROGRAM, glDeleteProgram);
	}
}

#endif
