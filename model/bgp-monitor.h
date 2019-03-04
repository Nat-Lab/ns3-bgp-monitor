/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef BGP_MONITOR_H
#define BGP_MONITOR_H

#include "bgpmon-fdreader.h"
#include "ns3/log.h"
#include "ns3/bgp-speaker.h"

#include <string.h>
//#include <sys/socket.h>
//#include <sys/un.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>
#include <cerrno>

#define BGPMON_ENDPOINT "/var/run/ns3-bgpmon.sock"

namespace ns3 {

class BGPMonitor {
	public:
	BGPMonitor(const std::string &m_in, const std::string &m_out);
	void Start (void);
	void AddSpeaker (Ptr<BGPSpeaker> s);

	private:
	void ReadCallback (uint8_t* buf, ssize_t len);
	std::vector<Ptr<BGPSpeaker>> m_speakers;
	Ptr<BGPMonitorFDReader> m_fdReader;
	int m_in_fd;
	int m_out_fd;
	std::string m_in;
	std::string m_out;	
};

}

#endif /* BGP_MONITOR_H */

