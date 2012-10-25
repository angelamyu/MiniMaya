/********************************************************************************
** Form generated from reading UI file 'doc.ui'
**
** Created: Thu Apr 26 10:34:12 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOC_H
#define UI_DOC_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPlainTextEdit>

QT_BEGIN_NAMESPACE

class Ui_doc
{
public:
    QPlainTextEdit *plainTextEdit;
    QPlainTextEdit *plainTextEdit_2;
    QPlainTextEdit *plainTextEdit_3;

    void setupUi(QDialog *doc)
    {
        if (doc->objectName().isEmpty())
            doc->setObjectName(QString::fromUtf8("doc"));
        doc->resize(649, 483);
        doc->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        plainTextEdit = new QPlainTextEdit(doc);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(30, 170, 611, 171));
        plainTextEdit_2 = new QPlainTextEdit(doc);
        plainTextEdit_2->setObjectName(QString::fromUtf8("plainTextEdit_2"));
        plainTextEdit_2->setGeometry(QRect(30, 350, 611, 141));
        plainTextEdit_3 = new QPlainTextEdit(doc);
        plainTextEdit_3->setObjectName(QString::fromUtf8("plainTextEdit_3"));
        plainTextEdit_3->setGeometry(QRect(30, 20, 611, 141));

        retranslateUi(doc);

        QMetaObject::connectSlotsByName(doc);
    } // setupUi

    void retranslateUi(QDialog *doc)
    {
        doc->setWindowTitle(QApplication::translate("doc", "Documentation", 0, QApplication::UnicodeUTF8));
        plainTextEdit->setPlainText(QApplication::translate("doc", "Visualizer -- Angela Yu: \n"
"\n"
"Camera is implemented using a spherical camera and is controlled by clicking and \n"
" dragging your mouse around. \n"
"\n"
"Move a reference point by typing 3 ints separated by only commas in the box next\n"
" to Set Ref Point and then click said button. \n"
"Snap view: selected a face, vertex, or halfedge, and then right click and choose\n"
" snap view from the little list. \n"
"Reset camera: right click in the viewing window and then click reset camera. This\n"
" also resets your saved views (aka, removes them). \n"
"Named views: go to a named view by right clicking (?) and selecting the named view\n"
" you wish the camera to be in\n"
"Saving your own views: In the textbox next to the save camera button, type in \n"
" a string to name your view. Then hit the save camera button. This will save\n"
" the camera and store it in the nearby list. \n"
"\n"
"You can pick edges, faces, and vertices. Move your mouse around, and when you \n"
" highlight a region that represents one o"
                        "f these structures, it will outline\n"
" the region in red. Faces are completely outlined. Generally, edges are   \n"
"\n"
" represented as rectangle looking shapes and vertices are represented as  \n"
"\n"
" triangles. Click on these, the outline will become white and you can\n"
" do things like change face colors and move vertices (using the x,y,z   \n"
"\n"
"sliders). \n"
"You can also pick the cubes in the lattice of .OBJ's if you turn the feature on. \n"
" When you click said cube, it'll turn white and you can move these cubes  \n"
"\n"
" around. Nonselected cubes are a blue-ish color. \n"
"Picking faces work on both planar and nonplanar faces.\n"
"\n"
"Load shaders by inputting a string into the box near the Load Shader button and \n"
" clicking said button. Make sure the string you enter in is the part before\n"
" \"Frag.frag\" and \"Vert.vert\" of the shader files and that these files are in\n"
" the project folder. Ex. type in \"diffuseTest\" in order to load   \n"
"\n"
"\"diffuseTestFrag.frag\" and \""
                        "diffuseTestVert.vert\". \n"
"\n"
"Materials are handled and are passed to the shader as lambert shading. Nothing   \n"
"\n"
"fancy. Default material is white colored if the material is not found in   \n"
"\n"
"the project folder. You can test this by loading the test.obj and you'll   \n"
"\n"
"notice some faces are red now. \n"
"\n"
"Move light source: Move light source to a location by clicking on lighting in the \n"
" menubar at the top. Then select Change Light Position. In the window that  \n"
"\n"
" pops up, type in three floats that are separated by only one comma. This  \n"
"\n"
" will change the light position to that spot.\n"
"\n"
"", 0, QApplication::UnicodeUTF8));
        plainTextEdit_2->setPlainText(QApplication::translate("doc", "Deformer -- Di Mu:\n"
"\n"
"Guide:\n"
"Load Mesh: In the menu, click on load, and choose a file to load an OBJ file.\n"
"Save Mesh: In the menu, click on save, and input filename to save an OBJ file.\n"
"Draw bounding box: input dimension at left-bottom, and click on \342\200\234show box\342\200\235 button to show the bounding box, and click on the \342\200\234hide box\342\200\235 button to disable the bounding box. \n"
"Twist the object (implemented using FFD):  Click on the twist.\n"
"Taper the object (implemented using FFD):  Click on the taper.\n"
"\n"
"Difficulties:\n"
"	I didn\342\200\231t realize that the global twist doesn\342\200\231t require FFD until last moment, but I don\342\200\231t have time to change it. I changed the control point positions and then used the Bezier interpolate formula to calculate the vertices of the deformed object. \n"
"", 0, QApplication::UnicodeUTF8));
        plainTextEdit_3->setPlainText(QApplication::translate("doc", "Geometer \342\200\223 Ana Mei:\n"
"Responsible for creating user interface to the polygon meshes. User interactions include context menus and dialog box messages. For example, to change a color of the face, the mouse has to select a face first before right-clicking in order to get such options to show up. \n"
"-	Camera functions can be found by right-clicking within the screen but not selecting anything from the cube\n"
"-	Color and Snap View only appears when a face is selected\n"
"-	Edit Mesh functions can be accessed by the buttons above or the file menu.\n"
"-	Can load and save files from the file menu\n"
"-	The deformation tab widget contains the deforming functions such as bounding box and FFDs\n"
"Polygon Mesh Operations:\n"
"1.	Insert vertex into an edge: must select a halfedge  first before performing this operation.\n"
"2.	Delete vertex: choose a halfedge and press the button called delete vertex.\n"
"3.	Select a vertex and translate in the X,Y,Z direction\n"
"4.	Insert edge by selecting two halfedge"
                        "s. These two halfedges must have a vertex in common.\n"
"5.	Split Quad: split a quad into two triangles. \n"
"Catmull-Clark Subdivision:\n"
"-	Able to smooth both the handmade cube and loaded obj file. It has a progress bar to inform the user that the program is still running when dealing with high polygon count.\n"
"", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class doc: public Ui_doc {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOC_H
