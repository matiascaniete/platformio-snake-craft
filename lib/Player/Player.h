#ifndef PLAYER_H
#define PLAYER_H

class Player
{
private:
    int stepSize;
    int dx, dy;

public:
    int looses = 0;
    int wins = 0;
    Player();
    void up();
    void down();
    void left();
    void right();
    void center();
    int getDX();
    int getDY();
    void loose();
    void win();
    int getScore();
};

#endif