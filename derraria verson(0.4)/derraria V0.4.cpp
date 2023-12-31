
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>



struct ID{//total IDS(65536)
	struct System{//total SystemIDs(8192)
		//starts at (57344)
		static const int16_t UNPLACED_ORE=57344;
		
		
		//ends at (65535)
	};
	struct Game{//total GameIDs(57344)
		//starts at (0)
		static const int16_t COPPER_ORE=9;
		static const int16_t IRON_ORE=10;
		static const int16_t GOLD_ORE=11;
		
		
		//ends at (57343)
	};
};



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

const std::string derraria_block_textures_png="derraria blocks V0.4.png";
const std::string derraria_player_stuff_textures_png="derraria player stuff V0.4.png";

const std::string DERRARIA_SAVE_VERSON="derraria_V(0.4)/";

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
std::vector<std::vector<int>> gen3DNoise(int worldseed,float zoom,int sizex,int sizey,int xp,int yp,int maxValue){
	std::vector<std::vector<int>> arrout(sizex,std::vector<int> (sizey,0));
	for (auto y = 0; y < sizey; ++y) {
		for (auto x = 0; x < sizex; ++x) {
			auto noise = (
				pn::perlin(double(x+xp) / (64.0/zoom), double(y+yp) / (64.0/zoom), worldseed * 0.25) * 1.0 +
				pn::perlin(double(x+xp) / (32.0/zoom), double(y+yp) / (32.0/zoom), worldseed * 0.75) * 0.5
			) / 1.5;
			arrout[x][y] = (noise * 0.5 + 0.5) * maxValue;
		}
	}
	return arrout;
}
std::vector<int> combine2DNoise(std::vector<int> noise1,std::vector<int> noise2,float amp1,float amp2){
	std::vector<int> arrout(noise1.size(),0);
	for (long unsigned int x = 0; x < noise1.size(); ++x) {
		arrout[x]=((noise1[x]*amp1)+(noise2[x]*amp2));
	}
	return arrout;
}
std::vector<std::vector<int>> noiseSorter3D(std::vector<std::vector<int>> noise,int num1,int num2){
	std::vector<std::vector<int>> out(noise.size(),std::vector<int> (noise[0].size(),0));
	for (uint x = 0; x < noise.size(); ++x) {
		for (uint y = 0; y < noise[0].size(); ++y) {
			if(noise[x][y]>num1){ out[x][y]=num1; }else if(noise[x][y]>num2){ out[x][y]=num2; }else{ out[x][y]=0; }
		}
	}
	return out;
}



void FPS(sf::Clock& ck){
	float fps = ck.restart().asSeconds();
	std::cout << "Fps: " << 1.0f/fps << "\n\n\n";
}

struct block{
	int16_t ID=0;
	int x=0,y=0;
};

struct chunk{
	int x=0;
	int y=0;
	block data[16][16];
};

struct player_data{
	int32_t seed=0;
	int x=0,y=0;
};

void SETUP(player_data& player,bool LoadTrueMakeFalse){
	if(LoadTrueMakeFalse){
		std::ifstream file(DERRARIA_SAVE_VERSON + "player_data.bin",std::ios::in|std::ios::binary);
		file.seekg(0,std::ios::beg);
		file.read(reinterpret_cast<char*>(&player),sizeof(player));
		file.close();
	}else{
		std::ofstream file(DERRARIA_SAVE_VERSON + "player_data.bin",std::ios::trunc|std::ios::out|std::ios::binary);
		file.write(reinterpret_cast<char*>(&player),sizeof(player));
		file.close();
	}
}

void SAVE_CHUNK(player_data& player,chunk chunkdata){
	std::fstream file(DERRARIA_SAVE_VERSON + "chunk(" + std::to_string(chunkdata.x) + "," + std::to_string(chunkdata.y) + ").bin",std::ios::out|std::ios::in|std::ios::binary);
	
	if(file.is_open()){
		file.write(reinterpret_cast<char*>(&chunkdata),sizeof(chunkdata));
	}else{
		file.write(reinterpret_cast<char*>(&chunkdata),sizeof(chunkdata));
	}
	
	file.close();
}

bool LOAD_CHUNK(player_data& player,chunk& chunkdata,int32_t xm,int32_t ym){
	std::ifstream file(DERRARIA_SAVE_VERSON + "chunk(" + std::to_string(xm) + "," + std::to_string(ym) + ").bin",std::ios::in|std::ios::binary);
	
	if(file.is_open()){
		file.read(reinterpret_cast<char*>(&chunkdata),sizeof(chunkdata));
		file.close();
		return true;
	}else{
		file.close();
		return false;
	}
	return false;
}



