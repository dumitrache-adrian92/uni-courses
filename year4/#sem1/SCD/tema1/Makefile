SERVER_SOURCES = server.cpp oauth_svc.c oauth_xdr.c oauth_procedures.cpp database.cpp
CLIENT_SOURCES = client.cpp oauth_clnt.c oauth_xdr.c

build:
	g++ -o server $(SERVER_SOURCES) -ltirpc -I/usr/include/tirpc
	g++ -o client $(CLIENT_SOURCES) -ltirpc -I/usr/include/tirpc

generate_static_skel:
	rm oauth.h oauth_xdr.c oauth_svc.c oauth_clnt.c -f
	rpcgen oauth.x -h -o oauth.h
	rpcgen oauth.x -c -o oauth_xdr.c
	rpcgen oauth.x -m -o oauth_svc.c
	rpcgen oauth.x -l -o oauth_clnt.c

generate_dynamic_skel:
	rpcgen oauth.x -Ss -o oauth_procedures.cpp
	rpcgen oauth.x -Sc -o client.cpp

clean:
	rm server client
