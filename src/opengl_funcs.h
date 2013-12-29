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

#ifndef __OPENGL_FUNCS_H__
#define __OPENGL_FUNCS_H__

#ifndef USE_GLEW

#include "opengl.h"

#ifdef __cplusplus
extern "C" {
#endif

extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;
extern PFNGLGENBUFFERSPROC glGenBuffers;
extern PFNGLBINDBUFFERPROC glBindBuffer;
extern PFNGLBUFFERDATAPROC glBufferData;
extern PFNGLBUFFERSUBDATAPROC glBufferSubData;
	
extern PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
	
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
extern PFNGLBLENDCOLORPROC glBlendColor;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLUNIFORM1FPROC glUniform1i;
extern PFNGLUNIFORM3FPROC glUniform3f;
	
extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
extern PFNGLDELETESHADERPROC glDeleteShader;
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
extern PFNGLDELETEPROGRAMPROC glDeleteProgram;

#ifdef __cplusplus
}
#endif // ifdef __cplusplus

#endif // USE_GLEW

#endif // __OPENGL_FUNCS_H__