chunk genChunk(player_data& player,chunk& chunkdata,int chunkX, int chunkY,int seed){
	chunk newChunk;
	if(!LOAD_CHUNK(player,newChunk,chunkX,chunkY)){
		std::ofstream filec(DERRARIA_SAVE_VERSON + "chunk(" + std::to_string(chunkX) + "," + std::to_string(chunkY) + ").bin",std::ios::out|std::ios::binary);
		filec.close();
		newChunk.x = chunkX;
		newChunk.y = chunkY;
		
		std::vector<int> arr=gen2DNoise(seed,0.25,16,chunkX*16,300.0);
		arr=combine2DNoise(arr,gen2DNoise(seed+1,1.0,16,chunkX*16,100),1,0.75);
		arr=combine2DNoise(arr,gen2DNoise(seed+2,1.62,16,chunkX*16,65),0.57,0.4);
		arr=combine2DNoise(arr,gen2DNoise(seed+3,3.0,16,chunkX*16,12),1,0.5);
		std::vector<std::vector<int>> ores=gen3DNoise(seed,11,16,16,chunkX*16,chunkY*16,255);
		ores=noiseSorter3D(ores,255,100);
		int blockID = 0;
		for (int x = 0; x < 16; ++x) {
			arr[x]-=100;
			for (int y = 0; y < 16; ++y){
				blockID = 0;
				if(arr[x]+1>y + chunkY * 16){
					blockID=6;
					if(ores[x][y]==0&&arr[x]+10<y + chunkY * 16){
						blockID=ID::System::UNPLACED_ORE;
					}
				}else if(arr[x]+2>y + chunkY * 16){
					blockID=8;
					if(ores[x][y]==0&&arr[x]+10<y + chunkY * 16){
						blockID=ID::System::UNPLACED_ORE;
					}
				}else if(y + chunkY * 16<250){
					blockID=12;
					if(ores[x][y]==0&&arr[x]+10<y + chunkY * 16){
						blockID=ID::System::UNPLACED_ORE;
					}
				}else if(arr[x]<y + chunkY * 16){
					blockID=2;
					if(ores[x][y]==0){
						blockID=ID::System::UNPLACED_ORE;
					}
				}
				newChunk.data[x][y].ID = blockID;
				newChunk.data[x][y].x = x + chunkX * 16;
				newChunk.data[x][y].y = y + chunkY * 16;
			}
		}
		int16_t checkaround[9]={0,0,0,0,0,0,0,0,0};
		bool good;
		for (int x = 0; x < 16; ++x) {
			for (int y = 0; y < 16; ++y){
				blockID = newChunk.data[x][y].ID;
				if(blockID==ID::System::UNPLACED_ORE){
					for (int i = 0; i < 9; ++i){
						checkaround[i]=0;
					}
					if (x > 0 && y > 0) checkaround[0] = newChunk.data[x-1][y-1].ID;
					if (x > 0) checkaround[1] = newChunk.data[x-1][y].ID;
					if (x > 0 && y < 15) checkaround[2] = newChunk.data[x-1][y+1].ID;
					if (y > 0) checkaround[3] = newChunk.data[x][y-1].ID;
					checkaround[4] = newChunk.data[x][y].ID;
					if (y < 15) checkaround[5] = newChunk.data[x][y+1].ID;
					if (x < 15 && y > 0) checkaround[6] = newChunk.data[x+1][y-1].ID;
					if (x < 15) checkaround[7] = newChunk.data[x+1][y].ID;
					if (x < 15 && y < 15) checkaround[8] = newChunk.data[x+1][y+1].ID;
					for (int i = 0; i < 9; ++i){
						if(checkaround[i]==ID::Game::COPPER_ORE||checkaround[i]==ID::Game::IRON_ORE||checkaround[i]==ID::Game::GOLD_ORE){
							blockID=checkaround[i];
							good=true;
							break;
						}else{
							good=false;
							
						}
					}
					if(!good){
						int prob=rand()%101;
						if(chunkY*16+y<1){
							if(prob>98){
								blockID=ID::Game::GOLD_ORE;
							}else if(prob>70){
								blockID=ID::Game::IRON_ORE;
							}else{
								blockID=ID::Game::COPPER_ORE;
							}
						}else if(chunkY*16+y<300&&chunkY*16+y>0){
							if(prob>85){
								blockID=ID::Game::IRON_ORE;
							}else{
								blockID=ID::Game::COPPER_ORE;
							}
						}else{
							if(prob>55){
								blockID=ID::Game::GOLD_ORE;
							}else{
								blockID=ID::Game::IRON_ORE;
							}
						}
					}
				}
				newChunk.data[x][y].ID = blockID;
			}
		}
	}
	
	
	
	
	return newChunk;
}

