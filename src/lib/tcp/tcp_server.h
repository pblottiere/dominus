#ifndef tcp_server_h__
#define tcp_server_h__

int init_server(int port);
char get_command_from_client(int tcp_server);
 
#endif  // tcp_server_h__

