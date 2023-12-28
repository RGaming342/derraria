#include <iostream>
#include <SFML/Graphics.hpp>
namespace pn{
	template<typename T>
	constexpr auto lerp(T a, T b, T t) -> T {
		return a + t * (b - a);
	}
	template<typename T>
	constexpr auto floor(T x) -> int {
		auto const xi = int(x);
		return (x < T(xi)) ? xi - 1 : xi;
	}
	template<typename T>
	constexpr auto fade(T t) -> T {
		return t * t * t * (t * (t * T(6.0) - T(15.0)) + T(10.0));
	}
	template<typename T>
	constexpr auto dot_grad(int hash, T xf) -> T {
		return (hash & 0x1) ? xf : -xf;
	}
	template<typename T>
	constexpr auto dot_grad(int hash, T xf, T yf) -> T {
		switch (hash & 0x7) {
			case 0x0: return  xf + yf;
			case 0x1: return  xf;
			case 0x2: return  xf - yf;
			case 0x3: return -yf;
			case 0x4: return -xf - yf;
			case 0x5: return -xf;
			case 0x6: return -xf + yf;
			case 0x7: return  yf;
			default:  return  T(0.0);
		}
	}
	template<typename T>
	constexpr auto dot_grad(int hash, T xf, T yf, T zf) -> T {
		switch (hash & 0xF) {
			case 0x0: return  xf + yf;
			case 0x1: return -xf + yf;
			case 0x2: return  xf - yf;
			case 0x3: return -xf - yf;
			case 0x4: return  xf + zf;
			case 0x5: return -xf + zf;
			case 0x6: return  xf - zf;
			case 0x7: return -xf - zf;
			case 0x8: return  yf + zf;
			case 0x9: return -yf + zf;
			case 0xA: return  yf - zf;
			case 0xB: return -yf - zf;
			case 0xC: return  yf + xf;
			case 0xD: return -yf + zf;
			case 0xE: return  yf - xf;
			case 0xF: return -yf - zf;
			default:  return  T(0.0);
		}
	}
	static constexpr unsigned char p[512] = {
		151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142,
		8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203,
		117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74,
		165, 71, 134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220,
		105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132,
		187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186,
		3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59,
		227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70,
		221, 153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178,
		185, 112, 104, 218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241,
		81, 51, 145, 235, 249, 14, 239, 107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176,
		115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195,
		78, 66, 215, 61, 156, 180,

		151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142,
		8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203,
		117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74,
		165, 71, 134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220,
		105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132,
		187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186,
		3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59,
		227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70,
		221, 153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178,
		185, 112, 104, 218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241,
		81, 51, 145, 235, 249, 14, 239, 107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176,
		115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195,
		78, 66, 215, 61, 156, 180,
	};
	template<typename T>
	constexpr auto perlin(T x) -> T {
		int const xi0 = floor(x);
		T const xf0 = x - T(xi0);
		T const xf1 = xf0 - T(1.0);
		int const xi = xi0 & 0xFF;
		T const u = fade(xf0);
		int const h0 = p[xi + 0];
		int const h1 = p[xi + 1];
		return lerp(dot_grad(h0, xf0), dot_grad(h1, xf1), u);
	}
	template<typename T>
	constexpr auto perlin(T x, T y) -> T {
		int const xi0 = floor(x) & 0xFF;
		int const yi0 = floor(y) & 0xFF;
		T const xf0 = x - T(xi0);
		T const yf0 = y - T(yi0);
		T const xf1 = xf0 - T(1.0);
		T const yf1 = yf0 - T(1.0);
		int const xi = xi0 & 0xFF;
		int const yi = yi0 & 0xFF;
		T const u = fade(xf0);
		T const v = fade(yf0);
		int const h00 = p[p[xi + 0] + yi + 0];
		int const h01 = p[p[xi + 0] + yi + 1];
		int const h10 = p[p[xi + 1] + yi + 0];
		int const h11 = p[p[xi + 1] + yi + 1];
		T const x1 = lerp(dot_grad(h00, xf0, yf0), dot_grad(h10, xf1, yf0), u);
		T const x2 = lerp(dot_grad(h01, xf0, yf1), dot_grad(h11, xf1, yf1), u);
		return lerp(x1, x2, v);
	}
	template<typename T>
	constexpr auto perlin(T x, T y, T z) -> T {
		int const xi0 = floor(x);
		int const yi0 = floor(y);
		int const zi0 = floor(z);
		T const xf0 = x - T(xi0);
		T const yf0 = y - T(yi0);
		T const zf0 = z - T(zi0);
		T const xf1 = xf0 - T(1.0);
		T const yf1 = yf0 - T(1.0);
		T const zf1 = zf0 - T(1.0);
		int const xi = xi0 & 0xFF;
		int const yi = yi0 & 0xFF;
		int const zi = zi0 & 0xFF;
		T const u = fade(xf0);
		T const v = fade(yf0);
		T const w = fade(zf0);
		int const h000 = p[p[p[xi + 0] + yi + 0] + zi + 0];
		int const h001 = p[p[p[xi + 0] + yi + 0] + zi + 1];
		int const h010 = p[p[p[xi + 0] + yi + 1] + zi + 0];
		int const h011 = p[p[p[xi + 0] + yi + 1] + zi + 1];
		int const h100 = p[p[p[xi + 1] + yi + 0] + zi + 0];
		int const h101 = p[p[p[xi + 1] + yi + 0] + zi + 1];
		int const h110 = p[p[p[xi + 1] + yi + 1] + zi + 0];
		int const h111 = p[p[p[xi + 1] + yi + 1] + zi + 1];
		T const x11 = lerp(dot_grad(h000, xf0, yf0, zf0), dot_grad(h100, xf1, yf0, zf0), u);
		T const x12 = lerp(dot_grad(h010, xf0, yf1, zf0), dot_grad(h110, xf1, yf1, zf0), u);
		T const x21 = lerp(dot_grad(h001, xf0, yf0, zf1), dot_grad(h101, xf1, yf0, zf1), u);
		T const x22 = lerp(dot_grad(h011, xf0, yf1, zf1), dot_grad(h111, xf1, yf1, zf1), u);
		T const y1 = lerp(x11, x12, v);
		T const y2 = lerp(x21, x22, v);
		return lerp(y1, y2, w);
	}
}

