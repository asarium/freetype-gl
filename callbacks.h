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

#ifndef __CALLBACKS_H__
#define __CALLBACKS_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	MESSAGE_INFO,
	MESSAGE_WARNING,
	MESSAGE_ERROR
} message_type_t;

typedef (*message_callback_t)(message_type_t type, const char* message);

void freetype_gl_set_message_callback(message_callback_t callback);

message_callback_t freetype_gl_get_message_callback();


typedef int(*filesystem_callback_t)(const char* filename, void* data, size_t* size);

void freetype_gl_set_filesystem_callback(filesystem_callback_t callback);

filesystem_callback_t freetype_gl_get_filesystem_callback();

#ifdef __cplusplus
}
#endif // ifdef __cplusplus

#endif // __CALLBACKS_H__
