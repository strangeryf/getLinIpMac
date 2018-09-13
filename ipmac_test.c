#include "ipmac.h"

int main (int argc, const char *argv[]) {
	char ipmac[MAX_HW_INFO_LEN]={0};
	getIpMac(ipmac);
	printf("%s\n", ipmac);
}
