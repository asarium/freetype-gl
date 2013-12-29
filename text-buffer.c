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
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <math.h>

#include "opengl.h"
#include "text-buffer.h"
#include "callbacks.h"


#define SET_GLYPH_VERTEX(value,x0,y0,z0,s0,t0,r,g,b,a,sh,gm) { \
	glyph_vertex_t *gv=&value;                                 \
	gv->x=x0; gv->y=y0; gv->z=z0;                              \
	gv->u=s0; gv->v=t0;                                        \
	gv->r=r; gv->g=g; gv->b=b; gv->a=a;                        \
	gv->shift=sh; gv->gamma=gm;}


// ----------------------------------------------------------------------------
text_buffer_t *
text_buffer_new( size_t depth, const char* vertex_name, const char* fragment_name )
{
    
    text_buffer_t *self = (text_buffer_t *) malloc (sizeof(text_buffer_t));
    self->buffer = vertex_buffer_new(
        "vertex:3f,tex_coord:2f,color:4f,ashift:1f,agamma:1f" );
    self->manager = font_manager_new( 512, 512, depth );
	self->shader = shader_load(vertex_name, fragment_name);
    self->shader_texture = glGetUniformLocation(self->shader, "texture");
    self->shader_pixel = glGetUniformLocation(self->shader, "pixel");
    self->line_start = 0;
    self->line_ascender = 0;
    self->base_color.color1.r = 0.0;
    self->base_color.color1.g = 0.0;
    self->base_color.color1.b = 0.0;
    self->base_color.color1.a = 1.0;
    self->line_descender = 0;
    return self;
}


// ----------------------------------------------------------------------------
void
text_buffer_delete(text_buffer_t* self)
{
	assert(self != NULL);

	vertex_buffer_delete(self->buffer);
	font_manager_delete(self->manager);

	glDeleteProgram(self->shader);

	free(self);
}

// ----------------------------------------------------------------------------
void
text_buffer_clear( text_buffer_t * self )
{    
    assert( self );

    vertex_buffer_clear( self->buffer );
    self->line_start = 0;
    self->line_ascender = 0;
    self->line_descender = 0;
}

// ----------------------------------------------------------------------------
void
text_buffer_render( text_buffer_t * self )
{
    glEnable( GL_BLEND );
    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, self->manager->atlas->id );
    if( self->manager->atlas->depth == 1 )
    {
        //glDisable( GL_COLOR_MATERIAL );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        glBlendColor( 1, 1, 1, 1 );
    }
    else
    {
        //glEnable( GL_COLOR_MATERIAL );
        //glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
        //glBlendFunc( GL_ONE, GL_ONE_MINUS_SRC_ALPHA );
        //glBlendColor( 1.0, 1.0, 1.0, 1.0 );
        //glBlendFunc( GL_CONSTANT_COLOR_EXT,  GL_ONE_MINUS_SRC_COLOR );
        //glBlendColor( self->base_color.r,
        //self->base_color.g,
        //self->base_color.b,
        //self->base_color.a );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        glBlendColor( 1, 1, 1, 1 );
    }

    glUseProgram( self->shader );
    glUniform1i( self->shader_texture, 0 );
    glUniform3f( self->shader_pixel,
                 1.0f/self->manager->atlas->width,
                 1.0f/self->manager->atlas->height,
                 (float) self->manager->atlas->depth );
    vertex_buffer_render( self->buffer, GL_TRIANGLES );
    glUseProgram( 0 );
}

// ----------------------------------------------------------------------------
void
text_buffer_printf( text_buffer_t * self, vec2 *pen, ... )
{
    markup_t *markup;
    wchar_t *text;
    va_list args;

    if( vertex_buffer_size( self->buffer ) == 0 )
    {
        self->origin = *pen;
    }

    va_start ( args, pen ); 
    do {
        markup = va_arg( args, markup_t * );
        if( markup == NULL )
        {
            return;
        }
        text = va_arg( args, wchar_t * );
        text_buffer_add_text( self, pen, markup, text, wcslen(text) );
    } while( markup != 0 );
    va_end ( args );
}

