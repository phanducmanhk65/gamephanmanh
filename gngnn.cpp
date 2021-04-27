
#include "function.h"
 #include "baseobject.h"
 #include "map.h"
 #include "mainobject.h"
 #include "imptimer.h"
 #include "threatobject.h"
 #include "text.h"
#include <iostream>
#include "SDL_syswm.h"

BaseObject g_background;
BaseObject menug;

TTF_Font* font=NULL ;
TextObject menugame[1];
bool InitData()
{
	//
	bool success = true;

	//Khởi tạo SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Cài texture
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Tạo cửa sổ
		gWindow = SDL_CreateWindow( "Phan Duc Manh", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Tạo renderer cho cửa sổ
			gscreen = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gscreen == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Khởi tạo màu
				SDL_SetRenderDrawColor( gscreen, 0xFF, 0xFF, 0xFF, 0xFF );

				//Khởi tạo load ảnh png
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				if(TTF_Init()==-1)
            {

		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
               success= false;

            }

			}


		}
	}





if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        success= false;
    }
    // Read file audio wav
    g_sound[0] = Mix_LoadWAV("sound//Laser.wav");
    g_sound[1] = Mix_LoadWAV("sound//rightfire.wav");
    if(g_sound[0]==NULL||g_sound[1]==NULL)
    {
        success= false;
    }
    font= TTF_OpenFont("font//dlxfont_.ttf",24);
    if(font==NULL)
    {
        success=false;
       printf("không mở đoc");
    }
	return success;
}
bool LoadBackground()//Hàm load ảnh nền
{


    bool ret = g_background.LoadImg("img//nen.png",gscreen);

    if(ret==false)
        return false;

    return true;
}
bool LoadMenu()
{
    bool men = menug.LoadImg("img//gameover.png",gscreen);
    if(!men)
        return false;
    return true;
}
bool state = false;

void close()//Hàm kết thúc
{
    g_background.Free();

    SDL_DestroyRenderer( gscreen );
    gscreen=NULL;
	SDL_DestroyWindow( gWindow );
	gWindow=NULL;

	IMG_Quit();
	SDL_Quit();
}

std::vector<Threatsobject*> MakeThreatList()//Dùng vector tạo 1 dãy các Threat(kẻ địch)
{
    std::vector<Threatsobject*> list_threats;

    Threatsobject* dynamic_threatS=new Threatsobject[20];//Tạo lớp threat động có thể di chuyển
    for(int i=0;i<20;i++)
    {
        Threatsobject* p_threat= (dynamic_threatS+ i);
        if(p_threat!=NULL)
        {
            p_threat->LoadImg("img//threat_left.png",gscreen);//Load ảnh threat động lên screen màn hình
            p_threat->set_clips();
              p_threat->set_type_move(1);
            p_threat->set_x_pos(500+i*500);//xét vị trí
            p_threat->set_y_pos(200);

            int  pos1= p_threat->get_x_pos()-60;
            int pos2= p_threat->get_x_pos()+60;

            p_threat->set_animation_pos(pos1,pos2);
              p_threat->set_input_left(1);
             list_threats.push_back(p_threat);
        }
    }

    Threatsobject* threats_obj = new Threatsobject[30];//Khởi tạo lớp threat không di chuyển, chỉ đứng im
    for(int i=0;i<30;i++)
    {
        Threatsobject* p_threat = (threats_obj+i);
        if(p_threat!=NULL)
        {
            p_threat->LoadImg("img//threat_level.png",gscreen);//Load ảnh threat tĩnh
            p_threat->set_clips();
            p_threat->set_x_pos(700+i*1200);
            p_threat->set_y_pos(250);

            p_threat->set_type_move(Threatsobject::STATIC_THREAT);
                 p_threat->set_input_left(0);
            BulletObject* p_bullet = new BulletObject();//Tạo đạn bắn cho threat tĩnh
           p_threat->InitBullet(p_bullet,gscreen);

            list_threats.push_back(p_threat);

        }
        if(p_threat==NULL)
            printf("cannot open");

    }

    return list_threats;
}






