#ifndef RAYCAD_PLUGIN_H
#define RAYCAD_PLUGIN_H

#include <vector>

// Mirror Raylib types manually to avoid including raylib.h in the SDK
#ifndef RAYLIB_H
typedef struct { float x, y, z; } Vector3;
typedef struct { unsigned char r, g, b, a; } Color;
#endif

enum ShapeType { SHAPE_CUBE=0, SHAPE_CYLINDER, SHAPE_SPHERE, SHAPE_WEDGE, SHAPE_CONE }; 
enum MaterialType { MAT_DEFAULT=0, MAT_STEEL, MAT_WOOD, MAT_GLASS, MAT_GLOW, MAT_CONCRETE };

struct Block {
    int id;
    Vector3 position;
    Vector3 size;
    Vector3 rotation;
    Color color;
    ShapeType type;
    MaterialType material;
    bool visible;
    Vector3 velocity;
    bool isSleeping;
};

struct RayCAD_Host {
    void (*Log)(const char* fmt, ...);
    void (*PushUndo)(void);
    void (*WakePhysics)(void);
    int* nextId;
    Color* activeColor;
    float* gridSize;
};

// Cross-platform export macro
#if defined(_WIN32)
    #define PLUGIN_API __declspec(dllexport)
#else
    #define PLUGIN_API __attribute__((visibility("default")))
#endif

extern "C" {
    typedef void (*PluginEntryFunc)(std::vector<Block>&, RayCAD_Host);
}

#endif