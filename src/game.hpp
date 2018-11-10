#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include "player.hpp"
#include "obstacle.hpp"
#include "coin.hpp"
#include "button.hpp"


#define TICK 0.005f

enum GameState
{
    MENU,
    PLAYING,
    SCOREBOARD,
    CLOSING
};

class Game
{
public:
    Game();
    void start();

private:
    sf::RenderWindow window;
    GameState gameState = MENU;
    int tickCounter = 0;    ///changing 1-1000, 1 per tick
    float hardnessCounter = 1;
    sf::Music menuMusic, inGameMusic;
    sf::SoundBuffer coinSoundBuf, cactusSoundBuf;
    sf::Sound coinSound, cactusSound;
    sf::Texture dinosaurTex, coinTex, obstacleTex, backgroundTex, menuBackgroundTex,
    scoreboardBackgroundTex, playButtonTex, scoreboardButtonTex, exitButtonTex, backToMenuButtonTex;
    sf::Font font1;
    sf::Text scoreText;
    Player player;
    Entity background;
    std::vector<Obstacle>   obstacleArray;
    std::vector<Coin>       coinArray;

    void procEvents();
    void update(sf::Time deltaTime);
    void render();
    void reset();
    void runGame();
    void displayMenu();
    void displayScoreboard();
    bool operator>>(const std::string &_filename);
};


#endif  // GAME

