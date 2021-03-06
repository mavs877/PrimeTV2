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

/* This class implements the User Interface, it inherits from three QT objects
 *  the MainWindow class and the Ui_MainWindo and Ui_parameters canvas that 
 * are object created with UI designer and dynamically linked to the application
 */


#ifndef WINDOWS_H
#define WINDOWS_H
#include <QFileDialog>
#include <QScrollArea>
#include <QVBoxLayout>
#include "ui_primetv.h"
#include "ui_parameters.h"
#include <mainops.h>
#include "canvas.h"
#include "libraries/configfile.h"

class QAction;
class QActionGroup;
class QLabel;
class QMenu;

class MainWindow : public QMainWindow, public Ui_MainWindow, public Ui_Parameters
{

   Q_OBJECT;
  
public:
  
    // constructor we only need the parameters object and the parent if there is any
    MainWindow(Parameters *p, QWidget *parent = 0);
    //copy constructor
    MainWindow(const MainWindow& other);
    //destructor
    ~MainWindow();
   
    
private slots:
    /* slots are functions that are going to be assigned to signals and events */
    
    /* launches an open file dialog to select and load the guest tree*/
    void loadGuest();
    
    /* launches an open file dialog to select and load the host tree*/
    void loadHost();
    
    /* reconciles the trees, calculate gamma and lambda, the cordinates and draw the tree on the screen*/
    void generateTree();
    
    /* exit the application */
    void exit();
    
    /* save the canvas in a file */
    void save();
    
    /* launches an open file dialog to select and load the map file if the reconcile option is activated */
    void loadMap();
    
    /* overloaded function called every time a parameter is modified to update the parameters */
    void update();
    
    /* reset the canvas and the parameters */
    void newImage();
    
    /* show or hide the parameters panel*/
    void showParameters();
    
    /* to activate the Lateral Transfer and load the values, it will draw the picture is there is a picture on
     * the canvas */
    void activateLGT();
    
    /* to activate the reconcilation mode, therefore the open map button will be enabled, because a map file is needed
     * to reconcile*/
    void activateReconcilation();
    
    /* to print the canvas */
    void print();
    
    /* a color selection dialog will show up and the color selected with will assigned the current font */
    void loadFontColor();
    
    /* launches and open dialog to load a configuration file where all the parameters will be stored */
    void loadConfigFile();
    
    /* open a dialog to save the current configuration into a config file */
    void saveConfigFile();
  
private:
    
   /* creates an open file dialog and returns the file chosen*/
    QString openFile(QString header);
    
    /* overloaded functions */
    virtual void resizeEvent(QResizeEvent* event);
    virtual void paintEvent(QPaintEvent* event);
    
    /* paint the current tree on the canvas */
    void paintTree();
    
    /* function that create all the actions and events asigned to the buttons*/
    void createActions();
    
    /* function that load the actual values of parameters in case the user has given parameters as input 
     * in the console */
    void loadParameters(Parameters *parameters);
    
    /* overloaded close Event function to handle the exit */
    void closeEvent(QCloseEvent *e);
    
    QVBoxLayout *verticalLayout; //vertical layout object to implement scrolling
    QScrollArea *scrollArea;  //scroll area widget to implement the scrolling
    QWidget *params; //parameters panel
    Canvas *widget; //canvas where the tree will be painted
    QString lastVisitedDir;
    Mainops *ops; // main operations
    Parameters *parameters;
    const char* reconciledtree;
    const char* speciestree;
    const char* genetree;
    const char* mapfile;
    bool guestTree;
    bool hostTree;
    bool menuparameters;
    bool isPainted;
    cairo_t* cr_; //cairo object
    bool mapfileStatus;
    ConfigFile *config;
   
};

#endif // WINDOWS_H