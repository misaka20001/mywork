#include <QApplication>
#include <QDialog>

#include "lzwdialog.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    LzwDialog *dialog = new LzwDialog;
    dialog->show();

    return app.exec();
}