void renderChunksWithCulling(sf::RenderWindow& window, const chunk (&chunks)[6][6], const sf::Texture (&blockTextures)[13], const sf::Vector2f& playerPos, const sf::Vector2f& viewSize) {
	sf::FloatRect viewRect(playerPos.x - viewSize.x / 2, playerPos.y - viewSize.y / 2, viewSize.x, viewSize.y);
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			const chunk& currentChunk = chunks[i][j];
			for (int y = 0; y < 16; ++y) {
				for (int x = 0; x < 16; ++x) {
					const block& currentBlock = currentChunk.data[x][y];
					sf::FloatRect blockRect(currentBlock.x * 8, currentBlock.y * 8, 8, 8);
					if (viewRect.intersects(blockRect)) {
						int blockID = currentBlock.ID;
						sf::Sprite blockSprite(blockTextures[blockID]);
						blockSprite.setPosition(currentBlock.x * 8, currentBlock.y * 8);
						window.draw(blockSprite);
					}
				}
			}
		}
	}
}

int main(){
	srand(time(NULL));
	int seed = rand();
	sf::RenderWindow window(sf::VideoMode(800,640),"DERRARIA");
	sf::Event event;
	
	player_data player;
	
	chunk loaded_chunks[6][6];
	
	player.seed=seed;
	if(true){
		bool b=0;
		std::cout<<"load=1,make=0 file\n> ";
		std::cin>>b;
		SETUP(player,b);
	}
	
	sf::Texture texturetx;
	sf::Sprite playersp;
	texturetx.loadFromFile(derraria_player_stuff_textures_png,sf::IntRect(0,0,16,24));
	playersp.setTexture(texturetx);
	playersp.setOrigin(8,8);
	
	for(int i=0;i<6;i++){
		for(int j=0;j<6;j++){
			
			loaded_chunks[i][j]=genChunk(player,loaded_chunks[i][j],i-3,j-3,player.seed);
			SAVE_CHUNK(player,loaded_chunks[i][j]);
		}
	}
	
	sf::View view;
	view.reset(sf::FloatRect(0, 0, 400, 320));
	sf::Texture block_textures[13];
	block_textures[0].loadFromFile(derraria_block_textures_png,sf::IntRect(0,248,8,8));
	block_textures[1].loadFromFile(derraria_block_textures_png,sf::IntRect(8,248,8,8));
	block_textures[2].loadFromFile(derraria_block_textures_png,sf::IntRect(8,0,8,8));
	block_textures[3].loadFromFile(derraria_block_textures_png,sf::IntRect(16,0,8,8));
	block_textures[4].loadFromFile(derraria_block_textures_png,sf::IntRect(24,0,8,8));
	block_textures[5].loadFromFile(derraria_block_textures_png,sf::IntRect(32,0,8,8));
	block_textures[6].loadFromFile(derraria_block_textures_png,sf::IntRect(40,0,8,8));
	block_textures[7].loadFromFile(derraria_block_textures_png,sf::IntRect(48,0,8,8));
	block_textures[8].loadFromFile(derraria_block_textures_png,sf::IntRect(0,0,8,8));
	block_textures[9].loadFromFile(derraria_block_textures_png,sf::IntRect(56,0,8,8));
	block_textures[10].loadFromFile(derraria_block_textures_png,sf::IntRect(64,0,8,8));
	block_textures[11].loadFromFile(derraria_block_textures_png,sf::IntRect(72,0,8,8));
	block_textures[12].loadFromFile(derraria_block_textures_png,sf::IntRect(80,0,8,8));
	
	sf::Clock ck;
	//window.setFramerateLimit(60);
	while(window.isOpen()){
		FPS(ck);
		for(int i=0;i<6;i++){
			for(int j=0;j<6;j++){
				SAVE_CHUNK(player,loaded_chunks[i][j]);
				loaded_chunks[i][j]=genChunk(player,loaded_chunks[i][j],(player.x/8)/16+(i-3),(player.y/8)/16+(j-3),player.seed);
			}
		}
		
		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed){ 
				std::fstream file(DERRARIA_SAVE_VERSON + "player_data.bin",std::ios::out|std::ios::in|std::ios::binary);
				file.seekp(0,std::ios::beg);
				file.write(reinterpret_cast<char*>(&player),sizeof(player));
				file.close();
				window.close();
			}
			
		}
		
		int speed=100;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			player.y+=(-speed);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			player.x+=(-speed);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			player.y+=(speed);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			player.x+=(speed);
		
		view.setCenter(player.x,player.y);
		playersp.setPosition(player.x,player.y);
		
		window.setView(view);
		window.clear();
		
		renderChunksWithCulling(window,loaded_chunks,block_textures,sf::Vector2f(player.x,player.y),view.getSize());
		
		window.draw(playersp);
		window.display();
	}
	
	return 0;
}
