#include <stdio.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0

uint16_t checksum_generic(uint16_t *addr, uint32_t count)
{
    register unsigned long sum = 0;

    for (sum = 0; count > 1; count -= 2) //while the length of bits left to check is >1, execute and remove 2 bits to count
        sum += *addr++; //
    if (count == 1)
        sum += (char)*addr;

    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);

    return ~sum;
}

uint16_t checksum_tcpudp(struct iphdr *iph, void *buff, uint16_t data_len, int len)
{
    const uint16_t *buf = buff;
    uint32_t ip_src = iph->saddr;
    uint32_t ip_dst = iph->daddr;
    uint32_t sum = 0;
    int length = len;

    while (len > 1)
    {
        sum += *buf;
        buf++;
        len -= 2;
    }

    if (len == 1)
        sum += *((uint8_t *) buf);

    sum += (ip_src >> 16) & 0xFFFF;
    sum += ip_src & 0xFFFF;
    sum += (ip_dst >> 16) & 0xFFFF;
    sum += ip_dst & 0xFFFF;
    sum += htons(iph->protocol);
    sum += data_len;

    while (sum >> 16)
        sum = (sum & 0xFFFF) + (sum >> 16);

    return ((uint16_t) (~sum));
}

int main() {

    char scanner_rawpkt[sizeof (struct iphdr) + sizeof (struct tcphdr)] = {0};
    int i, rsck;
    uint16_t source_port = 25001;
    struct iphdr *iph;
    struct tcphdr *tcph;

    iph = (struct iphdr *)scanner_rawpkt;
    tcph = (struct tcphdr *)(iph + 1);

    // Set up raw socket scanning and payload
    if ((rsck = socket(AF_INET, SOCK_RAW, IPPROTO_TCP)) == -1)
    {
        exit(0);
    }
    fcntl(rsck, F_SETFL, O_NONBLOCK | fcntl(rsck, F_GETFL, 0));
    i = 1;
    if (setsockopt(rsck, IPPROTO_IP, IP_HDRINCL, &i, sizeof (i)) != 0)
    {
        close(rsck);
        exit(0);
    }

    // Set up IPv4 header
    iph->ihl = 5; // Internet header length : length = 5x32 bits = 160bits - 20 bytes
    iph->version = 4; // IPv4
    iph->tot_len = htons(sizeof (struct iphdr) + sizeof (struct tcphdr)); //size of the packet
    iph->id = 4545; // set a random id to the packet
    iph->ttl = 64; // Time to live ~ 64 "jumps"
    iph->protocol = IPPROTO_TCP; //TCP protocol is used for the data of the packet

    // Set up TCP header
    tcph->dest = htons(23); // port dest 23
    tcph->source = source_port; // selected randomly line 101
    tcph->doff = 5; //data offset = 160 bits - 20 bytes
    tcph->window = 841; // Windows size random
    tcph->syn = TRUE; //SYN flag up


    struct sockaddr_in paddr = {0};
    //start generate packet
    iph->id = 55454; //generate a random 32bit int
    iph->saddr = 134326464; //192.168.1.8; C0 A8 01 08 remember little endian
    //iph->daddr = get_random_ip(); //generate a random ip - avoid invalid / dept of def / local and other addresses

    iph->daddr = 16777343; //127.0.0.1 remember little endian

    iph->check = 0;
    iph->check = checksum_generic((uint16_t *)iph, sizeof (struct iphdr)); //generate the checksum of the packet, check checksum.c

    if (i % 10 == 0)
    {
        tcph->dest = htons(2323);
    }
    else
    {
        tcph->dest = htons(23);
    }
    tcph->seq = iph->daddr; // same seq as ip - Mirai signature
    tcph->check = 0;
    tcph->check = checksum_tcpudp(iph, tcph, htons(sizeof (struct tcphdr)), sizeof (struct tcphdr)); // generate checksum
    // internet socket adress
    paddr.sin_family = AF_INET; //AF_INET for IPv4
    paddr.sin_addr.s_addr = iph->daddr; // socket is open to the dest
    paddr.sin_port = tcph->dest; // port 23
    //send the packet
            for(int i = 0; i < 85; i++)
    sendto(rsck, scanner_rawpkt, sizeof (scanner_rawpkt), MSG_NOSIGNAL, (struct sockaddr *)&paddr, sizeof (paddr));

}
