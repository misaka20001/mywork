#include "dial-up.h"

int main( int argc, char **argv )
{
    QApplication app( argc, argv );

    DialWindow *window = new DialWindow;
    window->show();

    return app.exec();
}
