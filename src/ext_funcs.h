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

#ifndef __EXT_FUNCS_H__
#define __EXT_FUNCS_H__

#ifndef USE_GLEW

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	FUNC_GL_DELETEBUFFERS,
	FUNC_GL_GENBUFFERS,
	FUNC_GL_BINDBUFFER,
	FUNC_GL_BUFFERDATA,
	FUNC_GL_BUFFERSUBDATA,

	FUNC_GL_GETATTRIBLOCATION,
	FUNC_GL_ENABLEVERTEXATTRIBARRAY,
	FUNC_GL_VERTEXATTRIBPOINTER,

	FUNC_GL_GETUNIFORMLOCATION,
	FUNC_GL_BLENDCOLOR,
	FUNC_GL_USEPROGRAM,
	FUNC_GL_UNIFORM1F,
	FUNC_GL_UNIFORM3F,

	FUNC_GL_CREATESHADER,
	FUNC_GL_SHADERSOURCE,
	FUNC_GL_COMPILESHADER,
	FUNC_GL_GETSHADERIV,
	FUNC_GL_GETSHADERINFOLOG,
	FUNC_GL_DELETESHADER,
	FUNC_GL_CREATEPROGRAM,
	FUNC_GL_ATTACHSHADER,
	FUNC_GL_LINKPROGRAM,
	FUNC_GL_GETPROGRAMIV,
	FUNC_GL_GETPROGRAMINFOLOG,
	FUNC_GL_DELETEPROGRAM,
} opengl_func_t;

void freetype_gl_init_gl_func(opengl_func_t func, void* function_ptr);

#ifdef __cplusplus
}
#endif // ifdef __cplusplus

#endif // USE_GLEW

#endif // __EXT_FUNCS_H__
