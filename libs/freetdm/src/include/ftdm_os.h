/*
 * Copyright (c) 2010, Sangoma Technologies
 * Moises Silva <moy@sangoma.com>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * * Neither the name of the original author; nor the names of any contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 * 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __FTDM_OS_H__
#define __FTDM_OS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ftdm_declare.h"
#include "ftdm_threadmutex.h"

#include <string.h>

#ifndef __WINDOWS__
#include <unistd.h>
#endif

/*! \brief sleep x amount of milliseconds */
#ifdef __WINDOWS__
#define ftdm_sleep(x) Sleep(x)
#else
#define ftdm_sleep(x) usleep(x * 1000)
#endif

/*! \brief strncpy replacement */
#define ftdm_copy_string(x,y,z) strncpy(x, y, z - 1) 

/*! \brief strncpy into a fixed-length buffer */
#define ftdm_set_string(x,y) strncpy(x, y, sizeof(x)-1) 

/*! \brief check for null or zero length string buffer */
#define ftdm_strlen_zero(s) (!s || *s == '\0')

/*! \brief check for zero length string buffer */
#define ftdm_strlen_zero_buf(s) (*s == '\0')

/*! \brief The memory handler. 
    Do not use directly this variable, use the memory macros and ftdm_global_set_memory_handler to override */	
FT_DECLARE_DATA extern ftdm_memory_handler_t g_ftdm_mem_handler;

/*!
  \brief Allocate uninitialized memory
  \param chunksize the chunk size
*/
#define ftdm_malloc(chunksize) g_ftdm_mem_handler.malloc(g_ftdm_mem_handler.pool, chunksize)

/*!
  \brief Reallocates memory
  \param buff the buffer
  \param chunksize the chunk size
*/
#define ftdm_realloc(buff, chunksize) g_ftdm_mem_handler.realloc(g_ftdm_mem_handler.pool, buff, chunksize)

/*!
  \brief Allocate initialized memory
  \param chunksize the chunk size
*/
#define ftdm_calloc(elements, chunksize) g_ftdm_mem_handler.calloc(g_ftdm_mem_handler.pool, elements, chunksize)

/*!
  \brief Free chunk of memory
  \param chunksize the chunk size
*/
#define ftdm_free(chunk) g_ftdm_mem_handler.free(g_ftdm_mem_handler.pool, chunk)

/*!
  \brief Free a pointer and set it to NULL unless it already is NULL
  \param it the pointer
*/
#define ftdm_safe_free(it) if (it) { ftdm_free(it); it = NULL; }

/*! \brief Duplicate string */
FT_DECLARE(char *) ftdm_strdup(const char *str);

/*! \brief Duplicate string with limit */
FT_DECLARE(char *) ftdm_strndup(const char *str, ftdm_size_t inlen);


#ifdef __cplusplus
} /* extern C */
#endif

#endif

/* For Emacs:
 * Local Variables:
 * mode:c
 * indent-tabs-mode:t
 * tab-width:4
 * c-basic-offset:4
 * End:
 * For VIM:
 * vim:set softtabstop=4 shiftwidth=4 tabstop=4:
 */
