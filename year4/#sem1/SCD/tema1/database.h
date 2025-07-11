#include <cstdint>
#include <string>
#include <queue>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <iostream>

#include "oauth.h"

// Class that represents the authorization database
class OauthDatabase
{
 protected:
	class Permission
	{
	 public:
		Permission() = default;
		/*
		 * A permission string is a string of characters that represent the
		 * permissions for a resource. The characters are as follows:
		 * R - read
		 * I - insert
		 * M - modify
		 * D - delete
		 * X - execute
		 */
		Permission(std::string resource, std::string permissions) : resource(resource) {
			for (char c : permissions) {
				switch (c) {
					case 'R':
						read = true;
						break;
					case 'I':
						insert = true;
						break;
					case 'M':
						modify = true;
						break;
					case 'D':
						del = true;
						break;
					case 'X':
						execute = true;
						break;
				}
			}
		}

		std::string resource;
		bool read = false;
		bool insert = false;
		bool modify = false;
		bool del = false;
		bool execute = false;
	};

	class Token
	{
	 public:
		Token() = default;
		Token(std::string value) : value(value) {}

		std::string value;
	};

	class RequestToken : public Token
	{
	 public:
		RequestToken(std::string value) : Token(value)
		{
			is_signed = false;
		}

		bool AttemptSign(std::unordered_map<std::string, Permission> permissions)
		{
			this->permissions = permissions;

			if (permissions.size() > 0) {
				is_signed = true;
			}

			return is_signed;
		}

		void MarkRefreshToken()
		{
			is_refresh = true;
			// A refresh token is always signed
			is_signed = true;
		}

		bool is_signed;
		bool is_refresh;
		std::unordered_map<std::string, Permission> permissions;
	};

	class AccessToken : public Token
	{
	 public:
		AccessToken(std::string value, uint32_t lifetime,
					std::unordered_map<std::string,
										Permission> permissions)
				: Token(value), lifetime(lifetime), permissions(permissions) {

		}

		std::unordered_map<std::string, Permission> permissions;
		int lifetime;
	};

	class User
	{
	 public:
		User() = default;
		User(std::string id) : id(id) {
			request_token = nullptr;
			access_token = nullptr;
		}

		void SetRequestToken(std::string token)
		{
			request_token = std::make_unique<RequestToken>(token);
		}

		void SetAccessToken(std::string token)
		{
			uint32_t lifetime = OauthDatabase::GetInstance()->token_lifetime;
			access_token = std::make_unique<AccessToken>(token, lifetime,
												request_token->permissions);
		}

		bool HasRequestToken(std::string token)
		{
			return request_token != nullptr && request_token->value == token;
		}

		bool HasAccessToken(std::string token)
		{
			return access_token != nullptr && access_token->value == token;
		}

		bool HasPermission(enum action action, std::string resource) {
			if (access_token == nullptr) {
				return false;
			}

			if (access_token->permissions.find(resource) == access_token->permissions.end()) {
				return false;
			}

			Permission permission = access_token->permissions[resource];
			switch (action) {
				case action::READ:
					return permission.read;
				case action::INSERT:
					return permission.insert;
				case action::MODIFY:
					return permission.modify;
				case action::DELETE:
					return permission.del;
				case action::EXECUTE:
					return permission.execute;
			}

			return false;
		}

		std::string id;
		std::unique_ptr<RequestToken> request_token;
		std::unique_ptr<AccessToken> access_token;
	};

   	OauthDatabase()
	{
   	}

   	static OauthDatabase *singleton_;

   	std::unordered_map<std::string, std::unique_ptr<User>> users;
	std::unordered_set<std::string> resources;
	std::queue<std::unordered_map<std::string, Permission>> approvals;

 public:
   	// Delete copy constructor and assignment operator to prevent cloning.
   	OauthDatabase(OauthDatabase &other) = delete;
   	void operator=(const OauthDatabase &) = delete;

   	// Returns the singleton instance of the database.
   	static OauthDatabase *GetInstance();
	/* Destroys the singleton instance of the database,
	 * freeing all associated memory in the process. */
	static void DestroyInstance();

   	// Populates the database with the given data.
   	void FillDatabase(char *user_ids, char *resources,
					  char *approvals, char *token_lifetime);
	void ParseUserIds(char *user_ids_filepath);
	void ParseResources(char *resources_filepath);
	void ParseApprovals(char *approvals_filepath);

	// Queries and actions
	bool IsUserValid(std::string user_id);
	void SetRequestToken(std::string user_id, std::string token);
	void SetAccessToken(std::string user_id, std::string token);
	bool AttemptSignRequestToken(std::string token);
	bool IsRequestTokenSigned(std::string token, std::string user_id);
	bool IsAccessTokenValid(std::string token, std::string user_id);
	bool IsAccessTokenExpired(std::string token, std::string user_id);
	bool ResourceExists(std::string resource);
	bool HasPermission(std::string resource, std::string user_id,
						enum action action);
	void UseAccessToken(std::string user_id, std::string token);
	int GetTokenLifetime(std::string token);
	void MarkRefreshToken(std::string user_id, std::string token);
	bool IsRefreshToken(std::string user_id, std::string token);

   	uint32_t token_lifetime;
};
