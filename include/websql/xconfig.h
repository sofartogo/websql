/*
 * =============================================================================
 *
 *       Filename:  xconfig.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/21/2013 10:54:34 AM
 *       Revision:  r1
 *       Compiler:  gcc (Ubuntu/Linaro 4.4.4-14ubuntu5) 4.4.5
 *
 *         Author:  Wang Wei (sofartogo), wangwei881116@gmail.com
 *        Company:  ICT ( Institute Of Computing Technology, CAS )
 *
 * =============================================================================
 */
#ifndef _WEBSQL_XCONFIG_H
#define _WEBSQL_XCONFIG_H

typedef struct websql_config_s_ websql_config_t;
typedef struct websql_server_config_s_ websql_server_config_t;
typedef struct websql_db_config_s_ websql_db_config_t;
typedef struct websql_log_config_s_ websql_log_config_t;

struct websql_config_s_ {
		websql_server_config_t *server_config;
		websql_db_config_t *db_config;
		websql_log_config_t *log_config;
};

struct websql_server_config_s_ {
	char *host;
	char *ports;
	char *username;
	char *password;
	char *pidfile;
};

struct websql_db_config_s_ {
	char *host;
	char *port;
	char *dbname;
	char *engine;
	char *encode;
};

struct websql_log_config_s_ {
	char *level;
	char *stream;
};

websql_config_t *websql_config_init(const char *conf_file);
void websql_config_fini(websql_config_t *config);

#endif
