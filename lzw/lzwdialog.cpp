#include "lzwdialog.h"
#include <QPixmap>
#include <QPainter>
#include <QFileDialog>
#include <QPoint>
#include <QMessageBox>
#include <iostream>

LzwDialog::LzwDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    pathList<<"shana"<<"Desktop"<<"File System"<<"software"<<"information"<<"free use"<< \
    "about ACG"<<"system"<<"Documents"<<"Music"<<"Pictures"<<"Videos"<<"Downloads"<<"other ..." ;

    progressBar->hide();

    connect( fileButton, SIGNAL(clicked()), this, SLOT(lzwOpenFile()) );

    initComboBox();
    connect( locationComboBox, SIGNAL(activated(int)), this, SLOT(lzwComboBoxOpenFile(int)));
    connect( quitButton, SIGNAL(clicked()), this, SLOT(close()));

    connect( compressButton, SIGNAL(clicked()), this, SLOT(callLzwEncode()));
    connect( decompressButton, SIGNAL(clicked()), this, SLOT(callLzwDecode()));


}

void LzwDialog::paintEvent( QPaintEvent * /* event */ )
{
    QPixmap pixmap(":/images/1.png");
    QPainter painter(this);
    int width = filenameLabel->width() + filenameLineEdit->width() + fileButton->width() + 35;
    painter.drawPixmap( width, 18, pixmap.width()/3, pixmap.height()/3, pixmap );
}

void LzwDialog::lzwOpenFile()
{
    QString filename = QFileDialog::getOpenFileName( this, \
           tr("Open File"), QDir::currentPath(), tr("All Files(*.*)"));

    if (!filename.isNull()){
        filenameLineEdit->setText(filename);
    }
}

void LzwDialog::lzwComboBoxOpenFile( int index )
{
    int i;

    if ( locationComboBox->itemText( index ) != QString("       other ...") ) return;
    QString currentDir = QFileDialog::getExistingDirectory( this, tr("Open File"), \
        QDir::currentPath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    QStringList currentDirList = currentDir.split("/");
    QString currentTopDir = currentDirList.at(currentDirList.count() - 1);

    if (!currentDir.isNull()){
        if ( locationComboBox->itemText( locationComboBox->count() - 1 ) != QString("Downloads")  )
            locationComboBox->removeItem( locationComboBox->count() - 2 );

        for ( i = 0; i < pathList.count() - 1; i++ ){
            if ( currentTopDir == pathList.at( i ) ) break;
        }

        if ( i == pathList.count() - 1 ){
            locationComboBox->insertItem( locationComboBox->count() - 1, \
                QIcon(QString(":/png/%1.png").arg(QString::number(15))), currentTopDir );
            locationComboBox->setCurrentIndex(locationComboBox->count() - 2 );
        }else
            locationComboBox->setCurrentIndex( i );
    }
}

void LzwDialog::initComboBox()
{
    QString currentPath = QDir::currentPath();
    QStringList currentPathList = currentPath.split("/");
    QString currentTopPath = currentPathList.at(currentPathList.count() - 1);

    locationComboBox->setEditable(true);
    for (int i = 0; i < pathList.count()-1; i++)
        locationComboBox->insertItem( i, QIcon(QString(":/png/%1.png").arg(QString::number(i+1))), pathList.at(i));
    int i = pathList.count() - 1;
    locationComboBox->insertItem( i, QIcon::QIcon(), QString("       ") + pathList.at(i));

    for ( i = 0; i < pathList.count() - 1; i++ ){
        if ( currentTopPath == pathList.at( i ) ) break;
    }

    if ( i == pathList.count() - 1)
        locationComboBox->insertItem( i, QIcon(QString(":/png/%1.png").arg(QString::number(i+1))), currentTopPath );
    locationComboBox->setCurrentIndex( i );

}

void LzwDialog::callLzwEncode()
{
    QString currentPath = QDir::currentPath();
    filePath = filenameLineEdit->text();

    if ( !filePath.isNull() ){
        QStringList filePathList = filePath.split("/");
        QString fileName = filePathList.at( filePathList.count() -1 );
        std::cout<<"fileName = "<<fileName.toStdString()<<std::endl;
        fileSavePath = currentPath + "/" + fileName + QString(".lzw");
        std::cout<<fileSavePath.toStdString()<<std::endl;
    }else
        fileSavePath = filePath;

    if ( !filePath.isNull() ){
        std::ifstream fin( filePath.toStdString().c_str() );
        std::ofstream fout( fileSavePath.toStdString().c_str() );

        if ( !(fin.is_open() && fout.is_open() ) ){
            QMessageBox::warning(this, "warning", "couldn't open this file\n");
        }else{
            lzw_compress *compress = new lzw_compress(fout);
            compressButton->setEnabled( false );
            progressBar->show();
            compress->LZWEncode( fin, fout, progressBar );
            compressButton->setEnabled( true );
            progressBar->hide();
            delete compress;
        }
    }
}

void LzwDialog::callLzwDecode()
{
    QString currentPath = QDir::currentPath();
    filePath = filenameLineEdit->text();

    if ( !filePath.isNull() ){
        QStringList filePathList = filePath.split("/");
        QString fileName = filePathList.at( filePathList.count() -1 );
        std::cout<<"fileName = "<<fileName.toStdString()<<std::endl;
        fileSavePath = currentPath + "/" + fileName;
        fileSavePath = fileSavePath.remove(".lzw");
        std::cout<<fileSavePath.toStdString()<<std::endl;
    }else
        fileSavePath = filePath;

    if ( !filePath.isNull() ){
        std::ifstream fin( filePath.toStdString().c_str() );
        std::ofstream fout( fileSavePath.toStdString().c_str() );

        if ( !(fin.is_open() && fout.is_open() ) ){
            QMessageBox::warning(this, "warning", "couldn't open this file\n");
        }else{
            lzw_decompress *decompress = new lzw_decompress;
            decompressButton->setEnabled( false );
            progressBar->show();
            decompress->LZWDecode( fin, fout, progressBar );
            decompressButton->setEnabled( true );
            progressBar->hide();
            delete decompress;
        }
    }
}


    
