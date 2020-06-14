/*Реализация кнопки для игры*/

#include "playbutton.h"


PlayButton::PlayButton(const int& number)
{
  this->setFixedSize(100,100);
  this->setText(QString::number(number));
  this->setStyleSheet("font-size: 16px;");
}

PlayButton::~PlayButton()
{

}
