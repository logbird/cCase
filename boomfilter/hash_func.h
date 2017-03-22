//djb2 hash
unsigned int djb_hash(const unsigned char *buf, int len);
//murmur2 hash
unsigned int murmur_hash(const unsigned char *buf, int len);
//crc16 hash
unsigned int crc16(const unsigned char *buf, int len);
