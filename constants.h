#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

// TILE AYARLARI
const int TILE_SIZE = 16;

// GRID AYARLARI (Dikdörtgen Harita)
const int COLS = 90;
const int ROWS = 50;
// Genişlik: 90 * 16 = 1440 px
// Yükseklik: 50 * 16 = 800 px

// Harita (1440x800) + Kenar Boşlukları
const int SCREEN_WIDTH = 1460;
const int SCREEN_HEIGHT = 900; // Altta 100px boşluk kalsın(UI için)
#endif