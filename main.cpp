#include <render_image.h>

#include <iostream>

#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   600

// global variables
bool quit{false};
SDL_Window* window;
render_image_t renderer;
int count = 0;

// from bottom left
#define PIXEL_POS_X 400
#define PIXEL_POS_Y 30


// main loop
void main_loop_step(){

    // update viewport size
    int resolution_x, resolution_y;

    SDL_GetWindowSize(window, &resolution_x, &resolution_y);
    glViewport(0, 0, resolution_x, resolution_y);

    renderer.update_size(resolution_x, resolution_y);

    std::vector<uint8_t> image_data(resolution_x*resolution_y*4);
    
    /************************************************/
    // change pixel data
    for (size_t i=0; i < image_data.size(); i++){
        image_data[i] = 0;
    }
    image_data[PIXEL_POS_Y*resolution_x*4 + PIXEL_POS_X*4] = count; //red
    image_data[PIXEL_POS_Y*resolution_x*4 + PIXEL_POS_X*4+1] = count; // green
    image_data[PIXEL_POS_Y*resolution_x*4 + PIXEL_POS_X*4+2] = count; // blue
    
    renderer.render(image_data);
    /************************************************/

    count += 1;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quit = true;
            return;
        }
    }

    SDL_GL_SwapWindow(window);    
}

// actual main function
int main(int argc, char* argv[]){

 #ifndef __EMSCRIPTEN__
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "Could not initialize SDL2, " << SDL_GetError();
    }

    SDL_GL_LoadLibrary(NULL);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#else
    SDL_Init(SDL_INIT_VIDEO);
#endif

#if defined(_WIN32)
    SDL_SetHint(SDL_HINT_VIDEO_WIN_D3DCOMPILER, "d3dcompiler_43.dll");
    SDL_SetHint(SDL_HINT_OPENGL_ES_DRIVER, "1");
#endif
    

    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
#ifndef __APPLE__
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
#else
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
#endif

    SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, 0);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);



    window = SDL_CreateWindow("Menios Pong",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    SDL_GLContext context = SDL_GL_CreateContext(window);

#ifndef __EMSCRIPTEN__

#ifndef __APPLE__
    gladLoadGLES2Loader(SDL_GL_GetProcAddress);
#else
    gladLoadGLLoader(SDL_GL_GetProcAddress);
#endif
    SDL_GL_MakeCurrent(window, context);
#else
    SDL_GL_MakeCurrent(window, context);
#endif

    // VSYNC
    SDL_GL_SetSwapInterval(1);


#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(&main_loop_step, 0, true);
#else

    while (!quit) {
        main_loop_step();
    }
#endif

    // Quit SDL
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}