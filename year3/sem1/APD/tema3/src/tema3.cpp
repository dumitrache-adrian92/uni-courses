#include "tema3.h"

using namespace std;

static Client client;
static Tracker tracker_info;
static int file_info_size;

void peer_get_file_info() {
    char *file_info = (char *) malloc(file_info_size);
    if (file_info == NULL) {
        printf("Malloc error\n");
        exit(1);
    }

    /* buffer in which we'll send the name of the file we want to download
     * to the tracker
     */
    char buffer[MESSAGE_SIZE];
    for (auto &file : client.need_files) {
        memset(buffer, 0, sizeof(buffer));

        /* R for request and the file we are requesting */
        strcpy(buffer, "R\n");
        strcat(buffer, file.filename);

        /* send the buffer to the tracker */
        MPI_Send(buffer, sizeof(buffer), MPI_CHAR, TRACKER_RANK, 0, MPI_COMM_WORLD);

        memset(file_info, 0, file_info_size + 1);

        /* receive the file info from the tracker */
        MPI_Status status;
        MPI_Recv(file_info, file_info_size, MPI_CHAR, TRACKER_RANK, 0, MPI_COMM_WORLD, &status);

        /* parse the seeds */
        char *token = strtok(file_info, "\n");
        string seeds = string(token);

        stringstream iss(seeds);

        file.seeds.clear();
        int seed;
        while (iss >> seed) {
            file.seeds.push_back(seed);
        }

        /* parse the number of chunks */
        token = strtok(NULL, "\n");
        int chunk_count = atoi(token);
        file.chunk_count = chunk_count;

        /* parse the chunks */
        file.chunks_needed.clear();
        for (int i = 0; i < chunk_count; i++) {
            token = strtok(NULL, "\n");
            string chunk = string(token);
            if (find(file.chunks_owned.begin(), file.chunks_owned.end(), chunk) == file.chunks_owned.end()) {
                file.chunks_needed.push_back(chunk);
            }
        }

        /* parse the peers */
        file.peers.clear();
        while (token != NULL) {
            token = strtok(NULL, "\n");
            if (token == NULL) {
                break;
            }

            stringstream iss2(token);

            int peer;
            int chunks_owned;
            iss2 >> peer >> chunks_owned;

            file.peers.push_back(make_pair(peer, chunks_owned));
        }
    }

    free(file_info);
}

void peer_send_initial_state() {
    /* buffer in which we'll send the filenames of all files we own, separated
     * by newlines, to the tracker
     */
    char initial_state[MAX_FILES * (MAX_FILENAME + 1) + 1];

    memset(initial_state, 0, sizeof(initial_state));

    for (auto file : client.have_files) {
        strcat(initial_state, file.filename);
        strcat(initial_state, "\n");
    }

    /* send the buffer to the tracker */
    MPI_Send(initial_state, sizeof(initial_state), MPI_CHAR, TRACKER_RANK, 0, MPI_COMM_WORLD);

    /* buffer in which we'll send the names of all chunks of every file
     * we own, separated by newlines, to the tracker
     */
    char buffer2[MAX_CHUNKS * (HASH_SIZE + 1) + 1];

    for (auto file : client.have_files) {
        memset(buffer2, 0, sizeof(buffer2));

        for (auto chunk : file.chunks_owned) {
            strcat(buffer2, chunk.c_str());
            strcat(buffer2, "\n");
        }

        /* send the buffer to the tracker */
        MPI_Send(buffer2, sizeof(buffer2), MPI_CHAR, TRACKER_RANK, 0, MPI_COMM_WORLD);
    }

    char ack[4];

    MPI_Bcast(ack, 4, MPI_CHAR, TRACKER_RANK, MPI_COMM_WORLD);

    if (strcmp(ack, "ACK") != 0) {
        printf("Tracker error\n");
        exit(1);
    }
}

int peer_choose_peer(vector<int> chunk_owners) {
    /* download from a peer that has a higher rank than the previously
     * used peer or the lowest ranked one if a higher rank doesn't exist*/
    int peer_rank = client.last_peer_chosen;
    int chosen_peer = -1;
    sort(chunk_owners.begin(), chunk_owners.end());

    for (auto peer : chunk_owners) {
        if (peer > peer_rank) {
            chosen_peer = peer;
            break;
        }
    }

    if (chosen_peer == -1) {
        chosen_peer = chunk_owners[0];
    }

    client.last_peer_chosen = chosen_peer;

    return chosen_peer;
}

