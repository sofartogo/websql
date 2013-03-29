/*
 * =============================================================================
 *
 *       Filename:  log.h
 *
 *    Description:  log utility.
 *
 *        Created:  10/20/2012 10:06:52 PM
 *
 *        Company:  ICT ( Institute Of Computing Technology, CAS )
 *
 * =============================================================================
 */

#ifndef _WEBSQL_LOG_H_
#define _WEBSQL_LOG_H_

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct websql_log_s_ websql_log_t;
typedef enum websql_log_level_e_ websql_log_level_e;

struct websql_log_s_ {
    char *level; /* unused right now. */
    FILE *stream;
};

enum websql_log_level_e_ {
	// WEBSQL_LOG_LEVEL_QUIET = 0,
	WEBSQL_LOG_LEVEL_ERROR = 1,
	WEBSQL_LOG_LEVEL_WARN  = 2,
	WEBSQL_LOG_LEVEL_INFO  = 3,
	WEBSQL_LOG_LEVEL_DEBUG = 4
};

extern websql_log_level_e log_level;

#define LOGSTREAM websql_log_get_stream()

#define LOG_ERROR(x) if (log_level >= WEBSQL_LOG_LEVEL_ERROR) \
    websql_log_message(WEBSQL_LOG_LEVEL_ERROR, __LINE__, __func__, websql_log_format_message x)
#define LOG_WARN(x) if(log_level >= WEBSQL_LOG_LEVEL_WARN) \
    websql_log_message(WEBSQL_LOG_LEVEL_WARN, __LINE__, __func__, websql_log_format_message x)
#define LOG_INFO(x) if(log_level >= WEBSQL_LOG_LEVEL_INFO) \
    websql_log_message(WEBSQL_LOG_LEVEL_INFO, __LINE__, __func__, websql_log_format_message x)
#define LOG_DEBUG(x) if(log_level == WEBSQL_LOG_LEVEL_DEBUG) \
    websql_log_message(WEBSQL_LOG_LEVEL_DEBUG, __LINE__, __func__, websql_log_format_message x)

extern void websql_log_message(
		websql_log_level_e level, int line,
		const char* funcname,
		const char* message);

extern const char * websql_log_format_message(const char* format, ...);

extern FILE * websql_log_get_stream(void);

extern void websql_log_set_stream(FILE *stream);

extern void websql_log_set_debug_level(websql_log_level_e level);

extern websql_log_t* websql_log_init(const char *logfile, const char *level);

extern void websql_log_free(websql_log_t *log);

#ifdef __cplusplus
}
#endif

#endif /* _websql_LOG_H_ */

