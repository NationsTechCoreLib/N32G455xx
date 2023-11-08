/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file gc0308.c
 * @author Nations
 * @version v1.0.2
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "gc0308.h"
#include "virtual_i2c.h"

/**
 * @brief   GC0308 registers init list.
 */
#if 1
const uint8_t GC0308_ConfigData[][2] = {
    // 54
//    {0xFE, 0x80}, // Reset

    {0xFE, 0x00}, // Select Page0

    {0xD2, 0x10}, // Close AEC
    {0x22, 0x55}, // Close AWB

    {0x03, 0x01}, // Exposure hight
    {0x04, 0x2C}, // Exposure low

    {0x5A, 0x56},
    {0x5B, 0x40},
    {0x5C, 0x4A},

    {0x22, 0x57}, // Enable AWB

    {0x01, 0xFA},
    {0x02, 0x70},
    {0x0F, 0x01},

    {0xE2, 0x00}, // Anti-Flicker step [11:8]
    {0xE3, 0x64}, // Anti-Flicker step [7:0]

    {0xE4, 0x02}, // Exp level 1  16.67Fps
    {0xE5, 0x58},
    {0xE6, 0x03}, // Exp level 2  12.5Fps
    {0xE7, 0x20},
    {0xE8, 0x04}, // Exp level 3  8.33Fps
    {0xE9, 0xB0},
    {0xEA, 0x09}, // Exp level 4  4.00Fps
    {0xEB, 0xC4},

    //  {0xEC, 0x20},

    {0x05, 0x00}, // Row start at 0
    {0x06, 0x00},
    {0x07, 0x00}, // Column start at 0
    {0x08, 0x00},

    {0x09, 0x01}, // Window height 488
    {0x0A, 0xE8},
    {0x0B, 0x02}, // Window width  648
    {0x0C, 0x88},

//    {0x09, (uint8_t)(((DVP_IMAGE_HEIGHT + 8) & 0xFF00) >> 8)}, // Window height
//    {0x0A, (uint8_t)(((DVP_IMAGE_HEIGHT + 8) & 0x00FF) >> 0)},
//    {0x0B, (uint8_t)(((DVP_IMAGE_WIDTH + 8) & 0xFF00) >> 8)}, // Window width
//    {0x0C, (uint8_t)(((DVP_IMAGE_WIDTH + 8) & 0x00FF) >> 0)},

    {0x0D, 0x02},
    {0x0E, 0x02},
    {0x10, 0x26},
    {0x11, 0x0D},
    {0x12, 0x2A},
    {0x13, 0x00},

    {0x14, 0x10},

    {0x15, 0x0A},
    {0x16, 0x05},
    {0x17, 0x01},
    {0x18, 0x44},
    {0x19, 0x44},
    {0x1A, 0x2A},
    {0x1B, 0x00},
    {0x1C, 0x49},
    {0x1D, 0x9A},
    {0x1E, 0x61},
    {0x1F, 0x17},

    {0x20, 0xFF},
    {0x21, 0xF8},
    {0x22, 0x57},
#if DVP_IMAGE_FORMAT == DVP_IMAGE_FORMAT_RGB565
    {0x24, 0xA6}, // Output format: RGB565
#else             // gray
    {0x24, 0xB1}, // Output format: Y (Grey)
#endif
    {0x25, 0x0F}, // DATA,PCLK,HSYNC,VSYNC

    // 67 output sync_mode
    {0x26, 0x02}, // SYNC_MODE
    {0x28, 0x11}, // CLK_DIV_MODE
    {0x2F, 0x01},
    {0x30, 0xF7},
    {0x31, 0x50},
    {0x32, 0x00},
    {0x39, 0x04},
    {0x3A, 0x20},
    {0x3B, 0x20},
    {0x3C, 0x00},
    {0x3D, 0x00},
    {0x3E, 0x00},
    {0x3F, 0x00},
    {0x50, 0x14},
    {0x53, 0x80},
    {0x54, 0x80},
    {0x55, 0x80},
    {0x56, 0x80},
    {0x8B, 0x20},
    {0x8C, 0x20},
    {0x8D, 0x20},
    {0x8E, 0x14},
    {0x8F, 0x10},
    {0x90, 0x14},
    {0x91, 0x3C},
    {0x92, 0x50},
    {0x5D, 0x12},
    {0x5E, 0x1A},
    {0x5F, 0x24},
    {0x60, 0x07},
    {0x61, 0x15},
    {0x62, 0x08},
    {0x64, 0x03},
    {0x66, 0xE8},
    {0x67, 0x86},
    {0x68, 0xA2},
    {0x69, 0x18},
    {0x6A, 0x0F},
    {0x6B, 0x00},
    {0x6C, 0x5F},
    {0x6D, 0x8F},
    {0x6E, 0x55},
    {0x6F, 0x38},
    {0x70, 0x15},
    {0x71, 0x33},
    {0x72, 0xDC},
    {0x73, 0x80},
    {0x74, 0x02},
    {0x75, 0x3F},
    {0x76, 0x02},
    {0x77, 0x54},
    {0x78, 0x88},
    {0x79, 0x81},
    {0x7A, 0x81},
    {0x7B, 0x22},
    {0x7C, 0xFF},
    {0x93, 0x48},
    {0x94, 0x02},
    {0x95, 0x07},
    {0x96, 0xE0},
    {0x97, 0x40},
    {0x98, 0xF0},
    {0xB1, 0x40},
    {0xB2, 0x40},
    {0xB3, 0x40},
    {0xB6, 0xE0},
    {0xBD, 0x38},
    {0xBE, 0x36},
    {0xD0, 0xCB},
    {0xD1, 0x10},
    {0xD2, 0x90}, // enable ACE
    {0xD3, 0x48},
    {0xD5, 0xF2},
    {0xD6, 0x16},
    {0xDB, 0x92},
    {0xDC, 0xA5},
    {0xDF, 0x23},
    {0xD9, 0x00},
    {0xDA, 0x00},
    {0xE0, 0x09},

    {0xED, 0x04},
    {0xEE, 0xA0},
    {0xEF, 0x40},
    {0x80, 0x03},
    {0x80, 0x03},

    {0x9F, 0x0B}, // Gamma1
    {0xA0, 0x16},
    {0xA1, 0x29},
    {0xA2, 0x3C},
    {0xA3, 0x4F},
    {0xA4, 0x5F},
    {0xA5, 0x6F},
    {0xA6, 0x8A},
    {0xA7, 0x9F},
    {0xA8, 0xB4},
    {0xA9, 0xC6},
    {0xAA, 0xD3},
    {0xAB, 0xDD},
    {0xAC, 0xE5},
    {0xAD, 0xF1},
    {0xAE, 0xFA},
    {0xAF, 0xFF},

    /*GC0308_GAMMA_SElECt,
    1:  //smallest gamma Curve
    {0x9F, 0x0B},
    {0xA0, 0x16},
    {0xA1, 0x29},
    {0xA2, 0x3C},
    {0xA3, 0x4F},
    {0xA4, 0x5F},
    {0xA5, 0x6F},
    {0xA6, 0x8A},
    {0xA7, 0x9F},
    {0xA8, 0xB4},
    {0xA9, 0xC6},
    {0xAA, 0xD3},
    {0xAB, 0xDD},
    {0xAC, 0xE5},
    {0xAD, 0xF1},
    {0xAE, 0xFA},
    {0xAF, 0xFF},

    2:
    {0x9F, 0x0E},
    {0xA0, 0x1C},
    {0xA1, 0x34},
    {0xA2, 0x48},
    {0xA3, 0x5A},
    {0xA4, 0x6B},
    {0xA5, 0x7B},
    {0xA6, 0x95},
    {0xA7, 0xAB},
    {0xA8, 0xBF},
    {0xA9, 0xCE},
    {0xAA, 0xD9},
    {0xAB, 0xE4},
    {0xAC, 0xEC},
    {0xAD, 0xF7},
    {0xAE, 0xFD},
    {0xAF, 0xFF},

    3:
    {0x9F, 0x10},
    {0xA0, 0x20},
    {0xA1, 0x38},
    {0xA2, 0x4E},
    {0xA3, 0x63},
    {0xA4, 0x76},
    {0xA5, 0x87},
    {0xA6, 0xA2},
    {0xA7, 0xB8},
    {0xA8, 0xCA},
    {0xA9, 0xD8},
    {0xAA, 0xE3},
    {0xAB, 0xEB},
    {0xAC, 0xF0},
    {0xAD, 0xF8},
    {0xAE, 0xFD},
    {0xAF, 0xFF},

    4:
    {0x9F, 0x14},
    {0xA0, 0x28},
    {0xA1, 0x44},
    {0xA2, 0x5D},
    {0xA3, 0x72},
    {0xA4, 0x86},
    {0xA5, 0x95},
    {0xA6, 0xB1},
    {0xA7, 0xC6},
    {0xA8, 0xD5},
    {0xA9, 0xE1},
    {0xAA, 0xEA},
    {0xAB, 0xF1},
    {0xAC, 0xF5},
    {0xAD, 0xFB},
    {0xAE, 0xFE},
    {0xAF, 0xFF},

    5:  //largest gamma Curve
    {0x9F, 0x15},
    {0xA0, 0x2A},
    {0xA1, 0x4A},
    {0xA2, 0x67},
    {0xA3, 0x79},
    {0xA4, 0x8C},
    {0xA5, 0x9A},
    {0xA6, 0xB3},
    {0xA7, 0xC5},
    {0xA8, 0xD5},
    {0xA9, 0xDF},
    {0xAA, 0xE8},
    {0xAB, 0xEE},
    {0xAC, 0xF3},
    {0xAD, 0xFA},
    {0xAE, 0xFD},
    {0xAF, 0xFF}, */
    //-----------GAMMA SELECT END--------------//

    {0xC0, 0x00},
    {0xC1, 0x10},
    {0xC2, 0x1C},
    {0xC3, 0x30},
    {0xC4, 0x43},
    {0xC5, 0x54},
    {0xC6, 0x65},
    {0xC7, 0x75},
    {0xC8, 0x93},
    {0xC9, 0xB0},
    {0xCA, 0xCB},
    {0xCB, 0xE6},
    {0xCC, 0xFF},
    {0xF0, 0x02},
    {0xF1, 0x01},
    {0xF2, 0x02},
    {0xF3, 0x30},

    {0xF7, 0x12},
    {0xF8, 0x0A},
    {0xF9, 0x9F},
    {0xFA, 0x78},

    // 51-------------------------------------------------------------
    {0xFE, 0x01}, // set Page1

    {0x00, 0xF5},
    {0x02, 0x20},
    {0x04, 0x10},
    {0x05, 0x08},
    {0x06, 0x20},
    {0x08, 0x0A},
    {0x0A, 0xA0},
    {0x0B, 0x60},
    {0x0C, 0x08},
    {0x0E, 0x44},
    {0x0F, 0x32},
    {0x10, 0x41},
    {0x11, 0x37},
    {0x12, 0x22},
    {0x13, 0x19},
    {0x14, 0x44},
    {0x15, 0x44},
    {0x16, 0xC2},
    {0x17, 0xA8},
    {0x18, 0x18},
    {0x19, 0x50},
    {0x1A, 0xD8},
    {0x1B, 0xF5},
    {0x70, 0x40},
    {0x71, 0x58},
    {0x72, 0x30},
    {0x73, 0x48},
    {0x74, 0x20},
    {0x75, 0x60},
    {0x77, 0x20},
    {0x78, 0x32},
    {0x30, 0x03},
    {0x31, 0x40},
    {0x32, 0x10}, // BLK Global_offset
    {0x33, 0xE0}, // BLK Current_R_offset
    {0x34, 0xE0}, // BLK Current_G_offset
    {0x35, 0x00}, // BLK Current_B_offset
    {0x36, 0x80},
    {0x37, 0x00},
    {0x38, 0x04},
    {0x39, 0x09},
    {0x3A, 0x12},
    {0x3B, 0x1C},
    {0x3C, 0x28},
    {0x3D, 0x31},
    {0x3E, 0x44},
    {0x3F, 0x57},
    {0x40, 0x6C},
    {0x41, 0x81},
    {0x42, 0x94},
    {0x43, 0xA7},
    {0x44, 0xB8},
    {0x45, 0xD6},
    {0x46, 0xEE},
    {0x47, 0x0D},

    {0x53, 0x82},
#if (DVP_IMAGE_FORMAT == DVP_IMAGE_FORMAT_GRAY)
    {0x54, 0x22},
    {0x55, 0x03},
    {0x56, 0x00},
    {0x57, 0x00},
    {0x58, 0x00},
    {0x59, 0x00},
#else
    {0x54, 0x77},
    {0x55, 0x03},
    {0x56, 0x02},
    {0x57, 0x05},
    {0x58, 0x02},
    {0x59, 0x05},
#endif

    {0xff, 0xff}, // end
};
#else
const uint8_t GC0308_ConfigData[][2] = {
    // 54
//    {0xFE, 0x80}, // Reset

    {0xFE, 0x00}, // Select Page0

    {0xD2, 0x10}, // Close AEC
    {0x22, 0x55}, // Close AWB

    {0x03, 0x01}, // Exposure hight
    {0x04, 0x2C}, // Exposure low

    {0x5A, 0x56},
    {0x5B, 0x40},
    {0x5C, 0x4A},

    {0x22, 0x57}, // Enable AWB

    {0x01, 0xFA},
    {0x02, 0x70},
    {0x0F, 0x01},

    {0xE2, 0x00}, // Anti-Flicker step [11:8]
    {0xE3, 0x64}, // Anti-Flicker step [7:0]

    {0xE4, 0x02}, // Exp level 1  16.67Fps
    {0xE5, 0x58},
    {0xE6, 0x03}, // Exp level 2  12.5Fps
    {0xE7, 0x20},
    {0xE8, 0x04}, // Exp level 3  8.33Fps
    {0xE9, 0xB0},
    {0xEA, 0x09}, // Exp level 4  4.00Fps
    {0xEB, 0xC4},

    //  {0xEC, 0x20},

    {0x05, 0x00}, // Row start at 0
    {0x06, 0x00},
    {0x07, 0x00}, // Column start at 0
    {0x08, 0x00},

    {0x09, (uint8_t)(((DVP_IMAGE_HEIGHT + 8) & 0xFF00) >> 8)}, // Window height
    {0x0A, (uint8_t)(((DVP_IMAGE_HEIGHT + 8) & 0x00FF) >> 0)},
    {0x0B, (uint8_t)(((DVP_IMAGE_WIDTH + 8) & 0xFF00) >> 8)}, // Window width
    {0x0C, (uint8_t)(((DVP_IMAGE_WIDTH + 8) & 0x00FF) >> 0)},

    {0x0D, 0x02},
    {0x0E, 0x02},
    {0x10, 0x22},
    {0x11, 0xFD},
    {0x12, 0x2A},
    {0x13, 0x00},

    {0x14, 0x10},

    {0x15, 0x0A},
    {0x16, 0x05},
    {0x17, 0x01},
    {0x18, 0x44},
    {0x19, 0x44},
    {0x1A, 0x1E},
    {0x1B, 0x00},
    {0x1C, 0xC1},
    {0x1D, 0x08},
    {0x1E, 0x60},
    {0x1F, 0x17},

    {0x20, 0xFF},
    {0x21, 0xF8},
    {0x22, 0x57},
#if DVP_IMAGE_FORMAT == DVP_IMAGE_FORMAT_RGB565
    {0x24, 0xA6}, // Output format: RGB565
#else             // gray
    {0x24, 0xB1}, // Output format: Y (Grey)
#endif
    {0x25, 0x0F}, // DATA,PCLK,HSYNC,VSYNC

    // 67 output sync_mode
    {0x26, 0x02}, // SYNC_MODE
    {0x28, 0x11}, // CLK_DIV_MODE
    {0x2F, 0x01},
    {0x30, 0xF7},
    {0x31, 0x50},
    {0x32, 0x00},
    {0x39, 0x04},
    {0x3A, 0x18},
    {0x3B, 0x20},
    {0x3C, 0x00},
    {0x3D, 0x00},
    {0x3E, 0x00},
    {0x3F, 0x00},
    {0x50, 0x10},
    {0x53, 0x82},
    {0x54, 0x80},
    {0x55, 0x80},
    {0x56, 0x82},
    {0x8B, 0x40},
    {0x8C, 0x40},
    {0x8D, 0x40},
    {0x8E, 0x2E},
    {0x8F, 0x2E},
    {0x90, 0x2E},
    {0x91, 0x3C},
    {0x92, 0x50},
    {0x5D, 0x12},
    {0x5E, 0x1A},
    {0x5F, 0x24},
    {0x60, 0x07},
    {0x61, 0x15},
    {0x62, 0x08},
    {0x64, 0x03},
    {0x66, 0xE8},
    {0x67, 0x86},
    {0x68, 0xA2},
    {0x69, 0x18},
    {0x6A, 0x0F},
    {0x6B, 0x00},
    {0x6C, 0x5F},
    {0x6D, 0x8F},
    {0x6E, 0x55},
    {0x6F, 0x38},
    {0x70, 0x15},
    {0x71, 0x33},
    {0x72, 0xDC},
    {0x73, 0x80},
    {0x74, 0x02},
    {0x75, 0x3F},
    {0x76, 0x02},
    {0x77, 0x54},
    {0x78, 0x88},
    {0x79, 0x81},
    {0x7A, 0x81},
    {0x7B, 0x22},
    {0x7C, 0xFF},
    {0x93, 0x48},
    {0x94, 0x00},
    {0x95, 0x05},
    {0x96, 0xE8},
    {0x97, 0x40},
    {0x98, 0xF0},
    {0xB1, 0x38},
    {0xB2, 0x38},
    {0xBD, 0x38},
    {0xBE, 0x36},
    {0xD0, 0xC9},
    {0xD1, 0x10},
    {0xD2, 0x90}, // enable ACE
    {0xD3, 0x80},
    {0xD5, 0xF2},
    {0xD6, 0x16},
    {0xDB, 0x92},
    {0xDC, 0xA5},
    {0xDF, 0x23},
    {0xD9, 0x00},
    {0xDA, 0x00},
    {0xE0, 0x09},

    {0xED, 0x04},
    {0xEE, 0xA0},
    {0xEF, 0x40},
    {0x80, 0x03},
    {0x80, 0x03},

    //  {0x9F, 0x10},   // Gamma3
    //  {0xA0, 0x20},
    //  {0xA1, 0x38},
    //  {0xA2, 0x4E},
    //  {0xA3, 0x63},
    //  {0xA4, 0x76},
    //  {0xA5, 0x87},
    //  {0xA6, 0xA2},
    //  {0xA7, 0xB8},
    //  {0xA8, 0xCA},
    //  {0xA9, 0xD8},
    //  {0xAA, 0xE3},
    //  {0xAB, 0xEB},
    //  {0xAC, 0xF0},
    //  {0xAD, 0xF8},
    //  {0xAE, 0xFD},
    //  {0xAF, 0xFF},

    {0x9F, 0x0B}, // Gamma1
    {0xA0, 0x16},
    {0xA1, 0x29},
    {0xA2, 0x3C},
    {0xA3, 0x4F},
    {0xA4, 0x5F},
    {0xA5, 0x6F},
    {0xA6, 0x8A},
    {0xA7, 0x9F},
    {0xA8, 0xB4},
    {0xA9, 0xC6},
    {0xAA, 0xD3},
    {0xAB, 0xDD},
    {0xAC, 0xE5},
    {0xAD, 0xF1},
    {0xAE, 0xFA},
    {0xAF, 0xFF},

    /*GC0308_GAMMA_SElECt,
    1:  //smallest gamma Curve
    {0x9F, 0x0B},
    {0xA0, 0x16},
    {0xA1, 0x29},
    {0xA2, 0x3C},
    {0xA3, 0x4F},
    {0xA4, 0x5F},
    {0xA5, 0x6F},
    {0xA6, 0x8A},
    {0xA7, 0x9F},
    {0xA8, 0xB4},
    {0xA9, 0xC6},
    {0xAA, 0xD3},
    {0xAB, 0xDD},
    {0xAC, 0xE5},
    {0xAD, 0xF1},
    {0xAE, 0xFA},
    {0xAF, 0xFF},

    2:
    {0x9F, 0x0E},
    {0xA0, 0x1C},
    {0xA1, 0x34},
    {0xA2, 0x48},
    {0xA3, 0x5A},
    {0xA4, 0x6B},
    {0xA5, 0x7B},
    {0xA6, 0x95},
    {0xA7, 0xAB},
    {0xA8, 0xBF},
    {0xA9, 0xCE},
    {0xAA, 0xD9},
    {0xAB, 0xE4},
    {0xAC, 0xEC},
    {0xAD, 0xF7},
    {0xAE, 0xFD},
    {0xAF, 0xFF},

    3:
    {0x9F, 0x10},
    {0xA0, 0x20},
    {0xA1, 0x38},
    {0xA2, 0x4E},
    {0xA3, 0x63},
    {0xA4, 0x76},
    {0xA5, 0x87},
    {0xA6, 0xA2},
    {0xA7, 0xB8},
    {0xA8, 0xCA},
    {0xA9, 0xD8},
    {0xAA, 0xE3},
    {0xAB, 0xEB},
    {0xAC, 0xF0},
    {0xAD, 0xF8},
    {0xAE, 0xFD},
    {0xAF, 0xFF},

    4:
    {0x9F, 0x14},
    {0xA0, 0x28},
    {0xA1, 0x44},
    {0xA2, 0x5D},
    {0xA3, 0x72},
    {0xA4, 0x86},
    {0xA5, 0x95},
    {0xA6, 0xB1},
    {0xA7, 0xC6},
    {0xA8, 0xD5},
    {0xA9, 0xE1},
    {0xAA, 0xEA},
    {0xAB, 0xF1},
    {0xAC, 0xF5},
    {0xAD, 0xFB},
    {0xAE, 0xFE},
    {0xAF, 0xFF},

    5:  //largest gamma Curve
    {0x9F, 0x15},
    {0xA0, 0x2A},
    {0xA1, 0x4A},
    {0xA2, 0x67},
    {0xA3, 0x79},
    {0xA4, 0x8C},
    {0xA5, 0x9A},
    {0xA6, 0xB3},
    {0xA7, 0xC5},
    {0xA8, 0xD5},
    {0xA9, 0xDF},
    {0xAA, 0xE8},
    {0xAB, 0xEE},
    {0xAC, 0xF3},
    {0xAD, 0xFA},
    {0xAE, 0xFD},
    {0xAF, 0xFF}, */
    //-----------GAMMA SELECT END--------------//

    {0xC0, 0x00},
    {0xC1, 0x10},
    {0xC2, 0x1C},
    {0xC3, 0x30},
    {0xC4, 0x43},
    {0xC5, 0x54},
    {0xC6, 0x65},
    {0xC7, 0x75},
    {0xC8, 0x93},
    {0xC9, 0xB0},
    {0xCA, 0xCB},
    {0xCB, 0xE6},
    {0xCC, 0xFF},
    {0xF0, 0x02},
    {0xF1, 0x01},
    {0xF2, 0x01},
    {0xF3, 0x30},
    {0xF9, 0x9F},
    {0xFA, 0x78},

    // 51-------------------------------------------------------------
    {0xFE, 0x01}, // set Page1

    {0x00, 0xF5},
    {0x02, 0x1A},
    {0x0A, 0xA0},
    {0x0B, 0x60},
    {0x0C, 0x08},
    {0x0E, 0x4C},
    {0x0F, 0x39},
    {0x11, 0x3F},
    {0x12, 0x72},
    {0x13, 0x13},
    {0x14, 0x42},
    {0x15, 0x43},
    {0x16, 0xC2},
    {0x17, 0xA8},
    {0x18, 0x18},
    {0x19, 0x40},
    {0x1A, 0xD0},
    {0x1B, 0xF5},
    {0x70, 0x40},
    {0x71, 0x58},
    {0x72, 0x30},
    {0x73, 0x48},
    {0x74, 0x20},
    {0x75, 0x60},
    {0x77, 0x20},
    {0x78, 0x32},
    {0x30, 0x03},
    {0x31, 0x40},
    {0x32, 0xE0}, // BLK Global_offset
    {0x33, 0xE0}, // BLK Current_R_offset
    {0x34, 0xE0}, // BLK Current_G_offset
    {0x35, 0xB0}, // BLK Current_B_offset
    {0x36, 0xC0},
    {0x37, 0xC0},
    {0x38, 0x04},
    {0x39, 0x09},
    {0x3A, 0x12},
    {0x3B, 0x1C},
    {0x3C, 0x28},
    {0x3D, 0x31},
    {0x3E, 0x44},
    {0x3F, 0x57},
    {0x40, 0x6C},
    {0x41, 0x81},
    {0x42, 0x94},
    {0x43, 0xA7},
    {0x44, 0xB8},
    {0x45, 0xD6},
    {0x46, 0xEE},
    {0x47, 0x0D},

    // 52 ---------Update the registers 2010/07/06-------------//
    {0xFE, 0x00}, // set Page0
    {0x10, 0x26},
    {0x11, 0x0D}, // FD,modified By mormo 2010/07/06
    {0x1A, 0x2A}, // 1E,modified By mormo 2010/07/06

    {0x1C, 0x49}, // C1,modified By mormo 2010/07/06
    {0x1D, 0x9A}, // 08,modified By mormo 2010/07/06
    {0x1E, 0x61}, // 60,modified By mormo 2010/07/06

    {0x3A, 0x20},

    {0x50, 0x14}, // 10,modified By mormo 2010/07/06
    {0x53, 0x80},
    {0x56, 0x80},

    {0x8B, 0x20}, // LSC
    {0x8C, 0x20},
    {0x8D, 0x20},
    {0x8E, 0x14},
    {0x8F, 0x10},
    {0x90, 0x14},

    {0x94, 0x02},
    {0x95, 0x07},
    {0x96, 0xE0},

    {0xB1, 0x40}, // YCPT
    {0xB2, 0x40},
    {0xB3, 0x40},
    {0xB6, 0xE0},

    {0xD0, 0xCB},
    {0xD3, 0x48},

    {0xF2, 0x02},
    {0xF7, 0x12},
    {0xF8, 0x0A},

    // Registers of Page1
    {0xFE, 0x01}, // set Page1
    {0x02, 0x20},
    {0x04, 0x10},
    {0x05, 0x08},
    {0x06, 0x20},
    {0x08, 0x0A},

    {0x0E, 0x44},
    {0x0F, 0x32},
    {0x10, 0x41},
    {0x11, 0x37},
    {0x12, 0x22},
    {0x13, 0x19},
    {0x14, 0x44},
    {0x15, 0x44},

    {0x19, 0x50},
    {0x1A, 0xD8},

    {0x32, 0x10},

    {0x35, 0x00},
    {0x36, 0x80},
    {0x37, 0x00},

    {0xFF, 0xFF}, // end
};
#endif

