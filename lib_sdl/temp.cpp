#include <SDL2/SDL.h>
#include "/Users/dvynokur/Library/Frameworks/SDL2_image.framework/Versions/A/Headers/SDL_image.h"
#include "/Users/dvynokur/Library/Frameworks/SDL2_mixer.framework/Versions/A/Headers/SDL_mixer.h"

#include <iostream>
#include <vector>


#define window_width 400
#define window_height 200

#define fps 60
// #include <OpenGL/gl.h>
// #include <OpenGL/glext.h>


void	cap_framerate(Uint32 starting_tick)
{

	if ((1000 / fps) > SDL_GetTicks() - starting_tick) {
		SDL_Delay(1000 / fps - (SDL_GetTicks()- starting_tick));
	}
}


class	Sprite {

protected:
	SDL_Surface 	*image;
	SDL_Rect		rect;
	int				origin_x, origin_y;

public:
	Sprite(Uint32 color, int x, int y, int w = 48, int h = 64) {
		image = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
		SDL_FillRect(image, NULL, color);
		rect = image->clip_rect;
		
		origin_x = rect.w / 2;
		origin_y = rect.h / 2;

		rect.x = x;
		rect.y = y;
	}

	void	update(){
		// Can be overridden!
	}

	void	draw(SDL_Surface *destination) {
		SDL_BlitSurface(image, NULL, destination, &rect);
	}

	SDL_Surface		*get_image() const  {
		return (image);
	}

	bool	operator==(const Sprite &other) const {
		return (image == other.get_image());
	}
};

class	Block : public Sprite {

public:
	Block(Uint32 color, int x, int y, int w = 48, int h = 64) :
	Sprite (color, x, y, w, h) {
		update_properties();
	}
	void	update_properties() {
		origin_x = 0;
		origin_y = 0;

		set_position(rect.x, rect.y);
	}
	void	set_position(int x, int y) {
		rect.x = x - origin_x;
		rect.y = y - origin_y;
	}

	void	set_image(const char filename[] = NULL) {
		if (filename != NULL) {
			SDL_Surface *loaded_image = NULL;
			// loaded_image = SDL_LoadBMP(filename);
			loaded_image = IMG_Load(filename);
			if (loaded_image != NULL) {
				image = loaded_image;
				int old_x = rect.x;
				int old_y = rect.y;

				rect = image->clip_rect;
				rect.x = old_x;
				rect.y = old_y;

				update_properties();
			}
		}
	}
};


class	SpriteGroup {

private:
	std::vector	<Sprite *> sprites;
	int			sprites_size;

public:
	SpriteGroup 	copy() {
		SpriteGroup new_group;

		for (int i = 0; i < sprites_size; i++) {
			new_group.add(sprites[i]);
		}
		return new_group;
	}
	std::vector<Sprite*> get_sprites() {
		return sprites;
	}
	void	add(Sprite *sprite) {
		sprites.push_back(sprite);
		sprites_size = sprites.size();
	}
	void	remove(Sprite sprite_object) {
		for (int i = 0; i < sprites_size; i++) {
			if (*sprites[i] == sprite_object) {
				sprites.erase(sprites.begin() + i);
			}
		}
		sprites_size = sprites.size();
	}

	bool	has(Sprite sprite_object) {
		for (int i = 0; i < sprites_size; i++) {
			if (*sprites[i] == sprite_object) {
				return (true);
			}
		}
		return (false);
	}

	void	update() {
		if (!sprites.empty()) {
			for (int i = 0; i < sprites_size; i++) {
				sprites[i]->update();
			}
		}
	}

	void	draw(SDL_Surface *destination) {
		if (!sprites.empty()) {
			for (int i = 0; i < sprites_size; i++) {
				sprites[i]->draw(destination);
			}
		}
	}

	void	empty() {
		sprites.clear();
		sprites_size = sprites.size();
	}

	int		size() {
		return (sprites_size);
	}
};




int main(int argc, char **argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);


	SDL_Window	*window = NULL;
	window = SDL_CreateWindow("Nibbler = Zmeika",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1700, 1000,
		SDL_WINDOW_RESIZABLE);

	if (window == NULL) {
		std::cout << "Error initializing" << std::endl << SDL_GetError() << std::endl;
	} 

	
	SDL_Surface	*screen = SDL_GetWindowSurface(window);

	// SDL_FreeSurface(surface)
	Uint32		white = SDL_MapRGB(screen->format, 255, 255, 255);
	Uint32		red = SDL_MapRGB(screen->format, 255, 0, 0);
	Uint32		blue = SDL_MapRGB(screen->format, 0, 0, 255);

	SDL_FillRect(screen, NULL, white);


	// Sprite	object(red, window_width/2, window_height/2);
	// Sprite	another(blue, window_width / 2 - 100, window_height / 2 + 20);

	// SpriteGroup	active_sprites;
	// active_sprites.add(&object);
	// active_sprites.add(&another);

	// // active_sprites.remove(object);

	// active_sprites.draw(screen);
	// std::cout << active_sprites.has(object) << std::endl;

	// // object.draw(screen);


	Block	block(red, 0, 0);
	block.set_image("snake2.ico");

	SpriteGroup	active_sprites;
	active_sprites.add(&block);

	active_sprites.draw(screen);


	SDL_UpdateWindowSurface(window);


	// Initializing audio

	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
	Mix_Chunk	*sound = NULL;
	sound = Mix_LoadWAV("quail1.wav");
	Mix_PlayChannel(-1, sound, 0); // 3th arg - number of loops, -1 is infinite loops


	Mix_Music *music = NULL;
	music = Mix_LoadMUS("applause.wav");
	Mix_PlayMusic(music, 0);

	Uint32	starting_tick;

	SDL_Event event;

	bool	running = true;

	while(running) {
		starting_tick = SDL_GetTicks();
		while (SDL_PollEvent (&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
				break ;
			}
		}
		// SDL_GetWindowPosition(window, &x, &y);
		// std::cout << x << ", " << y << std::endl;

		cap_framerate(starting_tick);


	}

	Mix_FreeChunk(sound);
	sound = NULL;
	Mix_CloseAudio();


	SDL_DestroyWindow(window);

	SDL_Quit();

	return (0);
}