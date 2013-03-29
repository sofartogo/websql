/*
 * =============================================================================
 *
 *       Filename:  websql.c
 *
 *    Description:  websql: HTTP interface to SQL(MySQL).
 *
 *        Created:  01/05/2013 10:47:21 AM
 *
 *        Company:  ICT ( Institute Of Computing Technology, CAS )
 *
 * =============================================================================
 */

#include <stdio.h>
#include <unistd.h>

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

int main(int argc, const char *argv[])
{
	websql_config_t *websql_config = websql_config_init("/home/wangwei/Work/websql/conf/websql.json");
	
	_server_save_pid(websql->server_config->pidfile);

	websql_log = websql_log_init(websql_config->log_config->stream, websql_config->log_config->level);

	LOG_DEBUG(("Init mysql server..."));

	MYSQL mysql;
	
	
    return 0;
}
