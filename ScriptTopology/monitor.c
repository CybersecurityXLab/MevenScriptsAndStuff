#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

	if(argc != 2 ){ //check if there is a correct number of argv
        fprintf(stderr, "usage : %s numberOfSubnets \n", argv[0]);
        exit(1);
    }

    int arg1 = atoi(argv[1]);
    FILE *file;
    char filename[20] = "subnet1.sh";

    //create the shell file subnet1.sh
    file = fopen(filename, "w");

    if(file == NULL){ //check if the file is opened
        fprintf(stderr, "Error opening file");
        exit(1);
    }

    fprintf(file, "printf \"sudo ifconfig eth1 10.10.1.1 netmask 255.255.0.0\\n");

    for(int i = 1; i <= arg1; i++){
        fprintf(file, "sudo ifconfig eth%d 10.10.%d.2 netmask 255.255.0.0\\n", i+1, i+1); //config network
    }

    //setup for the bridge
    fprintf(file, "sudo ovs-vsctl add-br br0\\n"
                  "sudo ovs-vsctl set-fail-mode br0 standalone\\n");
    fprintf(file,"sudo ovs-vsctl add-port br0 eth1\\n");

    for(int i = 0; i <= arg1; i++){
        fprintf(file, "sudo ovs-vsctl add-port br0 eth%d\\n", i+1);
    }

    //create the bridge towards monitor
    fprintf(file, "sudo ovs-vsctl -- set Bridge br0 mirrors=@m -- ");
    for(int i = 0; i <= arg1; i++){
        fprintf(file, "--id=@eth%d get Port eth%d ", i+1, i+1);
    }

    fprintf(file, "-- --id=@m create Mirror name=mymirrorsub1 select-dst-port=");

    for(int i = 1; i <= arg1; i++) {
        if(i == arg1){
            fprintf(file, "@eth%d", i+1);
        }else{
            fprintf(file, "@eth%d,", i+1);
        }
    }

    fprintf(file, " select-src-port=");

    for(int i = 1; i <= arg1; i++) {
        if(i == arg1){
            fprintf(file, "@eth%d", i+1);
        }else{
            fprintf(file, "@eth%d,", i+1);
        }
    }

    fprintf(file, " output-port=@eth1\""); //close command

    fclose(file);//close file
    return 0;
}