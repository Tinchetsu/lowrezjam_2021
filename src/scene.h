#ifndef __SCENE_H__
#define __SCENE_H__

typedef struct Scene {
    void  (*update)(void);
    void  (*draw)(void);
    void  (*dispose)(void);
} Scene;

#endif
