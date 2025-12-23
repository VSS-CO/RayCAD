#include "plugin.h" // Include the SDK we just fixed
#include <cmath>

// Remember to use extern "C" so RayCAD can find the function by its exact name
extern "C" PLUGIN_API void RunPlugin(std::vector<Block>& scene, RayCAD_Host host) {
    host.Log("Running Spiral Generator...");
    host.PushUndo(); // Save state so we can 'Undo' the whole staircase

    int steps = 30;
    float radius = 5.0f;
    float heightStep = 0.5f;
    
    for (int i = 0; i < steps; i++) {
        float angle = i * 0.4f; // Rotation of the spiral
        
        Block b;
        // Use the nextId pointer from the main app so IDs stay unique
        b.id = (*host.nextId)++; 
        
        // Calculate position using Polar coordinates
        b.position.x = cosf(angle) * radius;
        b.position.y = i * heightStep;
        b.position.z = sinf(angle) * radius;
        
        // Step size
        b.size = { 3.0f, 0.2f, 1.0f };
        
        // Use the current active color from the main app
        b.color = *host.activeColor; 
        
        // Rotation: Point the step toward the center
        b.rotation = { 0, -angle * (180.0f / 3.14159f), 0 };
        
        b.type = SHAPE_CUBE;
        b.material = MAT_DEFAULT;
        b.visible = true;
        b.isSleeping = true; // Don't let physics explode the stairs immediately
        
        scene.push_back(b);
    }
    
    host.Log("Spiral complete! Added 30 blocks.");
}