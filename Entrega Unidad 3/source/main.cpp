#ifndef NDEBUG
#include <vld.h> // Visual Leak Detector, útil en modo Debug para detectar fugas de memoria
#endif

#include "raylib.h"
#include <cstdlib>
#include <time.h>

int main(void)
{
    // Ventana de 1024x768 píxeles con un título personalizado
    InitWindow(1024, 768, "Sprites en accion - Leonel Tomas Mc Cormack");
    
    // Cargamos la imgagen
    Texture2D imagen = LoadTexture("Assets/ship-galaga.png");

    // Aplicamos un filtro bilineal a la textura
    SetTextureFilter(imagen, TEXTURE_FILTER_BILINEAR);

    // Posicion inicial de la nave 1 y nave 2
    Vector2 posImagen1 = {150, (768 / 2)};
    Vector2 posImagen2 = { 800, 500 };

    // velocidad que se le asignara a la nave
    Vector2 velocidad = { 5.0f, 5.0f };

    // Color de la nave 1 y nave 2
    Color colImagen1 = {255,161,0,255};
    Color colImagen2 = {0,158,47,255}; 


    // Rotacion de la nave 1 y nave 2
    float rotImagen1 = 0.0f;
    float rotImagen2 = 180.0f;

    // Escalado de la nave 1 y nave 2
    float escImagen1 = 0.5f;
    float escImagen2 = 0.3f;


    // Configuracion framerate
    SetTargetFPS(60);

    // Contador de veces presionada la barra espaciadora para activar el SWAP visual
    int contador = -1;
    
    // Bucle principal del juego (se repite hasta que se cierre la ventana)
    while (!WindowShouldClose())
    {

        // Aplicamos movimiento sobre la Nave 1 utilizando WSAD
        if (IsKeyDown('W')) {
            posImagen1.y -= velocidad.y;
        }
        if (IsKeyDown('S')) {
            posImagen1.y += velocidad.y;
        }
        if (IsKeyDown('A')) {
            posImagen1.x -= velocidad.x;
        }
        if (IsKeyDown('D')) {
            posImagen1.x += velocidad.x;
        }

        // Aplicamos movimiento sobre la Nave 2 utilizando las flechas de direccion 
        if (IsKeyDown(KEY_UP)) {
            posImagen2.y -= velocidad.y;
        }
        if (IsKeyDown(KEY_DOWN)) {
            posImagen2.y += velocidad.y;
        }
        if (IsKeyDown(KEY_LEFT)) {
            posImagen2.x -= velocidad.x;
        }
        if (IsKeyDown(KEY_RIGHT)) {
            posImagen2.x += velocidad.x;
        }

        // Aplicamos un SWAP que invierte las propiedades
        if (IsKeyPressed(KEY_SPACE)) {

            contador++;

            if ((contador % 2) == 0) {
                rotImagen1 = 180.0f;
                colImagen1 = { 0,158,47,255 };
                escImagen1 = 0.3f;

                rotImagen2 = 0.0f;
                colImagen2 = { 255,161,0,255 };
                escImagen2 = 0.5f;
            }
            else
            {
                rotImagen1 = 0.0f;
                colImagen1 = { 255,161,0,255 };
                escImagen1 = 0.5f;

                rotImagen2 = 180.0f;
                colImagen2 = { 0,158,47,255 };
                escImagen2 = 0.3f;
            }
        }
           
     
        // Iniciamos la etapa de dibujo
        BeginDrawing();

        // Limpiamos la pantalla 
        ClearBackground(RAYWHITE);

        // Dibujamos la imagen para la nave 1 con sus parametros personalizados
        DrawTextureEx(imagen, posImagen1, rotImagen1, escImagen1, colImagen1);

        // Dibujamos la imagen para la nvae 2 con otros parametros personalizados
        DrawTextureEx(imagen, posImagen2, rotImagen2, escImagen2, colImagen2);

        // Texto con la informacion del sprite "nave 1"
        DrawText("Nave 1", 2, 0, 25, BLACK);
        DrawText(TextFormat("Escala: %.1f", escImagen1), 2, 20, 25, BLACK);
        DrawText(TextFormat("Color(RGBA): R%d, G%d, B%d, A%d", colImagen1.r, colImagen1.g, colImagen1.b, colImagen1.a), 2, 50, 25, BLACK);
        DrawText(TextFormat("Posicion: %.1f, %.1f", posImagen1.x, posImagen1.y), 2, 70, 25, BLACK);

        // Texto con la informacion del sprite "nave 2"
        DrawText("Nave 2", 500, 0, 25, BLACK);
        DrawText(TextFormat("Escala: %.1f", escImagen2), 500, 20, 25, BLACK);
        DrawText(TextFormat("Color(RGBA): R%d, G%d, B%d, A%d", colImagen2.r, colImagen2.g, colImagen2.b, colImagen2.a), 500, 50, 25, BLACK);
        DrawText(TextFormat("Posicion: %.1f, %.1f", posImagen2.x, posImagen2.y), 500, 70, 25, BLACK);

        
        // Finalizamos el dibujo
        EndDrawing();
    }

    UnloadTexture(imagen);
    // Cerramos la ventana
    CloseWindow();

    return 0;
}

