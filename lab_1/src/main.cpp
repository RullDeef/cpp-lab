#include <QtWidgets/QApplication>
#include "ui/modelviewer.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    ui::ModelViewer viewer;
    viewer.show();
    return app.exec();
}
