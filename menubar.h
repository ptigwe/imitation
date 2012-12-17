#include <gtk/gtk.h>
#include <cv.h>
#include <highgui.h>
#include "uiactions.h"

#ifndef MENUBAR_H
#define MENUBAR_H

GtkWidget* initMenubar(GtkWindow* window, GtkWidget* vbox);

#endif