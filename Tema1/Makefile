build:
		rpcgen -C compute.x
		gcc -o myserver server.c compute_svc.c compute_xdr.c -lnsl -Wall
		gcc -o mycompute client.c compute_clnt.c compute_xdr.c -lnsl -Wall
clean:
		rm -f myserver mycompute compute.h compute_svc.c compute_clnt.c compute_xdr.c