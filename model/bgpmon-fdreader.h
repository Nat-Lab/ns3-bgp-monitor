#ifndef BGPMON_FDR_H_
#define BGPMON_FDR_H_

#include "ns3/unix-fd-reader.h"
#include <stdlib.h>
#include <unistd.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <sys/un.h>

namespace ns3 {

class BGPMonitorFDReader : public FdReader {
    private:
    FdReader::Data DoRead (void);
};

}

#endif // BGPMON_FDR_H_