//Hàm main
int main( int argc, char* argv[] )
{
	ImpTimer fps_timer;
	if( InitData()==false )
	{
		printf( "Failed to initialize!\n" );
		return -1;
	}

    //menug.LoadImg("img//nen.png",gscreen);
 bool quit =false;


int ret_menu = Func::MenuGame(gscreen, font, "Play Game", "Exit", "img//gameover.png");
    if (ret_menu == 1)

        {
            quit=true;
        }







    if(LoadBackground()==false)
     return -1;
//Khởi tạo các đối tượng của chương trình

if(font=NULL)
{
   printf("Không mở được ttf");
    }

        //Load phần text

     GameMap game_map;//Tạo map cho game
     game_map.LoadMap("map//map01.dat");
     game_map.LoadTiles(gscreen);

    MainObject p_player;
    p_player.LoadImg("img//player_right.png",gscreen);//Load ảnh nhân vật chính
    p_player.set_clips();


    std::vector<Threatsobject*> threat_list= MakeThreatList();//Tạo lớp vector kẻ địch

    TextObject time_game;
    time_game.Setcolorr(TextObject::BLACK_TEXT);

//menug.LoadImg("img//nen.png",gscreen);
//menug.Render(gscreen,NULL);
//SDL_RenderPresent();



     while( !quit )//Vòng lặp cho chương trình luôn chạy đến khi bị quit
			{
			    fps_timer.start();
			while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
                     p_player.HandleInputAction(e,gscreen);//xử lý chuyển động
				}
				SDL_SetRenderDrawColor( gscreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
                SDL_RenderClear(gscreen);

                g_background.Render(gscreen,NULL);
                game_map.DrawMap(gscreen);//vẽ map



                Map map_data = game_map.getMap();

                p_player.HandleBullet(gscreen);//xử lý đạn bắn cho nhân vật
                p_player.SetMapXY(map_data.start_x_,map_data.start_y_);//set vị trí nhân vật

                p_player.DoPlayer(map_data);//thực hiện hoạt động cho player
                p_player.Show(gscreen);



                for(int i=0;i<threat_list.size();i++)
                {
                    Threatsobject* p_threat= threat_list.at(i);
                   if(p_threat!=NULL)
                   {

                       p_threat->SetMapXY(map_data.start_x_,map_data.start_y_);//set vị trí địch
                       p_threat->ImpMoveType(gscreen);//dạng chuyển động
                       p_threat->DoPlayer(map_data);//các hoạt động cho địch
                       p_threat->MakeBullet(gscreen,SCREEN_WIDTH,SCREEN_HEIGHT);//Tạo đạn bắn

                       p_threat->Show(gscreen);//Hiển thị lên screen


                       SDL_Rect rect_player = p_player.GetRectFrame();
                       bool Bcol1 = false;
                       std::vector <BulletObject*> tbullet_list = p_threat->get_bullet_list();
                       for (int n =0;n< tbullet_list.size();n++)
                       {
                           BulletObject* pt_bullet = tbullet_list.at(n);
                           if(pt_bullet)
                           {
                               Bcol1 = Func::checkCollision(pt_bullet->GetRect(),rect_player);
                               if(Bcol1)
                               {
                                   p_threat->RemoveBullet(n);

                                   break;
                               }
                           }
                       }


                      SDL_Rect rect_threat = p_threat->GetRectFrame();
                      bool Bcol2 = Func::checkCollision(rect_player,rect_threat);
                      if(Bcol1||Bcol2)
                      {
                         MessageBox(NULL,"GAME KET THUC","Info",MB_OK|MB_ICONSTOP);


                             p_threat->Free();

                              //menug.LoadImg("img//gameover.png",gscreen);

                             close();

                             SDL_Quit();
                              return 0;

                      }
                    }

                }
                game_map.SetMap(map_data);
                game_map.DrawMap(gscreen);//vẽ map di chuyển

                std::vector<BulletObject*>bullet_arr = p_player.get_bullet_list();//Dùng vector để tạo loạt đạn bắn
                for(int r=0;r<bullet_arr.size();r++)

                {
                    BulletObject* p_bullet = bullet_arr.at(r);
                    if(p_bullet!=NULL)
                    {
                       for(int t=0;t<threat_list.size();t++)
                       {
                           Threatsobject* obj_threat= threat_list.at(t);
                           if(obj_threat!=NULL)
                           {
                               SDL_Rect tRect;
                               tRect.x=obj_threat->GetRect().x;
                               tRect.y=obj_threat->GetRect().y;
                               tRect.w=obj_threat->get_width_frame();
                               tRect.h= obj_threat->get_height_frame();

                               SDL_Rect bRect = p_bullet->GetRect();

                               bool bCol = Func:: checkCollision(bRect,tRect);//check sự va chạm
                               if(bCol)
                               {
                                   p_player.RemoveBullet(r);
                                   obj_threat->Free();
                                   threat_list.erase(threat_list.begin()+t);//Xóa kẻ địch khỏi màn hình
                                   Mix_PlayChannel(-1, g_sound[0], 0);//Tạo tiếng khi địch chết
                               }
                           }
                       }
                    }
                }

              std::string strTime="Time: ";
		Uint32 time_val = SDL_GetTicks() / 1000;
		Uint32 val_time = 300;
		//strTime += val_time;
SDL_Color color[2] = { { 255, 23, 45 },{0 , 0, 0 } };
  if(val_time>0)
     {time_game.SetText(strTime);
   //time_game.GetText();
    time_game.Setcolor(color[0].r,color[0].g,color[0].b);
    //time_game.LoadFromRenderText(font,gscreen);
    //time_game.RenderText(gscreen,SCREEN_WIDTH-200,10);}
                SDL_RenderPresent( gscreen );
                int real_imp_time = fps_timer.get_ticks();
                int time_one_frame= 1000/FRAME_PER_SECOND;
                if(real_imp_time<time_one_frame)
                {
                    int delay_time=time_one_frame-real_imp_time;
                    if(delay_time>=0)
                    SDL_Delay(delay_time);
                }
			}}

     close();
  return 0;

}