/**
 * @brief   Init the port used by gc0308.
 * @param   None
 * @retval: None
 */
static void GC0308_InitPort(void)
{
    GPIO_InitType GPIO_InitStruct;

#if ((BOARD_TYPE == BOARD_V1_1)||(BOARD_TYPE == BOARD_V1_2))
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
    GPIO_ConfigPinRemap(GPIO_RMP_SW_JTAG_SW_ENABLE,ENABLE);
#endif
    
    RCC_EnableAPB2PeriphClk( GC0308_MCLK_PORT_CLK
                            |GC0308_PWDN_PORT_CLK
                            |GC0308_RESET_PORT_CLK, 
                             ENABLE);

    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    /*  MCLK  */
    GPIO_InitStruct.Pin     = GC0308_MCLK_PIN;
    GPIO_InitPeripheral(GC0308_MCLK_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;

    /*  RESET  */
    GPIO_InitStruct.Pin     = GC0308_RESET_PIN;
    GPIO_InitPeripheral(GC0308_RESET_PORT, &GPIO_InitStruct);

    /*  PWDN  */
    GPIO_InitStruct.Pin        = GC0308_PWDN_PIN;
    GPIO_InitPeripheral(GC0308_PWDN_PORT, &GPIO_InitStruct);

    /* DVP MCLK output, MCO used */
    RCC_ConfigMco(RCC_MCO_PLLCLK);
    if (clks.SysclkFreq == 144000000)
    {
        RCC_ConfigMcoPllClk(RCC_MCO_PLLCLK_DIV3);
    }
    else if (clks.SysclkFreq == 96000000)
    {
        RCC_ConfigMcoPllClk(RCC_MCO_PLLCLK_DIV2);
    }
    else
    {
        while (1)
            ;
    }

    /* Reset GC0308 by reset pin*/
    GC0308_ENTER_PWDN;
    GC0308_ENTER_RESET;
    DelayUs(10000);
    
    GC0308_EXIT_PWDN;
    DelayUs(10000);
    
    GC0308_EXIT_RESET;
    DelayUs(10000);
}

/**
 * @brief   Reset GC0308 by software.
 * @param   None
 * @retval: None
 */
void GC0308_SoftReset(void)
{
    GC_WriteReg(GC0308_I2C_ADDR, GC0308_Rest_related, 0x80);
}

/**
 * @brief   Init GC0308.
 * @param   None
 * @retval: None
 */
void GC0308_Init(void)
{
    uint8_t  ID = 0;
    uint32_t i;

    /* Init port used for GC0308 */
    GC0308_InitPort();

    /* Init I2C interface used for GC0308 */
    GC_VirI2CInit();

    /* Reset GC0308 by software */
    GC0308_SoftReset();
    DelayUs(10000);

    /* Check GC0308 ID */
    do
    {
        GC_ReadReg(GC0308_I2C_ADDR, GC0308_ID, &ID);
        if(ID == GC0308_CHIP_ID)
            break;
    }
    while (1);

    /* Init GC0308 register by I2C interface */
    for (i = 0; ; i++)
    {
        if(GC0308_ConfigData[i][0]==GC0308_INVALIE_REG)
            break;

        GC_WriteReg(GC0308_I2C_ADDR,
                    GC0308_ConfigData[i][0], 
                    GC0308_ConfigData[i][1]);
        DelayUs(5);
    }
}

