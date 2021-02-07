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

void Game::doAction(uint8_t playerIndex, uint8_t action)
{
    switch (action)
    {
    case UP:
        player[playerIndex].up();
        break;
    case DOWN:
        player[playerIndex].down();
        break;
    case LEFT:
        player[playerIndex].left();
        break;
    case RIGHT:
        player[playerIndex].right();
        break;
    case CENTER:
        player[playerIndex].center();
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
