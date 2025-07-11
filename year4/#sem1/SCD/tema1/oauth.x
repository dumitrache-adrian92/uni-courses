/* fixed lengths for user id and tokens */
const USER_ID_LENGTH = 15;
const TOKEN_LEN = 15;

/* return codes for interface responses */
enum return_code {
	OK = 0,
	USER_NOT_FOUND = 1,
	REQUEST_DENIED = 2,
	NOT_SIGNED = 3,
	PERMISSION_GRANTED = 4,
	SIGNED = 5,
	PERMISSION_DENIED = 6,
	TOKEN_EXPIRED = 7,
	RESOURCE_NOT_FOUND = 8,
	OPERATION_NOT_PERMITTED = 9
};

/* the response to a request for an authorization token */
struct authorization_token_response {
	enum return_code code;
	string auth_request_token<TOKEN_LEN>;
};

/* the arguments for a request for an access token */
struct access_token_request {
	string request_token<TOKEN_LEN>;
	string id<USER_ID_LENGTH>;
	bool refresh;
};

/* the response to a request for an access token */
struct access_token_response {
	enum return_code code;
	string access_token<TOKEN_LEN>;
	string refresh_token<TOKEN_LEN>;
	int lifetime;
};

/* the arguments for a request to approve a request token */
struct token_approval_request {
	string request_token<TOKEN_LEN>;
};

/* the response to a request to approve a request token */
struct token_approval_response {
	enum return_code code;
	string request_token<TOKEN_LEN>;
};

/* possible actions on a resource */
enum action {
	READ = 0,
	MODIFY = 1,
	DELETE = 2,
	INSERT = 3,
	EXECUTE = 4,
	ERROR = 5
};

/* the arguments for a request to validate an action on a resource */
struct action_request {
	string user_id<>;
	string resource<>;
	enum action act;
	string action_name<>;
	string access_token<TOKEN_LEN>;
};

program OAUTH {
	version OAUTH_VERS {
		/* a request for an authorization token;
		 * input: a user id
		 * output: a return code and a valid request token if successful */
		authorization_token_response REQUEST_AUTHORIZATION(string<USER_ID_LENGTH>) = 1;
		/* a request for an access token;
		 * input: an auth request token, a user id and whether to refresh the
		 * token automatically or not
		 * output: a return code, an access token + its lifetime if
		 * successful and a refresh token if it was requested */
		access_token_response REQUEST_ACCESS_TOKEN(access_token_request) = 2;
		/* a request to approve a request token
		 * input: a request token
		 * output: a return code and the request token */
		token_approval_response APPROVE_REQUEST_TOKEN(token_approval_request) = 3;
		/* a request to validate an action on a resource
		 * input: user_id, resource, action, action_name and access token
		 * output: a return code signifying the result of the operation */
		enum return_code VALIDATE_DELEGATED_ACTION(action_request) = 4;
	} = 1;
} = 0x1337;
