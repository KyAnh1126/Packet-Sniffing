#include <iostream>
#include "network_interface.h"
#include "display_network_interfaces.h"
#include "display_packet.h"

#include "packet.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <termios.h>

#include <sys/ipc.h>
#include <sys/shm.h>

#include <cstring>

#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/ipv6.h>
#include <linux/tcp.h>
#include <linux/udp.h>

using namespace std;

#define PKID_SZ 10

char fifo[] = "my_fifo";

void* get_packet_detail_routine(void* tid) {
    while(1) {
        int fd;

        // cout << "opening..\n";
        fd = open(fifo, O_RDONLY);
        // cout << "opened, fd: " << fd << '\n';
        if(fd < 0) {
            perror("case 2: open fifo for read");
            exit(EXIT_FAILURE);
        }

        char buf_id[PKID_SZ];
        int nbytes_read;
        if((nbytes_read = read(fd, buf_id, PKID_SZ)) == -1) {
            perror("case 2: read from fifo");
            exit(EXIT_FAILURE);
        }
        close(fd);
        
        int id = atoi(buf_id);   
        --id;

        cout << "id: " << id << '\n';

        if(id + 1 > packets.size()) {
            fd = open(fifo, O_WRONLY);
            if(fd < 0) {
                perror("case 2: open fifo for write");
                exit(EXIT_FAILURE);
            }

            int nbytes_write;
            if((nbytes_write = write(fd, "-1", sizeof("-1"))) == -1) {
                perror("case 2: write to fifo");
                close(fd);
                exit(EXIT_FAILURE);
            }
            close(fd);
        }

        else {
            key_t key = ftok("shmfile", 65);
            int shmid = shmget(key, BUF_SZ, 0666 | IPC_CREAT);

            if(shmid < 0) {
                perror("shmget");
                exit(EXIT_FAILURE);
            }

            // cout << "shmid: " << shmid << '\n';

            char* sm = (char*) shmat(shmid, NULL, 0);

            packet cur = packets[id];
            memcpy(sm, cur.buffer, cur.total_length);

            // cout << "opening..\n";
            fd = open(fifo, O_WRONLY);
            // cout << "opened, fd: " << fd << '\n';
            if(fd < 0) {
                perror("case 2: open fifo for write");
                exit(EXIT_FAILURE);
            }

            int nbytes_write;
            if((nbytes_write = write(fd, sm, cur.total_length)) == -1) {
                perror("case 2: write to fifo");
                close(fd);
                exit(EXIT_FAILURE);
            }
            close(fd);

            sleep(1);

            shmdt(sm);
            shmctl(shmid, IPC_RMID, NULL);
        }
    }
    return (void*)0;
}

void* get_packets_routine(void* tid) {
    get_packets();
    return (void*)0;
}

int main() { 
    mkfifo(fifo, 0777);
    int n = -1;
    cout << "Welcome to my packet sniffing!\n";
    cout << "Enter your choice:\n";
    cout << "1. Get information of your network interfaces\n";
    cout << "2. Capture your packet\n";
    cout << "3. Get detail information of a packet\n";
    cout << "4. Exit\n";

    while(n < 1 || n > 4) {
        cout << "Your choice: ";
        cin >> n;
        if(n < 1 || n > 4) cout << "Invalid choice\n\n";
        else {
            switch(n) {
                case 1: {
                    get_network_interfaces();
                    display_network_interfaces();
                    break;
                }
                case 2: {
                    pthread_t get_packets_t;
                    pthread_t get_packet_detail_t;

                    pthread_create(&get_packets_t, NULL, get_packets_routine, (void*)1);
                    pthread_create(&get_packet_detail_t, NULL, get_packet_detail_routine, (void*)2);

                    pthread_join(get_packets_t, NULL);
                    pthread_join(get_packet_detail_t, NULL);
                    break;
                }
                case 3: {
                    char id[PKID_SZ];
                    cout << "Enter packet id: ";
                    cin >> id;

                    int fd;
                    // cout << "opening..\n";
                    fd = open(fifo, O_WRONLY);
                    // cout << "opened, fd: " << fd << '\n';
                    int nbytes_write;
                    if((nbytes_write = write(fd, id, PKID_SZ)) == -1) {
                        perror("case 3: write to fifo");
                        exit(EXIT_FAILURE);
                    }

                    close(fd);

                    // cout << "opening..\n";
                    fd = open(fifo, O_RDONLY);
                    // cout << "opened, fd: " << fd << '\n';
                    char* buffer = new char[BUF_SZ];

                    int nbytes_read;
                    if((nbytes_read = read(fd, buffer, BUF_SZ)) == -1) {
                        perror("case 3: read from fifo");
                        exit(EXIT_FAILURE);
                    }

                    if(strncasecmp(buffer, "-1", 2) == 0) {
                        cout << "\nInvalid packet id!\n";
                        break;
                    }

                    packet recv_packet;
                    get_packet(buffer, &recv_packet, atoi(id), nbytes_read);

                    cout << "\n\n***********************************PACKET INFO***********************************\n";
                    display_packet_general(&recv_packet);
                    display_packet_detail_pk(&recv_packet);

                    close(fd);

                    break;
                }
                case 4: {
                    exit(EXIT_SUCCESS);
                }
            }
        }
    }
}