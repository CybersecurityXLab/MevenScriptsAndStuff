//main file for the scan
//generate pcap files from nmap scans
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


#include "scan.h"

int main(int argc, char* argv[]){

    if(argc != 2){
        fprintf(stderr, "usage : %s ip\n", argv[0]);
        exit(1);
    }

    char* ip = argv[1];

    char* option[3];
    option[0] = "A";
    option[1] = "sS";
    option[2] = "p0-65535";

    char* option2 = "sS";
    char* option3 = "p0-65535";

    

    for(int i = 0; i<3; i++){
        if(fork() == 0){
           pcap(option[i]);
        }
        scanning(ip,option[i]);
        printf("scan done...\n");
    }

    return 0;
}