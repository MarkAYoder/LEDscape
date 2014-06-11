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

int main (void)
{
	const int num_pixels = 64; // 176;
	ledscape_t * const leds = ledscape_init(num_pixels);
	time_t last_time = time(NULL);
	unsigned last_i = 0;

	uint8_t rgb[3] = {4, 4, 4};

	unsigned i = 0;


	const unsigned report_interval = 1;
	unsigned last_report = 0;
	unsigned long delta_sum = 0;
	unsigned frames = 0;

		// Alternate frame buffers on each draw command
		const unsigned frame_num = i++ % 2;

		struct timeval start_tv, stop_tv, delta_tv;
		gettimeofday(&start_tv, NULL);
		ledscape_frame_t * const frame = ledscape_frame(leds, frame_num);

		ledscape_fill_color(
			frame,
			num_pixels,
			rgb[0],
			rgb[1],
			rgb[2]
		);

		// const uint32_t response = ledscape_wait(leds);
		ledscape_draw(leds, frame_num);

		gettimeofday(&stop_tv, NULL);
		timersub(&stop_tv, &start_tv, &delta_tv);

		frames++;
		delta_sum += delta_tv.tv_usec;
		if (stop_tv.tv_sec - last_report < report_interval)
			// continue;
		last_report = stop_tv.tv_sec;

		frames = delta_sum = 0;

	// ledscape_close(leds);

	return EXIT_SUCCESS;
}
