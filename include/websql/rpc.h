/*
 * =============================================================================
 *
 *       Filename:  rpc.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/02/2013 11:00:49 AM
 *       Revision:  r1
 *       Compiler:  gcc (Ubuntu/Linaro 4.4.4-14ubuntu5) 4.4.5
 *
 *         Author:  Wang Wei (sofartogo), wangwei881116@gmail.com
 *        Company:  ICT ( Institute Of Computing Technology, CAS )
 *
 * =============================================================================
 */
#ifndef _WEBSQL_RPC_H_
#define _WEBSQL_RPC_H_

#include <websql/evhttpx/evhttpx.h>

#define WEBSQL_RPC_MAX_PORTS_LISTENING_ON 32

typedef struct websql_rpc_callbacks_s_ websql_rpc_callbacks_t;
typedef struct websql_rpc_s_ websql_rpc_t;

struct websql_rpc_callbacks_s_ {
    ///* only for server status test. */
    //evhttpx_callback_t  *rpc_void_cb;
    //evhttpx_callback_t  *rpc_echo_cb;
    //evhttpx_callback_t  *rpc_head_cb;

    ///* websql reports and internal leveldb storage engine status. */
    //evhttpx_callback_t  *rpc_report_cb;
    //evhttpx_callback_t  *rpc_status_cb;
    //evhttpx_callback_t  *rpc_property_cb;

    ///* admin operations. */
    //evhttpx_callback_t  *rpc_new_cb;
    //evhttpx_callback_t  *rpc_compact_cb;
    //evhttpx_callback_t  *rpc_size_cb;
    //evhttpx_callback_t  *rpc_repair_cb;
    //evhttpx_callback_t  *rpc_destroy_cb;

    ///* set(C), get(R), update(U), delete(D) (CRUD)operations. */

    ///* set related operations. */
    //evhttpx_callback_t  *rpc_add_cb;
    //evhttpx_callback_t  *rpc_set_cb;
    //evhttpx_callback_t  *rpc_mset_cb;
    //evhttpx_callback_t  *rpc_append_cb;
    //evhttpx_callback_t  *rpc_prepend_cb;
    //evhttpx_callback_t  *rpc_insert_cb;

    ///* get related operations. */
    //evhttpx_callback_t  *rpc_get_cb;
    //evhttpx_callback_t  *rpc_mget_cb;
    //evhttpx_callback_t  *rpc_seize_cb;
    //evhttpx_callback_t  *rpc_mseize_cb;
    //evhttpx_callback_t  *rpc_range_cb;
    //evhttpx_callback_t  *rpc_regex_cb;

    ///* update related operations. */
    //evhttpx_callback_t  *rpc_incr_cb;
    //evhttpx_callback_t  *rpc_decr_cb;
    //evhttpx_callback_t  *rpc_cas_cb;
    //evhttpx_callback_t  *rpc_replace_cb;

    ///* delete related operations. */
    //evhttpx_callback_t  *rpc_del_cb;
    //evhttpx_callback_t  *rpc_mdel_cb;
    //evhttpx_callback_t  *rpc_remove_cb;
    //evhttpx_callback_t  *rpc_clear_cb;

    ///* miscs operations. */
    //evhttpx_callback_t  *rpc_sync_cb;
    //evhttpx_callback_t  *rpc_check_cb;
    //evhttpx_callback_t  *rpc_exists_cb;
    //evhttpx_callback_t  *rpc_version_cb;
};

struct websql_rpc_s_ {
    const char *host;
    uint16_t ports[WEBSQL_RPC_MAX_PORTS_LISTENING_ON];
    int backlog;

    evbase_t *evbase;
    evhttpx_t *httpx;

    websql_rpc_callbacks_t *callbacks;
};

extern websql_rpc_t * websql_rpc_init();

extern void websql_rpc_run(websql_rpc_t *rpc);

extern void websql_rpc_stop(websql_rpc_t *rpc);

#endif // _WEBSQL_RPC_H_

