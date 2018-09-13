#include "ipmac.h"

void getIpMac(char *ipmac) {
	struct ifaddrs *ifAddrStruct = NULL;
	struct ifaddrs *ifa = NULL;
	void *tmpAddrPtr = NULL;

	getifaddrs(&ifAddrStruct);
	
	struct ifreq ifr;

	int cur_len = 0;
	int ipv4_num = 0;
	int ipv6_num = 0;
	
	for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
		cur_len = strlen(ipmac);
		if (!ifa->ifa_addr) {
			continue;
		}
		
		// skip loop back inteface
		if (strncmp(ifa->ifa_name, "lo", IFNAMSIZ)==0) {
			continue;
		}
		
		if (ifa->ifa_addr->sa_family == AF_INET && ipv4_num < 1) { // IPv4 Address
			tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
			char addressBuffer[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
			snprintf(ipmac+cur_len, MAX_HW_INFO_LEN, "%s IPv4: %s, ", ifa->ifa_name, addressBuffer);
			
			cur_len = strlen(ipmac);
			
			// get MAC address
			int fd = socket(AF_INET, SOCK_DGRAM, 0);
			ifr.ifr_addr.sa_family = AF_INET;
			strncpy((char *)ifr.ifr_name, ifa->ifa_name, IFNAMSIZ-1);
			ioctl(fd, SIOCGIFHWADDR, &ifr);
			close(fd);
			
			byte *mac = (byte *)ifr.ifr_hwaddr.sa_data;
			snprintf(ipmac+cur_len, 32, "MAC: %.2X:%.2X:%.2X:%.2X:%.2X:%.2X; ", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
			
			ipv4_num++;
		} else if (ifa->ifa_addr->sa_family == AF_INET6 && ipv6_num < 1) { // IPv6 Address
			tmpAddrPtr=&((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
			char addressBuffer[INET6_ADDRSTRLEN];
			inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
			snprintf(ipmac+cur_len, MAX_HW_INFO_LEN, "%s IPv6: %s, ", ifa->ifa_name, addressBuffer);
			ipv6_num++;
		}
	}
	
	// remove trailing comma
	cur_len = strlen(ipmac);
	ipmac[cur_len-2] = 0;
	
	if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);
}
