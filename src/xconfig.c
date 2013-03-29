/*
 * =============================================================================
 *
 *       Filename:  xconfig.c
 *
 *    Description:  
 *
 *        Version:  0.0.1
 *        Created:  01/21/2013 11:10:01 AM
 *       Revision:  r1
 *       Compiler:  gcc (Ubuntu/Linaro 4.4.4-14ubuntu5) 4.4.5
 *
 *         Author:  Wang Wei (sofartogo), wangwei881116@gmail.com
 *        Company:  ICT ( Institute Of Computing Technology, CAS )
 *
 * =============================================================================
 */
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cJSON.h"
#include "log.h"
#include "xconfig.h"

static char *
_xconfig_json_content(const char *conf_file)
{
	int err = -1;
	long file_len = -1;
	FILE *fp = NULL;
	char *json_buf = NULL;

	fp = fopen(conf_file, "r");
	if (fp == NULL) {
		LOG_ERROR(("failed to open conf file : %s", conf_file));
		return NULL;
	}

	err = fseek(fp, 0, SEEK_END);
	if (err != 0) {
		LOG_ERROR(("failed to seek conf file : %s", strerror(errno)));
		return NULL;
	}

	file_len = ftell(fp);

	err = fseek(fp, 0, SEEK_SET);
	if (err != 0) {
		LOG_ERROR(("failed to seek : %s", strerror(errno)));
		return NULL;
	}

	json_buf = (char *)malloc(sizeof(char) * (file_len + 1));
	memset(json_buf, 0, file_len + 1);
	err = fread(json_buf, 1, file_len, fp);
	if (err != file_len) {
		fclose(fp);
		free(json_buf);
		LOG_ERROR(("failed to read file : %s", conf_file));
		return NULL;
	}

	fclose(fp);
	return json_buf;
}

static websql_config_t *
_xconfig_all(const char *config)
{
	assert(config != NULL);

	cJSON *root = NULL;
	cJSON *server = NULL;
	cJSON *db = NULL;
	cJSON *log = NULL;
	cJSON *iter = NULL;
	websql_config_t *websql_config = NULL;

	size_t config_vlen = -1;

	websql_config = (websql_config_t *)malloc(sizeof(websql_config_t));
	if (websql_config == NULL) {
		LOG_ERROR(("failed to make space for websql_config_t."));
		return NULL;
	}

	root = cJSON_Parse(config);
	if (!root) {
		LOG_ERROR(("parsing json error before: [%s]\n", 
					cJSON_GetErrorPtr()));
		free(websql_config);
		return NULL;
	}

	websql_server_config_t *server_config = 
		(websql_server_config_t *)malloc(sizeof(websql_server_config_t));
	if (server_config == NULL) {
		LOG_ERROR(("failed to make space for websql_server_config_t."));
		free(websql_config);
		cJSON_Delete(root);
		return NULL;
	} 
	websql_db_config_t *db_config = 
		(websql_db_config_t *)malloc(sizeof(websql_db_config_t));
	if (db_config == NULL) {
		LOG_ERROR(("failed to make space for websql_db_config_t."));
		free(websql_config);
		free(server_config);
		cJSON_Delete(root);
		return NULL;
	}
	websql_log_config_t *log_config = 
		(websql_log_config_t *)malloc(sizeof(websql_log_config_t));
	if (log_config == NULL) {
		LOG_ERROR(("failed to make space for websql_log_config_t."));
		free(websql_config);
		free(server_config);
		free(db_config);
		cJSON_Delete(root);
		return NULL;
	}


	//server config
	server = cJSON_GetObjectItem(root, "server");
	iter = cJSON_GetObjectItem(server, "host");
	config_vlen = strlen(iter->valuestring);
	server_config->host = 
		(char *)malloc(sizeof(char) * (config_vlen + 1));
	memset(server_config->host, 0, (config_vlen + 1));
	strncpy(server_config->host, iter->valuestring, config_vlen);
	config_vlen = -1;

	iter = cJSON_GetObjectItem(server, "ports");
	config_vlen = strlen(iter->valuestring);
	server_config->ports = 
		(char *)malloc(sizeof(char) * (config_vlen + 1));
	memset(server_config->ports, 0, (config_vlen + 1));
	strncpy(server_config->ports, iter->valuestring, config_vlen);
	config_vlen = -1;

	iter = cJSON_GetObjectItem(server, "username");
	config_vlen = strlen(iter->valuestring);
	server_config->username = 
		(char *)malloc(sizeof(char) * (config_vlen + 1));
	memset(server_config->username, 0, (config_vlen + 1));
	strncpy(server_config->username, iter->valuestring, config_vlen);
	config_vlen = -1;

	iter = cJSON_GetObjectItem(server, "password");
	config_vlen = strlen(iter->valuestring);
	server_config->password = 
		(char *)malloc(sizeof(char) * (config_vlen + 1));
	memset(server_config->password, 0, (config_vlen + 1));
	strncpy(server_config->password, iter->valuestring, config_vlen);
	config_vlen = -1;

	iter = cJSON_GetObjectItem(server, "pidfile");
	config_vlen = strlen(iter->valuestring);
	server_config->pidfile = 
		(char *)malloc(sizeof(char) * (config_vlen + 1));
	memset(server_config->pidfile, 0, (config_vlen + 1));
	strncpy(server_config->pidfile, iter->valuestring, config_vlen);
	config_vlen = -1;


	//db config
	db = cJSON_GetObjectItem(root, "db");

	iter = cJSON_GetObjectItem(db, "host");
	config_vlen = strlen(iter->valuestring);
	db_config->host = 
		(char *)malloc(sizeof(char) * (config_vlen + 1));
	memset(db_config->host, 0, (config_vlen + 1));
	strncpy(db_config->host, iter->valuestring, config_vlen);
	config_vlen = -1;

	iter = cJSON_GetObjectItem(db, "port");
	config_vlen = strlen(iter->valuestring);
	db_config->port = 
		(char *)malloc(sizeof(char) * (config_vlen + 1));
	memset(db_config->port, 0, (config_vlen + 1));
	strncpy(db_config->port, iter->valuestring, config_vlen);
	config_vlen = -1;

	iter = cJSON_GetObjectItem(db, "dbname");
	config_vlen = strlen(iter->valuestring);
	db_config->dbname = 
		(char *)malloc(sizeof(char) * (config_vlen + 1));
	memset(db_config->dbname, 0, (config_vlen + 1));
	strncpy(db_config->dbname, iter->valuestring, config_vlen);
	config_vlen = -1;
	
	iter = cJSON_GetObjectItem(db, "engine");
	config_vlen = strlen(iter->valuestring);
	db_config->engine = 
		(char *)malloc(sizeof(char) * (config_vlen + 1));
	memset(db_config->engine, 0, (config_vlen + 1));
	strncpy(db_config->engine, iter->valuestring, config_vlen);
	config_vlen = -1;

	iter = cJSON_GetObjectItem(db, "encode");
	config_vlen = strlen(iter->valuestring);
	db_config->encode = 
		(char *)malloc(sizeof(char) * (config_vlen + 1));
	memset(db_config->encode, 0, (config_vlen + 1));
	strncpy(db_config->encode, iter->valuestring, config_vlen);
	config_vlen = -1;

	log = cJSON_GetObjectItem(root, "log");
	
	iter = cJSON_GetObjectItem(log, "level");
	config_vlen = strlen(iter->valuestring);
	log_config->level = 
		(char *)malloc(sizeof(char) * (config_vlen + 1));
	memset(log_config->level, 0, (config_vlen + 1));
	strncpy(log_config->level, iter->valuestring, config_vlen);
	config_vlen = -1;

	iter = cJSON_GetObjectItem(log, "stream");
	config_vlen = strlen(iter->valuestring);
	log_config->stream = 
		(char *)malloc(sizeof(char) * (config_vlen + 1));
	memset(log_config->stream, 0, (config_vlen + 1));
	strncpy(log_config->stream, iter->valuestring, config_vlen);
	config_vlen = -1;

	websql_config->server_config = server_config;
	websql_config->db_config = db_config;
	websql_config->log_config = log_config;

	cJSON_Delete(root);

	return websql_config;
}

