/*Исполнительный файл класса MainWindow*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

int goal = 1; //Номер нужной кнопки
bool first = true; //Проверка на первый запуск
QTime seconds (0, 0, 0, 0); //Секунды
bool error = false; // Идентификатор ошибки

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{

  ui->setupUi(this);

  ui->btnLayout->setSpacing(0);

  createTable(); // Вызов таблицы

  //Timer
  ui->timeLabel->setText(seconds.toString("mm:ss"));
  timer = new QTimer();
  connect(timer, SIGNAL(timeout()), this, SLOT(slotTimer()));

  ui->goalLabel->setText(QString::number(goal));

}

MainWindow::~MainWindow()
{
  delete ui;
}


//Создание таблицы Шульте
void MainWindow::createTable() {
  QVector<int> numbers; // Массив номеров

  //Заполнение массива номеров
  for (int i = 1; i <= 25; ++i) {
      numbers.push_back(i);
    }

  //Перемешиваем массив номеров случайным образом с помощью STL <algorithm>
  std::random_shuffle(numbers.begin(), numbers.end());

  int num = 0; // Счётчик элементов массива

  //Создание кнопок
  for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < 5; ++j) {
          PlayButton *pb = new PlayButton(numbers[num++]); //Присваивание кнопке номера и переход к следующему номеру
          ui->btnLayout->addWidget(pb,i, j); //Добавление кнопки на слой
          connect(pb, SIGNAL(clicked()), this, SLOT(slotGetNumber())); //Соединяем кнопку с событием
          if (i == j && j == 2) {
              pb->setStyleSheet("color:blue; font-size: 16px;"); // Отмечаю центральную кнопку цветом
            }

          //Если запуск первый, кнопки недоступны
          if (!first) {
              pb->setEnabled(true);
            } else {
              pb->setEnabled(false);
            }
        }
    }
}

//Удаление "старых" кнопок
void MainWindow::clearTable()
{
  for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < 5; ++j) {
          QWidget *widget = ui->btnLayout->itemAtPosition(i,j)->widget();
          ui->btnLayout->removeWidget(widget);
          widget->hide();
        }
    }


}


//Запись результата в файл
void MainWindow::writeResult()
{
  QFile file ("save.bin");


  QDataStream stream (&file);

  file.open(QIODevice::Append);
  stream << seconds;
  file.close();
}

//Выход
void MainWindow::on_action_2_triggered()
{
    this->close();
}

//Старт
void MainWindow::on_startButton_clicked()
{
  QMessageBox msgStart;
  msgStart.setText("Принцип работы: \n"
                   "1. Сфокусируйте взгляд на центральном квадрате таблицы \n"
                   "2. Найдите все числа от 1 до 25 \n"
                   "3. Нажимайте кнопки строго по порядку, каждая ошибка добавляет секунду Вашему результату");
  msgStart.exec();

  // Обнуление данных
  first = false;
  goal = 1;
  ui->goalLabel->setText(QString::number(goal));

  seconds.setHMS(0, 0, 0, 0);
  ui->timeLabel->setText(seconds.toString("mm:ss"));
  timer->start(1000);


  clearTable();  // Удаляю старую таблицу Шульте
  createTable(); // Создаю новую  таблицу Шульте


}

void MainWindow::slotGetNumber()
{
  //Определяем объект, который вызвал сигнал
   PlayButton *button = (PlayButton*) sender();

   //Проверка правильности нажатия
    if (button->text() == "25" && button->text() == QString::number(goal)) {
          button->setEnabled(false);
          timer->stop();

          QMessageBox msg;
          msg.setText("Отлично! Ваш результат: " + seconds.toString("mm:ss") + " секунд.");
          msg.exec();

          writeResult(); // Запись результата

          //goal = 1;
         // ui->goalLabel->setText(QString::number(goal));

        } else if (button->text() == QString::number(goal)) {
       //* После чего делаем её недоступной и переводим требуемый номер на 1
       button->setEnabled(false);
       ui->goalLabel->setText(QString::number(++goal));
     } else {
       seconds = seconds.addSecs(1); // Штрафная секунда
       ui->timeLabel->setText("<FONT COLOR=#FF0000>" + seconds.toString("mm:ss") + "</FONT>"); // Перекрашиваем текст в красный, чтобы показать ошибку
       error = true; // Переключаем error
     }



}

//Ежесекундные операции
void MainWindow::slotTimer()
{
  seconds = seconds.addSecs(1); //Прибавить секунду

  if (!error) {
      ui->timeLabel->setText(seconds.toString("mm:ss")); // Обновить данные
    }
  else {
      error = !error; // Вернуть значение error
    }

}

void MainWindow::on_action_triggered()
{
    progressWindow = new Progress();

    progressWindow->show();
}
