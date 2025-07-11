#include "common.h"

uint8_t simple_csum(uint8_t *buf, size_t len) {

	/* TODO 1.1: Implement the simple checksum algorithm */
	uint8_t sum = 0;

	for (int i = 0; i < len; i++) {
		sum += buf[i];
	}

	return sum % 256;
}

uint32_t crc32(uint8_t *buf, size_t len)
{
	/* unsigned char *buffer contine payload-ul, len este lungimea acestuia */
    /* Prin conventie crc-ul initial are toti bitii setati pe 1 */
    uint32_t crc = ~0; // 0xffffffff
    const uint32_t POLY = 0xEDB88320;

    /* Parcurgem fiecare byte din buffer */
    while(len--)
    {
        /* crc contine restul impartirii la fiecare etapa */
        /* nu ne intereseaza catul */
        /* adunam urmatorii 8 bytes din buffer */
        crc = crc ^ *buf++;
        for( int bit = 0; bit < 8; bit++ )
        {
            /* 10011 ) 11010110110000 = Bytes of payload
                =Poly   10011,,.,,....
                        -----,,.,,....
                         10011,.,,....  (operatia de xor cand primul bit e 1)
                         10011,.,,....
                         -----,.,,....
                          00001.,,....  (asta e noua valoare a lui crc) (crc >> 1) ^ POLY
            */
            if( crc & 1 )
                crc = (crc >> 1) ^ POLY;
            else
                /* 10011 ) 11010110110000 = Bytes of payload
                    =Poly   10011,,.,,....
                            -----,,.,,....
                             10011,.,,....
                             10011,.,,....
                             -----,.,,....
                              00001.,,....  primul bit e 0,
                              00000.,,....
                              -----.,,....
                               00010,,.... am facut shift la dreapta, pentru ca suntem pe **little endian**
                */
                crc = (crc >> 1);
        }
    }
    // Prin conventie, o sa facem flip la toti bitii
    crc = ~crc;
    return crc;
}
