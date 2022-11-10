#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include "../lmdb.h"
#include "../midl.h"

#define NBR_THREADS 11
#define NBR_DB 100

void* run(void* param) {
    char* dir_name = (char*) param;
    printf("Starting %s\n", dir_name);
    MDB_env* env;
    //MDB_txn* parent_txn;
    mdb_env_create(&env);
    mdb_env_set_maxdbs(env, NBR_DB);
    if (mdb_env_open(env, dir_name, MDB_NOTLS, 0600) != 0) {
        printf("ERROR opening env\n");
        goto exit;
    }
    int parent_txn_res;
    /*if ((parent_txn_res = mdb_txn_begin(env, NULL, 0, &parent_txn) != 0)) {
        printf("[%s]ERROR opening parent_txn, %d\n", dir_name, parent_txn_res);
        fprintf(stderr, "errno code: %d ", errno);
        perror("Cause");
        goto exit;
    }*/

    for (int i=0; i<NBR_DB;++i) {
        char* db_name = malloc(100);
        sprintf(db_name, "db_%i", i);

        MDB_txn* txn;

        if (mdb_txn_begin(env, NULL, 0, &txn) != 0) {
            printf("ERROR opening nested txn\n");
            printf("[%s]ERROR opening parent_txn, %d\n", dir_name, parent_txn_res);
            fprintf(stderr, "errno code: %d ", errno);
            perror("Cause");
            //goto exit;
            goto exit_loop;
        }

        MDB_dbi db;
        sleep(1);
        /*if (mdb_dbi_open(txn, db_name, MDB_CREATE, &db) != 0) {
            printf("ERROR opening db\n");
            mdb_txn_abort(txn);
            goto exit_loop;
        } else {*/
            mdb_txn_commit(txn);
        //}
        free(db_name);
        continue;
exit_loop:
        free(db_name);
        goto exit;
    }
    //mdb_txn_commit(parent_txn);
    printf("ok env\n");
exit:
    free(dir_name);
    mdb_env_close(env);

    return NULL;
}

int main(int argc, char** argv) {
    pthread_t threads[NBR_THREADS];
    for (int i = 0; i < NBR_THREADS; ++i) {
        char* dir_name = malloc(100);
        sprintf(dir_name, "tmp_env_%i", i);
        pthread_create(&threads[i], NULL, run, dir_name);
    }
    
    for (int i = 0; i < NBR_THREADS; ++i) {
        void* retval;
        pthread_join(threads[i], &retval);
    }
    printf("ok!\n");
    return 0;
}