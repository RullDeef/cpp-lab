#include "mainwindow.h"
#include <QApplication>

// #define TEST

#ifdef TEST
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include "controller.h"
#endif

int main(int argc, char *argv[])
{
#ifdef TEST
    QThread* thread = QThread::currentThread();
    return QtConcurrent::run([thread]() -> int
    {
        Door* door = new Door();
        Cabin* cabin = new Cabin();
        Controller* controller = new Controller(cabin, door);

        ControllerButton* buttons[5];

        for (size_t i = 0; i < sizeof(buttons) / sizeof(*buttons); i++)
        {
            buttons[i] = new ControllerButton(i + 1);
            controller->addButton(buttons[i]);
        }

        buttons[2]->pressButton();

        thread->wait(6000);

        return 0;
    }).result();
#else
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
#endif
}
