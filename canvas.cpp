/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  <copyright holder> <email>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
    Author : Jose Fernandez Navarro  -  jc.fernandez.navarro@gmail.com
*/



#include <QDebug>
#include <QPainter>
#include <QResizeEvent>
#include <QPrinter>
#include <QPrintDialog>
#include <QX11Info>
#include "canvas.h"
#include <cairo/cairo-xlib-xrender.h>

Canvas::Canvas(QWidget* parent)
  : QWidget(parent),cr_(0)
{

}

//destroys the cairo object if it exists
Canvas::~Canvas()
{
    if (cr_) {
        cairo_destroy(cr_);
        cr_ = 0;
    }
}

cairo_t* Canvas::getCairoCanvas()
{
  return cr_;
}

cairo_surface_t* Canvas::getCairoSurface()
{
  return surface_;
}

void Canvas::paintEvent(QPaintEvent* )
{
    if (!cr_) return;

    QPainter(this).drawPixmap(0, 0, buf_);
}


/* This function uses Xlib and X11 to
 * create a Cairo drawable object from a Qt display object
 * and link them */
void Canvas::paintCanvas()
{
    buf_ = QPixmap(width(),height());
    buf_.fill(Qt::white);
    
    const QX11Info& info = buf_.x11Info();
    Display* display = info.display();
 
    Drawable drawable = buf_.handle();
    Screen* screen = XScreenOfDisplay(display, info.screen());
 
    Visual* visual = reinterpret_cast<Visual*>(info.visual());
    XRenderPictFormat *format = XRenderFindVisualFormat(display, visual);

    surface_ = cairo_xlib_surface_create_with_xrender_format(display, drawable, screen, format,width(),height());
    cr_ = cairo_create(surface_);

}

bool Canvas::saveCanvas(const QString& fileName, const char* format, int quality)
{
  if(!buf_)
  {
    return false;
  }
  else
  {
    return buf_.save(fileName,format,quality);
    
  }
    
}

/*This function creates the printer object to capture the filename
 * and then print the Cairo Canvas on the pdf page that will
 * have the same size
 */
bool Canvas::saveCanvasPDF(const QString& fileName)
{   
   QPrinter printer(QPrinter::ScreenResolution);
   printer.setOutputFileName(fileName);
   printer.setOutputFormat(QPrinter::PdfFormat);
   printer.setFullPage(true);
   printer.setPageSize(QPrinter::A4);
   //TODO this is just a hack, the resolution should be calculated according to the size of the canvas
   //TODO another solution would be to scale the painter to the size of A4
   printer.setResolution(150);
   QPixmap pixmap = QPixmap::grabWidget(this);
   QPainter painter;
   painter.begin(&printer);
   painter.drawPixmap(0, 0, pixmap);
   painter.end();
   return true;
}

/*This function launches a printing dialog to select the printing device
and then send the canvas to the printer to be printed out*/
bool Canvas::print()
{
  QPrinter printer;
  printer.setPageSize(QPrinter::A4);
  //TODO this is just a hack, the resolution should be calculated according to the size of the canvas
  //TODO another solution would be to scale the painter to the size of A4
  printer.setResolution(150);
  printer.setFullPage(true);
  QPrintDialog print(&printer , this);
  if(print.exec()== QPrintDialog::Accepted)
  {
      QPixmap pixmap = QPixmap::grabWidget(this);
      QPainter painter;
      painter.begin(&printer);
      painter.drawPixmap(0, 0, pixmap);
      painter.end();
      return true;
  }
  else
    return false;
}


void Canvas::resizeEvent(QResizeEvent* )
{
    paintCanvas();
}




