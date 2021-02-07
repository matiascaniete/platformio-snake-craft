#include "Game.h"

Game::Game()
{
    this->snake[0] = Snake();
    this->snake[1] = Snake();
    this->player[0] = Player();
    this->player[1] = Player();

    this->snake[0].assignPlayer(this->player[0]);
    this->snake[1].assignPlayer(this->player[1]);
    this->mouse = Mouse();
}

void Game::init(Adafruit_PCD8544 &display)
{
    this->display = &display;

    display.begin();
    display.setContrast(50);

    snake[0].init(display.width(), display.height(), stepSize, BLACK, Position(stepSize * 2, stepSize * 2));
    snake[1].init(display.width(), display.height(), stepSize, WHITE, Position(display.width() - stepSize * 2, display.height() - stepSize * 2));
    mouse.init(display.width(), display.height(), stepSize);

    flags[FLAG_SOMEONE_ATE] = false;
}

void Game::welcome()
{
    display->setTextSize(2);
    display->setTextColor(BLACK);
    for (int i = -5; i <= 0; i++)
    {
        display->clearDisplay(); // clears the screen and buffer
        display->setCursor(i * 2, 10);
        display->println(F(" SNAKE"));
        display->println(F(" CRAFT"));
        display->display();
        delay(100);
    }

    delay(1000);
}

void Game::restart()
{
    snake[0].killed = 0;
    snake[0].ate = 0;

    snake[1].killed = 0;
    snake[1].ate = 0;
}

void Game::senseJoystick(uint8_t playerIndex, int joysticX, int joysticY, bool button)
{
    int ld = joysticX > JOY_MID + JOY_THR;
    int rd = joysticX < JOY_MID - JOY_THR;
    int dd = joysticY > JOY_MID + JOY_THR;
    int ud = joysticY < JOY_MID - JOY_THR;

    if (rd)
    {
        player[playerIndex].right();
    }

    if (ld)
    {
        player[playerIndex].left();
    }

    if (dd)
    {
        player[playerIndex].down();
    }

    if (ud)
    {
        player[playerIndex].up();
    }

    if (button)
    {
        player[playerIndex].center();
    }
}

void Game::senseIRRemoteDVD(uint8_t playerIndex, uint32_t value)
{
    // Códigos Sony DVD RMT-D178P
    switch (value)
    {
    case 0x9EB92:
        player[playerIndex].up();
        break;
    case 0x5EB92:
        player[playerIndex].down();
        break;
    case 0xDEB92:
        player[playerIndex].left();
        break;
    case 0x3EB92:
        player[playerIndex].right();
        break;
    case 0xD0B92:
        player[playerIndex].center();
        break;

    default:
        break;
    }
}

void Game::senseIRRemoteTV(uint8_t playerIndex, uint32_t value)
{
    // Códigos Sony TV RMT-TX300E
    switch (value)
    {

    case 0x2F0:
        player[1].up();
        break;
    case 0xAF0:
        player[1].down();
        break;
    case 0x2D0:
        player[1].left();
        break;
    case 0xCD0:
        player[1].right();
        break;
    case 0xA70:
        player[1].center();
        break;

    default:
        break;
    }
}

bool Game::compute(Snake &snake)
{
    if (mouse.isEatenBy(snake))
    {
        mouse.kill();
        mouse.born();
        if (mouse.killed > 4)
        {
            level++;
            mouse.killed = 0;
        }
        
        snake.grow();
        if (snake.ate > 4)
        {
            snake.getPlayer()->win();
            snake.ate = 0;
        }
        
        Serial.println(snake.getPlayer()->getScore());
        flags[FLAG_SOMEONE_ATE] = true;
    }

    if (snake.isEatenBy(snake))
    {
        snake.kill();
    }

    return false;
}

bool Game::compute(Snake &snake, Snake &otherSnake)
{
    if (snake.isEatenBy(otherSnake))
    {
        snake.kill();
        otherSnake.kill();

        return true;
    }

    compute(snake);

    return false;
}

bool Game::draw()
{
    snake[0].move(player[0].getDX() * stepSize, player[0].getDY() * stepSize);
    snake[1].move(player[1].getDX() * stepSize, player[1].getDY() * stepSize);

    bool c1 = compute(snake[1], snake[0]);
    bool c2 = compute(snake[0], snake[1]);

    snake[0].draw(*display);
    snake[1].draw(*display);
    mouse.draw(*display);

    display->setTextSize(1);
    display->println(level);

    display->display();

    if (c1 || c2)
    {
        return true;
    }

    return false;
}

int Game::getScore(uint8_t snakeIndex)
{
    return snake[snakeIndex].ate;
}

bool Game::someoneAte()
{
    bool flag = flags[FLAG_SOMEONE_ATE];
    flags[FLAG_SOMEONE_ATE] = false;
    return flag;
}

uint8_t Game::getLevel()
{
    return level;
}
