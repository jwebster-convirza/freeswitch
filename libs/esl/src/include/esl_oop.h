/*
 * Copyright (c) 2007, Anthony Minessale II
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

#define EXTERN_C extern "C" {
#ifndef _ESL_OOP_H_
#define _ESL_OOP_H_
#include <esl.h>
#ifdef __cplusplus
EXTERN_C
#endif

#define this_check(x) do { if (!this) { esl_log(ESL_LOG_ERROR, "object is not initalized\n"); return x;}} while(0)
#define this_check_void() do { if (!this) { esl_log(ESL_LOG_ERROR, "object is not initalized\n"); return;}} while(0)


class ESLevent {
 public:
	esl_event_t *event;
	char *serialized_string;
	int mine;

	ESLevent(const char *type, const char *subclass_name = NULL);
	ESLevent(esl_event_t *wrap_me, int free_me = 0);
	ESLevent(ESLevent *me);
	virtual ~ESLevent();
	const char *serialize(const char *format = NULL);
	bool setPriority(esl_priority_t priority = ESL_PRIORITY_NORMAL);
	const char *getHeader(char *header_name);
	char *getBody(void);
	const char *getType(void);
	bool addBody(const char *value);
	bool addHeader(const char *header_name, const char *value);
	bool delHeader(const char *header_name);
};



class ESLconnection {
 private:
	esl_handle_t handle;
	ESLevent *last_event_obj;
 public:
	ESLconnection(const char *host, const char *port, const char *password);
	ESLconnection(int socket);
	virtual ~ESLconnection();
	int connected();
	ESLevent *getInfo();
	esl_status_t send(const char *cmd);
	ESLevent *sendRecv(const char *cmd);
	esl_status_t sendEvent(ESLevent *send_me);
	ESLevent *recvEvent();
	ESLevent *recvEventTimed(int ms);
	esl_status_t filter(const char *header, const char *value);
	esl_status_t events(const char *etype, const char *value);
	esl_status_t execute(const char *app, const char *arg = NULL, const char *uuid = NULL);
	int setBlockingExecute(const char *val);
	int setEventLock(const char *val);
};

void eslSetLogLevel(int level);



#ifdef __cplusplus
}
#endif

#endif