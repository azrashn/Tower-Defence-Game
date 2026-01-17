#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

const int TILE_SIZE = 40;

// GRID AYARLARI (Dikdörtgen Harita)
const int COLS = 36;
const int ROWS = 20;
// Genişlik: 36 * 40 = 1440 px
// Yükseklik: 20 * 40 = 800 px

// Harita: 1440x800 + Kenar Boşlukları
const int SCREEN_WIDTH = 1460;
const int SCREEN_HEIGHT = 900; // Altta 100px boşluk kalsın(UI için)
#endif