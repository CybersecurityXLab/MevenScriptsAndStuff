#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {

    if(argc != 3 ){ //check if there is a correct number of argv
        fprintf(stderr, "usage : %s subnetNumber numberOfDeviceOnSubnet\n", argv[0]);
        exit(1);
    }

    if(atoi(argv[1]) < 2 ){ // avoid negative network
        fprintf(stderr, "please select a positive integer - subnet 1 is reserved for the monitor\n");
        exit(1);
    }

    FILE *file;
    char filename[20];

    //create the shell file subnetX.sh
    strcpy(filename, "subnet");
    strcat(filename, argv[1]);
    strcat(filename, ".sh");
    file = fopen(filename, "w");



    if(file == NULL){ //check if the file is opened
        fprintf(stderr, "Error opening file");
        exit(1);
    }

    int arg1 = atoi(argv[1]);
    int arg2 = atoi(argv[2]);

    fprintf(file, "printf \""); //start writing the commands needed for the file executed on the ovs

    //ifconfig network on subnetX.sh + ifconfig devices on output lines
    fprintf(file, "sudo ifconfig eth1 10.10.%d.1 netmask 255.255.0.0\\n", arg1);
    printf("please enter the followings commands on the corresponding device of the subnet : \n");
    for(int i = 2; i <= arg2+1; i++){
        fprintf(file, "sudo ifconfig eth%d 10.10.%d.%d netmask 255.255.0.0\\n", i, arg1, i*2-1); //config network
        printf("device #%d : sudo ifconfig eth1 10.10.%d.%d netmask 255.255.0.0\n", i-1, arg1, i*2-2); // config device

    }

    //setup for the bridge
    fprintf(file, "sudo ovs-vsctl add-br br0\\n"
                  "sudo ovs-vsctl set-fail-mode br0 standalone\\n");

    fprintf(file,"sudo ovs-vsctl add-port br0 eth1\\n");
    for(int i = 1; i <= arg2; i++){
        fprintf(file, "sudo ovs-vsctl add-port br0 eth%d\\n", i);
    }


    //create the bridge towards monitor's network
    fprintf(file, "sudo ovs-vsctl -- set Bridge br0 mirrors=@m -- ");
    for(int i = 1; i <= arg2+1; i++){
        fprintf(file, "--id=@eth%d get Port eth%d ", i, i);
    }

    fprintf(file, "-- --id=@m create Mirror name=mymirrorsub%d select-dst-port=", arg1);

    for(int i = 2; i <= arg2+1; i++) {
        if(i-1 == arg2){
            fprintf(file, "@eth%d", i);
        }else{
            fprintf(file, "@eth%d,", i);
        }
    }

    fprintf(file, " select-src-port=");

    for(int i = 2; i-1 <= arg2; i++) {
        if(i-1 == arg2){
            fprintf(file, "@eth%d", i);
        }else{
            fprintf(file, "@eth%d,", i);
        }
    }

    fprintf(file, " output-port=@eth1\""); //close command

    fclose(file);//close file
    return 0;
}
