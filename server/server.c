/* Skeleton code for Computer Networks 2022 @ LIACS */
#include <stdlib.h>
#include "asp.h"
#include "wave.h"


int main(int argc, char** argv) {
    // TODO: Parse command-line options 
    (void) argc;
    const char* filename = argv[1];

    // Open the WAVE file
    struct wave_file wave;
    if (wave_open(&wave, filename) < 0) {
        return EXIT_FAILURE;
    }

    // TODO: Read and send audio data
    asp_socket_info asi;
    asi.sockfd = create_socket();
    asi.local_addr = bind_address_to_socket(asi.sockfd, 1235);
    asi.local_addrlen = get_address_length(asi.local_addr);

    do{
        asi.remote_addr = receive_acknowledgemnt(asi.sockfd);
    }while(1);


    // Clean up
    wave_close(&wave);

    return EXIT_SUCCESS;
}