// ----------------------------------------------------------------------------
void
text_buffer_move_last_line( text_buffer_t * self, float dy )
{
    size_t i, j;
    for( i=self->line_start; i < vector_size( self->buffer->items ); ++i )
    {
        ivec4 *item = (ivec4 *) vector_get( self->buffer->items, i);
		for (j = item->vert.vstart; j<(size_t)item->vert.vstart + item->vert.vcount; ++j)
        {
            glyph_vertex_t * vertex =
                (glyph_vertex_t *)  vector_get( self->buffer->vertices, j );
            vertex->y -= dy;
        }
    }
}


// ----------------------------------------------------------------------------
void
text_buffer_add_text( text_buffer_t * self,
                      vec2 * pen, markup_t * markup,
                      wchar_t * text, size_t length )
{
    font_manager_t * manager = self->manager;
    size_t i;

    if( markup == NULL )
    {
        return;
    }

    if( !markup->font )
    {
        markup->font = font_manager_get_from_markup( manager, markup );
        if( ! markup->font )
		{
			freetype_gl_get_message_callback()(MESSAGE_ERROR, "Houston, we've got a problem!");
			return;
        }
    }

    if( length == 0 )
    {
        length = wcslen(text);
    }
    if( vertex_buffer_size( self->buffer ) == 0 )
    {
        self->origin = *pen;
    }

    text_buffer_add_wchar( self, pen, markup, text[0], 0 );
    for( i=1; i<length; ++i )
    {
        text_buffer_add_wchar( self, pen, markup, text[i], text[i-1] );
    }
}

