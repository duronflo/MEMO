#ifndef SETTINGS_H
#define SETTINGS_H

#define TFT_MOSI 51
#define TFT_SCK 52
#define TFT_CS  53  // Chip select line for TFT display
#define TFT_DC   49  // Data/command line for TFT
#define TFT_RST  47  // Reset line for TFT (or connect to +5V)



// GUI Config
#define XAKK 5
#define YAKK 20
#define XTEX 55
#define YTEX 5
#define XAMP 110
#define YAMP 13


typedef enum { ST_INIT, ST_BATT_STARTER, ST_BATT_LIVING, ST_CAR_INFO} state_t ;

#endif
