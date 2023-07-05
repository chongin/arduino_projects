#ifndef _IO_H
#define _IO_H

#include "common.h"

/* Constants */
static constexpr double DEGREES_PER_RADIAN =
    (180.0 / 3.141592653589793238463); ///< Degrees per radian for conversion

void io_motion_cal(struct twig_struct *twig_data);
void io_x_imu3_gui(struct twig_struct *twig_data);
void io_imu(float voltage, struct twig_struct *twig_data);
String io_imu_to_string(struct twig_struct *twig_data);

#endif
