#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "oauth.h"
#include "utils.h"

using namespace std;

class Client
{
public:
	Client(char *host)
	{
#ifndef	DEBUG
		clnt = clnt_create(host, OAUTH, OAUTH_VERS, "udp");
		if (clnt == NULL) {
			clnt_pcreateerror(host);
			exit(1);
		}
	}
#endif	/* DEBUG */

	~Client()
	{
#ifndef	DEBUG
		clnt_destroy(clnt);
#endif	 /* DEBUG */
	}

	void HandleRefresh(std::string user_id)
	{
		char *user_id_cstr = (char *) user_id.c_str();
		char *auth_request_token = (char *) user_to_refresh[user_id].c_str();

		access_token_request request_access_token_1_arg;
		request_access_token_1_arg.id = user_id_cstr;
		request_access_token_1_arg.request_token = auth_request_token;
		request_access_token_1_arg.refresh = true;

		access_token_response *resp3 =
				request_access_token_1(&request_access_token_1_arg, clnt);

		if (resp3 == (access_token_response *) NULL) {
			clnt_perror (clnt, "call failed");
		}

		if (resp3->code != return_code::OK) {
			return;
		}

		user_to_tokens[user_id] = resp3->access_token;
		user_to_lifetime[user_id] = resp3->lifetime;
		user_to_refresh[user_id] = resp3->refresh_token;
	}

	void HandleRequest(std::string user_id, bool refresh)
	{
		char *user_id_cstr = (char *) user_id.c_str();
		char *auth_request_token;

		authorization_token_response *resp =
				request_authorization_1(&user_id_cstr, clnt);

		if (resp == (authorization_token_response *) NULL) {
			clnt_perror (clnt, "call failed");
		}

		if (resp->code != return_code::OK) {
			cout << ReturnCodeToString(resp->code) << endl;
			return;
		}
		auth_request_token = resp->auth_request_token;

		token_approval_request approve_request_token_1_arg;
		approve_request_token_1_arg.request_token = auth_request_token;

		token_approval_response *resp2 =
				approve_request_token_1(&approve_request_token_1_arg, clnt);

		if (resp2 == (token_approval_response *) NULL) {
			clnt_perror (clnt, "call failed");
		}

		access_token_request request_access_token_1_arg;
		request_access_token_1_arg.id = user_id_cstr;
		request_access_token_1_arg.request_token = auth_request_token;
		request_access_token_1_arg.refresh = refresh;

		access_token_response *resp3 =
				request_access_token_1(&request_access_token_1_arg, clnt);

		if (resp3 == (access_token_response *) NULL) {
			clnt_perror (clnt, "call failed");
		}

		if (resp3->code != return_code::OK) {
			cout << ReturnCodeToString(resp3->code) << endl;
			return;
		}

		user_to_tokens[user_id] = resp3->access_token;
		user_to_lifetime[user_id] = resp3->lifetime;

		cout << auth_request_token << " -> " << resp3->access_token;

		if (refresh) {
			cout << "," << resp3->refresh_token;
			user_to_refresh[user_id] = resp3->refresh_token;
		}

		cout << endl;
	}

	void HandleAction(std::string user_id, std::string resource,
					std::string action)
	{
		if (user_to_lifetime[user_id] == 0 &&
					user_to_refresh.find(user_id) != user_to_refresh.end()) {
			HandleRefresh(user_id);
		}

		char *access_token;

		if (user_to_tokens.find(user_id) == user_to_tokens.end()) {
			access_token = (char *) "";
		}
		else {
			access_token = (char *) user_to_tokens[user_id].c_str();
			user_to_lifetime[user_id]--;
		}

		action_request validate_delegated_action_1_arg;
		validate_delegated_action_1_arg.user_id = (char *) user_id.c_str();
		validate_delegated_action_1_arg.resource = (char *) resource.c_str();
		validate_delegated_action_1_arg.access_token = access_token;
		validate_delegated_action_1_arg.act = StringToAction(action);
		validate_delegated_action_1_arg.action_name = (char *) action.c_str();

		enum return_code *resp =
				validate_delegated_action_1(&validate_delegated_action_1_arg, clnt);

		if (resp == (enum return_code *) NULL) {
			clnt_perror (clnt, "call failed");
		}

		cout << ReturnCodeToString(*resp) << endl;
	}

	void ParseClientCommands(char *client_file)
	{
		std::ifstream client_file_stream(client_file);
		std::string line;

		while(std::getline(client_file_stream, line)) {
			std::vector<std::string> tokens;
			tokens = SplitString(line, ',');

			std::string user_id = tokens[0];
			std::string command = tokens[1];

			if (command == "REQUEST") {
				bool refresh = false;
				std::string refresh_str = tokens[2];
				if (refresh_str == "1") {
					refresh = true;
				}

				HandleRequest(user_id, refresh);
			} else {
				std::string resource = tokens[2];
				HandleAction(user_id, resource, command);
			}
		}
	}

 private:
	CLIENT *clnt;
	std::unordered_map<string, string> user_to_tokens;
	std::unordered_map<string, string> user_to_refresh;
	std::unordered_map<string, int> user_to_lifetime;
};

int main(int argc, char *argv[])
{
	if (argc < 3) {
		printf("usage: %s server_host <client.in>\n", argv[0]);
		exit(1);
	}
	char *host = argv[1];
	char *client_file = argv[2];

	Client clnt(host);
	clnt.ParseClientCommands(client_file);

	exit(0);
}
