#include "bgpmon-fdreader.h"

namespace ns3 {

FdReader::Data BGPMonitorFDReader::DoRead (void) {
    uint32_t len = 65536;
    uint8_t *buf = (uint8_t *) malloc (len);
    ssize_t read_len = read (m_fd, buf, len);

    /*socklen_t size = sizeof(sizeof(struct sockaddr_un));
    struct sockaddr_un *saddr = (struct sockaddr_un *) malloc(size);
    
    ssize_t read_len = recvfrom(m_fd, buf, len, 0, (sockaddr *) saddr, &size);
    std::cout << "doread end" << std::endl;
    std::cout << "peer: " << saddr->sun_path << std::endl;*/

    delete buf;
    return FdReader::Data (NULL, read_len); // we don't care
}

}