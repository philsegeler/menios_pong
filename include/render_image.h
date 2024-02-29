#ifdef __gnu_linux__

#include <glad.h>
#include <SDL2/SDL.h>

#elif defined(_WIN32)
#define SDL_MAIN_HANDLED

#include <glad.h>
#include <SDL.h>

#elif defined(__APPLE__)

#include <glad.h>
#include <SDL.h>

#elif defined(__EMSCRIPTEN__)

#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES 1
#include <GLES3/gl3.h>
#include <GLES3/gl31.h>
#include <GLES3/gl32.h>
#include <SDL.h>
#include <SDL_opengles2.h>
#else
#endif

#include <vector>

class render_image_t{
public:

    void update_size(unsigned int x, unsigned int y);

    void render(std::vector<uint8_t>);

    void destroy();

protected:
    GLuint texture_{0};
    GLuint framebuffer_{0};
    bool init_{false};
    unsigned int x_{0};
    unsigned int y_{0};
};