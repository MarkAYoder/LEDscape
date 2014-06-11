/** \file
 * Test the ledscape library by pulsing RGB on the first three LEDS.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <inttypes.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include "ledscape.h"

static void ledscape_fill_color(
	ledscape_frame_t * const frame,
	const unsigned num_pixels,
	const uint8_t r,
	const uint8_t g,
	const uint8_t b
)
{
	for (unsigned i = 0 ; i < num_pixels ; i++) {
		for (unsigned strip = 0 ; strip < LEDSCAPE_NUM_STRIPS ; strip++) {
			ledscape_set_color(frame, strip, i, r, g, b);
		}
	}
}

int main (int argc, char *argv[])
{
	const int num_pixels = 64; // 176;
	ledscape_t * const leds = ledscape_init(num_pixels);

	uint8_t rgb[3] = {0, 0, 0};
	if(argc == 4) {
	    for(int i=0; i<3; i++) {
	        rgb[i] = atoi(argv[i+1]);
	    }
	}

	unsigned frame_num = 0;

	ledscape_frame_t * const frame = ledscape_frame(leds, frame_num);

	ledscape_fill_color(
		frame,
		num_pixels,
		rgb[0],
		rgb[1],
		rgb[2]
	);

	ledscape_draw(leds, frame_num);

	return EXIT_SUCCESS;
}
