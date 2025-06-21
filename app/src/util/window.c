#include "window.h"

SDL_Window *
sc_create_sdl_window(const char *title, int64_t x, int64_t y, int64_t width,
                     int64_t height, int64_t flags) {
    SDL_Window *window = NULL;

    SDL_PropertiesID props = SDL_CreateProperties();
    if (!props) {
        return NULL;
    }

    bool ok;

    ok = SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING,
                               title);
    if (!ok) {
        goto error;
    }

    ok = SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_X_NUMBER, x);
    if (!ok) {
        goto error;
    }

    ok = SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_Y_NUMBER, y);
    if (!ok) {
        goto error;
    }

    ok = SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER,
                               width);
    if (!ok) {
        goto error;
    }

    ok = SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER,
                               height);
    if (!ok) {
        goto error;
    }

    ok = SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_FLAGS_NUMBER,
                               flags);
    if (!ok) {
        goto error;
    }

    window = SDL_CreateWindowWithProperties(props);

error:
    SDL_DestroyProperties(props);
    return window;
}
