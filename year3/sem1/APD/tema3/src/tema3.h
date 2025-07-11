#pragma once

#include <bits/stdc++.h>
#include <mpi.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define TRACKER_RANK 0
#define MAX_FILES 10
#define MAX_FILENAME 15
#define HASH_SIZE 32
#define MAX_CHUNKS 100
#define MESSAGE_SIZE 2 + HASH_SIZE * 10 + 1
#define REQUEST_CHUNK_TAG 1
#define SEND_CHUNK_TAG 2

// message codes
#define REQUEST_FILE_INFO 'R'
#define FINISHED_FILE_DOWNLOAD 'F'
#define FINISHED_ALL_FILE_DOWNLOADS 'S'
#define UPDATE 'U'

struct File {
    char filename[MAX_FILENAME];
    int chunk_count;
    vector<string> chunks_needed;
    vector<string> chunks_owned;
    vector<int> seeds;
    vector<pair<int, int>> peers;

    File(string filename, int chunk_count) : File(filename) {
        this->chunk_count = chunk_count;
    }

    File(string filename) {
        strcpy(this->filename, filename.c_str());
    }
};

struct Client {
    int have_file_count;
    int need_file_count;
    int download_segment_count;
    int segments_to_announce;

    int numtasks;
    int last_peer_chosen;

    vector<File> have_files;
    vector<File> need_files;

    Client() {
        download_segment_count = 0;
        segments_to_announce = 0;
        last_peer_chosen = 0;
    }
};

struct Swarm {
    unordered_map<int, vector<string>> client_chunks;
    unordered_map<string, vector<int>> file_seeds;
    unordered_map<string, vector<pair<int, int>>> file_peers;
    unordered_map<string, vector<string>> file_chunks;
    unordered_map<string, vector<int>> chunk_clients;

    Swarm() {
    }
};

struct Tracker {
    Swarm swarm;
    int clients_still_downloading;

    Tracker() {
    }
};
