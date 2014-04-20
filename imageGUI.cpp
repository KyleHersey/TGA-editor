#include "imageGUI.h"
#include "image.h"

#include <QWidget>
#include <cstdlib>

#include <stdexcept>

#include "iostream"
using std::cout;
using std::endl;

#include "fstream"
using std::ifstream;

#include "string"
using std::string;

#include <sstream>
using std::stringstream;

#include "QtGui"

imageGUI::imageGUI(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Image Editor");

    QWidget* main = new QWidget(this);

    //make objects
    iFileLabel = new QLabel("Input File: ", this);
    iFile = new QLineEdit(this);

    oFileLabel = new QLabel("Output File: ", this);
    oFile = new QLineEdit(this);

    invert = new QPushButton("Invert", this);
    blur = new QPushButton("Blur", this);
    flipX = new QPushButton("Flip Horizontally", this);
    flipY = new QPushButton("Flip Vertically", this);
    grey = new QPushButton("Make Greyscale", this);
    rotateR = new QPushButton("Rotate Right", this);
    rotateL = new QPushButton("Rotate Left", this);
    edge = new QPushButton("Edge Detect", this);

    //make input panel
    QWidget* iPanel = new QWidget(this);
    QHBoxLayout* iLayout = new QHBoxLayout;
        iPanel->setLayout(iLayout);
    iLayout->addWidget(iFileLabel);
    iLayout->addWidget(iFile);

    //make output layout
    QWidget* oPanel = new QWidget(this);
    QBoxLayout* oLayout = new QHBoxLayout;
        oPanel->setLayout(oLayout);
    oLayout->addWidget(oFileLabel);
    oLayout->addWidget(oFile);

    //make invert layout
    QWidget* invertPanel = new QWidget(this);
    QBoxLayout* invertLayout = new QHBoxLayout;
        invertPanel->setLayout(invertLayout);
    invertLayout->addWidget(invert);

    //make blur layout, button
     QWidget* blurPanel = new QWidget(this);
    QBoxLayout* blurLayout = new QHBoxLayout;
        blurPanel->setLayout(blurLayout);
    blurLayout->addWidget(blur);

    //make flip layout
    QWidget* flipPanel = new QWidget(this);
    QBoxLayout* flipLayout = new QHBoxLayout;
        flipPanel->setLayout(flipLayout);
    flipLayout->addWidget(flipX);
    flipLayout->addWidget(flipY);

    //greyscale layout
    QWidget* greyPanel = new QWidget(this);
    QBoxLayout* greyLayout = new QHBoxLayout;
        greyPanel->setLayout(greyLayout);
    greyLayout->addWidget(grey);

    //rotate layout
    QWidget* rotPanel = new QWidget(this);
    QBoxLayout* rotLayout = new QHBoxLayout;
        rotPanel->setLayout(rotLayout);
    rotLayout->addWidget(rotateL);
    rotLayout->addWidget(rotateR);

    //edgeDetect layout
    QWidget* edgePanel = new QWidget(this);
    QBoxLayout* edgeLayout = new QHBoxLayout;
        edgePanel->setLayout(edgeLayout);
    edgeLayout->addWidget(edge);

    //assign top and bottom panels to main layout
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(iPanel);
    mainLayout->addWidget(oPanel);
    mainLayout->addWidget(invertPanel);
    mainLayout->addWidget(blurPanel);
    mainLayout->addWidget(flipPanel);
    mainLayout->addWidget(greyPanel);
    mainLayout->addWidget(rotPanel);
    mainLayout->addWidget(edgePanel);
    main->setLayout(mainLayout);


    setCentralWidget(main);


    connect(invert, SIGNAL(clicked()), this, SLOT(invertMethod()));
    connect(blur, SIGNAL(clicked()), this, SLOT(blurMethod()));
    connect(flipX, SIGNAL(clicked()), this, SLOT(flipXMethod()));
    connect(flipY, SIGNAL(clicked()), this, SLOT(flipYMethod()));
    connect(grey, SIGNAL(clicked()), this, SLOT(greyMethod()));
    connect(rotateR, SIGNAL(clicked()), this, SLOT(rotateRightMethod()));
    connect(rotateL, SIGNAL(clicked()), this, SLOT(rotateLeftMethod()));
    connect(edge, SIGNAL(clicked()), this, SLOT(edgeDetectMethod()));
}


