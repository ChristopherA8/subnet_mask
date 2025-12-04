using namespace std;

/**
 * Get IP Address
 * @return uint32_t of full padded IP Address
 */
uint32_t getUserIp();

/**
 * Get subnet mask
 * @return uint32_t of full padded subnet mask
 */
uint32_t getSubnetMask();

/**
 * Validate subnet mask format
 * @return bool
 */
bool validateSubnetMask(uint32_t mask);

/**
 * Returns shorthand for subnet mask
 * 
 * Examples: `/24` `/8` `/16` etc...
 * @return int
 */
int subnetMaskShorthand(uint32_t mask);

/**
 * Returns the network address of a given ip with submask
 * @return network address like (192.168.0.0)
 */
string networkAddressStr(uint32_t ip, uint32_t mask);

/**
 * Print errors and exit program
 * @param code int
 */
void endProgram(int code);

/**
 * ChatGPT made this
 * @param 32bit padded ip
 */
void printBinaryOctets(uint32_t ip);