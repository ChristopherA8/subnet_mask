#include <iostream>
#include "main.hh"

int main() {

   uint32_t userIp = getUserIp();
   if (!userIp) endProgram(1);
      uint32_t subnetMask = getSubnetMask();
   if (!subnetMask || !validateSubnetMask(subnetMask)) endProgram(2);

   cout << "\n== User IP ========================\n";
   printBinaryOctets(userIp);
   cout << "== Subnet Mask ";
   printf("/%-2d ", subnetMaskShorthand(subnetMask));
   cout << "================\n";
   printBinaryOctets(subnetMask);
   cout << "== Network Address ================\n";
   cout << networkAddressStr(userIp, subnetMask);
   cout << "\n== Broadcast Address ==============\n";
   cout << broadcastAddressStr(userIp, subnetMask);
   cout << "\n===================================\n";

   return 0;
}

uint32_t getUserIp() {

   cout << "Enter IP address: ";

   string str;
   cin >> str;

   if (str.length() == 0) return 0;

   uint8_t octet1, octet2, octet3, octet4;
   octet1 = stoi(str.substr(0, str.find(".")));
   str = str.substr(str.find("."));
   octet2 = stoi(str.substr(1, str.find(".", 1) - 1));
   str = str.substr(str.find(".", 1));
   octet3 = stoi(str.substr(1, str.find(".", 1) - 1));
   str = str.substr(str.find(".", 1));
   octet4 = stoi(str.substr(1, str.find(".", 1) - 1));

   uint32_t ip = (octet1 << 24) | (octet2 << 16) | (octet3 << 8) | octet4;
   return ip;
}

uint32_t getSubnetMask() {

   cout << "Enter subnet mask (Ex. 255.255.252.0 or /24): ";

   string str;
   cin >> str;

   if (str.length() == 0) return 0;

   if (str.length() == 2) {
      uint8_t shorthand = stoi(str.substr(1,2));
      switch (shorthand) {
      case 1:
         return 2147483648u;
      case 2:
         return 3221225472u;
      case 3:
         return 3758096384u;
      case 4:
         return 4026531840u;
      case 5:
         return 4160749568u;
      case 6:
         return 4227858432u;
      case 7:
         return 4261412864u;
      case 8:
         return 4278190080u;
      case 9:
         return 4286578688u;
      default:
         return 0;
         break;
      }
   } else if (str.length() == 3) {
      uint8_t shorthand = stoi(str.substr(1,3));
      switch (shorthand) {
      case 10:
         return 4290772992u;
         break;
      case 11:
         return 0xFFE00000u;
      case 12:
         return 0xFFF00000u;
      case 13:
         return 0xFFF80000u;
      case 14:
         return 0xFFFC0000u;
      case 15:
         return 0xFFFE0000u;
      case 16:
         return 0xFFFF0000u;
      case 17:
         return 0xFFFF8000u;
      case 18:
         return 0xFFFFC000u;
      case 19:
         return 0xFFFFE000u;
      case 20:
         return 0xFFFFF000u;
      case 21:
         return 0xFFFFF800u;
      case 22:
         return 0xFFFFFC00u;
      case 23:
         return 0xFFFFFE00u;
      case 24:
         return 0xFFFFFF00u;
      case 25:
         return 0xFFFFFF80u;
      case 26:
         return 0xFFFFFFC0u;
      case 27:
         return 0xFFFFFFE0u;
      case 28:
         return 0xFFFFFFF0u;
      case 29:
         return 0xFFFFFFF8u;
      case 30:
         return 0xFFFFFFFCu;
      case 31:
         return 0xFFFFFFFEu;
      case 32:
         return 0xFFFFFFFFu;
      default:
         return 0;
         break;
      }
   } else {
      uint8_t octet1, octet2, octet3, octet4;
      octet1 = stoi(str.substr(0, str.find(".")));
      str = str.substr(str.find("."));
      octet2 = stoi(str.substr(1, str.find(".", 1) - 1));
      str = str.substr(str.find(".", 1));
      octet3 = stoi(str.substr(1, str.find(".", 1) - 1));
      str = str.substr(str.find(".", 1));
      octet4 = stoi(str.substr(1, str.find(".", 1) - 1));

      uint32_t mask = (octet1 << 24) | (octet2 << 16) | (octet3 << 8) | octet4;
      return mask;
   }
}

bool validateSubnetMask(uint32_t mask) {
   int flag = 0;
   for (int i = 3; i >= 0; i--) {
      uint8_t octet = (mask >> (i * 8)) & 0xFF;

      for (int b = 7; b >= 0; b--) {
         // If the previous bit has been flagged as zero and the current 
         // bit is 1 we have an invalid subnet mask bit sequence
         if (flag && (((octet >> b) & 1) == 1)) return false;
         if (((octet >> b) & 1) == 0) flag = 1;
      }
   }

   return true;
}

int subnetMaskShorthand(uint32_t mask) {
   int counter = 0;
   for (int i = 3; i >= 0; i--) {
      uint8_t octet = (mask >> (i * 8)) & 0xFF;

      for (int b = 7; b >= 0; b--) {
         // If the previous bit has been flagged as zero and the current 
         // bit is 1 we have an invalid subnet mask bit sequence
         if (((octet >> b) & 1) == 1) counter++;
      }
   }

   return counter;
}

string networkAddressStr(uint32_t ip, uint32_t mask) {
   uint32_t networkIp = ip & mask;
   return addressStr(networkIp);
}

string broadcastAddressStr(uint32_t ip, uint32_t mask) {
   uint32_t adr = ip | (mask ^ 0xFFFFFFFF);
   return addressStr(adr);
}

string addressStr(uint32_t adr) {
   return to_string((adr >> 24) & 0xFF) + "." +
         to_string((adr >> 16) & 0xFF) + "." +
         to_string((adr >> 8)  & 0xFF) + "." +
         to_string( adr        & 0xFF);
}

void endProgram(int code) {
   switch (code) {
      case 1: // IP Format Error
         printf("\nError: Wrong ip format (Ex. 192.168.1.252)\n");
         exit(1);
         break;
      case 2: // Subnet Mask Format Error
         printf("\nError: Wrong subnet mask format (Ex. 255.255.255.0)\n");
         exit(1);
         break;
      default:
         printf("\nFatal Error: Exiting program!\n");
         exit(1);
         break;
   }
}

void printBinaryOctets(uint32_t ip) {
   for (int i = 3; i >= 0; i--) {
      uint8_t octet = (ip >> (i * 8)) & 0xFF;

      for (int b = 7; b >= 0; b--) {
         printf("%d", (octet >> b) & 1);
      }

      if (i > 0) printf(".");
   }
   printf("\n");
}