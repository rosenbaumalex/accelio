/*
 * Copyright (c) 2013 Mellanox Technologies®. All rights reserved.
 *
 * This software is available to you under a choice of one of two licenses.
 * You may choose to be licensed under the terms of the GNU General Public
 * License (GPL) Version 2, available from the file COPYING in the main
 * directory of this source tree, or the Mellanox Technologies® BSD license
 * below:
 *
 *      - Redistribution and use in source and binary forms, with or without
 *        modification, are permitted provided that the following conditions
 *        are met:
 *
 *      - Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 *      - Neither the name of the Mellanox Technologies® nor the names of its
 *        contributors may be used to endorse or promote products derived from
 *        this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef XIO_SESSION_PRIV_H
#define XIO_SESSION_PRIV_H

#define XIO_ACTION_ACCEPT	1
#define XIO_ACTION_REDIRECT	2
#define XIO_ACTION_REJECT	3

#define MAX_PORTAL_LEN		192
#define MAX_RESOURCE_LEN	1024
#define SETUP_BUFFER_LEN	3840   /* 4096-256 */

/* Common API */

/*---------------------------------------------------------------------------*/
/* xio_on_conn_disconnected			                             */
/*---------------------------------------------------------------------------*/
int xio_on_conn_disconnected(struct xio_session *session,
			     struct xio_conn *conn,
			     union xio_conn_event_data *event_data);

/*---------------------------------------------------------------------------*/
/* xio_on_conn_closed							     */
/*---------------------------------------------------------------------------*/
int xio_on_conn_closed(struct xio_session *session,
		       struct xio_conn *conn,
		       union xio_conn_event_data *event_data);

/*---------------------------------------------------------------------------*/
/* xio_on_conn_error							     */
/*---------------------------------------------------------------------------*/
int xio_on_conn_error(struct xio_session *session,
		      struct xio_conn *conn,
		      union xio_conn_event_data *event_data);

/*---------------------------------------------------------------------------*/
/* xio_on_new_message							     */
/*---------------------------------------------------------------------------*/
int xio_on_new_message(struct xio_session *session,
		       struct xio_conn *conn,
		       union xio_conn_event_data *event_data);

/*---------------------------------------------------------------------------*/
/* xio_on_send_completion						     */
/*---------------------------------------------------------------------------*/
int xio_on_send_completion(struct xio_session *session,
			   struct xio_conn *conn,
			   union xio_conn_event_data *event_data);

/*---------------------------------------------------------------------------*/
/* xio_on_assign_in_buf							     */
/*---------------------------------------------------------------------------*/
int xio_on_assign_in_buf(struct xio_session *session,
			 struct xio_conn *conn,
			 union xio_conn_event_data *event_data);

/*---------------------------------------------------------------------------*/
/* xio_on_cancel_request						     */
/*---------------------------------------------------------------------------*/
int xio_on_cancel_request(struct xio_session *sess,
			  struct xio_conn *conn,
			  union xio_conn_event_data *event_data);

/*---------------------------------------------------------------------------*/
/* xio_on_cancel_response						     */
/*---------------------------------------------------------------------------*/
int xio_on_cancel_response(struct xio_session *sess,
			   struct xio_conn *conn,
			   union xio_conn_event_data *event_data);

/*---------------------------------------------------------------------------*/
/* xio_on_conn_message_error						     */
/*---------------------------------------------------------------------------*/
int xio_on_conn_message_error(struct xio_session *session,
			      struct xio_conn *conn,
			      union xio_conn_event_data *event_data);

/*---------------------------------------------------------------------------*/
/* xio_session_read_header						     */
/*---------------------------------------------------------------------------*/
int xio_session_read_header(struct xio_task *task,
			    struct xio_session_hdr *hdr);

/*---------------------------------------------------------------------------*/
/* xio_session_notify_teardown						     */
/*---------------------------------------------------------------------------*/
void xio_session_notify_teardown(struct xio_session *session, int reason);

/*---------------------------------------------------------------------------*/
/* xio_session_notify_connection_closed					     */
/*---------------------------------------------------------------------------*/
void xio_session_notify_connection_closed(struct xio_session *session,
					  struct xio_connection *connection);

/*---------------------------------------------------------------------------*/
/* xio_session_find_connection_by_ctx					     */
/*---------------------------------------------------------------------------*/
struct xio_connection *xio_session_find_connection_by_ctx(
		struct xio_session *session,
		struct xio_context *ctx);


/* Server API */

/*---------------------------------------------------------------------------*/
/* xio_on_setup_req_recv			                             */
/*---------------------------------------------------------------------------*/
int xio_on_setup_req_recv(struct xio_connection *connection,
			  struct xio_task *task);

/*---------------------------------------------------------------------------*/
/* xio_on_connection_hello_req_recv			                     */
/*---------------------------------------------------------------------------*/
int xio_on_connection_hello_req_recv(struct xio_connection *connection,
				     struct xio_task *task);

/*---------------------------------------------------------------------------*/
/* xio_session_write_accept_rsp						     */
/*---------------------------------------------------------------------------*/
struct xio_msg *xio_session_write_accept_rsp(
		struct xio_session *session,
		uint16_t action,
		const char **portals_array,
		uint16_t portals_array_len,
		void *user_context,
		uint16_t user_context_len);

