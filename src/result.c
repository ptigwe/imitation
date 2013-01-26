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

void result_draw_legend(IplImage* dst, int steps)
{
    int img_height = dst->height - (2 * Y_OFFSET);
    int img_width = X_OFFSET2;
    
    int height = img_height / steps;
    
    int i;
    double x1 = dst->width - X_OFFSET2 + 20;
    double x2 = dst->width - 40;
    for(i = 0; i < steps; ++i)
    {    
        double c = ((double)i) / ((double) steps);
        double y1 = img_height - (c * img_height) + Y_OFFSET;
        double y2 = y1 - height;
        
        CvPoint p1 = cvPoint(x1, y1);
        CvPoint p2 = cvPoint(x2, y2);
        
        CvScalar color = colourmap_gray_to_rgb(c);
        //printf("%.3f -> %.1f  %.1f, %.1f\n", c, color.val[0], color.val[1], color.val[2]);
        cvRectangle(dst, p1, p2, color, CV_FILLED, 8, 0);
    }
    
    double x3 = x1 + 5;
    double x4 = x2 - 5;
    
    CvFont font;
    cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, FONT_SCALE, FONT_SCALE, 0, 1, CV_AA);
    CvSize text_size;
    gchar str[4];
    
    for(i = 0; i <= 5; ++i)
    {
        double c = (double) i / 5;
        double y = img_height - (c * img_height) + Y_OFFSET;
        
        CvPoint p1 = cvPoint(x1, y);
        CvPoint p2 = cvPoint(x3, y);
        
        cvLine(dst, p1, p2, CV_RGB(0, 0, 0), 1, 8, 0);
        
        p1 = cvPoint(x2, y);
        p2 = cvPoint(x4, y);
        cvLine(dst, p1, p2, CV_RGB(0, 0, 0), 1, 8, 0);
        
        g_sprintf(str, "%.1f", c);
        
        cvGetTextSize(str, &font, &text_size, NULL);
        p1 = cvPoint(p1.x + 5, p1.y + (text_size.height / 2));
        cvPutText(dst, str, p1, &font, CV_RGB(0, 0, 0));
    }
    
    cvRectangle(dst, cvPoint(x1, Y_OFFSET), cvPoint(x2, img_height + Y_OFFSET), CV_RGB(0, 0, 0), 1, 8, 0);
}

void result_draw_grid(IplImage* dst)
{
    double height = dst->height - (2 * Y_OFFSET);
    double width = dst->width - (X_OFFSET1 + X_OFFSET2);
    
    cvRectangle(dst, cvPoint(X_OFFSET1, Y_OFFSET), cvPoint(width + X_OFFSET1, height + Y_OFFSET), CV_RGB(0, 0, 0), 1, 8, 0);
    
    CvFont font;
    cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, FONT_SCALE, FONT_SCALE, 0, 1, CV_AA);
    CvSize text_size;
    
    int i;
    for(i = 0; i <= 4; ++i)
    {
        double t = (double) i / 2;
        int x = ((t / 2) * width) + X_OFFSET1;
        int y1 = Y_OFFSET;
        int y2 = height + Y_OFFSET;
        
        CvPoint p1 = cvPoint(x, y1);
        CvPoint p2 = cvPoint(x, y2);
        
        cvLine(dst, p1, p2, CV_RGB(0, 0, 0), 1, 8, 0);
        printf("Grid x - %f\n", t);
        
        gchar str[4];
        g_sprintf(str, "%.1f", t);
        
        cvGetTextSize(str, &font, &text_size, NULL);
        p1 = cvPoint(p1.x - (text_size.width / 2), p2.y + text_size.height + 10);
        cvPutText(dst, str, p1, &font, CV_RGB(0, 0, 0));
    }
    
    for(i = 0; i <= 10; ++i)
    {
        double t = ((double) i / 5) - 1;
        int x1 = X_OFFSET1;
        int x2 = X_OFFSET1 + width;
        int y = height - (((double) i / 10) * height) + Y_OFFSET;
        
        CvPoint p1 = cvPoint(x1, y);
        CvPoint p2 = cvPoint(x2, y);
        
        cvLine(dst, p1, p2, CV_RGB(0, 0, 0), 1, 8, 0);
        printf("Grid y - %f\n", t);
        
        gchar str[4];
        g_sprintf(str, "%.1f", t);
        
        cvGetTextSize(str, &font, &text_size, NULL);
        p1 = cvPoint(p1.x - text_size.width - 5, p1.y + (text_size.height / 2));
        cvPutText(dst, str, p1, &font, CV_RGB(0, 0, 0));
    }
}

void result_to_image(result_t *res, IplImage *res_img, IplImage *coop_img, IplImage *def_img, IplImage *mix_img)
{
    int n = res->n;
    double height = res_img->height - (2 * Y_OFFSET);
    double width = res_img->width - (X_OFFSET1 + X_OFFSET2);
    double y_spacing = height / n;
    double x_spacing = width / n;
    
    int s;
    for(s = 0; s < n; ++s)
    {    
        double s_i = ((double) s) / ((double) n);
        double y1 = height - (s_i * height) + Y_OFFSET;
        double y2 = y1 - y_spacing;
        int t;
        for(t = 0; t < n; ++t)
        {
            double t_i = ((double) t) / ((double) n);
            
            double x1 = (t_i * width) + X_OFFSET1;
            double x2 = x1 + x_spacing;
            
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
    
    result_draw_grid(res_img);
    result_draw_grid(coop_img);
    result_draw_grid(def_img);
    result_draw_grid(mix_img);
    
    result_draw_legend(res_img, 100);
    result_draw_legend(coop_img, 100);
    result_draw_legend(def_img, 100);
    result_draw_legend(mix_img, 100);
}