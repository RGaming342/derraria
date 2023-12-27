#include <iostream>
#include <SFML/Graphics.hpp>

void FPS(sf::Clock& ck){
	float fps = ck.restart().asSeconds();
	std::cout << "Fps: " << 1.0f/fps << "\n\n\n";
}

struct block{
	int ID=0;
	int x=0,y=0;
	sf::Sprite displayable_block;
};

struct player_data{
	int x=0,y=0;
	sf::Texture texture;
	sf::Sprite player;
};

int main(){
	int num = 0;
	sf::RenderWindow window(sf::VideoMode(800,640),"DERRARIA");
	sf::Event event;
	std::vector<std::vector<block>> world;
	int world_SIZE_X=52,world_SIZE_Y=42;
	world.resize(world_SIZE_X);
	
	sf::View view;
	view.reset(sf::FloatRect(0, 0, 400, 320));
	sf::Texture block_textures[9];
	block_textures[0].loadFromFile("terraria.png",sf::IntRect(0,120,8,8));
	block_textures[1].loadFromFile("terraria.png",sf::IntRect(56,0,8,8));
	block_textures[2].loadFromFile("terraria.png",sf::IntRect(8,0,8,8));
	block_textures[3].loadFromFile("terraria.png",sf::IntRect(16,0,8,8));
	block_textures[4].loadFromFile("terraria.png",sf::IntRect(24,0,8,8));
	block_textures[5].loadFromFile("terraria.png",sf::IntRect(32,0,8,8));
	block_textures[6].loadFromFile("terraria.png",sf::IntRect(40,0,8,8));
	block_textures[7].loadFromFile("terraria.png",sf::IntRect(48,0,8,8));
	block_textures[8].loadFromFile("terraria.png",sf::IntRect(0,0,8,8));
	
	player_data player;
	player.texture.loadFromFile("player.png",sf::IntRect(0,0,16,24));
	player.player.setTexture(player.texture);
	
	for(int i=0;i<world_SIZE_X;i++){
		world[i].resize(world_SIZE_Y);
		for(int j=0;j<world_SIZE_Y;j++){
			srand(time(NULL) + i+(j*100));
			world[i][j].ID=rand()%8+1;
			world[i][j].x=8*(i-(world_SIZE_X*0.5));
			world[i][j].y=8*(j-(world_SIZE_Y*0.5));
			world[i][j].displayable_block.setTexture(block_textures[world[i][j].ID]);
			world[i][j].displayable_block.setPosition(world[i][j].x,world[i][j].y);
		}
	}
	
	int xm=0,ym=0;
	
	//sf::Clock ck;
	window.setFramerateLimit(60);
	while(window.isOpen()){
		//FPS(ck);
		srand(time(NULL) + num);
		num = rand();
		
		
		
		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed) window.close();
			
		}
		
		int speed=1;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			player.player.move(0,-speed);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			player.player.move(-speed,0);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			player.player.move(0,speed);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			player.player.move(speed,0);
		
		
		
		view.setCenter(player.player.getPosition().x,player.player.getPosition().y);
		
		window.setView(view);
		window.clear();
		for(int i=0;i<52;i++){
			for(int j=0;j<42;j++){
				window.draw(world[i][j].displayable_block);
			}
		}
		window.draw(player.player);
		window.display();
	}
	
	
	
	
	
	return 0;
}
