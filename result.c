#include "result.h"

result_t *result_new(int n)
{
    result_t *res;
    res = (result_t *)g_malloc(sizeof(result_t));
    res->n = n;
    
    res->result = (double **)g_malloc(sizeof(double *) * n);
    res->cooperate = (double **)g_malloc(sizeof(double *) * n);
    res->defect = (double **)g_malloc(sizeof(double *) * n);
    res->mixed = (double **)g_malloc(sizeof(double *) * n);
    
    int i;
    for(i = 0; i < n; ++i)
    {
        res->result[i] = (double *)g_malloc(sizeof(double) * n);
        res->cooperate[i] = (double *)g_malloc(sizeof(double) * n);
        res->defect[i] = (double *)g_malloc(sizeof(double) * n);
        res->mixed[i] = (double *)g_malloc(sizeof(double) * n);
        
        int j;
        for(j = 0; j <= n; ++j)
        {
            res->result[i][j] = 0;
            res->cooperate[i][j] = 0;
            res->defect[i][j] = 0;
            res->mixed[i][j] = 0;
        }
    }
    
    return res;
}

void result_free(result_t *res)
{
    int i;
    for(i = 0; i < res->n; ++i)
    {
        g_free(res->result[i]);
        g_free(res->cooperate[i]);
        g_free(res->defect[i]);
        g_free(res->mixed[i]);
    }
    
    g_free(res->result);
    g_free(res->cooperate);
    g_free(res->defect);
    g_free(res->mixed);
    
    g_free(res);
}

void result_to_image(result_t *res, IplImage *res_img, IplImage *coop_img, IplImage *def_img, IplImage *mix_img)
{
    int n = res->n;
    double spacing = res_img->height / n;
    
    int s;
    for(s = 0; s < n; ++s)
    {    
        double s_i = ((double) s) / ((double) n);
        double y1 = res_img->height - (s_i * res_img->height);
        double y2 = y1 - spacing;
        int t;
        for(t = 0; t < n; ++t)
        {
            double t_i = ((double) t) / ((double) n);
            
            double x1 = (t_i * res_img->width);
            double x2 = x1 + spacing;
            
            CvPoint p1 = cvPoint(x1, y1);
            CvPoint p2 = cvPoint(x2, y2);

            //printf("%.3f -> %.1f  %.1f, %.1f\n", c, colour.val[0], colour.val[1], colour.val[2]);
            //printf("%.1f, %.1f -> %.1f, %.1f\n", x1, y1, x2, y2);
            
            CvScalar colour = colourmap_gray_to_rgb(res->result[s][t]);
            cvRectangle(res_img, p1, p2, colour, CV_FILLED, 8, 0);
            
            colour = colourmap_gray_to_rgb(res->cooperate[s][t]);
            cvRectangle(coop_img, p1, p2, colour, CV_FILLED, 8, 0);
            
            colour = colourmap_gray_to_rgb(res->defect[s][t]);
            cvRectangle(def_img, p1, p2, colour, CV_FILLED, 8, 0);
            
            colour = colourmap_gray_to_rgb(res->mixed[s][t]);
            cvRectangle(mix_img, p1, p2, colour, CV_FILLED, 8, 0);
        }
    }
}