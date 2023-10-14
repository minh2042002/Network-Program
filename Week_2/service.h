#ifndef SERVICE_H
#define SERVICE_H

void findIPAddressByDomainName(char *domainName);
void findDomainNameByIPAddress(char *ipAddress);
int is_valid_ipv4(const char *input);
int is_valid_domain(const char *input);

#endif