#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "scan.h"

void pcap(char* aOption){
    char pcap[50];
    strcpy(pcap, "tcpdump -i eth0 -w nmap-");
    strcat(pcap, aOption);
    strcat(pcap, ".pcap");
    printf("saving tcp traffic\n");
    system(pcap);
    if(aOption=="A"){
    sleep(150);
    }else
    sleep(10);
    exit(0);
}

void scanning(char* aIp,char* aOption){
    char scan[25];
    strcpy(scan, "nmap ");
    strcat(scan, " -");
    strcat(scan, aOption);
    strcat(scan, " ");
    strcat(scan, aIp);
    printf("scanning\n");
    system(scan); 
    if(aOption=="A"){
    sleep(150);
    }else
    sleep(10);
}
