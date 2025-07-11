#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "database.h"
#include "oauth.h"

extern void oauth_1(struct svc_req *rqstp, register SVCXPRT *transp);

int main (int argc, char **argv)
{
	if (argc < 5) {
		printf("usage: %s <userIDs.db> <resources.db> \
<approvals.db> <token_lifetime>\n", argv[0]);
		exit(1);
	}

	register SVCXPRT *transp;

	pmap_unset(OAUTH, OAUTH_VERS);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, OAUTH, OAUTH_VERS, oauth_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (OAUTH, OAUTH_VERS, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, OAUTH, OAUTH_VERS, oauth_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (OAUTH, OAUTH_VERS, tcp).");
		exit(1);
	}

	OauthDatabase::GetInstance()->FillDatabase(argv[1], argv[2], argv[3], argv[4]);

	svc_run();

	OauthDatabase::DestroyInstance();

	return 0;

	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}