#ifndef IMAGEGUI_H_INCLUDED
#define IMAGEGUI_H_INCLUDED

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QLabel>

class imageGUI : public QMainWindow
{
    Q_OBJECT

public:
    imageGUI(QWidget *parent = 0);
    virtual ~imageGUI(){}

private:

    QLabel* iFileLabel;
    QLineEdit* iFile;
    QLabel* oFileLabel;
    QLineEdit* oFile;

    QPushButton* invert;
    QPushButton* blur;
    QPushButton* flipX;
    QPushButton* flipY;
    QPushButton* grey;
    QPushButton* rotateR;
    QPushButton* rotateL;
    QPushButton* edge;

private slots:
    bool checkFile(const char* fileName);

    void invertMethod();
    void blurMethod();
    void flipXMethod();
    void flipYMethod();
    void greyMethod();
    void rotateRightMethod();
    void rotateLeftMethod();
    void edgeDetectMethod();
};

#endif // IMAGEGUI_H_INCLUDED
