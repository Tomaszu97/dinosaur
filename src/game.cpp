#include "game.hpp"

Game::Game():
    window(sf::VideoMode(800,333), "Dinosaur - the game",sf::Style::Close|sf::Style::Titlebar),
    player(sf::Vector2f(100.f, 283.f))
{
    dinosaurTex.loadFromFile("data/dinosaur-animated.png");
    coinTex.loadFromFile("data/coin-animated.png");
    obstacleTex.loadFromFile("data/cactus-animated.png");
    backgroundTex.loadFromFile("data/background-animated.png");
    menuBackgroundTex.loadFromFile("data/menuBackground.png");
    scoreboardBackgroundTex.loadFromFile("data/scoreboardBackground.png");
    playButtonTex.loadFromFile("data/playButton.png");
    scoreboardButtonTex.loadFromFile("data/scoreboardButton.png");
    exitButtonTex.loadFromFile("data/exitButton.png");
    backToMenuButtonTex.loadFromFile("data/backToMenuButton.png");
    menuMusic.openFromFile("data/elevator.wav");
    inGameMusic.openFromFile("data/runningInThe90s.wav");
    font1.loadFromFile("data/DejaVuSans-Bold.ttf");
    coinSoundBuf.loadFromFile("data/coinSound.wav");
    cactusSoundBuf.loadFromFile("data/oof.wav");

    window.setFramerateLimit(120);
    window.setVerticalSyncEnabled(true);
    player.setTexture(dinosaurTex);
    player.setAnimationGrid(8,2);
    background.setTexture(backgroundTex);

    background.setAnimationGrid(1,1);

    background.setPosition((float)window.getSize().x/2, (float)window.getSize().y/2);
    scoreText.setFont(font1);
    scoreText.setColor(sf::Color(94,72,5,255));
    coinSound.setBuffer(coinSoundBuf);
    cactusSound.setBuffer(cactusSoundBuf);
    inGameMusic.setVolume(80);
    menuMusic.setLoop(true);
    inGameMusic.setLoop(true);
    std::srand((int)std::time(nullptr));

}

void Game::procEvents()
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            gameState = CLOSING;
        }
    }
}

