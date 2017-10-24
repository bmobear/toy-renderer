/*
	osmesa.cpp
	for offscreen rendering
*/

#include "main.h"

#ifdef OFFSCREEN_RENDER

// extern
void initOSMesaContext();
OSMesaContext ctx;

void initOSMesaContext()
{
	void *pbuffer;
	#if OSMESA_MAJOR_VERSION * 100 + OSMESA_MINOR_VERSION >= 305
	   /* specify Z, stencil, accum sizes */
	      ctx = OSMesaCreateContextExt( OSMESA_RGBA, 24, 8, 0, NULL );
	#else
	      ctx = OSMesaCreateContext( OSMESA_RGBA, NULL );
	#endif
	if (!ctx) {
	     cout << "OSMesaCreateContext failed!\n";
	     exit(1);
	}
	pbuffer = malloc( WINDOW_WIDTH * WINDOW_HEIGHT * 4 * sizeof(GLuint) );
	if (!pbuffer) {
	      cout << "Alloc image buffer failed!\n";
	      exit(1);
	}
	/* Bind the buffer to the context and make it current */
	if (!OSMesaMakeCurrent( ctx, pbuffer, GL_UNSIGNED_BYTE, WINDOW_WIDTH, WINDOW_HEIGHT )) {
	      cout << "OSMesaMakeCurrent failed!\n";
	      exit(1);
	}

}

#endif