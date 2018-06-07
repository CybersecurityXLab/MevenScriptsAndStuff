//
// Created by root on 6/6/18.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    if (argc != 3) { //check if there is a correct number of argv
        fprintf(stderr, "usage : %s numberOfSubnet numberOfDevicePerSubnet\n"
                        "subnet1 is used for the monitor", argv[0]);
        exit(1);
    }

    int subnets = atoi(argv[1]);
    int devices = atoi(argv[2]);

    FILE *file;
    //char filename[20] = "rspec.xml";

    file = fopen("rspec.xml", "w");

    if (file == NULL) { //check if the file is opened
        fprintf(stderr, "Error opening file");
        exit(1);
    }

    //monitor
    fprintf(file, "<rspec xmlns=\"http://www.geni.net/resources/rspec/3\" xmlns:emulab=\"http://www.protogeni.net/resources/rspec/ext/emulab/1\" xmlns:tour=\"http://www.protogeni.net/resources/rspec/ext/apt-tour/1\" xmlns:jacks=\"http://www.protogeni.net/resources/rspec/ext/jacks/1\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://www.geni.net/resources/rspec/3    http://www.geni.net/resources/rspec/3/request.xsd\" type=\"request\">\n"
                  "<node xmlns=\"http://www.geni.net/resources/rspec/3\" client_id=\"Monitor\">\n"
                  "<icon xmlns=\"http://www.protogeni.net/resources/rspec/ext/jacks/1\" url=\"https://portal.geni.net/images/Xen-VM.svg\"/>\n"
                  "<site xmlns=\"http://www.protogeni.net/resources/rspec/ext/jacks/1\" id=\"Site 1\"/>\n"
                  "<sliver_type xmlns=\"http://www.geni.net/resources/rspec/3\" name=\"emulab-xen\">\n"
                  "<disk_image xmlns=\"http://www.geni.net/resources/rspec/3\" name=\"urn:publicid:IDN+emulab.net+image+emulab-ops:UBUNTU16-64-STD\"/>\n"
                  "</sliver_type>\n"
                  "<services xmlns=\"http://www.geni.net/resources/rspec/3\">\n"
                  "</services>\n"
                  "<interface xmlns=\"http://www.geni.net/resources/rspec/3\" client_id=\"interface-0\">\n"
                  "<ip xmlns=\"http://www.geni.net/resources/rspec/3\" address=\"10.10.1.1\" type=\"ipv4\" netmask=\"255.255.255.0\"/>\n"
                  "</interface>\n"
                  "</node>\n"
                  //backbone
                  "<node xmlns=\"http://www.geni.net/resources/rspec/3\" client_id=\"Backbone\">\n"
                  "<icon xmlns=\"http://www.protogeni.net/resources/rspec/ext/jacks/1\" url=\"https://portal.geni.net/images/router.svg\"/>\n"
                  "<site xmlns=\"http://www.protogeni.net/resources/rspec/ext/jacks/1\" id=\"Site 1\"/>\n"
                  "<sliver_type xmlns=\"http://www.geni.net/resources/rspec/3\" name=\"emulab-xen\">\n"
                  "<disk_image xmlns=\"http://www.geni.net/resources/rspec/3\" name=\"urn:publicid:IDN+emulab.net+image+emulab-ops:UBUNTU14-OVS2.31\"/>\n"
                  "</sliver_type>\n"
                  "<services xmlns=\"http://www.geni.net/resources/rspec/3\">\n"
                  "<execute xmlns=\"http://www.geni.net/resources/rspec/3\" command=\"wget\" shell=\"/bin/sh\"/>\n"
                  "<execute xmlns=\"http://www.geni.net/resources/rspec/3\" command=\"chmod 777 bridge.sh\" shell=\"/bin/sh\"/>\n"
                  "<execute xmlns=\"http://www.geni.net/resources/rspec/3\" command=\"./bridge.sh 1 %d\" shell=\"/bin/sh\"/>\n",
            subnets);
    fprintf(file, "</services>\n"
                  "<interface xmlns=\"http://www.geni.net/resources/rspec/3\" client_id=\"interface-1\">\n"
                  "<ip xmlns=\"http://www.geni.net/resources/rspec/3\" address=\"10.10.1.2\" type=\"ipv4\" netmask=\"255.255.255.0\"/>\n"
                  "</interface>\n");

    //interface to subnets
    for(int i = 2; i <= subnets; i++){
        fprintf(file, "<interface xmlns=\"http://www.geni.net/resources/rspec/3\" client_id=\"interface-%d\">\n",
                i);
        fprintf(file, "<ip xmlns=\"http://www.geni.net/resources/rspec/3\" address=\"10.10.2.%d\" type=\"ipv4\" netmask=\"255.255.255.0\"/>\n",
                i * 2 - 3);
        fprintf(file, "</interface>\n");
    }

    fprintf(file,"</node>\n");

    int interfaceNb = subnets*2;
    for(int i = 1; i < subnets; i++){//subnets
        fprintf(file, "<node xmlns=\"http://www.geni.net/resources/rspec/3\" client_id=\"Subnet%d\">\n",
                i + 1);
        fprintf(file, "<icon xmlns=\"http://www.protogeni.net/resources/rspec/ext/jacks/1\" url=\"https://portal.geni.net/images/router.svg\"/>\n"
                      "<site xmlns=\"http://www.protogeni.net/resources/rspec/ext/jacks/1\" id=\"Site 1\"/>\n"
                      "<sliver_type xmlns=\"http://www.geni.net/resources/rspec/3\" name=\"emulab-xen\">\n"
                      "<disk_image xmlns=\"http://www.geni.net/resources/rspec/3\" name=\"urn:publicid:IDN+emulab.net+image+emulab-ops:UBUNTU14-OVS2.31\"/>\n"
                      "</sliver_type>\n"
                      "<services xmlns=\"http://www.geni.net/resources/rspec/3\">\n"
                      "<execute xmlns=\"http://www.geni.net/resources/rspec/3\" command=\"wget\" shell=\"/bin/sh\"/>\n"
                      "<execute xmlns=\"http://www.geni.net/resources/rspec/3\" command=\"chmod 777 bridge.sh\" shell=\"/bin/sh\"/>\n"
                      "<execute xmlns=\"http://www.geni.net/resources/rspec/3\" command=\"./bridge.sh 1\" shell=\"/bin/sh\"/>\n"
                      "</services>\n"
                      //interface to backbone
                      "<interface xmlns=\"http://www.geni.net/resources/rspec/3\" client_id=\"interface-%d\">\n",
                subnets+i);
        fprintf(file,
                "<ip xmlns=\"http://www.geni.net/resources/rspec/3\" address=\"10.10.2.%d\" type=\"ipv4\" netmask=\"255.255.255.0\"/>\n",
                i*2);
        fprintf(file, "</interface>\n");

        for(int j = 1; j <= devices; j++) {//interface to devices
            fprintf(file, "<interface xmlns=\"http://www.geni.net/resources/rspec/3\" client_id=\"interface-%d\">\n",
                    interfaceNb);
                    interfaceNb += 2;
            fprintf(file,
                    "<ip xmlns=\"http://www.geni.net/resources/rspec/3\" address=\"10.10.%d.%d\" type=\"ipv4\" netmask=\"255.255.255.0\"/>\n",
                    i*2+1, (j) * 2 - 1);
            fprintf(file, "</interface>\n");
        }

        fprintf(file, "</node>\n");
    }

    //devices
    interfaceNb = subnets*2;
    for(int i = 1; i < subnets; i++) {
        for(int j = 1; j <= devices; j++) {

            fprintf(file, "<node xmlns=\"http://www.geni.net/resources/rspec/3\" client_id=\"Device%d.%d\">\n",
                    i+1,j);
            fprintf(file, "<icon xmlns=\"http://www.protogeni.net/resources/rspec/ext/jacks/1\" url=\"https://portal.geni.net/images/Xen-VM.svg\"/>\n"
                    "<site xmlns=\"http://www.protogeni.net/resources/rspec/ext/jacks/1\" id=\"Site 1\"/>\n"
                    "<sliver_type xmlns=\"http://www.geni.net/resources/rspec/3\" name=\"emulab-xen\">\n"
                    "<disk_image xmlns=\"http://www.geni.net/resources/rspec/3\" name=\"urn:publicid:IDN+emulab.net+image+emulab-ops:UBUNTU16-64-STD\"/>\n"
                    "</sliver_type>\n"
                    "<services xmlns=\"http://www.geni.net/resources/rspec/3\">\n"
                    "</services>\n");
            //interface to subnet
            fprintf(file, "<interface xmlns=\"http://www.geni.net/resources/rspec/3\" client_id=\"interface-%d\">\n",
                    interfaceNb+1);
            interfaceNb+=2;
            fprintf(file, "<ip xmlns=\"http://www.geni.net/resources/rspec/3\" address=\"10.10.%d.%d\" type=\"ipv4\" netmask=\"255.255.255.0\"/>\n"
                    "</interface>\n"
                    "</node>\n"
                    , i*2+1, j*2);
        }
    }

    //link monitor backbone
    fprintf(file, "<link xmlns=\"http://www.geni.net/resources/rspec/3\" client_id=\"link-0\">\n"
                  "<interface_ref xmlns=\"http://www.geni.net/resources/rspec/3\" client_id=\"interface-0\"/>\n"
                  "<interface_ref xmlns=\"http://www.geni.net/resources/rspec/3\" client_id=\"interface-1\"/>\n"
                  "</link>\n");

    //link subnet to monitor
    for(int i = 1; i < subnets; i++) {
        fprintf(file, "<link xmlns=\"http://www.geni.net/resources/rspec/3\" client_id=\"link-%d\">\n",
                i);
        fprintf(file, "<interface_ref xmlns=\"http://www.geni.net/resources/rspec/3\" client_id=\"interface-%d\"/>\n",
                i+1);
        fprintf(file, "<interface_ref xmlns=\"http://www.geni.net/resources/rspec/3\" client_id=\"interface-%d\"/>\n",
                subnets+i);
        fprintf(file, "<site xmlns=\"http://www.protogeni.net/resources/rspec/ext/jacks/1\" id=\"undefined\"/>\n"
                      "<link_attribute xmlns=\"http://www.protogeni.net/resources/rspec/ext/emulab/1\" key=\"nomac_learning\" value=\"yep\"/>\n"
                      "</link>\n");
    }


    for(int i = subnets; i < (subnets-1)*devices+subnets; i++) { // link device to subnet
            fprintf(file, "<link xmlns=\"http://www.geni.net/resources/rspec/3\" client_id=\"link-%d\">\n",
                    i);
            fprintf(file, "<interface_ref xmlns=\"http://www.geni.net/resources/rspec/3\" client_id=\"interface-%d\"/>\n",
                    i*2);
            fprintf(file, "<interface_ref xmlns=\"http://www.geni.net/resources/rspec/3\" client_id=\"interface-%d\"/>\n",
                    i*2+1);
            fprintf(file, "<site xmlns=\"http://www.protogeni.net/resources/rspec/ext/jacks/1\" id=\"undefined\"/>\n"
                          "<link_attribute xmlns=\"http://www.protogeni.net/resources/rspec/ext/emulab/1\" key=\"nomac_learning\" value=\"yep\"/>\n"
                          "</link>\n");
        }




    fprintf(file,"</rspec>");
    fclose(file);
    return 0;
}

