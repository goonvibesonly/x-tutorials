/**
 * @file get_gps.c
 * @brief GPS library used by a python library to retrieve lat and lat
 * coordinates using gps.h
 * @version 0.1
 * @date 2023-09-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <errno.h>
#include <gps.h>
#include <math.h>    // isnan
#include <stdbool.h> // bool
#include <stdio.h>
#include <stdlib.h> // calloc
#include <string.h>
#include <unistd.h>

bool get_gps(double *lat, double *lon) {
  struct gps_data_t gps_data;

  if ((gps_open(GPSD_SHARED_MEMORY, NULL, &gps_data)) == -1) {
    printf("code: %d, reason: %s\n", errno, gps_errstr(errno));
    return false;
  }

  for (int i = 0; i < 10; i++) {
    /* read data */
    if ((gps_read(&gps_data, NULL, 0)) == -1) {
      printf("error occured reading gps data. code: %d, reason: %s\n", errno,
             gps_errstr(errno));
    } else {
      /* Display data from the GPS receiver. */
      if ((gps_data.status == STATUS_FIX) &&
          (gps_data.fix.mode == MODE_2D || gps_data.fix.mode == MODE_3D) &&
          !isnan(gps_data.fix.latitude) && !isnan(gps_data.fix.longitude)) {
        *lat = gps_data.fix.latitude;
        *lon = gps_data.fix.longitude;
        // printf("latitude: %f, longitude: %f, speed: %f\n",
        // gps_data.fix.latitude, gps_data.fix.longitude, gps_data.fix.speed);
        return true;
      } else {
        printf("no GPS data available\n");
        return false;
      }
    }
    sleep(3);
  }

  /* When you are done... */
  gps_close(&gps_data);
  return true;
}
