#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <fstream>
using namespace std;
ifstream hiScoreRead("highscore.txt");
bool gameOver;
const int width = 20;
const int height = 20;
int x,y, fruitX,fruitY,score,tailSize;
int highScore=0;
string highScoreName;
char filler;
int tailX[100]; int tailY[100];
enum eDirection{STOP =0, LEFT,RIGHT,UP,DOWN};
eDirection dir;
void startScreen(){
    cout<<" Welcome to Snake! "<<endl<<"   By Chad Kalil   "<<endl<<" To play, press Y"<<endl<<endl<<endl;
    cout<<" The current High Score is: ";
    hiScoreRead>>highScore>>highScoreName;
    hiScoreRead.close();
    if (highScore==0);
    else
        cout<<highScore<<" by: "<<highScoreName;

}
void Setup()
{
    gameOver=false;
    dir = STOP;
    x=width/2; //center the head of the snake
    y=height/2;
    fruitX= rand()%width; //spawn a random fruit
    fruitY=rand()%height; //todo what if fruit is 0
    score=0;
    for (int i=0;i<100;i++){ //resets the snake tail for a new game
        tailX[i]=0;tailY[i]=0;
    }
    tailSize=0; //reset tail size
}
void Draw()
{
system("cls"); //clears the console
for (int i=0; i<width+2;i++)
    cout<<"#";
cout<<endl;
for (int i=0; i<height;i++)
    {
        for (int j=0; j<=width; j++){
            if (j==0)
                cout<<"#";
            else if (j==x && i==y)
                cout<<"O";
            else if (j==fruitX && i==fruitY)
                cout<<"F";
            else
            {
                bool print = false;
                for (int k=0;k<tailSize;k++){
                    if (tailX[k]==j & tailY[k]==i) {
                        cout << "o";
                        print = true;
                    }

                }
                if (!print)
                    cout<<" ";
            }

            if (j==width)
                cout<<"#";
        }
        cout<<endl;
    }

for (int i=0;i<width+2;i++)
    cout<<"#";
cout<<endl;
cout<<"Current Score: "<<score<<endl;
}
void Input()
{
    if (_kbhit()){
        switch(_getch()){
            case 'a':
                dir=LEFT;
                break;
            case 'd':
                dir=RIGHT;
                break;
            case 's':
                dir=DOWN;
                break;
            case 'w':
                dir=UP;
                break;
            case'x':
                gameOver=true;
                break;

        }
    }
}
void Logic()
{
    int prevX= tailX[0];
    int prevY= tailY[0];
    int prev2X, prev2Y;
    tailX[0]=x;
    tailY[0]=y;
    for (int i=1;i<tailSize;i++)
    {
        prev2X=tailX[i];
        prev2Y=tailY[i];
        tailX[i]=prevX;
        tailY[i]=prevY;
        prevX=prev2X;
        prevY=prev2Y;
    }
    switch(dir){
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }
    if (x > width || x <0 || y>height || y<0)
        gameOver=true;
    for (int i=0;i<tailSize;i++){
        if (x==tailX[i] && y==tailY[i])
            gameOver=true;
    }
    if (x==fruitX && y==fruitY){
        tailSize++;
        score++;
        fruitX= rand()%width; //spawn a random fruit
        fruitY=rand()%height;
    }
}
int main() {
    startScreen();
    char userInput;
    userInput=getch();
    while (userInput=='y'|| userInput=='Y') {
        Setup();
        while (!gameOver) {
            Draw();
            Input();
            Logic();
            Sleep(20);
        }
        cout << "Game Over" << endl;
        if (score>highScore){
            cout<<"High Score!!!"<<endl;
            highScore=score;
            cout<<"Please enter your name followed by enter"<<endl;
            cin>>highScoreName;
            ofstream hiScore("highscore.txt");
            hiScore<<highScore<<" "<<highScoreName;
            hiScore.close();
        }
        else
            cout<<"The current high score is "<<highScore<<" by "<<highScoreName<<endl;
        cout << "Your Final Score: " << score<<endl;
        cout << "New Game? If yes press Y"<<endl;
        Sleep(500); //todo find a way to make this not autoquit when you're turning as hit
        userInput=getch();
    }



return 0;
}