/*---------------------------------------------------------------------------*/
/* xio_session_write_reject_rsp						     */
/*---------------------------------------------------------------------------*/
struct xio_msg *xio_session_write_reject_rsp(
		struct xio_session *session,
		enum xio_status reason,
		void *user_context,
		uint16_t user_context_len);

/*---------------------------------------------------------------------------*/
/* xio_on_setup_rsp_send_comp			                             */
/*---------------------------------------------------------------------------*/
int xio_on_setup_rsp_send_comp(struct xio_connection *connection,
			       struct xio_task *task);

/*---------------------------------------------------------------------------*/
/* xio_on_fin_req_recv				                             */
/*---------------------------------------------------------------------------*/
int xio_on_fin_req_recv(struct xio_connection *connection,
			struct xio_task *task);

/*---------------------------------------------------------------------------*/
/* xio_on_fin_rsp_send_comp						     */
/*---------------------------------------------------------------------------*/
int xio_on_fin_rsp_send_comp(struct xio_connection *connection,
			     struct xio_task *task);

/*---------------------------------------------------------------------------*/
/* xio_on_connection_hello_rsp_send_comp				     */
/*---------------------------------------------------------------------------*/
int xio_on_connection_hello_rsp_send_comp(struct xio_connection *connection,
					  struct xio_task *task);

/*---------------------------------------------------------------------------*/
/* xio_on_server_conn_established					     */
/*---------------------------------------------------------------------------*/
int xio_on_server_conn_established(struct xio_session *session,
				   struct xio_conn *conn,
				   union xio_conn_event_data *event_data);

/*---------------------------------------------------------------------------*/
/* xio_on_conn_event_server				                     */
/*---------------------------------------------------------------------------*/
int xio_on_conn_event_server(void *observer, void *sender, int event,
				    void *event_data);

/* Client API */

/*---------------------------------------------------------------------------*/
/* xio_session_write_setup_req						     */
/*---------------------------------------------------------------------------*/
struct xio_msg *xio_session_write_setup_req(struct xio_session *session);

/*---------------------------------------------------------------------------*/
/* xio_on_connection_hello_rsp_recv			                     */
/*---------------------------------------------------------------------------*/
int xio_on_connection_hello_rsp_recv(struct xio_connection *connection,
				     struct xio_task *task);

/*---------------------------------------------------------------------------*/
/* xio_session_accept_connection					     */
/*---------------------------------------------------------------------------*/
int xio_session_accept_connection(struct xio_session *session);

/*---------------------------------------------------------------------------*/
/* xio_session_redirect_connection					     */
/*---------------------------------------------------------------------------*/
int xio_session_redirect_connection(struct xio_session *session);

/*---------------------------------------------------------------------------*/
/* xio_on_connection_rejected			                             */
/*---------------------------------------------------------------------------*/
int xio_on_connection_rejected(struct xio_session *session,
			       struct xio_connection *connection);

/*---------------------------------------------------------------------------*/
/* xio_read_setup_rsp							     */
/*---------------------------------------------------------------------------*/
int xio_read_setup_rsp(struct xio_connection *connection,
		       struct xio_task *task,
		       uint16_t *action);

/*---------------------------------------------------------------------------*/
/* xio_on_setup_rsp_recv			                             */
/*---------------------------------------------------------------------------*/
int xio_on_setup_rsp_recv(struct xio_connection *connection,
			  struct xio_task *task);


/*---------------------------------------------------------------------------*/
/* xio_on_fin_rsp_recv				                             */
/*---------------------------------------------------------------------------*/
int xio_on_fin_rsp_recv(struct xio_connection *connection,
			struct xio_task *task);


/*---------------------------------------------------------------------------*/
/* xio_on_conn_refused							     */
/*---------------------------------------------------------------------------*/
int xio_on_conn_refused(struct xio_session *session,
			struct xio_conn *conn,
			union xio_conn_event_data *event_data);


/*---------------------------------------------------------------------------*/
/* xio_on_client_conn_established					     */
/*---------------------------------------------------------------------------*/
int xio_on_client_conn_established(struct xio_session *session,
				   struct xio_conn *conn,
				   union xio_conn_event_data *event_data);

/*---------------------------------------------------------------------------*/
/* xio_on_conn_event_client						     */
/*---------------------------------------------------------------------------*/
int xio_on_conn_event_client(void *observer, void *sender, int event,
			     void *event_data);

/* Should be in xio_ connection.h but it doesn't compile if moved there */
/*---------------------------------------------------------------------------*/
/* xio_connection_set_conn						     */
/*---------------------------------------------------------------------------*/
static inline void xio_connection_set_conn(struct xio_connection *connection,
					   struct xio_conn *conn)
{
	if (connection->conn && connection->conn == conn)
		return;

	if (connection->conn)
		xio_conn_unreg_observer(connection->conn,
					&connection->session->observer);

	if (conn) {
		xio_conn_unreg_observer(conn,
					&connection->session->observer);
		xio_conn_reg_observer(conn,
				      &connection->session->observer,
				      connection->session->session_id);
	}

	connection->conn = conn;
}


#endif /* XIO_SESSION_PRIV_H */
