#ifndef tcp_client_h__
#define tcp_client_h__
 
void connect_to_server(char* IP, int port);
void send_remote_message(char* IP, int port, char* message);
 
#endif  // tcp_client_h__

