#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
//#include <time.h>
#include <iostream>

using namespace sf;


const int M = 13;
const int N = 6;

int field[M][N] = {0};

struct Point
{int x,y,numColor;} a[3], b[3],aux[6];

int c[3];

int figures[1][3] =
{
	0,2,4 // I
};


bool centinela=false;

int puntuacion=0,jewels=0,level=0,auxi=1;
double multiplicadordelay=0.02;

bool check()
{
   for (int i=0;i<3;i++)
	  if (a[i].x<0 || a[i].x>=N || a[i].y>=M) return 0;
      else if (field[a[i].y][a[i].x]) return 0;

   return 1;
};


int main()
{
    srand(time(0));

    sf::RenderWindow window;
    window.create(sf::VideoMode(1280, 720), "Columns, baby!");

    window.setFramerateLimit(60);

    Texture t1,t2,t3;
	t1.loadFromFile("images/tilesmia.png");
	t2.loadFromFile("images/fondo.png");
    t3.loadFromFile("images/gameover.png");

	Font font;
	font.loadFromFile("images/majorforce.ttf");
    sf::Text mytextpuntos;
    sf::Text mytextlevel;
    sf::Text mytextjewels;

    sf::Clock relojito;


	Sprite s(t1), background(t2),  siguienteficha(t1),  gameover(t3);

    int dx=0; bool rotate=0; int colorNum=1;
	float timer=0,delay=0.5;

	Clock clock;

    a[0].x = 3, a[0].y = 1;
    a[1].x = 3, a[1].y = 2;
    a[2].x = 3, a[2].y = 3;
    a[0].numColor = 1+rand()%6;
    a[1].numColor = 1+rand()%6;
    a[2].numColor = 1+rand()%6;
    c[0] = 1+rand()%6;
    c[1] = 1+rand()%6;
    c[2] = 1+rand()%6;
    bool unavez=false;


    while (window.isOpen())
    {
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer+=time;
        window.setKeyRepeatEnabled(false);
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();

			if (e.type == Event::KeyPressed)
			  if (e.key.code==Keyboard::Up) rotate=true;
			  else if (e.key.code==Keyboard::Left) dx=-1;
			  else if (e.key.code==Keyboard::Right) dx=1;
		}

	if (Keyboard::isKeyPressed(Keyboard::Down)) delay=0.05;

	//// <- Move -> ///
	for (int i=0;i<3;i++)
	{ b[i]=a[i]; a[i].x+=dx;
	//std::cout<<a[i].numColor<<"  "<<std::endl;
	}

    if (!check())
    for (int i=0;i<3;i++){

    a[i]=b[i];




}
	//////Rotate//////
	if (rotate)
	  {

        int aux=a[2].numColor;
        a[2].numColor=a[1].numColor;
        a[1].numColor=a[0].numColor;
        a[0].numColor=aux;

   	    if (!check()) for (int i=0;i<3;i++) a[i]=b[i];
	  }

	///////Tick//////

	if (timer>delay)
	  {
	    for (int i=0;i<3;i++) { b[i]=a[i]; a[i].y+=1;

}
        puntuacion++;
		if (!check())
		{
		 for (int i=0;i<3;i++){
		 /*
		    std::cout<<"La x de a = "<<b[i].x<<"    La y de a = "<<b[i].y;
            std::cout<<std::endl;
            std::cout<<"La x de b = "<<b[i].x<<"    La y de b = "<<b[i].y;
            std::cout<<std::endl;
            std::cout<<"El color de a  "<<a[i].numColor;
            std::cout<<std::endl;
            */
        field[b[i].y][b[i].x]=a[i].numColor;
        //c[i]= 1+rand()%7;


        }
        ////CREACION SIGUIENTE PIEZA////
		 for (int i=0;i<3;i++)
		   {
		   	//colorNum=1+rand()%7;

		    a[i].x = 3;
		    a[i].y = i;
		    a[i].numColor = c[i];
            c[i]= 1+rand()%6;

		   }

		}

	  	timer=0;
	  }

    ////BORRAR LINEAS HORIZONTALES+PUNTUACION////

	for (int i=M-1;i>0;i--)
	{
		for (int j=0;j<N;j++)
		{
		    if (field[i][j]!=0){

            int count=0;
		    int x=field[i][j];
		    //aux[i][j]

            int t=j;
            while(x==field[i][t]&&t<N){
            t++;
            count++;

            }

                if(count>2){
                jewels+=count;
                puntuacion+=10*count;
                for (int z=j;z<N&&count!=0;z++){

                    if(x==field[i][z]){

                    field[i][z]=0;
                    count--;

                    }

                    }
                }
		    }
		}

	}

    ////BORRAR LINEAS VERTICALES+PUNTUACION////

	for (int j=0;j<N;j++)
	{

		for (int i=M-1;i>0;i--)
		{

            if(field[i][j]!=0){

            int t=i;
            int count=0;
            int x=field[i][j];

            while (x==field[t][j]&&t>0)
            {
            t--;
            count++;
            }


            if(count>2){
            jewels+=count;
            puntuacion+=10*count;
                for(int h=i;h>0&&count!=0;h--){
                field[h][j]=0;
                count--;

                }
                }
            }

        }


    }


    ////BORRAR DIAGONAL DE ABAJO IZQUIERDA A ARRIBA DERECHA+PUNTUACION////


    for(int j=0;j<N;j++)
    {

        for(int i=M-3;i>=0;i--)
        {

        int count=0;
        int x=field[i][j];
            if(x!=0)
            for(int z=i,t=j;z<M&&t<N;z++,t++)
            {

                if(x==field[z][t]){

                count++;

                }
                else{
                z=66;

                }

            }
            if(count>2){
            jewels+=count;
            puntuacion+=10*count;
            for(int z=i,t=j;count>0&&z<M&&t<N;z++,t++)
            {
            field[z][t]=0;
            count--;
            }

            }




        }

    }

    ////BORRAR DIAGONAL DE ABAJO DERECHA A ARRIBA IZQUIERDA+PUNTUACION////


    for(int j=N-1;j>=0;j--)
    {

        for(int i=M-3;i>=0;i--)
        {

        int count=0;
        int x=field[i][j];
            if(x!=0)
            for(int z=i,t=j;z<M&&t>=0;z++,t--)
            {

                if(x==field[z][t]){

                count++;

                }
                else{
                z=66;

                }

            }
            if(count>2){
            jewels+=count;
            puntuacion+=10*count;
            for(int z=i,t=j;count>0&&z<M&&t>=0;z++,t--)
            {
            field[z][t]=0;
            count--;
            }
            }



        }

    }

	////BUSCAR CEROS Y CORRER LA MATRIZ HACIA ARRIBA////

	for (int j=0;j<N;j++)
	{

		for (int i=M-1;i>0;i--)
		{

            int t=i;
            int count=0;

            while (field[i][j]==0&&field[t-1][j]!=0&&t>0)
            {
            t--;
            count++;
            }

            if(count>0)
                for(int h=i;h>0&&count!=0;h--){
                field[h][j]=field[h-1][j];
                count--;


                if(count==0){
                field[h-1][j]=0;
                }

                }

        }


    }

    ////puntuacion////

        std::stringstream sspuntos;
        sspuntos << puntuacion;
        mytextpuntos.setString(sspuntos.str());
        mytextpuntos.setFont(font);
        mytextpuntos.setPosition(387,391);

        std::stringstream sslevel;
        sslevel << level;
        mytextlevel.setString(sslevel.str());
        mytextlevel.setFont(font);
        mytextlevel.setPosition(387,493);

        std::stringstream ssjewels;
        ssjewels << jewels;
        mytextjewels.setString(ssjewels.str());
        mytextjewels.setFont(font);
        mytextjewels.setPosition(387,598);

    ////////auxilio//////////
    dx=0; rotate=0; delay=0.5;

    ////Sumar nivees y aumentar tick////
    if(puntuacion>250*auxi){

    level++;
    delay=delay-(auxi*multiplicadordelay);
    auxi++;
    //std::cout<<"delay1"<<delay<<std::endl;
    }

    if(delay<0.09)
    delay=0.1;



    ////endgame putothorgordo////

    for(int j=0;j<N&&centinela==false;j++){
        if(field[0][j]!=0){

        centinela=true;
        relojito.restart();
        //window.close();
        }

    }
    //std::cout<<"relojito: "<<relojito.getElapsedTime().asSeconds()<<std::endl;
    if(relojito.getElapsedTime().asSeconds()>3&&centinela==true){
    window.close();

    }


    /////////draw//////////
    window.clear(Color::White);

    if(centinela==true){
    window.draw(gameover);
    }

    else{

    window.draw(background);

    window.draw(mytextpuntos);
    window.draw(mytextlevel);
    window.draw(mytextjewels);


	for (int i=0;i<M;i++){
	//std::cout<<std::endl;
	 for (int j=0;j<N;j++)
	   {
	   // std::cout<<field[i][j];
	   	for (int x=0;x<3;x++)
	  {
        //std::cout<<c[x];
        siguienteficha.setTextureRect(IntRect(c[x]*34,0,34,34));
		siguienteficha.setPosition(456,209+34*x);
		//siguienteficha.move(28,31);
        window.draw(siguienteficha);

		s.setTextureRect(IntRect(a[x].numColor*34,0,34,34));
		s.setPosition(a[x].x*34+1,a[x].y*34+1);
		s.move(536,206); //offset
		window.draw(s);
	  }
         if (field[i][j]==0) continue;
		 s.setTextureRect(IntRect(field[i][j]*34,0,34,34));
		 s.setPosition(j*34+1,i*34+1);
		 s.move(536,206); //offset
		 window.draw(s);
	   }


}

    }
//	window.draw(frame);
 	window.display();
	}

    return 0;
}
