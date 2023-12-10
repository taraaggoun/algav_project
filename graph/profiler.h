#pragma once

#include <time.h>

typedef struct ProfileResult
{
	const char* name;
	size_t size;
	int start, end;
} ProfileResult;


void begin_session(const char* filename);

void end_session(void);

void write_profile(ProfileResult result);

clock_t begin_profile();

void end_profile(const char* name, size_t size, clock_t start);


#define BEGIN_PROFILE_SESSION(filename) begin_session(filename)
#define END_PROFILE_SESSION() end_session()

#define BEGIN_PROFILE_FUNCTION() begin_profile()
#define END_PROFILE_FUNCTION(size, start) end_profile(__FUNCTION__, size, start)
