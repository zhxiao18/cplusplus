#include "MutexLock.h"
#include <stdio.h>
#include <iostream>

using std::cout;
using std::endl;

MutexLock::MutexLock(){
    int ret = pthread_mutex_init(&_mutex, nullptr);
    if(ret){
        perror("pthread_mutex_init");
        return;
    }
}

MutexLock::~MutexLock(){
    int ret = pthread_mutex_destroy(&_mutex);
    if(ret){
        perror("pthread_mutex_destroy");
        return;
    }
}

void MutexLock::lock(){
    int ret = pthread_mutex_lock(&_mutex);
    if(ret){
        perror("pthread_mutex_lock");
        return;
    }
}
void MutexLock::unlock(){
    int ret = pthread_mutex_unlock(&_mutex);
    if(ret){
        perror("pthread_mutex_unlock");
        return;
    }
}

void MutexLock::trylock(){
    int ret = pthread_mutex_trylock(&_mutex);
    if(ret){
        perror("pthread_mutex_trylock");
        return;
    }
}