bool imageGUI::checkFile(const char* fileName){
    ifstream check(fileName);
    return check.good();
}


void imageGUI::invertMethod(){

    QString inputQString = iFile->text();
    string inputFile = inputQString.toStdString();
    if(!checkFile(inputFile.c_str())){
        throw std::runtime_error("File not found");
    }

    QString outputQString = oFile->text();
    string outputFile = outputQString.toStdString();

    image original(inputFile);
    image inverted = original;
    inverted.invert();
    inverted.toFile(outputFile);
}

void imageGUI::blurMethod(){
    QString inputQString = iFile->text();
    string inputFile = inputQString.toStdString();
    if(!checkFile(inputFile.c_str())){
        throw std::runtime_error("File not found");
    }

    QString outputQString = oFile->text();
    string outputFile = outputQString.toStdString();

    image original(inputFile);
    image blurred = original;
    blurred.blur();
    blurred.toFile(outputFile);
}

void imageGUI::flipXMethod(){
    QString inputQString = iFile->text();
    string inputFile = inputQString.toStdString();
    if(!checkFile(inputFile.c_str())){
        throw std::runtime_error("File not found");
    }

    QString outputQString = oFile->text();
    string outputFile = outputQString.toStdString();

    image original(inputFile);
    image flippedX = original;
    flippedX.flipX();
    flippedX.toFile(outputFile);
}

void imageGUI::flipYMethod(){
    QString inputQString = iFile->text();
    string inputFile = inputQString.toStdString();
    if(!checkFile(inputFile.c_str())){
        throw std::runtime_error("File not found");
    }

    QString outputQString = oFile->text();
    string outputFile = outputQString.toStdString();

    image original(inputFile);
    image flippedY = original;
    flippedY.flipY();
    flippedY.toFile(outputFile);
}

void imageGUI::greyMethod(){
    QString inputQString = iFile->text();
    string inputFile = inputQString.toStdString();
    if(!checkFile(inputFile.c_str())){
        throw std::runtime_error("File not found");
    }

    QString outputQString = oFile->text();
    string outputFile = outputQString.toStdString();

    image original(inputFile);
    image grey = original;
    grey.greyScale();
    grey.toFile(outputFile);
}

void imageGUI::rotateRightMethod(){
    QString inputQString = iFile->text();
    string inputFile = inputQString.toStdString();
    if(!checkFile(inputFile.c_str())){
        throw std::runtime_error("File not found");
    }

    QString outputQString = oFile->text();
    string outputFile = outputQString.toStdString();

    image original(inputFile);
    image rotR = original;
    rotR.rotateRight();
    rotR.toFile(outputFile);
}

void imageGUI::rotateLeftMethod(){
    QString inputQString = iFile->text();
    string inputFile = inputQString.toStdString();
    if(!checkFile(inputFile.c_str())){
        throw std::runtime_error("File not found");
    }

    QString outputQString = oFile->text();
    string outputFile = outputQString.toStdString();

    image original(inputFile);
    image rotL = original;
    rotL.rotateLeft();
    rotL.toFile(outputFile);
}

void imageGUI::edgeDetectMethod(){
    QString inputQString = iFile->text();
    string inputFile = inputQString.toStdString();
    if(!checkFile(inputFile.c_str())){
        throw std::runtime_error("File not found");
    }

    QString outputQString = oFile->text();
    string outputFile = outputQString.toStdString();

    image original(inputFile);
    image edge = original;
    edge.edgeDetect();
    edge.toFile(outputFile);
}