const std::string derraria_block_textures_png="derraria blocks V0.1.png";
const std::string derraria_player_stuff_textures_png="derraria player stuff V0.1.png";


std::vector<int> gen2DNoise(int worldseed,float zoom,int size,int xp,float maxValue) {
	std::vector<int> arrout(size,0);
	for (auto x = 0; x < size; ++x) {
		auto noise = (
				pn::perlin(double(x+xp) / (64.0/zoom), double(0), worldseed * 0.25) * 1.0 +
				pn::perlin(double(x+xp) / (32.0/zoom), double(0), worldseed * 0.75) * 0.5
			) / 0.61;
        arrout[x] = (noise * 0.5 + 0.5) * maxValue;
	}
	return arrout;
}

std::vector<std::vector<int>> gen3DNoise(int worldseed,float zoom,int sizex,int sizey,int xp,int yp){
	std::vector<std::vector<int>> arrout(sizex,std::vector<int> (sizey,0));
	for (auto y = 0; y < sizey; ++y) {
		for (auto x = 0; x < sizex; ++x) {
			auto noise = (
				pn::perlin(double(x+xp) / (64.0/zoom), double(y+yp) / (64.0/zoom), worldseed * 0.25) * 1.0 +
				pn::perlin(double(x+xp) / (32.0/zoom), double(y+yp) / (32.0/zoom), worldseed * 0.75) * 0.5
			) / 1.5;
			arrout[x][y] = (noise * 0.5 + 0.5) * 255.0;
		}
	}
	return arrout;
}

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
	block_textures[0].loadFromFile(derraria_block_textures_png,sf::IntRect(0,120,8,8));
	block_textures[1].loadFromFile(derraria_block_textures_png,sf::IntRect(56,0,8,8));
	block_textures[2].loadFromFile(derraria_block_textures_png,sf::IntRect(8,0,8,8));
	block_textures[3].loadFromFile(derraria_block_textures_png,sf::IntRect(16,0,8,8));
	block_textures[4].loadFromFile(derraria_block_textures_png,sf::IntRect(24,0,8,8));
	block_textures[5].loadFromFile(derraria_block_textures_png,sf::IntRect(32,0,8,8));
	block_textures[6].loadFromFile(derraria_block_textures_png,sf::IntRect(40,0,8,8));
	block_textures[7].loadFromFile(derraria_block_textures_png,sf::IntRect(48,0,8,8));
	block_textures[8].loadFromFile(derraria_block_textures_png,sf::IntRect(0,0,8,8));
	
	player_data player;
	player.texture.loadFromFile(derraria_player_stuff_textures_png,sf::IntRect(0,0,16,24));
	player.player.setTexture(player.texture);
	player.player.setOrigin(8,8);
	
	for(int i=0;i<world_SIZE_X;i++){
		world[i].resize(world_SIZE_Y);
		for(int j=0;j<world_SIZE_Y;j++){
			srand(time(NULL) + i+(j*100));
			world[i][j].ID=1;
			world[i][j].x=8*(i-(world_SIZE_X*0.5));
			world[i][j].y=8*(j-(world_SIZE_Y*0.5));
			world[i][j].displayable_block.setTexture(block_textures[world[i][j].ID]);
			world[i][j].displayable_block.setPosition(world[i][j].x,world[i][j].y);
		}
	}
	
	int xm=10;
	float z=0;
	
	//sf::Clock ck;
	window.setFramerateLimit(60);
	while(window.isOpen()){
		//FPS(ck);
		srand(time(NULL) + num);
		num = rand();
		
		for(int i=1;i<51;i++){
			for(int j=1;j<41;j++){
				world[i][j].ID=1;
				world[i][j].displayable_block.setTexture(block_textures[world[i][j].ID]);
			}
		}
		
		std::vector<int> arr=gen2DNoise(0,z,51,xm,40.0);
		for(int i=1;i<51;i++){
			arr[i]++;
			world[i][static_cast<int>(arr[i])].ID=8;
			world[i][static_cast<int>(arr[i])].displayable_block.setTexture(block_textures[world[i][static_cast<int>(arr[i])].ID]);
			std::cout<<arr[i]<<" ";
		}
		std::cout<<"\n\n";
		
		
		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed) window.close();
			
		}
		
		int speed=5;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){z-=0.01;}
			//player.player.move(0,-speed);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){xm-=speed;}
			//player.player.move(-speed,0);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){z+=0.01;}
			//player.player.move(0,speed);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){xm+=speed;}
			//player.player.move(speed,0);
		
		
		
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