void peer_file_download_notification(string filename) {
    char buffer[MESSAGE_SIZE];
    memset(buffer, 0, sizeof(buffer));
    strcpy(buffer, "F\n");
    strcat(buffer, filename.c_str());

    MPI_Send(buffer, sizeof(buffer), MPI_CHAR, TRACKER_RANK, 0, MPI_COMM_WORLD);
}

void peer_update_status(string filename) {
    char buffer[MESSAGE_SIZE];
    memset(buffer, 0, sizeof(buffer));
    strcpy(buffer, "U\n");
    strcat(buffer, filename.c_str());
    strcat(buffer, "\n");
    strcat(buffer, to_string(client.segments_to_announce).c_str());
    strcat(buffer, "\n");

    MPI_Send(buffer, sizeof(buffer), MPI_CHAR, TRACKER_RANK, 0, MPI_COMM_WORLD);
}

void *download_thread_func(void *arg) {
    int rank = *(int*) arg;

    peer_send_initial_state();
    peer_get_file_info();

    while (!client.need_files.empty()) {
        auto &file = client.need_files.front();
        string chunk = file.chunks_needed.front();
        int chunk_index = file.chunks_owned.size();
        file.chunks_needed.erase(file.chunks_needed.begin());

        vector<int> chunk_owners;
        chunk_owners.insert(chunk_owners.end(), file.seeds.begin(), file.seeds.end());

        for (auto peer : file.peers) {
            if (peer.second > chunk_index) {
                chunk_owners.push_back(peer.first);
            }
        }

        /* choose peer, send request and wait for confirmation */
        int chosen_peer = peer_choose_peer(chunk_owners);

        MPI_Send(chunk.c_str(), HASH_SIZE + 1, MPI_CHAR, chosen_peer, REQUEST_CHUNK_TAG, MPI_COMM_WORLD);

        char ack[4];
        MPI_Recv(ack, 4, MPI_CHAR, chosen_peer, SEND_CHUNK_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        file.chunks_owned.push_back(chunk);
        client.download_segment_count++;
        client.segments_to_announce++;

        // if we have all the chunks, construct the file and inform the tracker
        unsigned long int chunk_c = file.chunk_count;
        if (file.chunks_owned.size() == chunk_c) {
            // construct the file
            string filename = "client" + to_string(rank) + "_" + file.filename;
            FILE *f = fopen(filename.c_str(), "w");

            for (auto chunk : file.chunks_owned) {
                fputs(chunk.c_str(), f);
                fputs("\n", f);
            }

            fclose(f);

            // remove the file from the list of needed files
            client.need_files.erase(client.need_files.begin());
            client.need_file_count--;

            // inform the tracker that we have the entire file now
            peer_file_download_notification(file.filename);

            client.segments_to_announce = 0;
        }

        if (client.download_segment_count == 10) {
            /* inform the tracker that we have downloaded 10 segments and
             * ask for file information again
             */

            if (client.segments_to_announce != 0) {
                peer_update_status(file.filename);
                client.segments_to_announce = 0;
            }

            client.download_segment_count = 0;
            peer_get_file_info();
        }
    }

    // inform the tracker that we have all the files we need
    char message[MESSAGE_SIZE];
    strcpy(message, "S\n");

    MPI_Send(message, sizeof(message), MPI_CHAR, TRACKER_RANK, 0, MPI_COMM_WORLD);

    return NULL;
}

void *upload_thread_func(void *arg) {
    char buffer[HASH_SIZE + 1];
    char ack[4];

    while (true) {
        memset(buffer, 0, sizeof(buffer));

        // receive a request from a peer (or a stop signal from the tracker)
        MPI_Status status;
        MPI_Recv(buffer, sizeof(buffer), MPI_CHAR, MPI_ANY_SOURCE, REQUEST_CHUNK_TAG, MPI_COMM_WORLD, &status);

        if (status.MPI_SOURCE == TRACKER_RANK && strcmp(buffer, "END") == 0) {
            break;
        }

        // send the "chunk" to the peer
        MPI_Send(ack, sizeof(ack), MPI_CHAR, status.MPI_SOURCE, SEND_CHUNK_TAG, MPI_COMM_WORLD);
    }

    return NULL;
}

void tracker_get_initial_state(int numtasks) {
    for (int i = 1; i < numtasks; i++) {
        /* buffer in which we'll receive the filenames of all files owned by
         * peer i, separated by newlines
         */
        char buffer[MAX_FILES * (MAX_FILENAME + 1) + 1];
        memset(buffer, 0, sizeof(buffer));

        /* receive the buffer from peer i */
        MPI_Recv(buffer, sizeof(buffer), MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        /* parse the buffer and add the files to the list of files */
        vector<string> filenames;
        char *token = strtok(buffer, "\n");
        while (token != NULL) {
            filenames.push_back(string(token));
            token = strtok(NULL, "\n");
        }

        for (auto filename : filenames) {
            tracker_info.swarm.file_seeds[filename].push_back(i);

            /* buffer in which we'll receive the names of all chunks of every
             * file owned by peer i, separated by newlines
             */
            char buffer2[MAX_CHUNKS * (HASH_SIZE + 1) + 1];
            memset(buffer2, 0, sizeof(buffer2));

            /* receive the buffer from peer i */
            MPI_Recv(buffer2, sizeof(buffer2), MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            /* parse the buffer */
            vector<string> chunks;
            token = strtok(buffer2, "\n");
            while (token != NULL) {
                chunks.push_back(string(token));
                token = strtok(NULL, "\n");
            }

            /* add the chunks to the list of chunks owned by peer i */
            for (auto chunk : chunks) {
                tracker_info.swarm.client_chunks[i].push_back(chunk);
                tracker_info.swarm.chunk_clients[chunk].push_back(i);
            }

            /* if it's the first time we see this file, add its chunks to the
             * list of chunks of the file
             */
            if (tracker_info.swarm.file_chunks.find(filename) == tracker_info.swarm.file_chunks.end()) {
                tracker_info.swarm.file_chunks[filename] = chunks;
            }
        }
    }
}

void tracker_send_file_info(char *message, char *file_info, MPI_Status status) {
    /* buffer in which we'll place the rank of the seeds on the
     * first line, the number of chunks on the second and
     * all the chunks of the file on the next lines
     * then each line will contain the rank of a peer that has
     * and how many chunks he has (if he has 10 chunks, it means
     * he has the first 10 chunks of the file)
     */
    char *filename = message + 2;

    memset(file_info, 0, file_info_size);

    /* seeds */
    for (auto client : tracker_info.swarm.file_seeds[string(filename)]) {
        strcat(file_info, to_string(client).c_str());
        strcat(file_info, " ");
    }
    strcat(file_info, "\n");
    strcat(file_info, to_string(tracker_info.swarm.file_chunks[string(filename)].size()).c_str());
    strcat(file_info, "\n");

    /* chunks */
    for (auto chunk : tracker_info.swarm.file_chunks[string(filename)]) {
        strcat(file_info, chunk.c_str());
        strcat(file_info, "\n");
    }

    /* peer info */
    for (auto x : tracker_info.swarm.file_peers[string(filename)]) {
        strcat(file_info, to_string(x.first).c_str());
        strcat(file_info, " ");
        strcat(file_info, to_string(x.second).c_str());
        strcat(file_info, "\n");
    }

    /* send the file info to the peer */
    MPI_Send(file_info, file_info_size, MPI_CHAR, status.MPI_SOURCE, 0, MPI_COMM_WORLD);
}

void tracker_mark_seeder(char *message, MPI_Status status) {
    char *filenameF = message + 2;

    /* add the peer to the list of seeds */
    tracker_info.swarm.file_seeds[string(filenameF)].push_back(status.MPI_SOURCE);

    /* remove it from the peer list */
    tracker_info.swarm.file_peers[string(filenameF)].erase(
        remove_if(tracker_info.swarm.file_peers[string(filenameF)].begin(),
                  tracker_info.swarm.file_peers[string(filenameF)].end(),
                  [status](pair<int, int> x)
                  { return x.first == status.MPI_SOURCE; }),
        tracker_info.swarm.file_peers[string(filenameF)].end());
}

void tracker_update_peer_status(char *message, MPI_Status status) {
    char *filenameU = strtok(message + 2, "\n");
    char *segmentCount = strtok(NULL, "\n");

    /* update the number of chunks owned by the peer */
    bool found = false;

    for (auto &x : tracker_info.swarm.file_peers[string(filenameU)]) {
        if (x.first == status.MPI_SOURCE) {
            x.second += atoi(segmentCount);
            found = true;
        }
    }

    if (!found) {
        tracker_info.swarm.file_peers[string(filenameU)].push_back(make_pair(status.MPI_SOURCE, atoi(segmentCount)));
    }
}

void tracker_send_stop_signal(int numtasks) {
    /* send a stop signal to all peers */
    char end[4] = "END";
    for (int i = 1; i < numtasks; i++) {
        MPI_Send(end, 4, MPI_CHAR, i, REQUEST_CHUNK_TAG, MPI_COMM_WORLD);
    }
}

void tracker(int numtasks, int rank) {
    tracker_info = Tracker();
    tracker_info.clients_still_downloading = numtasks - 1;
    tracker_get_initial_state(numtasks);

    char ack[4];
    strcpy(ack, "ACK");
    MPI_Bcast(ack, 4, MPI_CHAR, TRACKER_RANK, MPI_COMM_WORLD);

    char *file_info = (char *) malloc(file_info_size);

    /* receive messages until no more clients need files */
    while (tracker_info.clients_still_downloading > 0) {
        /* buffer for receiving messages from peers
         * size is given by the maximum size of a message (a peer informing
         * the tracker of 10 new downloaded segments)
         */
        char message[MESSAGE_SIZE];
        memset(message, 0, sizeof(message));

        /* receive a message from a peer */
        MPI_Status status;
        MPI_Recv(message, sizeof(message), MPI_CHAR, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);

        switch (message[0]) {
            case REQUEST_FILE_INFO:
            {
                tracker_send_file_info(message, file_info, status);
                break;
            }
            case FINISHED_FILE_DOWNLOAD:
            {
                tracker_mark_seeder(message, status);
                break;
            }
            case FINISHED_ALL_FILE_DOWNLOADS:
            {
                tracker_info.clients_still_downloading--;
                break;
            }
            case UPDATE:
            {
                tracker_update_peer_status(message, status);
                break;
            }
        }
    }

    tracker_send_stop_signal(numtasks);

    free(file_info);
}

void read_entry_file(int rank) {
    char input_file[MAX_FILENAME];
    sprintf(input_file, "in%d.txt", rank);

    std::ifstream f(input_file);

    f >> client.have_file_count;

    for (int i = 0; i < client.have_file_count; i++) {
        char filename[MAX_FILENAME];
        f >> filename;

        int chunk_count;
        f >> chunk_count;

        File file = File(filename, chunk_count);

        for (int j = 0; j < chunk_count; j++) {
            char hash[HASH_SIZE];
            f >> hash;

            file.chunks_owned.push_back(hash);
        }

        client.have_files.push_back(file);
    }

    f >> client.need_file_count;

    for (int i = 0; i < client.need_file_count; i++) {
        char filename[MAX_FILENAME];
        f >> filename;

        client.need_files.push_back(File(filename));
    }

    f.close();
}

void peer(int numtasks, int rank) {
    pthread_t download_thread;
    pthread_t upload_thread;
    void *status;
    int r;

    client = Client();
    client.numtasks = numtasks;
    read_entry_file(rank);

    r = pthread_create(&download_thread, NULL, download_thread_func, (void *) &rank);
    if (r) {
        printf("Eroare la crearea thread-ului de download\n");
        exit(-1);
    }

    r = pthread_create(&upload_thread, NULL, upload_thread_func, (void *) &rank);
    if (r) {
        printf("Eroare la crearea thread-ului de upload\n");
        exit(-1);
    }

    r = pthread_join(download_thread, &status);
    if (r) {
        printf("Eroare la asteptarea thread-ului de download\n");
        exit(-1);
    }

    r = pthread_join(upload_thread, &status);
    if (r) {
        printf("Eroare la asteptarea thread-ului de upload\n");
        exit(-1);
    }
}

int main(int argc, char *argv[]) {
    int numtasks, rank;

    int provided;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);
    if (provided < MPI_THREAD_MULTIPLE) {
        fprintf(stderr, "MPI nu are suport pentru multi-threading\n");
        exit(-1);
    }
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    file_info_size = numtasks * 2 + 1 + MAX_CHUNKS * (HASH_SIZE + 1) + numtasks * 4 + 2;

    if (rank == TRACKER_RANK) {
        tracker(numtasks, rank);
    } else {
        peer(numtasks, rank);
    }

    MPI_Finalize();
}
