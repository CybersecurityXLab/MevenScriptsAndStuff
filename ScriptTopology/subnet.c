#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    if(argc != 3 ){ //check if there is a correct number of argv
        fprintf(stderr, "usage : %s subnetNumber numberOfDeviceOnSubnet\n", argv[0]);
        exit(1);
    }

    int arg1 = atoi(argv[1]);
    int arg2 = atoi(argv[2]);

    if(arg1 == 1 && arg2 != 1){
        fprintf(stderr, "subnet 1 is reserved for 1 device : the monitor\n");
        exit(1);
    }

    FILE *file;
    char filename[20] = "subnet1.sh";

    //create the shell file subnetX.sh
    strcpy(filename, "subnet");
    strcat(filename, argv[1]);
    strcat(filename, ".sh");
    file = fopen(filename, "w");

    if(file == NULL){ //check if the file is opened
        fprintf(stderr, "Error opening file");
        exit(1);
    }


    if (arg1 == 1) {
        printf("Remember to run sudo ifconfig eth1 10.10.1.1 netmask 255.255.255.0 on the monitor !\n");
        fprintf(file, "#!/bin/sh\n"
                      "sudo ifconfig eth1 10.10.1.2 netmask 255.255.255.0\n"
                      "sudo ifconfig eth2 10.10.2.1 netmask 255.255.255.0\n");

    }else {
        //config network
        fprintf(file, "#!/bin/sh\n"
                      "sudo ifconfig eth1 10.10.%d.1 netmask 255.255.255.0\n"
                      "sudo ifconfig eth2 10.10.2.%d netmask 255.255.255.0\n", arg1 + 1, arg1);
    }



    //setup for the bridge
    fprintf(file, "sudo ovs-vsctl add-br br0\n"
                  "sudo ovs-vsctl set-fail-mode br0 standalone\n"
                  "sudo ovs-vsctl add-port br0 eth1\n"
                  "sudo ovs-vsctl add-port br0 eth2\n");


    //create the bridge towards monitor
    fprintf(file, "sudo ovs-vsctl -- set Bridge br0 mirrors=@m "
                  "-- --id=@eth1 get Port eth1 "
                  "-- --id=@eth2 get Port eth2 ");
    if(arg1 ==1){
        fprintf(file, "-- --id=@m create Mirror name=mymirrorsub1 select-dst-port=@eth2 "
                      "select-src-port=@eth2"
                      "output-port=@eth1\n"); //script finished
    }else{
        fprintf(file, "-- --id=@m create Mirror name=mymirrorsub1 select-dst-port=@eth1 "
                      "select-src-port=@eth1"
                      "output-port=@eth2\n"); //script finished
    }


    fclose(file);//close file
    return 0;
}