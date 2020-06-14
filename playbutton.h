/*Заголовочный файл кнопки для игры*/
#ifndef PLAYBUTTON_H
#define PLAYBUTTON_H

#include <QPushButton>

class PlayButton : public QPushButton
{
public:
  PlayButton(const int& number);
  ~PlayButton();

};

#endif // PLAYBUTTON_H
