#include "ush.h"

unsigned long mx_hex_to_nbr(const char *hex) {
	int length = 0;
	unsigned long number = 0;

	if (hex != NULL) {
		for (; hex[length];) {
			length++;
		}
	}
	else {
		return number;
	}
	
	unsigned long base = 1;

	for (int i = 0; i <= length; i++) {
		if (hex[length - i] >= '0' && hex[length - i] <= '9') {
			number = number + (hex[length - i] - 48) * base;
			base = base * 16;
		}
		if (hex[length - i] >= 'A' && hex[length - i] <= 'F') {
			number = number + (hex[length - i] - 55) * base;
			base = base * 16;
		}
		if (hex[length - i] >= 'a' && hex[length - i] <= 'f') {
			number = number + (hex[length - i] - 87) * base;
			base = base * 16;
		}
	}
	
	return number;
}