void Game::update(sf::Time deltaTime)
{
    float deltaT = deltaTime.asSeconds();
    tickCounter++;
    if(tickCounter == 1200)  tickCounter = 1;

    ///#####################################################
    ///Polymorphism test!
    ///All of them use sayHello() functions derived from Entity, but those functions do many things
    std::vector<Entity*> sampleEntities;
    sampleEntities.push_back(&background);  ///Entity
    sampleEntities.push_back(&player);      ///Player
    if(!obstacleArray.empty())  sampleEntities.push_back(&obstacleArray[0]); ///Obstacle
    if(!coinArray.empty())      sampleEntities.push_back(&coinArray[0]);     ///Coin

    for(auto currentEntity: sampleEntities) ///c++11 again
    {
        currentEntity->sayHello();
    }

    ///#####################################################
    ///check escape button
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::M) )gameState = MENU;

    ///#####################################################
    ///jump!
    ///if dinosaur is in the air - decrease its vertical speed

    if(player.getPosition().y < player.getStartingPosition().y)
    {
        float fallFaster = 1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  fallFaster = 4;
        player.setMovementVector(player.getMovementVector()+(sf::Vector2f(0.f, 8000.f)*deltaT*fallFaster));


        ///if dinosaur will land below or on the ground in the next tick - stop jumping and return to starting position
        if((player.getPosition().y+player.getMovementVector().y*deltaT) >= player.getStartingPosition().y)
        {
            player.setPosition(player.getStartingPosition());
            player.setMovementVector(sf::Vector2f(0.f, 0.f));
            player.changeTrack(0);
        }
    }
    ///if dinosaur is on the ground and space is pressed - set vertical movement speed
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player.getPosition().y == player.getStartingPosition().y)
    {
        player.setMovementVector(sf::Vector2f(0.f, -2400.f));
        player.setSpinning(1);
        player.changeTrack(1);
    }

    ///#####################################################
    ///rotate
    if(player.isSpinning())
    {
        player.rotate(5);
        if(abs(player.getRotation()) == 0)   player.setSpinning(0);
    }

    ///#####################################################
    ///spawn window
    if(tickCounter%150 == 0)
    {
        ///spawn a cactus
        if(std::rand()%4 == 1)
        {
            Obstacle obstacle;
            obstacle.setTexture(obstacleTex);
            obstacle.setAnimationGrid(5,1);
            obstacle.setPosition(sf::Vector2f(800.f, 280.f));
            obstacle.setMovementVector(sf::Vector2f(-800.f*hardnessCounter, 0.f));
            obstacleArray.push_back(obstacle);
        }
        ///spawn coins
        else if(std::rand()%4 == 1)
        {
            Coin coin;
            coin.setTexture(coinTex);
            coin.setAnimationGrid(6,1);
            coin.setScale(0.6f, 0.6f);
            coin.setPosition(sf::Vector2f(800.f, 280.f));
            coin.setMovementVector(sf::Vector2f(-800.f*hardnessCounter, 0.f));
            coinArray.push_back(coin);
        }
        else if(std::rand()%8 == 1)
        {
            Coin coin;
            coin.setTexture(coinTex);
            coin.setAnimationGrid(6,1);
            coin.setScale(0.6f, 0.6f);
            coin.setColor(sf::Color::Red);
            coin.setPosition(sf::Vector2f(800.f, 150.f));
            coin.setMovementVector(sf::Vector2f(-800.f*hardnessCounter, 0.f));
            coinArray.push_back(coin);
        }
        else if(std::rand()%10 == 1)
        {
            Coin coin;
            coin.setTexture(coinTex);
            coin.setAnimationGrid(6,1);
            coin.setScale(0.6f, 0.6f);
            coin.setColor(sf::Color::Cyan);
            coin.setPosition(sf::Vector2f(800.f, 50.f));
            coin.setMovementVector(sf::Vector2f(-800.f*hardnessCounter, 0.f));
            coinArray.push_back(coin);
        }
    }

    ///#####################################################
    ///increase hardness
    hardnessCounter += 0.00003f;
    if(hardnessCounter > 2) hardnessCounter = 2;
    if(hardnessCounter > 1.3)   inGameMusic.setPitch(1.25);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) hardnessCounter=1.3f;

    ///#####################################################
    ///animate objects

    if(tickCounter%8 == 0)
    {
        player.updateAnimation();
        background.updateAnimation();
        for(int i=0; i<(int)obstacleArray.size(); i++)   obstacleArray[i].updateAnimation();
        for(int i=0; i<(int)coinArray.size(); i++)       coinArray[i].updateAnimation();
    }

    ///#####################################################
    ///move every object according to its speed
    ///detect collisions and do stuff with it
    ///delete objects outside visible area

    player.move(player.getMovementVector()*deltaT);

    for(int i=0; i<(int)obstacleArray.size(); i++)
    {
        obstacleArray[i].move(obstacleArray[i].getMovementVector()*deltaT);
        if(!obstacleArray[i].getGlobalBounds().intersects(background.getGlobalBounds()))    obstacleArray.erase(obstacleArray.begin()+i);
        else if(obstacleArray[i].getGlobalBounds().intersects(player.getGlobalBounds()))
        {
            gameState = MENU;
            reset();
            cactusSound.play();
        }
    }

    for(int i=0; i<(int)coinArray.size(); i++)
    {
        coinArray[i].move(coinArray[i].getMovementVector()*deltaT);
        if(!coinArray[i].getGlobalBounds().intersects(background.getGlobalBounds())) coinArray.erase(coinArray.begin()+i);
        else if(coinArray[i].getGlobalBounds().intersects(player.getGlobalBounds()))
        {
            ///add certain amount of score depending on coins color
            if(coinArray[i].getColor() == sf::Color::Cyan)   player.addScore(100);
            else if(coinArray[i].getColor() == sf::Color::Red)   player.addScore(50);
            else    player.addScore(10);
            coinArray.erase(coinArray.begin()+i);

            std::string temp = "SCORE: ";
            temp += std::to_string(player.getScore());
            scoreText.setString(temp);

            coinSound.play();
        }
    }

}

void Game::render()
{
    window.clear();

    window.draw(background);
    for(auto currentObject : obstacleArray)   window.draw(currentObject);
    for(auto currentObject : coinArray) window.draw(currentObject);
    window.draw(player);
    window.draw(scoreText);

    window.display();
}

void Game::reset()
{
    hardnessCounter=1;
    inGameMusic.setPitch(1);
    obstacleArray.clear();
    coinArray.clear();
    player.resetScore();
    player.setSpinning(0);
    player.setRotation(0);
    player.setMovementVector(sf::Vector2f(0.f,0.f));
    player.setPosition(player.getStartingPosition());
    player.changeTrack(0);
}

void Game::runGame()
{
    Button escapeButton(window, sf::Keyboard::Escape);
    scoreText.setString("SCORE: 0");

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time TimePerFrame = sf::seconds(TICK);
    while (window.isOpen())
    {
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            procEvents();
            update(TimePerFrame);

            if(escapeButton.isClicked())
            {
                reset();
                gameState = MENU;   ///go back to menu if Escape is clicked
            }
            if(gameState != PLAYING)    return;
        }
        render();
        procEvents();
    }
}

