/*******************************************************************************
 * Copyright (c) 2010, Jean-David Gadina - www.xs-labs.com
 * Distributed under the Boost Software License, Version 1.0.
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ******************************************************************************/

/* $Id$ */

/*!
 * @file        md5.c
 * @copyright   (c) 2011 - Jean-David Gadina - www.xs-labs.com
 * @abstract    MD5 functions
 */

/* Local includes */
#include "egpack.h"

/*!
 * @function    egpack_file_md5_checksum
 * @abstract    Gets a MD5 checksum of a file pointer
 * @param       fp      The file pointer
 * @param       hash    Character buffer (32 bytes minimum)
 * @result      void
 */
void egpack_file_md5_checksum( FILE * fp, char * hash )
{
    MD5_CTX             ctx;
    size_t              length;
    long                offset;
    unsigned int        i;
    unsigned long       size;
    unsigned char       digest[ MD5_DIGEST_LENGTH ];
    char                tmp[ EGPACK_BUFFER_LENGTH ];
    char                hex[ 3 ] = { 0, 0, 0 };
    
    /* Ensures the buffer is clear */
    memset( hash, 0, MD5_DIGEST_LENGTH * 2 + 1 );
    
    /* File size and current offset */
    size      = fsize( fp );
    offset    = ftell( fp );
    
    /* Seeks to the beginning of the file */
    fseek( fp, 0, SEEK_SET );
    
    /* MD5 initialization */
    MD5_Init( &ctx );
    
    /* Reads the file's data */
    while( ( length = fread( tmp, sizeof( char ), EGPACK_BUFFER_LENGTH, fp ) ) )
    {
        /* Updates the MD5 data */
        MD5_Update( &ctx, tmp, length );
    }
    
    /* MD5 end */
    MD5_Final( digest, &ctx );
    
    /* Process each byte of the MD5 digest */
    for( i = 0; i < MD5_DIGEST_LENGTH; i++ )
    {
        /* Human readable MD5 (hexadecimal) */
        sprintf( hex, "%02x", digest[ i ] );
        strcat( hash, hex );
    }
    
    /* Seeks to the original position */
    fseek( fp, offset, SEEK_SET );
}
