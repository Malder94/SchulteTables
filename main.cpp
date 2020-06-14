/*Главный файл*/

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.setFixedHeight(w.height()+100); // Запрещаю менять высоту окна; Ширина уже задана

  //Добавление стилей
  QFile file(":/style.qss");
  if(file.open(QFile::ReadOnly)) {
        QString StyleSheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(StyleSheet);
  }

  w.show();
  return a.exec();
}
