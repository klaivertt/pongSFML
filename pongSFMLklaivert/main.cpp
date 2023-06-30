#include <SFML/Graphics.hpp>
#include <random>
#include <string>

using namespace sf;
using namespace std;

// Constantes pour la taille de la fenêtre de jeu
const int WIN_WIDTH = 1800;
const int WIN_HEIGHT = 900;

// Variables
RenderWindow window;
Font font;
Text txt;

float posRaquettesLeftX = 50;
float posRaquettesRightX = WIN_WIDTH - 70;
float posRaquettesLeftY = WIN_HEIGHT / 2;
float posRaquettesRightY = posRaquettesLeftY;
float RaquettesSpeed = 0.15f;
int RaquettesHeight = 150;
int RaquettesWidht = 20;

float ballSpeed = 0.05f;
Vector2f ballDir = Vector2f(1.5f, 2.0f);
float ballPosX = WIN_WIDTH / 2;
float ballPosY = WIN_HEIGHT / 2;

double interceptionProb = 0.8; // 80% de probabilité de récupérer la balle
int numHitBalls = 0;

int scoreJ1 = 0;
int scoreJ2 = 0;

Color colorRaquetteLeft = Color::Red;
Color colorRaquetteRight = Color::Blue;
Color colorBalle;

void SetText(Text& text, const string& str)
{
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(Color::White);
    text.setString(str);
    text.setPosition(Vector2f(WIN_WIDTH / 2 - text.getLocalBounds().width / 2, 20));
}

void UpdateBall()
{
    ballPosX += ballDir.x * ballSpeed;
    ballPosY += ballDir.y * ballSpeed;

    float ballRadius = 15.0f;

    if ((ballPosX - ballRadius < posRaquettesLeftX + RaquettesWidht &&
        ballPosX - ballRadius > posRaquettesLeftX &&
        ballPosY - ballRadius < posRaquettesLeftY + RaquettesHeight &&
        ballPosY + ballRadius > posRaquettesLeftY)
        ||
        (ballPosX + ballRadius < posRaquettesRightX + RaquettesWidht &&
            ballPosX + ballRadius > posRaquettesRightX &&
            ballPosY - ballRadius < posRaquettesRightY + RaquettesHeight &&
            ballPosY + ballRadius > posRaquettesRightY))
    {
        ballDir.x *= -1;
        if (ballPosX < WIN_WIDTH / 2)
        {
            colorBalle = colorRaquetteLeft;
        }
        else
        {
            colorBalle = colorRaquetteRight;
        }
    }

    if (ballPosX < 0)
    {
        scoreJ2++;
        ballPosX = WIN_WIDTH / 2;
        ballPosY = WIN_HEIGHT / 2;
        ballDir.x = -fabs(ballDir.x);
        ballDir.y *= -1;
        SetText(txt, to_string(scoreJ1) + " | " + to_string(scoreJ2));
        

        // Réinitialiser la probabilité d'interception de l'IA
        interceptionProb = 0.8;
    }

    if (ballPosX > WIN_WIDTH)
    {
        scoreJ1++;
        ballPosX = WIN_WIDTH / 2;
        ballPosY = WIN_HEIGHT / 2;
        ballDir.x = fabs(ballDir.x);
        ballDir.y *= -1;
        SetText(txt, to_string(scoreJ1) + " | " + to_string(scoreJ2));
        

        // Réinitialiser la probabilité d'interception de l'IA
        interceptionProb = 0.8;

        // Réinitialiser le nombre de balles touchées
        numHitBalls = 0;
    }

    if (ballPosY > WIN_HEIGHT || ballPosY < 0)
    {
        ballDir.y *= -1;
    }
}

void MoveAIPaddle()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    double randomProb = dis(gen);
    double moveProb = 0.6;

    
    double recoveryProb = 0.2;

    if (randomProb < moveProb)
    {
        if (ballPosY < posRaquettesRightY + RaquettesHeight / 2)
        {
            posRaquettesRightY -= RaquettesSpeed;
            if (posRaquettesRightY < 0)
                posRaquettesRightY = 0;
        }
        else
        {
            posRaquettesRightY += RaquettesSpeed;
            if (posRaquettesRightY + RaquettesHeight > WIN_HEIGHT)
                posRaquettesRightY = WIN_HEIGHT - RaquettesHeight;
        }

        double randomMoveProb = 0.1;
        double randomMoveAmount = 2.0;

        if (randomProb < randomMoveProb)
        {
            std::uniform_real_distribution<> randomMoveDis(-randomMoveAmount, randomMoveAmount);
            double randomMove = randomMoveDis(gen);
            posRaquettesRightY += randomMove;

            if (posRaquettesRightY < 0)
                posRaquettesRightY = 0;
            else if (posRaquettesRightY + RaquettesHeight > WIN_HEIGHT)
                posRaquettesRightY = WIN_HEIGHT - RaquettesHeight;
        }

        if (numHitBalls >= 1)
        {
            double decreaseProb = 0.05;
            double minProb = 0.3;

            interceptionProb -= decreaseProb;
            if (interceptionProb < minProb)
                interceptionProb = minProb;
        }
    }
}

void CheckBtn()
{
    if (Keyboard::isKeyPressed(Keyboard::Up))
    {
        posRaquettesLeftY -= RaquettesSpeed;
    }

    if (Keyboard::isKeyPressed(Keyboard::Down))
    {
        posRaquettesLeftY += RaquettesSpeed;
    }
}

int main()
{
    window.create(VideoMode(WIN_WIDTH, WIN_HEIGHT, 32), "Pong SFML C++", Style::Default);
    font.loadFromFile("res/poppins.ttf");
    SetText(txt, to_string(scoreJ1) + " | " + to_string(scoreJ2));

    CircleShape circleShape(15);
    circleShape.setPosition(ballPosX, ballPosY);

    RectangleShape rectangleShapeLeft(Vector2f(RaquettesWidht, RaquettesHeight));
    rectangleShapeLeft.setPosition(posRaquettesLeftX, posRaquettesLeftY);
    rectangleShapeLeft.setFillColor(colorRaquetteLeft);

    RectangleShape rectangleShapeRight(Vector2f(RaquettesWidht, RaquettesHeight));
    rectangleShapeRight.setPosition(posRaquettesRightX, posRaquettesRightY);
    rectangleShapeRight.setFillColor(colorRaquetteRight);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }

        CheckBtn();
        rectangleShapeLeft.setPosition(posRaquettesLeftX, posRaquettesLeftY);
        rectangleShapeRight.setPosition(posRaquettesRightX, posRaquettesRightY);

        UpdateBall();
        circleShape.setPosition(ballPosX, ballPosY);

        if (ballDir.x < 0 && colorBalle != colorRaquetteRight)
        {
            colorBalle = colorRaquetteRight;
        }
        else if (ballDir.x > 0 && colorBalle != colorRaquetteLeft)
        {
            colorBalle = colorRaquetteLeft;
        }

        MoveAIPaddle();

        window.clear(Color::Transparent);

        window.draw(txt);
        window.draw(circleShape);
        window.draw(rectangleShapeLeft);
        window.draw(rectangleShapeRight);
        circleShape.setFillColor(colorBalle);

        window.display();
    }

    return 0;
}
