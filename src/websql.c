/*
 * =============================================================================
 *
 *       Filename:  websql.c
 *
 *    Description:  
 *
 *        Version:  0.0.1
 *        Created:  04/02/2013 11:09:07 AM
 *       Revision:  r1
 *       Compiler:  gcc (Ubuntu/Linaro 4.4.4-14ubuntu5) 4.4.5
 *
 *         Author:  Wang Wei (sofartogo), wangwei881116@gmail.com
 *        Company:  ICT ( Institute Of Computing Technology, CAS )
 *
 * =============================================================================
 */
#include <stdio.h>
#include <unistd.h>

#include <websql/rpc.h>
#include <websql/websql.h>
#include <websql/xconfig.h>


static void _server_save_pid(const char *pidfile)
{
	FILE *fp;

	if (access(pidfile, F_OK) == 0) {
		if ((fp = fopen(pidfile, "r")) != NULL) {
			char pidbuf[128];
			if (fgets(pidbuf, sizeof pidbuf, fp) != NULL) {
				unsigned long pid;
				if (safe_strtoul(pidbuf, &pid) && kill((pid_t)pid, 0) == 0) {
                    LOG_WARN(("the pid file contained the following (running) pid: %u\n", pid));
				}
			}
			fclose(fp);
		}
	}	

	if ((fp = fopen(pidfile, "w")) == NULL) {
		LOG_ERROR(("can not open pid file %s for writting", pidfile));
		return;
	}

	fprintf(fp, "%ld\n", (long)getpid());

	if (fclose(fp) != 0) {
		LOG_ERROR(("can not close the pid file %s", pidfile));
	}
}

void _mysql_service_init(MYSQL *mysql, db_config_t *config)
{
	if (mysql_init(mysql) == NULL) {
		LOG_FATAL(("init mysql failed."));
		exit(-1);
	}

	if (mysql_real_connect(mysql, config->host, config->username, config->password, NULL, config->port, NULL, 0) == NULL) {
		LOG_FATAL(("connect to mysql server failed."));
		exit(-1);
	}

	LOG_DEBUG(("connect to mysql succeed."));

	char encode[64];
	snprintf(encode, sizeof encode, "set names %s", config->encode);

	if (mysql_query(encode) != 0) {
		LOG_WARN(("set mysql encode %s failed.", config->encode));
		return;
	}

	LOG_DEBUG(("set mysql encode %s succeed.", config->encode));

}

int main(int argc, const char *argv[])
{
	websql_config_t *websql_config = websql_config_init("/home/wangwei/Work/websql/conf/websql.json");
	
	_server_save_pid(websql->server_config->pidfile);

	websql_log_t *websql_log = websql_log_init(websql_config->log_config->stream, websql_config->log_config->level);

	LOG_DEBUG(("Init mysql service begin..."));
	MYSQL mysql;
	_mysql_service_init(&mysql, websql_config->db_config);
	LOG_DEBUG(("Init mysql service done..."));
	websql_rpc_t *rpc = websql_rpc_init()
	LOG_DEBUG(("Init rpc service begin..."));
	
	LOG_DEBUG(("Init rpc service end..."));

    return 0;
}

