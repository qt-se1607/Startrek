TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    began.c
SOURCES += allegro.c
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
    variate.h \
    allegro.h \
    began.h
HEADERS += color.h
