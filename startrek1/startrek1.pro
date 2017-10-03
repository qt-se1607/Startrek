TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    init.c \
    plane_bullet.c \
    game.c

INCLUDEPATH+=-I/usr/include/allegro5
LIBS+=-L/usr/lib -lallegro
LIBS+=-L/usr/lib -lallegro_color
LIBS+=-L/usr/lib -lallegro_audio
LIBS+=-L/usr/lib -lallegro_acodec
LIBS+=-L/usr/lib -lallegro_font
LIBS+=-L/usr/lib -lallegro_image
LIBS+=-L/usr/lib -lallegro_main
LIBS+=-L/usr/lib -lallegro_memfile
LIBS+=-L/usr/lib -lallegro_physfs
LIBS+=-L/usr/lib -lallegro_primitives
LIBS+=-L/usr/lib -lallegro_ttf
LIBS+=-L/usr/lib -lallegro_video

HEADERS += \
    color.h \
    variate.h \
    init.h \
    plane_bullet.h \
    game.h