void Game::displayMenu()
{
    sf::Sprite menuBackground;
    Button playButton(window, sf::Keyboard::R), scoreboardButton(window, sf::Keyboard::S), exitButton(window, sf::Keyboard::Escape);

    menuBackground.setTexture(menuBackgroundTex);
    playButton.setTexture(playButtonTex);
    scoreboardButton.setTexture(scoreboardButtonTex);
    exitButton.setTexture(exitButtonTex);

    playButton.setPosition(sf::Vector2f(300.f, 100.f));
    scoreboardButton.setPosition(sf::Vector2f(300.f, 170.f));
    exitButton.setPosition(sf::Vector2f(300.f, 240.f));

    sf::Clock c;
    sf::Time t = sf::seconds(0.05f);
    while(1)
    {
        ///take care of window close button
        procEvents();

        ///check if buttons are clicked by mouse or triggered using their binding
        if(playButton.isClicked())  gameState = PLAYING;
        if(exitButton.isClicked())  gameState = CLOSING;
        if(scoreboardButton.isClicked())    gameState = SCOREBOARD;

        if(gameState != MENU)   return;

        window.clear();
        window.draw(menuBackground);
        window.draw(playButton);
        window.draw(scoreboardButton);
        window.draw(exitButton);
        window.display();

        while(c.getElapsedTime() < t);
        c.restart();
    }
}

void Game::displayScoreboard()
{
    std::string tempScoreBoardString;
    std::ifstream file;
    file.open("data/scoreBoard.txt");
    if(file.good())
    {
        for(int i=0; i<10; i++)
        {
            std::string temp;
            std::getline(file, temp);
            tempScoreBoardString += temp;
            tempScoreBoardString += "\n";
        }
        file.close();
    }
    else
    {
        tempScoreBoardString = "Could'nt load\nscoreboard from file";
    }

    sf::Sprite scoreboardBackground;
    Button backToMenuButton(window, sf::Keyboard::Escape);
    sf::Text scoreboard;

    scoreboardBackground.setTexture(scoreboardBackgroundTex);
    backToMenuButton.setTexture(backToMenuButtonTex);
    scoreboard.setFont(font1);

    scoreboard.setString(tempScoreBoardString);
    scoreboard.setCharacterSize(25);
    scoreboard.setColor(sf::Color(94,72,5,255));

    scoreboard.setPosition(sf::Vector2f(20.f, 20.f));
    backToMenuButton.setPosition(sf::Vector2f(400.f, 150.f));

    sf::Clock c;
    sf::Time t = sf::seconds(0.05f);
    while(1)
    {
        ///take care of window close button
        procEvents();

        ///check if button is pressed either by mouse or its bint key
        if(backToMenuButton.isClicked())    gameState = MENU;
        if(gameState != SCOREBOARD)   return;

        window.clear();
        window.draw(scoreboardBackground);
        window.draw(backToMenuButton);
        window.draw(scoreboard);
        window.display();

        while(c.getElapsedTime() < t);
        c.restart();
    }
}

void Game::start()
{
    while(1)
    {
        switch(gameState)
        {
        case MENU:
            menuMusic.play();
            displayMenu();
            menuMusic.pause();
            break;

        case PLAYING:
            inGameMusic.play();
            runGame();
            *this >> (std::string)"data/scoreBoard.txt";
            inGameMusic.pause();
            break;

        case SCOREBOARD:
            menuMusic.play();
            displayScoreboard();
            menuMusic.pause();
            break;

        case CLOSING:
            window.close();
            return;
        }
    }
}

bool Game::operator>>(const std::string &_fileName)
{
    ///update scoreboard to file
    std::vector<std::string> names;
    std::vector<int> scores;

    std::ifstream ifile;
    ifile.open(_fileName, std::ios::in);
    if(ifile.good())
    {
        std::string tempName;
        int tempScore;
        while(ifile >> tempName >> tempScore)   ///fill in vector arrays with names and scores
        {
            names.push_back(tempName);
            scores.push_back(tempScore);
        }

        if(names.empty() && scores.empty())     ///put current record in correct place
        {
            names.push_back(player.getName());
            scores.push_back(player.getHighScore());
        }
        else
        {
            for(int i=0; i<(int)names.size(); i++)
            {
                if(player.getHighScore() >= scores[i])
                {
                    names.insert(names.begin()+i, player.getName());
                    scores.insert(scores.begin()+i, player.getHighScore());
                    break;
                }
                else if(i == (int)names.size()-1)
                {
                    names.push_back(player.getName());
                    scores.push_back(player.getHighScore());
                }
            }
        }

        ifile.close();
    }

    std::ofstream ofile;
    ofile.open(_fileName, std::ios::out);
    if(ofile.good())
    {
        ofile.clear();
        for(int i=0; i<10; i++)
        {
            if(i < (int)names.size())
            {
                ofile << names[i] << "\t" << std::to_string(scores[i]) << "\n";              ///put top 10 scores back to file
            }
        }

        ofile.close();
        return 1;
    }

    return 0;
}
