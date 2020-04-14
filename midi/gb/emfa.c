#include	<stdio.h>
#include	<string.h>

int read();
void* malloc();
void* memmem();

void const* null = 0;
const int bufferSize = 10000000;
const char notFoundMessageTemplate[] = "not found(%s)\n";

//
// cmd < gbLoopFile[.aif] > out.mid
//
int main() {

	unsigned char const* buffer = malloc(bufferSize);
	const int l = read(0, buffer, bufferSize);

	char const* startMarker = "MThd";
	unsigned char const* startMarkerPtr = memmem(
		buffer,
		bufferSize,
		startMarker,
		strlen(startMarker)
	);
	if (startMarkerPtr == null) {
		fprintf(stderr, notFoundMessageTemplate, startMarker);
		return 1;
	}

	char const* endMarker = "CHS";
	unsigned char const* endMarkerPtr = memmem(
		startMarkerPtr,
		bufferSize - (startMarkerPtr - buffer), 
		endMarker, 
		strlen(endMarker)
	);
	if (endMarkerPtr == null) {
		fprintf(stderr, notFoundMessageTemplate, endMarker);
		return 2;
	}

	for (
		unsigned char const* ptr = startMarkerPtr;
		ptr <= endMarkerPtr;
		ptr++
	) {
		putchar(*ptr);
	}

}

