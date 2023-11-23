#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Qt Window Example");
    mainWindow.setGeometry(100, 100, 400, 300); // Set window position and size

    mainWindow.show();

    return app.exec();
}