websql_config_t *
websql_config_init(const char *conf_file)
{
	assert(file != NULL);

	websql_config_t *websql_config = NULL;
	char *config_json = _xconfig_json_content(conf_file);
	websql_config = _xconfig_all(config_json);
	free(config_json);
	return websql_config;
}

void websql_config_fini(websql_config_t *config)
{
	assert(config != NULL);

	if (config->server_config != NULL) {
		if (config->server_config->host != NULL) {
			free(config->server_config->host);
			config->server_config->host = NULL;
		}
		if (config->server_config->ports != NULL) {
			free(config->server_config->ports);
			config->server_config->ports = NULL;
		}
		if (config->server_config->username != NULL) {
			free(config->server_config->username);
			config->server_config->username = NULL;
		}
		if (config->server_config->password != NULL) {
			free(config->server_config->password);
			config->server_config->password = NULL;
		}
		free(config->server_config);
		config->server_config = NULL;
	}

	if (config->db_config != NULL) {
		if (config->db_config->host != NULL) {
			free(config->db_config->host);
			config->db_config->host = NULL;
		}
		if (config->db_config->port != NULL) {
			free(config->db_config->port);
			config->db_config->port = NULL;
		}
		if (config->db_config->dbname != NULL) {
			free(config->db_config->dbname);
			config->db_config->dbname = NULL;
		}
		if (config->db_config->engine != NULL) {
			free(config->db_config->engine);
			config->db_config->engine = NULL;
		}
		if (config->db_config->encode != NULL) {
			free(config->db_config->encode);
			config->db_config->encode = NULL;
		}
		free(config->db_config);
		config->db_config = NULL;
	}
	if (config->log_config != NULL) {
		if (config->log_config->level != NULL) {
			free(config->log_config->level);
			config->log_config->level = NULL;
		}
		if (config->log_config->stream != NULL) {
			free(config->log_config->stream);
			config->log_config->stream = NULL;
		}
		free(config->log_config);
		config->log_config = NULL;
	}
	free(config);
	config = NULL;
}
