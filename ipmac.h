#ifndef ipmac__h
#define ipmac__h

#ifdef __cplusplus
extern "C"
{
#endif

#include <ifaddrs.h>
#include <string.h> 
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <unistd.h>

// keep two interfaces: one IPv4, one IPv6
#define MAX_HW_INFO_LEN (IFNAMSIZ*2 + INET_ADDRSTRLEN + INET6_ADDRSTRLEN + 9*2 + 32)
typedef unsigned char byte;

extern void getIpMac(char *ipmac);

#ifdef __cplusplus
}
#endif

#endif
