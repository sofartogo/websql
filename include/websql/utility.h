/*
 * =============================================================================
 *
 *       Filename:  utility.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/02/2013 11:01:26 AM
 *       Revision:  r1
 *       Compiler:  gcc (Ubuntu/Linaro 4.4.4-14ubuntu5) 4.4.5
 *
 *         Author:  Wang Wei (sofartogo), wangwei881116@gmail.com
 *        Company:  ICT ( Institute Of Computing Technology, CAS )
 *
 * =============================================================================
 */
#ifndef _WEBSQL_UTILITY_H_
#define _WEBSQL_UTILITY_H_

#include <stdbool.h>

/*
 * Wrappers around strtoull/strtoll that are safer and easier to
 * use.  For tests and assumptions, see internal_tests.c.
 *
 * str   a NULL-terminated base decimal 10 unsigned integer
 * out   out parameter, if conversion succeeded
 *
 * returns true if conversion succeeded.
 */
bool safe_strtoull(const char *str, uint64_t * out);
bool safe_strtoll(const char *str, int64_t * out);
bool safe_strtoul(const char *str, uint32_t * out);
bool safe_strtol(const char *str, int32_t * out);

/*
 * Get GMT formatted time.
 */
char * gmttime_now(void);

#endif // _WEBSQL_UTILITY_H_

