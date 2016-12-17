#include <jni.h>
#include <string>
#include <iostream>
#include "mongoose.h"
#include <thread>
using namespace std;

static void client_handler(struct mg_connection *conn, int ev, void *p) {
    if (ev == MG_EV_CONNECT) {
        if (conn->flags & MG_F_CLOSE_IMMEDIATELY) {
            printf("%s\n", "Error connecting to server!");
            exit(EXIT_FAILURE);
        }
        mg_send(conn, &(conn->recv_mbuf), (int)conn->recv_mbuf.len);
        printf("%s\n", "Connected to server. Type a message and press enter.");
    } else if (ev == MG_EV_RECV) {
        printf("we have a party lol! \n");
    } else if (ev == MG_EV_ACCEPT) {
        mg_send(conn, NULL, 0);
    } else if (ev == MG_EV_POLL) {
        cout << "poll called\n";
    }

}

void poll(){
    cout << "Hello, there! :>)\n";
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    nc = mg_connect(&mgr, "tcp://192.168.0.100:1234", client_handler);
    if(nc != NULL){
        mg_send(nc, NULL, 0);
        for(;;){
            mg_mgr_poll(&mgr, 1000);
        }
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_io_github_dmi3coder_streamanillaandroid_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    thread pollThread(poll);
    pollThread.detach();

}
