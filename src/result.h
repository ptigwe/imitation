#include <cv.h>
#include <highgui.h>
#include <glib.h>
#include "colourmap.h"

#ifndef RESULT_H
#define RESULT_H

#define X_OFFSET1 60
#define X_OFFSET2 90
#define Y_OFFSET 30
#define FONT_SCALE 0.5

typedef struct
{
    double **result;
    double **cooperate;
    double **defect;
    double **mixed;
    int n;
}result_t;

result_t *result_new(int n);
void result_free(result_t *res);
void result_to_image(result_t *res, IplImage *res_img,IplImage *coop_img, IplImage *def_img, IplImage *mix_img);

#endif