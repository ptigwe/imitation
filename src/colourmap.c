#include "colourmap.h"

double colourmap_interpolate(double t, double v1, double v2)
{
    return ((1 - t) * v1) + (t * v2);
}

CvScalar colourmap_interpolate_colours(double t, CvScalar c1, CvScalar c2)
{
    double r = colourmap_interpolate(t, c1.val[0], c2.val[0]);
    double g = colourmap_interpolate(t, c1.val[1], c2.val[1]);
    double b = colourmap_interpolate(t, c1.val[2], c2.val[2]);
    
    return cvScalar(r, g, b, 0);
}

CvScalar colourmap_gray_to_rgb(double gray)
{
    CvScalar black = CV_RGB(0, 0, 0);
    double p = (double)128 / 255;
    CvScalar purple = CV_RGB(p, 0, p);
    CvScalar red = CV_RGB(1, 0, 0);
    CvScalar yellow = CV_RGB(1, 1, 0);
    
    double black_point = 0;
    double purple_point = 0.2;
    double red_point = 0.6;
    double yellow_point = 1;
    
    if(gray < purple_point)
    {
        double val = gray / purple_point;
        return colourmap_interpolate_colours(val, black, purple);
    }
    
    if(gray < red_point)
    {
        double val = (gray - purple_point) / (red_point - purple_point);
        return colourmap_interpolate_colours(val, purple, red);
    }
    
    if(gray < yellow_point)
    {
        double val = (gray - red_point) / (yellow_point - red_point);
        return colourmap_interpolate_colours(val, red, yellow);
    }
    return yellow;
}
