/*Заголовочный файл класса MainWindow*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QTimer>
#include <QTime>
#include <QFile>
#include <QMessageBox>
#include <algorithm>
#include "playbutton.h"
#include "progress.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:

  void on_startButton_clicked(); // Кнопка "Старт"
  void on_action_triggered(); // Пункт меню "Прогресс"
  void on_action_2_triggered(); // Пункт меню "Выход"

  void slotGetNumber(); //Получение номера нажатой кнопки
  void slotTimer(); //Слот таймера



private:
  Ui::MainWindow *ui;
  Progress *progressWindow;

  QTimer *timer = new QTimer(); //Timer

  void createTable(); // Создание таблицы Шульте
  void clearTable(); // Очистка старой таблицы
  void writeResult(); // Запись результата в файл
};


#endif // MAINWINDOW_H
