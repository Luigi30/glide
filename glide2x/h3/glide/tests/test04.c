/*
** Copyright (c) 1997, 3Dfx Interactive, Inc.
** All Rights Reserved.
**
** This is UNPUBLISHED PROPRIETARY SOURCE CODE of 3Dfx Interactive, Inc.;
** the contents of this file may not be disclosed to third parties, copied or
** duplicated in any form, in whole or in part, without the prior written
** permission of 3Dfx Interactive, Inc.
**
** RESTRICTED RIGHTS LEGEND:
** Use, duplication or disclosure by the Government is subject to restrictions
** as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
** and Computer Software clause at DFARS 252.227-7013, and/or in similar or
** successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
** rights reserved under the Copyright Laws of the United States.
**
*/

#include <stdlib.h>
#include <stdio.h>
#ifndef __linux__
#include <conio.h>
#endif
#include <assert.h>
#include <string.h>

#include <glide.h>
#include "tlib.h"


GrHwConfiguration hwconfig;
static char version[80];

static const char name[]    = "test04";
static const char purpose[] = "draws gouraud shaded triangle";
static const char usage[]   = "-n <frames> -r <res> -d <filename>";

int main( int argc, char **argv) {
    char match; 
    char **remArgs;
    int  rv;

    GrScreenResolution_t resolution = GR_RESOLUTION_640x480;
    float                scrWidth   = 640.0f;
    float                scrHeight  = 480.0f;
    int frames                      = -1;
    FxBool               scrgrab = FXFALSE;
    char                 filename[256];

    /* Process Command Line Arguments */
    while( (rv = tlGetOpt( argc, argv, "nrd", &match, &remArgs )) ) {
        if ( rv == -1 ) {
            printf( "Unrecognized command line argument\n" );
            printf( "%s %s\n", name, usage );
            printf( "Available resolutions:\n%s\n",
                    tlGetResolutionList() );
	    exit(1);
        }
        switch( match ) {
        case 'n':
            frames = atoi( remArgs[0] );
            break;
        case 'r':
            resolution = tlGetResolutionConstant( remArgs[0], 
                                                  &scrWidth, 
                                                  &scrHeight );
            break;
        case 'd':
            scrgrab = FXTRUE;
            frames = 1;
            strcpy(filename, remArgs[0]);
            break;
        }
    }

    tlSetScreen( scrWidth, scrHeight );

    grGlideGetVersion( version );

    printf( "%s:\n%s\n", name, purpose );
    printf( "%s\n", version );
    printf( "Resolution: %s\n", tlGetResolutionString( resolution ) );
    if ( frames == -1 ) {
        printf( "Press A Key To Begin Test.\n" );
        tlGetCH();
    }
    
    /* Initialize Glide */
    grGlideInit();
    assert( grSstQueryHardware( &hwconfig ) );
    grSstSelect( 0 );
    assert( grSstWinOpen( 0,
                      resolution,
                      GR_REFRESH_60Hz,
                      GR_COLORFORMAT_ABGR,
                      GR_ORIGIN_UPPER_LEFT,
                      2, 1 ) );
    
    tlConSet( 0.0f, 0.0f, 1.0f, 1.0f, 
              60, 30, 0xffffff );

    /* Set up Render State - gouraud shading */
    grColorCombine( GR_COMBINE_FUNCTION_LOCAL,
                    GR_COMBINE_FACTOR_NONE,
                    GR_COMBINE_LOCAL_ITERATED,
                    GR_COMBINE_OTHER_NONE,
                    FXFALSE );
    
    tlConOutput( "Press a key to quit\n" );
    while( frames-- && tlOkToRender()) {
        GrVertex vtxA, vtxB, vtxC;

        if (hwconfig.SSTs[0].type == GR_SSTTYPE_SST96) {
          tlGetDimsByConst(resolution,
                           &scrWidth, 
                           &scrHeight );
        
          grClipWindow(0, 0, (FxU32) scrWidth, (FxU32) scrHeight);
        }

        grBufferClear( 0x00, 0, GR_WDEPTHVALUE_FARTHEST );

        vtxA.x = tlScaleX( 0.3f ), vtxA.y = tlScaleY( 0.3f );
        vtxA.r = 255.0f, vtxA.g = 0.0f, vtxA.b = 0.0f;

        vtxB.x = tlScaleX( 0.8f ), vtxB.y = tlScaleY( 0.4f );
        vtxB.r = 0.0f, vtxB.g = 255.0f, vtxB.b = 0.0f;

        vtxC.x = tlScaleX( 0.5f ), vtxC.y = tlScaleY( 0.8f );
        vtxC.r = 0.0f, vtxC.g = 0.0f, vtxC.b = 255.0f;

        grDrawTriangle( &vtxA, &vtxB, &vtxC );

        tlConRender();
        grBufferSwap( 1 );

        /* grab the frame buffer */
        if (scrgrab) {
          if (!tlScreenDump(filename, (FxU16)scrWidth, (FxU16)scrHeight))
            printf( "Cannot open %s\n", filename);
          scrgrab = FXFALSE;
        }

        if ( tlKbHit() ) frames = 0;
    }
    
    grGlideShutdown();
    exit(0);
}