// ----------------------------------------------------------------------------
void
text_buffer_add_wchar( text_buffer_t * self,
                       vec2 * pen, markup_t * markup,
                       wchar_t current, wchar_t previous )
{
    size_t vcount = 0;
    size_t icount = 0;
    vertex_buffer_t * buffer = self->buffer;
    texture_font_t * font = markup->font;
    float gamma = markup->gamma;

    // Maximum number of vertices is 20 (= 5x2 triangles) per glyph:
    //  - 2 triangles for background
    //  - 2 triangles for overline
    //  - 2 triangles for underline
    //  - 2 triangles for strikethrough
    //  - 2 triangles for glyph
    glyph_vertex_t vertices[4*5];
    GLuint indices[6*5];
    texture_glyph_t *glyph;
    texture_glyph_t *black;
    float kerning = 0;
   
    if( current == L'\n' )
    {
		pen->coords.x = self->origin.coords.x;
		pen->coords.y += self->line_descender;
        self->line_descender = 0;
        self->line_ascender = 0;
        self->line_start = vector_size( self->buffer->items );
        return;
    }

    if( markup->font->ascender > self->line_ascender )
    {
		float y = pen->coords.y;
		pen->coords.y -= (markup->font->ascender - self->line_ascender);
		text_buffer_move_last_line(self, floorf(y - pen->coords.y));
        self->line_ascender = markup->font->ascender;
    }
    if( markup->font->descender < self->line_descender )
    {
        self->line_descender = markup->font->descender;
    }

    glyph = texture_font_get_glyph( font, current );
    black = texture_font_get_glyph( font, -1 );
        
    if( glyph == NULL )
    {
        return;
    }
    
    if( previous && markup->font->kerning )
    {
        kerning = texture_glyph_get_kerning( glyph, previous );
    }
	pen->coords.x += kerning;
        
    // Background
    if( markup->background_color.color2.alpha > 0 )
    {
		float r = markup->background_color.color1.r;
		float g = markup->background_color.color1.g;
		float b = markup->background_color.color1.b;
		float a = markup->background_color.color1.a;
		float x0 = (pen->coords.x - kerning);
		float y0 = floorf(pen->coords.y + font->descender);
        float x1 = ( x0 + glyph->advance_x );
		float y1 = floorf(y0 + font->height + font->linegap);
        float s0 = black->s0;
        float t0 = black->t0;
        float s1 = black->s1;
        float t1 = black->t1;

        SET_GLYPH_VERTEX(vertices[vcount+0],
						floorf(x0), y0, 0, s0, t0, r, g, b, a, x0 - (floorf(x0)), gamma);
        SET_GLYPH_VERTEX(vertices[vcount+1],
						floorf(x0), y1, 0, s0, t1, r, g, b, a, x0 - (floorf(x0)), gamma);
        SET_GLYPH_VERTEX(vertices[vcount+2],
						floorf(x1), y1, 0, s1, t1, r, g, b, a, x1 - (floorf(x1)), gamma);
        SET_GLYPH_VERTEX(vertices[vcount+3],
						floorf(x1), y0, 0, s1, t0, r, g, b, a, x1 - (floorf(x1)), gamma);
        indices[icount + 0] = vcount+0;
        indices[icount + 1] = vcount+1;
        indices[icount + 2] = vcount+2;
        indices[icount + 3] = vcount+0;
        indices[icount + 4] = vcount+2;
        indices[icount + 5] = vcount+3;
        vcount += 4;
        icount += 6;
    }
        
    // Underline
    if( markup->underline )
    {
        float r = markup->underline_color.color1.r;
        float g = markup->underline_color.color1.g;
        float b = markup->underline_color.color1.b;
        float a = markup->underline_color.color1.a;
		float x0 = (pen->coords.x - kerning);
		float y0 = floorf(pen->coords.y + font->underline_position);
        float x1 = ( x0 + glyph->advance_x );
		float y1 = floorf(y0 + font->underline_thickness);
        float s0 = black->s0;
        float t0 = black->t0;
        float s1 = black->s1;
        float t1 = black->t1;

        SET_GLYPH_VERTEX(vertices[vcount+0],
						floorf(x0), y0, 0, s0, t0, r, g, b, a, x0 - (floorf(x0)), gamma);
        SET_GLYPH_VERTEX(vertices[vcount+1],
						floorf(x0), y1, 0, s0, t1, r, g, b, a, x0 - (floorf(x0)), gamma);
        SET_GLYPH_VERTEX(vertices[vcount+2],
						floorf(x1), y1, 0, s1, t1, r, g, b, a, x1 - (floorf(x1)), gamma);
        SET_GLYPH_VERTEX(vertices[vcount+3],
						floorf(x1), y0, 0, s1, t0, r, g, b, a, x1 - (floorf(x1)), gamma);
        indices[icount + 0] = vcount+0;
        indices[icount + 1] = vcount+1;
        indices[icount + 2] = vcount+2;
        indices[icount + 3] = vcount+0;
        indices[icount + 4] = vcount+2;
        indices[icount + 5] = vcount+3;
        vcount += 4;
        icount += 6;
    }
    
    // Overline
    if( markup->overline )
    {
        float r = markup->overline_color.color1.r;
        float g = markup->overline_color.color1.g;
        float b = markup->overline_color.color1.b;
        float a = markup->overline_color.color1.a;
		float x0 = (pen->coords.x - kerning);
		float y0 = floorf(pen->coords.y + (int)font->ascender);
        float x1 = ( x0 + glyph->advance_x );
		float y1 = floorf(y0 + (int)font->underline_thickness);
        float s0 = black->s0;
        float t0 = black->t0;
        float s1 = black->s1;
        float t1 = black->t1;
        SET_GLYPH_VERTEX(vertices[vcount+0],
						floorf(x0), y0, 0, s0, t0, r, g, b, a, x0 - (floorf(x0)), gamma);
        SET_GLYPH_VERTEX(vertices[vcount+1],
						floorf(x0), y1, 0, s0, t1, r, g, b, a, x0 - (floorf(x0)), gamma);
        SET_GLYPH_VERTEX(vertices[vcount+2],
						floorf(x1), y1, 0, s1, t1, r, g, b, a, x1 - (floorf(x1)), gamma);
        SET_GLYPH_VERTEX(vertices[vcount+3],
						floorf(x1), y0, 0, s1, t0, r, g, b, a, x1 - (floorf(x1)), gamma);
        indices[icount + 0] = vcount+0;
        indices[icount + 1] = vcount+1;
        indices[icount + 2] = vcount+2;
        indices[icount + 3] = vcount+0;
        indices[icount + 4] = vcount+2;
        indices[icount + 5] = vcount+3;
        vcount += 4;
        icount += 6;
    }
        
    /* Strikethrough */
    if( markup->strikethrough )
    {
        float r = markup->strikethrough_color.color1.r;
        float g = markup->strikethrough_color.color1.g;
        float b = markup->strikethrough_color.color1.b;
        float a = markup->strikethrough_color.color1.a;
		float x0 = (pen->coords.x - kerning);
		float y0 = floorf(pen->coords.y + (int)font->ascender*.33f);
        float x1  = ( x0 + glyph->advance_x );
		float y1 = floorf(y0 + (int)font->underline_thickness);
        float s0 = black->s0;
        float t0 = black->t0;
        float s1 = black->s1;
        float t1 = black->t1;
        SET_GLYPH_VERTEX(vertices[vcount+0],
						floorf(x0), y0, 0, s0, t0, r, g, b, a, x0 - (floorf(x0)), gamma);
        SET_GLYPH_VERTEX(vertices[vcount+1],
						floorf(x0), y1, 0, s0, t1, r, g, b, a, x0 - (floorf(x0)), gamma);
        SET_GLYPH_VERTEX(vertices[vcount+2],
						floorf(x1), y1, 0, s1, t1, r, g, b, a, x1 - (floorf(x1)), gamma);
        SET_GLYPH_VERTEX(vertices[vcount+3],
						floorf(x1), y0, 0, s1, t0, r, g, b, a, x1 - (floorf(x1)), gamma);
        indices[icount + 0] = vcount+0;
        indices[icount + 1] = vcount+1;
        indices[icount + 2] = vcount+2;
        indices[icount + 3] = vcount+0;
        indices[icount + 4] = vcount+2;
        indices[icount + 5] = vcount+3;
        vcount += 4;
        icount += 6;
    }
    {
        // Actual glyph
        float r = markup->foreground_color.color2.red;
        float g = markup->foreground_color.color2.green;
        float b = markup->foreground_color.color2.blue;
        float a = markup->foreground_color.color2.alpha;
		float x0 = (pen->coords.x + glyph->offset_x);
		float y0 = floorf(pen->coords.y + glyph->offset_y);
        float x1 = ( x0 + glyph->width );
		float y1 = floorf(y0 - glyph->height);
        float s0 = glyph->s0;
        float t0 = glyph->t0;
        float s1 = glyph->s1;
        float t1 = glyph->t1;

        SET_GLYPH_VERTEX(vertices[vcount+0],
						floorf(x0), y0, 0, s0, t0, r, g, b, a, x0 - (floorf(x0)), gamma);
        SET_GLYPH_VERTEX(vertices[vcount+1],
						floorf(x0), y1, 0, s0, t1, r, g, b, a, x0 - (floorf(x0)), gamma);
        SET_GLYPH_VERTEX(vertices[vcount+2],
						floorf(x1), y1, 0, s1, t1, r, g, b, a, x1 - (floorf(x1)), gamma);
        SET_GLYPH_VERTEX(vertices[vcount+3],
						floorf(x1), y0, 0, s1, t0, r, g, b, a, x1 - (floorf(x1)), gamma);
        indices[icount + 0] = vcount+0;
        indices[icount + 1] = vcount+1;
        indices[icount + 2] = vcount+2;
        indices[icount + 3] = vcount+0;
        indices[icount + 4] = vcount+2;
        indices[icount + 5] = vcount+3;
        vcount += 4;
        icount += 6;
    
        vertex_buffer_push_back( buffer, vertices, vcount, indices, icount );
		pen->coords.x += glyph->advance_x * (1.0f + markup->spacing);
    }
}
