#include <stdio.h>
#include <ifaddrs.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

int getifaddrs_perf()
{
        struct ifaddrs *ifaddr, *ifa;
        int n;

        if (getifaddrs(&ifaddr) == -1) {
                perror("getifaddrs");
                return 1;
        }

        /* touch the data */
        for (ifa = ifaddr, n = 0; ifa != NULL; ifa = ifa->ifa_next, n++) {
                if (ifa->ifa_addr == NULL)
                        continue;
                if (!ifa->ifa_addr->sa_family)
                        continue;
        }

        freeifaddrs(ifaddr);

	return 0;
}

int main(void)
{
	getifaddrs_perf();
	return 0;
}
