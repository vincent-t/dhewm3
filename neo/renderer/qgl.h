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

// 3D textures
extern void ( APIENTRY *qglTexImage3D)(GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, const GLvoid *);

// shared texture palette
extern	void ( APIENTRY *qglColorTableEXT)( int, int, int, int, int, const void * );

// EXT_stencil_two_side
//extern	PFNGLACTIVESTENCILFACEEXTPROC	qglActiveStencilFaceEXT;
// ARB_separate_stencil
extern	void ( APIENTRY *qglStencilOpSeparate )( GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass );
extern	void ( APIENTRY *qglStencilFuncSeparate ) ( GLenum face, GLenum func, GLint ref, GLuint mask );

// ARB_texture_compression
extern	PFNGLCOMPRESSEDTEXIMAGE2DARBPROC	qglCompressedTexImage2DARB;
extern	PFNGLGETCOMPRESSEDTEXIMAGEARBPROC	qglGetCompressedTexImageARB;

// ARB_vertex_program / ARB_fragment_program
extern PFNGLVERTEXATTRIBPOINTERARBPROC		qglVertexAttribPointerARB;
extern PFNGLENABLEVERTEXATTRIBARRAYARBPROC	qglEnableVertexAttribArrayARB;
extern PFNGLDISABLEVERTEXATTRIBARRAYARBPROC	qglDisableVertexAttribArrayARB;
extern PFNGLPROGRAMSTRINGARBPROC			qglProgramStringARB;
extern PFNGLBINDPROGRAMARBPROC				qglBindProgramARB;
extern PFNGLGENPROGRAMSARBPROC				qglGenProgramsARB;
extern PFNGLPROGRAMENVPARAMETER4FVARBPROC	qglProgramEnvParameter4fvARB;
extern PFNGLPROGRAMLOCALPARAMETER4FVARBPROC	qglProgramLocalParameter4fvARB;

// GL_EXT_depth_bounds_test
extern PFNGLDEPTHBOUNDSEXTPROC              qglDepthBoundsEXT;

// GL_ARB_shading_language_100
extern void ( APIENTRY * qglDeleteObjectARB )( GLhandleARB obj );
extern GLhandleARB ( APIENTRY * qglGetHandleARB )( GLenum pname );
extern void ( APIENTRY * qglDetachObjectARB )( GLhandleARB containerObj, GLhandleARB attachedObj );
extern GLhandleARB ( APIENTRY * qglCreateShaderObjectARB )( GLenum shaderType );
extern void ( APIENTRY * qglShaderSourceARB )( GLhandleARB shaderObj, GLsizei count, const GLcharARB* *string, const GLint *length ); extern void ( APIENTRY * qglCompileShaderARB )( GLhandleARB shaderObj );
extern GLhandleARB ( APIENTRY * qglCreateProgramObjectARB )( void );
extern void ( APIENTRY * qglAttachObjectARB )( GLhandleARB containerObj, GLhandleARB obj );
extern void ( APIENTRY * qglLinkProgramARB )( GLhandleARB programObj );
extern void ( APIENTRY * qglUseProgramObjectARB )( GLhandleARB programObj );
extern void ( APIENTRY * qglValidateProgramARB )( GLhandleARB programObj );
extern void ( APIENTRY * qglUniform1fARB )( GLint location, GLfloat v0 );
extern void ( APIENTRY * qglUniform2fARB )( GLint location, GLfloat v0, GLfloat v1 );
extern void ( APIENTRY * qglUniform3fARB )( GLint location, GLfloat v0, GLfloat v1, GLfloat v2 );
extern void ( APIENTRY * qglUniform4fARB )( GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3 );
extern void ( APIENTRY * qglUniform1iARB )( GLint location, GLint v0 );
extern void ( APIENTRY * qglUniform2iARB )( GLint location, GLint v0, GLint v1 );
extern void ( APIENTRY * qglUniform3iARB )( GLint location, GLint v0, GLint v1, GLint v2 );
extern void ( APIENTRY * qglUniform4iARB )( GLint location, GLint v0, GLint v1, GLint v2, GLint v3 );
extern void ( APIENTRY * qglUniform2fvARB )( GLint location, GLsizei count, const GLfloat *value );
extern void ( APIENTRY * qglUniform3fvARB )( GLint location, GLsizei count, const GLfloat *value );
extern void ( APIENTRY * qglUniform4fvARB )( GLint location, GLsizei count, const GLfloat *value );
extern void ( APIENTRY * qglUniform2ivARB )( GLint location, GLsizei count, const GLint *value );
extern void ( APIENTRY * qglUniform3ivARB )( GLint location, GLsizei count, const GLint *value );
extern void ( APIENTRY * qglUniform4ivARB )( GLint location, GLsizei count, const GLint *value );
extern void ( APIENTRY * qglUniformMatrix2fvARB )( GLint location, GLsizei count, GLboolean transpose, const GLfloat *value );
extern void ( APIENTRY * qglUniformMatrix3fvARB )( GLint location, GLsizei count, GLboolean transpose, const GLfloat *value );
extern void ( APIENTRY * qglUniformMatrix4fvARB )( GLint location, GLsizei count, GLboolean transpose, const GLfloat *value );
extern void ( APIENTRY * qglGetObjectParameterfvARB )( GLhandleARB obj, GLenum pname, GLfloat *params );
extern void ( APIENTRY * qglGetObjectParameterivARB )( GLhandleARB obj, GLenum pname, GLint *params );
extern void ( APIENTRY * qglGetInfoLogARB )( GLhandleARB obj, GLsizei maxLength, GLsizei *length, GLcharARB *infoLog );
extern void ( APIENTRY * qglGetAttachedObjectsARB )( GLhandleARB containerObj, GLsizei maxCount, GLsizei *count, GLhandleARB *obj );
extern GLint ( APIENTRY * qglGetUniformLocationARB )( GLhandleARB programObj, const GLcharARB *name );
extern void ( APIENTRY * qglGetActiveUniformARB )( GLhandleARB programObj, GLuint index, GLsizei maxIndex, GLsizei *length, GLint *size, GLenum *type, GLcharARB *name );
extern void ( APIENTRY * qglGetUniformfvARB )( GLhandleARB programObj, GLint location, GLfloat *params );
extern void ( APIENTRY * qglGetUniformivARB )( GLhandleARB programObj, GLint location, GLint *params );
extern void ( APIENTRY * qglGetShaderSourceARB )( GLhandleARB obj, GLsizei maxLength, GLsizei *length, GLcharARB *source );
extern void ( APIENTRY * qglBindAttribLocationARB )( GLhandleARB programObj, GLuint index, const GLcharARB *name );
extern void ( APIENTRY * qglGetActiveAttribARB )( GLhandleARB programObj, GLuint index, GLsizei maxLength, GLsizei *length, GLint *size, GLenum *type, GLcharARB *name );
extern GLint ( APIENTRY * qglGetAttribLocationARB )( GLhandleARB programObj, const GLcharARB *name );
extern void ( APIENTRY * qglGetShaderiv )(GLuint shader, GLenum pname, GLint* param);
extern void ( APIENTRY * qglDeleteShader )(GLuint shader);
extern void ( APIENTRY * qglGetShaderInfoLog )(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog);

#endif
