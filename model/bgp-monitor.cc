/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "bgp-monitor.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("BGPMonitor");

BGPMonitor::BGPMonitor (const std::string &m_in, const std::string &m_out) {
    m_in_fd = m_out_fd = -1;
    this->m_in = m_in;
    this->m_out = m_out;
}

void BGPMonitor::AddSpeaker (Ptr<BGPSpeaker> s) {
    m_speakers.push_back(s);
}

void BGPMonitor::Start(void) {
    /*struct sockaddr_un saddr;
    memset(&saddr, 0, sizeof(saddr));
    strcpy(saddr.sun_path, BGPMON_ENDPOINT);
    saddr.sun_family = AF_UNIX;

    std::remove(BGPMON_ENDPOINT);
    m_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    NS_ABORT_MSG_IF (m_fd < 0, "socket() failed: " << m_fd);
    int bs = bind(m_fd, (struct sockaddr *) &saddr, sizeof(saddr));
    NS_ABORT_MSG_IF (bs < 0, "bind() failed: " << bs);*/

    mkfifo(m_in.c_str(), 0660);
    mkfifo(m_out.c_str(), 0660);
    m_in_fd = open(m_in.c_str(), O_RDWR);
    m_out_fd = open(m_out.c_str(), O_RDWR);

    m_fdReader = Create<BGPMonitorFDReader> ();
    m_fdReader->Start(m_in_fd, MakeCallback (&BGPMonitor::ReadCallback, this));
}

void BGPMonitor::ReadCallback (uint8_t* buf, ssize_t len) {
    std::ostringstream outstr;
    for (auto speaker : m_speakers) {
        outstr << speaker->getAsn() << "|";
        
        auto peers = speaker->getPeers();
        for (auto peer : *peers) {
            outstr << peer->asn << ";";
        }

        outstr << "|";

        auto routes = speaker->getRoutes();
        for (auto route : *routes) {
            outstr << route->getPrefix() << "/" << (int) route->getLength() << ",";
            auto path = route->getAsPath();
            for (auto as : *path) outstr << as << " ";
            outstr << "," << route->next_hop << "," << (int) route->local << ";";
        }

        outstr << std::endl;
    }

    std::string out = outstr.str();
    size_t ret_len = out.length();
    ssize_t write_len = write(m_out_fd, out.data(), ret_len);
    NS_ABORT_MSG_IF (write_len < 0, "write() failed: " << write_len << "(" << std::strerror(errno) << ")");
    NS_ABORT_MSG_IF (ret_len != (size_t) write_len, "write() failed: ret_len(" << ret_len << ") != write_len(" << write_len << ")");
}

}
