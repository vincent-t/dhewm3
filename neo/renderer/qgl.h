/*
===========================================================================

Doom 3 GPL Source Code
Copyright (C) 1999-2011 id Software LLC, a ZeniMax Media company.

This file is part of the Doom 3 GPL Source Code ("Doom 3 Source Code").

Doom 3 Source Code is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Doom 3 Source Code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Doom 3 Source Code.  If not, see <http://www.gnu.org/licenses/>.

In addition, the Doom 3 Source Code is also subject to certain additional terms. You should have received a copy of these additional terms immediately following the terms and conditions of the GNU General Public License which accompanied the Doom 3 Source Code.  If not, please request a copy in writing from id Software at the address below.

If you have questions concerning this license or the applicable additional terms, you may contact in writing id Software LLC, c/o ZeniMax Media Inc., Suite 120, Rockville, Maryland 20850 USA.

===========================================================================
*/
/*
** QGL.H
*/

#ifndef __QGL_H__
#define __QGL_H__

#if defined( ID_DEDICATED ) && defined( _WIN32 )
// to allow stubbing gl on windows, define WINGDIAPI to nothing - it would otherwise be
// extended to __declspec(dllimport) on MSVC (our stub is no dll.)
	#ifdef WINGDIAPI
		#pragma push_macro("WINGDIAPI")
		#undef WINGDIAPI
		#define WINGDIAPI
	#endif
#endif

#include <SDL_opengl.h>

#if defined( ID_DEDICATED ) && defined( _WIN32 )
// restore WINGDIAPI
	#ifdef WINGDIAPI
		#pragma pop_macro("WINGDIAPI")
	#endif
#endif

typedef void (*GLExtension_t)(void);

#ifdef __cplusplus
	extern "C" {
#endif

GLExtension_t GLimp_ExtensionPointer( const char *name );

#ifdef __cplusplus
	}
#endif

// declare qgl functions
#define QGLPROC(name, rettype, args) extern rettype (APIENTRYP q##name) args;
#include "renderer/qgl_proc.h"

// multitexture
extern	void ( APIENTRY * qglMultiTexCoord2fARB )( GLenum texture, GLfloat s, GLfloat t );
extern	void ( APIENTRY * qglMultiTexCoord2fvARB )( GLenum texture, GLfloat *st );
extern	void ( APIENTRY * qglActiveTextureARB )( GLenum texture );
extern	void ( APIENTRY * qglClientActiveTextureARB )( GLenum texture );

// ARB_MapBufferRange
extern PFNGLMAPBUFFERRANGEPROC qglMapBufferRange;
extern PFNGLFLUSHMAPPEDBUFFERRANGEPROC qglFlushMappedBufferRange;

// ARB_vertex_buffer_object
extern PFNGLBINDBUFFERARBPROC qglBindBufferARB;
extern PFNGLDELETEBUFFERSARBPROC qglDeleteBuffersARB;
extern PFNGLGENBUFFERSARBPROC qglGenBuffersARB;
extern PFNGLISBUFFERARBPROC qglIsBufferARB;
extern PFNGLBUFFERDATAARBPROC qglBufferDataARB;
extern PFNGLBUFFERSUBDATAARBPROC qglBufferSubDataARB;
extern PFNGLGETBUFFERSUBDATAARBPROC qglGetBufferSubDataARB;
extern PFNGLMAPBUFFERARBPROC qglMapBufferARB;
extern PFNGLUNMAPBUFFERARBPROC qglUnmapBufferARB;
extern PFNGLGETBUFFERPARAMETERIVARBPROC qglGetBufferParameterivARB;
extern PFNGLGETBUFFERPOINTERVARBPROC qglGetBufferPointervARB;


// ARB_separate_stencil
extern	void ( APIENTRY *qglStencilOpSeparate )( GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass );
extern	void ( APIENTRY *qglStencilFuncSeparate ) ( GLenum face, GLenum func, GLint ref, GLuint mask );

// ARB_texture_compression
extern	PFNGLCOMPRESSEDTEXIMAGE2DARBPROC	qglCompressedTexImage2DARB;
extern	PFNGLGETCOMPRESSEDTEXIMAGEARBPROC	qglGetCompressedTexImageARB;

