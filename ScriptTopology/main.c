#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {

    if(argc != 3 ){
        fprintf(stderr, "usage : %s subnetNumber numberOfDeviceOnSubnet", argv[0]);
        exit(1);
    }
    FILE *file;
    char filename[20];

    strcpy(filename, "subnet");
    strcat(filename, argv[1]);
    strcat(filename, ".sh");
    printf("%s", filename);
    file = fopen(filename, "w");



    if(file == NULL){
        fprintf(stderr, "Error opening file");
        exit(1);
    }

    fprintf(file, "fprintf \"");

    int number = atoi(argv[2]);
    printf("\n%s\n", argv[2]);
    printf("%d", number);
    //><
    for(int i = 0; i < number; i++){
        fprintf(file, "sudo ifconfig eth%d netmask 255.255.0.0\\n", i);
    }

    fclose(file);
    return 0;
}