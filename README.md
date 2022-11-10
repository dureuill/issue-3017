meillisearch/meilisearch#3017 minimal reproducer
================================================

Minimal reproduction of meillisearch/meilisearch#3017 directly using lmdb in C.

Issue
-----

Running the provided example with NBR_THREADS = 11 causes the following output:

```
Starting tmp_env_0
Starting tmp_env_3
Starting tmp_env_5
Starting tmp_env_2
Starting tmp_env_4
Starting tmp_env_1
Starting tmp_env_6
Starting tmp_env_7
Starting tmp_env_8
Starting tmp_env_10
Starting tmp_env_9
ERROR opening nested txn
[tmp_env_9]ERROR opening parent_txn, 0
errno code: 22 Cause: Invalid argument
```

running with NBR_THREADS = 10 does not exhibit any issue:

```
Starting tmp_env_0
Starting tmp_env_1
Starting tmp_env_2
Starting tmp_env_3
Starting tmp_env_4
Starting tmp_env_5
Starting tmp_env_6
Starting tmp_env_7
Starting tmp_env_8
Starting tmp_env_9
ok env
ok env
ok env
ok env
ok env
ok env
ok env
ok env
ok env
ok env
ok!
```

Tested on MacBook Pro M1 2021 Ventura 13.0