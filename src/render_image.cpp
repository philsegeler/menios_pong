#include <render_image.h>
#include <iostream>

void render_image_t::update_size(unsigned int x, unsigned int y){
    if (this->framebuffer_ == 0)
        glGenFramebuffers(1, &this->framebuffer_);

    this->x_ = x;
    this->y_ = y;

    if (this->texture_ == 0)
        glGenTextures(1, &this->texture_);

    glBindTexture(GL_TEXTURE_2D, this->texture_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#ifdef __EMSCRIPTEN__
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
#endif

        //glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer_);
    glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer_);
    glBindTexture(GL_TEXTURE_2D, this->texture_);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->texture_, 0);
}

void render_image_t::render(std::vector<uint8_t> data){

    if (data.size() != this->x_*this->y_*4){
        throw "image data for display is not the required size.";
    }

    glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer_);
    glBindTexture(GL_TEXTURE_2D, this->texture_);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, this->x_, this->y_, GL_RGBA, GL_UNSIGNED_BYTE, &data[0]);
    
    glBindFramebuffer(GL_READ_FRAMEBUFFER, this->framebuffer_);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBlitFramebuffer(0, 0, this->x_, this->y_, 0, 0, this->x_, this->y_, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

void render_image_t::destroy(){
    glDeleteTextures(1, &this->texture_);
}