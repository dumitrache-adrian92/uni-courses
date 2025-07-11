#include <fstream>
#include <iostream>
#include <sstream>

#include "database.h"
#include "utils.h"

OauthDatabase* OauthDatabase::singleton_ = nullptr;

OauthDatabase *OauthDatabase::GetInstance()
{
    // Create the singleton object if it doesn't exist yet
    if (singleton_ == nullptr) {
        singleton_ = new OauthDatabase();
    }

    return singleton_;
}

void OauthDatabase::DestroyInstance()
{
    // Destroy the singleton object
    if (singleton_ != nullptr) {
        delete singleton_;
        singleton_ = nullptr;
    }
}

void OauthDatabase::ParseUserIds(char *user_ids_filepath)
{
    std::ifstream user_ids_file(user_ids_filepath);
    int n;
    user_ids_file >> n;

    std::string user_id;
    for(int i = 0; i < n; i++) {
        user_ids_file >> user_id;
        users[user_id] = std::make_unique<User>(user_id);
    }
}

void OauthDatabase::ParseResources(char *resources_filepath)
{
    std::ifstream resources_file(resources_filepath);
    int n;
    resources_file >> n;

    std::string resource;
    for(int i = 0; i < n; i++) {
        resources_file >> resource;
        resources.insert(resource);
    }
}

void OauthDatabase::ParseApprovals(char *approvals_filepath)
{
    std::ifstream approvals_file(approvals_filepath);

    std::string approval;
    while (!approvals_file.eof()) {
        approvals_file >> approval;

        // *,- signifies a rejection with no permissions
        if (approval == "*,-") {
            approvals.push(std::unordered_map<std::string, Permission>());
            continue;
        }

        // format: resource,permissions,resource,permissions,...
        std::vector<std::string> tokens = SplitString(approval, ',');
        std::unordered_map<std::string, Permission> permission_list;

        for (int i = 0; i < tokens.size(); i += 2) {
            std::string resource = tokens[i];
            std::string permissions = tokens[i + 1];
            permission_list[resource] = Permission(resource, permissions);
        }

        approvals.push(permission_list);
    }
}

void OauthDatabase::FillDatabase(char *user_ids_filepath, char *resources_filepath,
                                 char *approvals_filepath, char *token_lifetime)
{
    // parse the input files and populate the database
    ParseUserIds(user_ids_filepath);
    ParseResources(resources_filepath);
    ParseApprovals(approvals_filepath);

    // set the token lifetime
    this->token_lifetime = atoi(token_lifetime);
}

bool OauthDatabase::IsUserValid(std::string user_id)
{
    if (users.find(user_id) == users.end()) {
        return false;
    }

    return true;
}

void OauthDatabase::SetRequestToken(std::string user_id, std::string token)
{
    users[user_id]->SetRequestToken(token);
}

void OauthDatabase::SetAccessToken(std::string user_id, std::string token)
{
    users[user_id]->SetAccessToken(token);
}

// Returns true if the request token is signed, false otherwise
bool OauthDatabase::AttemptSignRequestToken(std::string token)
{
    auto permissions = approvals.front();
    approvals.pop();

    for (auto &kv : users) {
        auto user = kv.second.get();
        if (user->HasRequestToken(token)) {
            return user->request_token->AttemptSign(permissions);
        }
    }

    return false;
}

bool OauthDatabase::IsRequestTokenSigned(std::string token,
                                         std::string user_id)
{
    return users[user_id]->request_token->is_signed;
}

bool OauthDatabase::IsAccessTokenValid(std::string token, std::string user_id)
{
    return users[user_id]->HasAccessToken(token);
}

bool OauthDatabase::IsAccessTokenExpired(std::string token,
                                         std::string user_id)
{
    return users[user_id]->access_token->lifetime == 0;
}

bool OauthDatabase::ResourceExists(std::string resource)
{
    return resources.find(resource) != resources.end();
}

bool OauthDatabase::HasPermission(std::string resource, std::string user_id,
                                  enum action action)
{
    return users[user_id]->HasPermission(action, resource);
}

void OauthDatabase::UseAccessToken(std::string user_id, std::string token)
{
    users[user_id]->access_token->lifetime--;
}

int OauthDatabase::GetTokenLifetime(std::string user_id)
{
    if (users.find(user_id) == users.end()) {
        return 0;
    }

    if (users[user_id]->access_token == nullptr) {
        return 0;
    }

    return users[user_id]->access_token->lifetime;
}

void OauthDatabase::MarkRefreshToken(std::string user_id, std::string token)
{
    users[user_id]->request_token->MarkRefreshToken();

    // refresh tokens have the same permissions as the access token
    users[user_id]->request_token->permissions =
        users[user_id]->access_token->permissions;
}

bool OauthDatabase::IsRefreshToken(std::string user_id, std::string token)
{
    return users[user_id]->request_token->is_refresh;
}