// ARB_vertex_program
extern PFNGLVERTEXATTRIBPOINTERARBPROC		qglVertexAttribPointerARB;
extern PFNGLENABLEVERTEXATTRIBARRAYARBPROC	qglEnableVertexAttribArrayARB;
extern PFNGLDISABLEVERTEXATTRIBARRAYARBPROC	qglDisableVertexAttribArrayARB;
extern GLint (APIENTRY *qglGetAttribLocation)(GLuint programObj, const GLchar *name);
extern void (APIENTRY *qglBindAttribLocation)(GLuint programObj, GLuint index, const GLchar *name);
extern void (APIENTRY *qglBindFragDataLocation)(GLuint programObj, GLuint index, const GLchar *name);

// GL_EXT_depth_bounds_test
extern PFNGLDEPTHBOUNDSEXTPROC              qglDepthBoundsEXT;

// GL_ARB_shading_language_100
extern void (APIENTRY *qglDeleteShader)(GLuint obj);
extern void (APIENTRY *qglDeleteProgram)(GLuint obj);
extern void (APIENTRY *qglDetachShader)(GLuint containerObj, GLuint attachedObj);
extern GLuint (APIENTRY *qglCreateShader)(GLenum shaderType);
extern void (APIENTRY *qglShaderSource)(GLuint shaderObj, GLsizei count, const GLchar **string, const GLint *length);
extern void (APIENTRY *qglCompileShader)(GLuint shaderObj);
extern GLuint (APIENTRY *qglCreateProgram)(void);
extern void (APIENTRY *qglAttachShader)(GLuint containerObj, GLuint obj);
extern void (APIENTRY *qglLinkProgram)(GLuint programObj);
extern void (APIENTRY *qglUseProgram)(GLuint programObj);
extern void (APIENTRY *qglValidateProgram)(GLuint programObj);
extern void (APIENTRY *qglUniform1f)(GLint location, GLfloat v0);
extern void (APIENTRY *qglUniform2f)(GLint location, GLfloat v0, GLfloat v1);
extern void (APIENTRY *qglUniform3f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
extern void (APIENTRY *qglUniform4f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
extern void (APIENTRY *qglUniform1i)(GLint location, GLint v0);
extern void (APIENTRY *qglUniform2i)(GLint location, GLint v0, GLint v1);
extern void (APIENTRY *qglUniform3i)(GLint location, GLint v0, GLint v1, GLint v2);
extern void (APIENTRY *qglUniform4i)(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
extern void (APIENTRY *qglUniform1fv)(GLint location, GLsizei count, const GLfloat *value);
extern void (APIENTRY *qglUniform2fv)(GLint location, GLsizei count, const GLfloat *value);
extern void (APIENTRY *qglUniform3fv)(GLint location, GLsizei count, const GLfloat *value);
extern void (APIENTRY *qglUniform4fv)(GLint location, GLsizei count, const GLfloat *value);
extern void (APIENTRY *qglUniform1iv)(GLint location, GLsizei count, const GLint *value);
extern void (APIENTRY *qglUniform2iv)(GLint location, GLsizei count, const GLint *value);
extern void (APIENTRY *qglUniform3iv)(GLint location, GLsizei count, const GLint *value);
extern void (APIENTRY *qglUniform4iv)(GLint location, GLsizei count, const GLint *value);
extern void (APIENTRY *qglUniformMatrix2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
extern void (APIENTRY *qglUniformMatrix3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
extern void (APIENTRY *qglUniformMatrix4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
extern void (APIENTRY *qglGetShaderiv)(GLuint obj, GLenum pname, GLint *params);
extern void (APIENTRY *qglGetProgramiv)(GLuint obj, GLenum pname, GLint *params);
extern void (APIENTRY *qglGetShaderInfoLog)(GLuint obj, GLsizei maxLength, GLsizei *length, GLchar *infoLog);
extern void (APIENTRY *qglGetProgramInfoLog)(GLuint obj, GLsizei maxLength, GLsizei *length, GLchar *infoLog);
extern void (APIENTRY *qglGetAttachedShaders)(GLuint containerObj, GLsizei maxCount, GLsizei *count, GLuint *obj);
extern GLint (APIENTRY *qglGetUniformLocation)(GLuint programObj, const GLchar *name);
extern void (APIENTRY *qglGetActiveUniform)(GLuint programObj, GLuint index, GLsizei maxLength, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
extern void (APIENTRY *qglGetUniformfv)(GLuint programObj, GLint location, GLfloat *params);
extern void (APIENTRY *qglGetUniformiv)(GLuint programObj, GLint location, GLint *params);
extern void (APIENTRY *qglGetShaderSource)(GLuint obj, GLsizei maxLength, GLsizei *length, GLchar *source);
#endif
