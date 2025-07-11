#include <iostream>
#include <stdlib.h>
#include <string>

#include "database.h"
#include "oauth.h"
#include "token.h"

std::string ActionToString(enum action action) {
    switch (action) {
        case action::READ:
            return "READ";
        case action::INSERT:
            return "INSERT";
        case action::MODIFY:
            return "MODIFY";
        case action::DELETE:
            return "DELETE";
        case action::EXECUTE:
            return "EXECUTE";
        default:
            return "ERROR";
    }
}

authorization_token_response *
request_authorization_1_svc(char **argp, struct svc_req *rqstp)
{
	static authorization_token_response  result;
	static char auth_request_token[TOKEN_LEN + 1];

	memset(auth_request_token, 0, TOKEN_LEN + 1);

	std::string user_id = *argp;

	std::cout << "BEGIN " << user_id << " AUTHZ" << std::endl;

	if (!OauthDatabase::GetInstance()->IsUserValid(user_id)) {
		result.code = return_code::USER_NOT_FOUND;
		result.auth_request_token = const_cast<char *> ("");
		return &result;
	}

	result.code = return_code::OK;

	// generate a request token
	char *token = generate_access_token(*argp);

	// copy the token to the result
	memcpy(auth_request_token, token, TOKEN_LEN + 1);
	result.auth_request_token = auth_request_token;

	// store the request token
	OauthDatabase::GetInstance()->SetRequestToken(user_id,
										std::string(auth_request_token));

	// free the memory allocated for the token
	free(token);

	std::cout << "  RequestToken = " << auth_request_token << std::endl;

	return &result;
}

access_token_response *
request_access_token_1_svc(access_token_request *argp, struct svc_req *rqstp)
{
	static access_token_response  result;
	static char access_token[TOKEN_LEN + 1];
	static char refresh_token[TOKEN_LEN + 1];

	std::string user_id = argp->id;
	std::string request_token = argp->request_token;
	bool refresh = argp->refresh;

	if (!OauthDatabase::GetInstance()->IsUserValid(user_id)) {
		result.code = return_code::USER_NOT_FOUND;
		result.access_token = const_cast<char *> ("");
		result.refresh_token = const_cast<char *> ("");
		result.lifetime = 0;
		return &result;
	}

	if (!OauthDatabase::GetInstance()->IsRequestTokenSigned(request_token,
															user_id)) {
		result.code = return_code::REQUEST_DENIED;
		result.access_token = const_cast<char *> ("");
		result.refresh_token = const_cast<char *> ("");
		result.lifetime = 0;
		return &result;
	}

	if (OauthDatabase::GetInstance()->IsRefreshToken(user_id, request_token)) {
		std::cout << "BEGIN " << user_id << " AUTHZ REFRESH" << std::endl;
	}

	// generate an access token
	char *token = generate_access_token(argp->request_token);

	// copy the token to the result
	memcpy(access_token, token, TOKEN_LEN + 1);

	// store the access token
	OauthDatabase::GetInstance()->SetAccessToken(user_id,
										std::string(access_token));

	// free the memory allocated for the token
	free(token);

	std::cout << "  AccessToken = " << access_token << std::endl;

	result.code = OK;
	result.access_token = access_token;
	result.lifetime = OauthDatabase::GetInstance()->token_lifetime;

	if (refresh) {
		// generate a refresh token
		char *refresh = generate_access_token(access_token);

		// copy the token to the result
		memcpy(refresh_token, refresh, TOKEN_LEN + 1);

		// store the refresh token
		OauthDatabase::GetInstance()->SetRequestToken(user_id,
										std::string(refresh_token));
		OauthDatabase::GetInstance()->MarkRefreshToken(user_id,
										std::string(refresh_token));

		// free the memory allocated for the token
		free(refresh);

		result.refresh_token = refresh_token;

		std::cout << "  RefreshToken = " << refresh_token << std::endl;
	} else {
		result.refresh_token = const_cast<char *> ("");
	}

	return &result;
}

token_approval_response *
approve_request_token_1_svc(token_approval_request *argp, struct svc_req *rqstp)
{
	static token_approval_response  result;
	static char auth_request_token[TOKEN_LEN + 1];

	if (OauthDatabase::GetInstance()
			->AttemptSignRequestToken(argp->request_token)) {
		result.code = SIGNED;
	} else {
		result.code = NOT_SIGNED;
	}

	memcpy(auth_request_token, argp->request_token, TOKEN_LEN + 1);
	result.request_token = auth_request_token;

	return &result;
}

// Generates the server status string for a validation request.
std::string get_validate_status(std::string resource, std::string access_token,
								int lt, enum action act, bool permit,
								std::string act_name)
{
	if (lt < 0) {
		access_token = "";
		lt = 0;
	}

	std::string lifetime = std::to_string(lt);
	std::string action;

	if (act != ERROR) {
		action = ActionToString(act);
	} else {
		action = act_name;
	}

	std::string status = "(" + action + "," + resource + "," +
						  access_token + "," + lifetime + ")";

	if (permit) {
		return "PERMIT " + status;
	} else {
		return "DENY " + status;
	}
}

enum return_code *
validate_delegated_action_1_svc(action_request *argp, struct svc_req *rqstp)
{
	static enum return_code result;

	std::string user_id = argp->user_id;
	std::string resource = argp->resource;
	std::string access_token = argp->access_token;
	std::string act_name = argp->action_name;

	if (!OauthDatabase::GetInstance()->IsUserValid(user_id)) {
		result = USER_NOT_FOUND;
		std::cout << get_validate_status(resource, access_token, 0, argp->act,
										false, act_name) << std::endl;
		return &result;
	}

	if (!OauthDatabase::GetInstance()->IsAccessTokenValid(access_token,
														user_id)) {
		result = PERMISSION_DENIED;
		std::cout << get_validate_status(resource, access_token, 0, argp->act,
										false, act_name) << std::endl;
		return &result;
	}

	if (OauthDatabase::GetInstance()->IsAccessTokenExpired(access_token,
														user_id)) {
		result = TOKEN_EXPIRED;
		std::cout << get_validate_status(resource, access_token, -1, argp->act,
										false, act_name) << std::endl;
		return &result;
	}

	// decrement the lifetime of the access token
	OauthDatabase::GetInstance()->UseAccessToken(user_id, access_token);

	int lt = OauthDatabase::GetInstance()->GetTokenLifetime(user_id);

	if (!OauthDatabase::GetInstance()->ResourceExists(resource)) {
		result = RESOURCE_NOT_FOUND;
		std::cout << get_validate_status(resource, access_token, lt, argp->act,
										false, act_name) << std::endl;

		return &result;
	}

	if (!OauthDatabase::GetInstance()->HasPermission(resource, user_id,
													argp->act)) {
		result = OPERATION_NOT_PERMITTED;
		std::cout << get_validate_status(resource, access_token, lt, argp->act,
										false, act_name) << std::endl;
		return &result;
	}

	result = PERMISSION_GRANTED;

	std::cout << get_validate_status(resource, access_token, lt, argp->act,
									true, act_name) << std::endl;

	return &result;
}
