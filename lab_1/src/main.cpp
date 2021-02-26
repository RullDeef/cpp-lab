#include <QtWidgets/QApplication>
#include "core/model.hpp"
#include "ui/modelviewer.hpp"

int main(int argc, char* argv[])
{
    core::Model model;
    core::load_model("model.txt", model);

    QApplication app(argc, argv);

    ui::ModelViewer viewer;
    viewer.show();

    return app.exec();
}
