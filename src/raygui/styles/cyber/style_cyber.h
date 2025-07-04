//////////////////////////////////////////////////////////////////////////////////
//                                                                              //
// StyleAsCode exporter v2.0 - Style data exported as a values array            //
//                                                                              //
// USAGE: On init call: GuiLoadStyleCyber();                                   //
//                                                                              //
// more info and bugs-report:  github.com/raysan5/raygui                        //
// feedback and support:       ray[at]raylibtech.com                            //
//                                                                              //
// Copyright (c) 2020-2023 raylib technologies (@raylibtech)                    //
//                                                                              //
//////////////////////////////////////////////////////////////////////////////////

#define CYBER_STYLE_PROPS_COUNT  17

// Custom style name: Cyber
static const GuiStyleProp cyberStyleProps[CYBER_STYLE_PROPS_COUNT] = {
    { 0, 0, 0x2f7486ff },    // DEFAULT_BORDER_COLOR_NORMAL 
    { 0, 1, 0x024658ff },    // DEFAULT_BASE_COLOR_NORMAL 
    { 0, 2, 0x51bfd3ff },    // DEFAULT_TEXT_COLOR_NORMAL 
    { 0, 3, 0x82cde0ff },    // DEFAULT_BORDER_COLOR_FOCUSED 
    { 0, 4, 0x3299b4ff },    // DEFAULT_BASE_COLOR_FOCUSED 
    { 0, 5, 0xb6e1eaff },    // DEFAULT_TEXT_COLOR_FOCUSED 
    { 0, 6, 0xeb7630ff },    // DEFAULT_BORDER_COLOR_PRESSED 
    { 0, 7, 0xffbc51ff },    // DEFAULT_BASE_COLOR_PRESSED 
    { 0, 8, 0xd86f36ff },    // DEFAULT_TEXT_COLOR_PRESSED 
    { 0, 9, 0x134b5aff },    // DEFAULT_BORDER_COLOR_DISABLED 
    { 0, 10, 0x02313dff },    // DEFAULT_BASE_COLOR_DISABLED 
    { 0, 11, 0x17505fff },    // DEFAULT_TEXT_COLOR_DISABLED 
    { 0, 16, 0x0000000e },    // DEFAULT_TEXT_SIZE 
    { 0, 17, 0x00000000 },    // DEFAULT_TEXT_SPACING 
    { 0, 18, 0x81c0d0ff },    // DEFAULT_LINE_COLOR 
    { 0, 19, 0x00222bff },    // DEFAULT_BACKGROUND_COLOR 
    { 0, 20, 0x00000015 },    // DEFAULT_TEXT_LINE_SPACING 
};

// WARNING: This style uses a custom font: "Kyrou 7 Wide.ttf" (size: 14, spacing: 0)

#define CYBER_STYLE_FONT_ATLAS_COMP_SIZE 2286

// Font atlas image pixels data: DEFLATE compressed
static unsigned char cyberFontData[CYBER_STYLE_FONT_ATLAS_COMP_SIZE] = { 0xed,
    0xdd, 0x81, 0x6e, 0xdb, 0x36, 0x10, 0x06, 0x60, 0x21, 0xef, 0xff, 0xc6, 0x99, 0xf6, 0x0f, 0xe8, 0xd0, 0x2d, 0x45, 0x6b,
    0x89, 0x3c, 0x92, 0xb2, 0xec, 0x7c, 0xfd, 0x80, 0x61, 0x88, 0x62, 0x5b, 0xa2, 0x78, 0xe4, 0x49, 0x0a, 0xcf, 0xd9, 0x00,
    0x00, 0x00, 0x00, 0x26, 0xcb, 0xc5, 0x9f, 0x96, 0xe6, 0x9f, 0xce, 0x3b, 0xa2, 0x9f, 0xff, 0x9e, 0x7b, 0xec, 0xfa, 0x57,
    0x7f, 0xbb, 0xe7, 0xe1, 0xb9, 0xd3, 0x9e, 0x5f, 0x7f, 0x92, 0xc3, 0xdf, 0x4d, 0xa9, 0x75, 0x73, 0x7a, 0xc6, 0x8e, 0xcf,
    0x4c, 0x5f, 0xbc, 0x3d, 0xde, 0x87, 0x74, 0xbf, 0x62, 0xe5, 0xc8, 0xf8, 0xf3, 0xdf, 0xde, 0xd5, 0xdf, 0x8f, 0x7b, 0x71,
    0x5b, 0x2f, 0xcf, 0xc9, 0x1e, 0xa5, 0xe1, 0x37, 0xce, 0x5e, 0xbf, 0x0d, 0xec, 0xfd, 0x7e, 0xe9, 0x5c, 0x94, 0xd3, 0x31,
    0x63, 0x5b, 0x70, 0x34, 0x19, 0x3c, 0x97, 0x19, 0x1e, 0xd1, 0xda, 0xe3, 0xff, 0xac, 0x5f, 0xe4, 0xb7, 0xff, 0x6e, 0xa5,
    0x48, 0xcb, 0xc2, 0xf8, 0xdf, 0xba, 0xc6, 0x97, 0xf5, 0x79, 0x51, 0x1a, 0x22, 0xbd, 0xff, 0x35, 0xad, 0x47, 0x5b, 0x1b,
    0xf1, 0xd2, 0xfc, 0xbb, 0x29, 0x1d, 0xf1, 0xac, 0x33, 0xd2, 0x3b, 0x72, 0x9e, 0xb5, 0xc6, 0x8a, 0xa3, 0xf9, 0xfa, 0xb3,
    0xcf, 0xc1, 0xd7, 0xef, 0xcb, 0xc7, 0xc8, 0xbd, 0xa1, 0xa5, 0xf6, 0xf2, 0x27, 0xa6, 0x90, 0xcd, 0xcd, 0x3a, 0xfb, 0xab,
    0xf3, 0xc2, 0x94, 0x63, 0x29, 0x43, 0x67, 0xef, 0xf8, 0x73, 0xab, 0xf3, 0xf7, 0xda, 0x11, 0xaf, 0x3f, 0xd7, 0xcf, 0xa4,
    0xd1, 0xbc, 0x36, 0x9a, 0xfd, 0x6c, 0xa9, 0x2c, 0x88, 0xdf, 0x79, 0x63, 0xf1, 0xcc, 0x1c, 0x69, 0x24, 0xef, 0x3c, 0xda,
    0xf6, 0xf9, 0x43, 0xfb, 0x5e, 0xbd, 0xca, 0xfc, 0x9f, 0x81, 0xf3, 0x97, 0x52, 0x3b, 0x9f, 0xe5, 0x94, 0xad, 0x47, 0x7c,
    0xfc, 0xe9, 0x7b, 0xe1, 0x98, 0x3f, 0xb2, 0xff, 0x67, 0x9b, 0x92, 0xd3, 0x66, 0xe2, 0xb9, 0x4c, 0xf7, 0xb5, 0xd2, 0xbf,
    0x71, 0x5b, 0xcf, 0x99, 0x93, 0xbf, 0x7f, 0xd8, 0x17, 0xe7, 0x62, 0x57, 0xc4, 0xff, 0xff, 0xa3, 0x58, 0x06, 0x22, 0x36,
    0x83, 0x33, 0xcc, 0xdc, 0xeb, 0xff, 0x71, 0xfb, 0xd0, 0xf9, 0xcb, 0xf4, 0xab, 0xda, 0xff, 0xa3, 0x37, 0xa5, 0xfc, 0x21,
    0xd3, 0x46, 0xd9, 0x7d, 0xe1, 0xbd, 0xe4, 0x2c, 0xca, 0xd2, 0x1e, 0xcd, 0xff, 0xd7, 0x65, 0x3b, 0x6b, 0xae, 0x96, 0x7a,
    0xee, 0x9d, 0x56, 0xaf, 0xff, 0xd3, 0x38, 0xba, 0xac, 0x8b, 0xff, 0xeb, 0xfd, 0x35, 0x78, 0xfe, 0x72, 0xf1, 0xf5, 0xf9,
    0x9c, 0x2b, 0xf4, 0x7a, 0xc6, 0xb3, 0xf6, 0xfa, 0xff, 0xaa, 0x11, 0x63, 0x45, 0xfe, 0x9f, 0x17, 0xcf, 0xff, 0x7b, 0xee,
    0xff, 0xe7, 0x4d, 0xe2, 0x3f, 0xc3, 0x4f, 0xa4, 0x32, 0xfd, 0xfe, 0x7c, 0x5b, 0xb6, 0x3b, 0xf6, 0x7c, 0x21, 0x43, 0x47,
    0x3c, 0xeb, 0x5e, 0x4c, 0x26, 0xfd, 0x6e, 0x1a, 0x67, 0xc5, 0xda, 0xfd, 0xdd, 0xe7, 0xde, 0xff, 0xf7, 0xfc, 0x1f, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x9e, 0xd5, 0x9d, 0xb9, 0xe0, 0x75, 0x95,
    0x55, 0xb4, 0x23, 0xab, 0x6e, 0x47, 0xd6, 0xec, 0x56, 0x5f, 0x79, 0x5e, 0x87, 0xa8, 0xbe, 0xce, 0xb8, 0x7d, 0x95, 0x73,
    0xdf, 0xba, 0xe1, 0xb1, 0xea, 0x28, 0x39, 0x5d, 0x47, 0xdf, 0x56, 0x8f, 0xe0, 0xbc, 0x76, 0xeb, 0x59, 0x25, 0xab, 0xf5,
    0xb5, 0x5f, 0x57, 0xd6, 0xa6, 0x4c, 0xb9, 0x05, 0x7b, 0x56, 0xbf, 0xa7, 0xab, 0x3e, 0x41, 0x75, 0x1d, 0xfa, 0x75, 0x55,
    0x01, 0xc7, 0x57, 0xc8, 0x1f, 0xbf, 0xf3, 0xbe, 0xfc, 0x28, 0xda, 0xf7, 0x38, 0x13, 0xce, 0xd9, 0x8a, 0xf8, 0xcf, 0x61,
    0x45, 0x80, 0x5c, 0x58, 0xdb, 0x75, 0x5d, 0x25, 0xdc, 0x75, 0x95, 0x76, 0xce, 0xe3, 0xbf, 0xbd, 0x66, 0x73, 0x26, 0x47,
    0x6b, 0xca, 0xd1, 0x33, 0x6b, 0x04, 0xa8, 0x8c, 0x5b, 0x33, 0xe2, 0xbf, 0x9a, 0x3b, 0xbc, 0x76, 0xfc, 0x57, 0xeb, 0x89,
    0xe5, 0xe0, 0xbc, 0xa7, 0xb1, 0x6f, 0xdf, 0x61, 0xfb, 0x76, 0xd3, 0xf8, 0x3f, 0x8f, 0xa9, 0x0c, 0x57, 0x29, 0x9e, 0xd7,
    0x9f, 0xe6, 0xd9, 0x9b, 0xa2, 0xb4, 0x56, 0xd3, 0x73, 0x2f, 0x8f, 0x2c, 0xab, 0xf2, 0xff, 0x9c, 0x5c, 0x79, 0xa4, 0x29,
    0x97, 0x9d, 0x3b, 0xc6, 0xb6, 0x8e, 0x5a, 0x8f, 0x2b, 0x8a, 0x9d, 0xd5, 0x2b, 0x7c, 0xfe, 0xfc, 0x3e, 0x56, 0x4f, 0xf9,
    0x9a, 0xf8, 0x1f, 0x8f, 0xc4, 0x3c, 0x65, 0xce, 0x9a, 0x73, 0x6f, 0x22, 0xc5, 0x79, 0x6b, 0xcd, 0x6b, 0xaf, 0x98, 0xff,
    0xf3, 0x52, 0xf3, 0x7f, 0xcb, 0xf5, 0x7f, 0x26, 0x5c, 0xbd, 0xd6, 0x5a, 0x6d, 0x6f, 0x3e, 0x97, 0x2b, 0xf2, 0xff, 0x96,
    0x99, 0x7d, 0x7c, 0xfe, 0x1f, 0xd9, 0x9a, 0xe6, 0x59, 0xf8, 0xfa, 0xf8, 0x6f, 0x3b, 0xa6, 0x5c, 0xfa, 0xda, 0xd7, 0x8b,
    0xff, 0xdc, 0xe2, 0xfe, 0x5f, 0x16, 0xd6, 0x66, 0xce, 0x94, 0xd1, 0x6d, 0x4d, 0xfc, 0xb7, 0xd5, 0x43, 0x1f, 0xb9, 0xfe,
    0x1f, 0x8b, 0xf0, 0xf3, 0x08, 0xf8, 0x4b, 0xfc, 0x4f, 0xca, 0xff, 0x67, 0xbd, 0xba, 0xff, 0x5e, 0xc9, 0xc8, 0x0c, 0xda,
    0x7e, 0x4c, 0x99, 0x9e, 0x7f, 0x8f, 0xd6, 0xf6, 0x5d, 0x9d, 0xff, 0xcf, 0x7a, 0xfd, 0x56, 0x3e, 0xef, 0xe7, 0x5b, 0xc6,
    0x7a, 0xe5, 0xf6, 0x84, 0x6f, 0x73, 0x58, 0xfd, 0x7c, 0xcf, 0x77, 0x94, 0xbe, 0xdf, 0x53, 0x6c, 0x6d, 0x70, 0xef, 0xe7,
    0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x77, 0x5e, 0x65, 0x75, 0xbf, 0x15,
    0x53, 0x69, 0x58, 0x1f, 0xda, 0x52, 0x3f, 0xf3, 0xb8, 0xfa, 0xe6, 0xa3, 0x1a, 0x12, 0x7b, 0x53, 0xed, 0xcd, 0x59, 0xad,
    0xd9, 0x5a, 0x07, 0x61, 0xb4, 0x4e, 0x67, 0xe5, 0xdd, 0x5b, 0x5a, 0xf9, 0x7c, 0xcd, 0x63, 0x4e, 0xd6, 0x01, 0x6f, 0x13,
    0x7b, 0xe0, 0xf9, 0x9a, 0xe7, 0x0c, 0xd4, 0x5c, 0x18, 0xa9, 0x22, 0x98, 0x85, 0x2b, 0x4c, 0x53, 0x6a, 0x95, 0xf6, 0x0a,
    0x1c, 0xad, 0x5b, 0x33, 0xa9, 0xca, 0xc3, 0xea, 0x7e, 0x3d, 0x63, 0x6b, 0x7f, 0x1d, 0x85, 0x67, 0xc4, 0xff, 0x71, 0x0f,
    0xc9, 0xe4, 0xb3, 0xdd, 0xf7, 0xd3, 0xb3, 0xd8, 0x7f, 0x5c, 0x5b, 0xf9, 0xa3, 0xb1, 0xdf, 0xf4, 0x6c, 0xcf, 0xf0, 0x59,
    0xce, 0x60, 0x25, 0x84, 0xbd, 0x73, 0xbe, 0x69, 0x8f, 0xfe, 0xb1, 0x9e, 0xb7, 0x6e, 0x05, 0xfc, 0x3b, 0xc5, 0xff, 0x56,
    0xac, 0x58, 0xb8, 0x3a, 0xfe, 0xb7, 0xa6, 0x7d, 0xca, 0xb4, 0x23, 0x9a, 0x57, 0x7d, 0xfb, 0xa3, 0x3b, 0xc7, 0x9a, 0x53,
    0xcb, 0x2a, 0x17, 0xd6, 0x7a, 0x48, 0x47, 0xef, 0xaa, 0x8e, 0x00, 0x29, 0xce, 0xff, 0xfd, 0x2d, 0x3d, 0x2b, 0xc7, 0x78,
    0xcd, 0xf8, 0xaf, 0xb5, 0x66, 0x06, 0xce, 0xf0, 0xda, 0xf9, 0x7f, 0x66, 0xe5, 0xee, 0x4a, 0x74, 0xec, 0x0f, 0xde, 0x65,
    0x2f, 0xcf, 0xce, 0xf5, 0xab, 0x83, 0xad, 0xe9, 0x3b, 0x19, 0xf6, 0xee, 0xd7, 0xe5, 0x97, 0xf8, 0xcc, 0x92, 0x6b, 0xf4,
    0x1c, 0xb4, 0x70, 0xb5, 0x1a, 0x69, 0x6f, 0xfc, 0xe7, 0xd2, 0xf9, 0x7f, 0x6b, 0xfc, 0xf6, 0x8c, 0xad, 0x74, 0xbe, 0xb6,
    0xe2, 0xbb, 0xd6, 0x5f, 0x99, 0xd3, 0x1e, 0xbb, 0xa6, 0x1e, 0xed, 0xcc, 0x6f, 0xe8, 0xc8, 0x84, 0x7e, 0x9b, 0x93, 0x4f,
    0x48, 0x31, 0x07, 0xef, 0xcd, 0xfc, 0x7b, 0xc6, 0xd9, 0x74, 0xdc, 0x19, 0xc8, 0xc1, 0x18, 0x98, 0x45, 0x39, 0xf8, 0xcc,
    0x79, 0x30, 0x53, 0xf3, 0xb5, 0x75, 0x77, 0x17, 0x57, 0x66, 0x74, 0xd7, 0xbc, 0xdb, 0xb3, 0xda, 0xe4, 0xca, 0xf9, 0x3f,
    0xdd, 0xd9, 0xee, 0xc8, 0xfc, 0x9f, 0xe1, 0x3a, 0x99, 0x67, 0xb9, 0xdf, 0x76, 0xbb, 0xf9, 0xbf, 0x2d, 0x36, 0x73, 0x79,
    0xfe, 0x2f, 0xfe, 0xaf, 0x7e, 0xd2, 0xb2, 0xbd, 0x44, 0xfc, 0xaf, 0xbd, 0xfe, 0x9f, 0x33, 0x82, 0x54, 0x67, 0xd9, 0x6d,
    0xf1, 0x33, 0x82, 0xfa, 0xab, 0xd6, 0xc5, 0xff, 0xf6, 0xad, 0xaa, 0x35, 0xbe, 0x5b, 0x6d, 0xca, 0x67, 0xc4, 0x7f, 0x4b,
    0xfe, 0x9f, 0xe2, 0xfd, 0xff, 0xf6, 0x6f, 0xd8, 0x4a, 0x57, 0xce, 0xd2, 0x9e, 0x77, 0xbc, 0x67, 0x8f, 0xe0, 0x9d, 0x47,
    0xb4, 0xb1, 0xe7, 0xff, 0x77, 0x1b, 0x83, 0xc7, 0xbe, 0x53, 0xe5, 0x3b, 0xf7, 0x7f, 0x75, 0x97, 0xf1, 0xd7, 0x72, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xcf, 0x5e, 0xb7, 0x90, 0x4b, 0xd7, 0xcb, 0x57, 0xeb,
    0xd6, 0xf5, 0xaf, 0x58, 0xcd, 0xa4, 0x96, 0xc9, 0xa4, 0xb3, 0xb5, 0x37, 0xac, 0xce, 0xcf, 0x60, 0xbb, 0x67, 0xf8, 0x77,
    0xd2, 0xb0, 0x22, 0x2c, 0xa5, 0x33, 0x7c, 0xbf, 0x75, 0xab, 0x23, 0xab, 0x06, 0x33, 0xb5, 0x75, 0x67, 0x9e, 0xef, 0x9c,
    0x56, 0xc3, 0xfe, 0x6a, 0x2f, 0x56, 0x5f, 0x49, 0x69, 0xc5, 0x64, 0xca, 0xb5, 0x09, 0x7a, 0xc7, 0xbb, 0x74, 0xb6, 0x59,
    0xef, 0xb9, 0xfe, 0xda, 0xc6, 0xad, 0x55, 0x66, 0xbe, 0x6e, 0xdf, 0xcb, 0x3d, 0xfb, 0x73, 0xa8, 0xdf, 0xa7, 0x3c, 0x42,
    0x6f, 0x53, 0xea, 0x7a, 0xb7, 0x54, 0xe3, 0xd8, 0x1b, 0xd6, 0xd0, 0x67, 0xb8, 0x36, 0x58, 0xca, 0xed, 0x30, 0xb3, 0xe7,
    0x8d, 0x7d, 0xda, 0xd9, 0x5a, 0xed, 0x0c, 0xcc, 0xa0, 0x29, 0xd6, 0xbf, 0xcb, 0x60, 0x65, 0x88, 0x1c, 0xac, 0xf1, 0xce,
    0xb2, 0xf5, 0xed, 0xe9, 0x8c, 0xfe, 0xf6, 0xe3, 0x4d, 0x73, 0x9b, 0xb6, 0xd5, 0xab, 0xfe, 0xb8, 0x7d, 0x56, 0xba, 0x97,
    0x66, 0x9b, 0x5a, 0x9b, 0x5e, 0x9d, 0x6f, 0xdc, 0xbd, 0xb6, 0xc7, 0x79, 0xf5, 0xb1, 0xf5, 0xd7, 0x06, 0x95, 0x5a, 0x2c,
    0xf3, 0xe2, 0x3f, 0xdd, 0x15, 0xa5, 0xf6, 0xa1, 0xab, 0x8e, 0xbe, 0xf8, 0x6f, 0x7b, 0xdf, 0x94, 0xe6, 0xff, 0xb3, 0xf8,
    0x5b, 0xbb, 0x7d, 0xb4, 0xda, 0x7e, 0x35, 0xfe, 0xfb, 0xfb, 0x40, 0x16, 0xd4, 0x48, 0x3d, 0xcb, 0x4a, 0x2a, 0x5b, 0xc6,
    0xaf, 0xb1, 0xd7, 0xc5, 0xff, 0x51, 0xeb, 0x8d, 0xe6, 0x1b, 0xb3, 0xe6, 0xff, 0x0c, 0xe7, 0xff, 0xad, 0x7d, 0x35, 0xcd,
    0xdf, 0x2f, 0xd4, 0x92, 0x53, 0x1d, 0x55, 0x77, 0xde, 0x4f, 0xbf, 0x29, 0x63, 0x2b, 0x7e, 0x1b, 0xc6, 0xea, 0xed, 0x3d,
    0xe3, 0xf6, 0x9c, 0xca, 0x9d, 0xd7, 0x6f, 0x9d, 0x31, 0xf6, 0xdd, 0x23, 0xfe, 0xb3, 0x28, 0xd3, 0xc9, 0x50, 0xbb, 0xa6,
    0x6b, 0xdf, 0xaf, 0xb9, 0xbb, 0x94, 0xcb, 0xaa, 0x8a, 0xce, 0xf9, 0x2e, 0x8c, 0x75, 0xdb, 0x5b, 0xc7, 0xc1, 0xfd, 0x82,
    0xf9, 0x7f, 0xe5, 0x1d, 0xd0, 0x7a, 0x55, 0xf8, 0x6b, 0xe2, 0xff, 0x59, 0xd7, 0x46, 0xeb, 0xfa, 0x76, 0x4f, 0xfc, 0xe7,
    0xe2, 0xe3, 0xb8, 0x3e, 0xfe, 0x3f, 0xfe, 0x18, 0x41, 0xe9, 0xc8, 0x6b, 0xd7, 0x6c, 0x9f, 0x39, 0xbe, 0x8c, 0x8e, 0x75,
    0xcf, 0xc9, 0xff, 0x9f, 0x1f, 0xff, 0x77, 0xbe, 0x43, 0x91, 0x37, 0xba, 0x43, 0x93, 0x5f, 0xee, 0xb2, 0x5c, 0xf7, 0x3c,
    0xb6, 0x7e, 0xfd, 0xfd, 0x5a, 0xdb, 0xc7, 0xee, 0xff, 0x7f, 0xdf, 0xfc, 0xff, 0xce, 0x7f, 0xb3, 0xe0, 0xef, 0x36, 0x56,
    0xb6, 0xd3, 0xfd, 0xe3, 0x7b, 0xfe, 0xc8, 0xfc, 0xe8, 0x6e, 0xc8, 0xf7, 0xcd, 0xff, 0xef, 0xff, 0x17, 0x4b, 0xaa, 0xad,
    0x5e, 0x71, 0x4d, 0x72, 0xc7, 0xfb, 0x7b, 0xb3, 0xfb, 0xfb, 0xd1, 0xbd, 0xd0, 0x55, 0xf9, 0xff, 0x76, 0xf3, 0xfb, 0xff,
    0xf0, 0x9a, 0xe3, 0x13, 0x20, 0xfe, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xde, 0xf7, 0xaf, 0x29,
    0x53, 0x5e, 0x37, 0x91, 0x1f, 0x6b, 0xc8, 0x3f, 0x06, 0x56, 0x23, 0xad, 0xab, 0x22, 0x7b, 0x5c, 0x03, 0xeb, 0x73, 0xe0,
    0xef, 0x47, 0xd7, 0x1e, 0x57, 0x26, 0xad, 0x1f, 0x7d, 0xc6, 0x91, 0xa5, 0x78, 0xae, 0xc6, 0xd7, 0x32, 0xe7, 0xb7, 0xff,
    0x9f, 0xbb, 0xd6, 0xf7, 0x71, 0xbd, 0x84, 0xb1, 0x33, 0xd2, 0xb3, 0xf2, 0xf0, 0x5e, 0x15, 0x0a, 0xf7, 0x1f, 0xed, 0x91,
    0xc3, 0x3a, 0x92, 0x77, 0xae, 0x22, 0xbb, 0x97, 0xaa, 0xcb, 0xac, 0x3f, 0xae, 0xb1, 0x78, 0xc8, 0x49, 0x5d, 0xcf, 0xe7,
    0x54, 0xbb, 0x3d, 0x3b, 0x57, 0xc7, 0xb5, 0xb0, 0xf7, 0xc6, 0xf5, 0xf2, 0xc7, 0x55, 0x91, 0x33, 0x38, 0xfa, 0x9d, 0x47,
    0x7f, 0x4a, 0x47, 0xf7, 0xa7, 0x33, 0x96, 0xe6, 0x4f, 0xc8, 0xa4, 0xea, 0x5c, 0xc7, 0xad, 0xb1, 0xbf, 0xf0, 0x4a, 0xe1,
    0xbd, 0x2b, 0xfe, 0xf3, 0x25, 0x43, 0xc8, 0x0b, 0xae, 0x6e, 0x69, 0x1d, 0x8f, 0x5f, 0x6b, 0xe5, 0x4c, 0x9a, 0x57, 0x84,
    0x8f, 0x54, 0xdc, 0xb1, 0x9e, 0xaa, 0xbd, 0x27, 0x9e, 0xf7, 0xd3, 0x7b, 0x57, 0x91, 0xfd, 0x3c, 0x39, 0xae, 0xbc, 0x6c,
    0xf5, 0x9b, 0xb6, 0x56, 0x49, 0x21, 0x3b, 0x78, 0xd6, 0xd6, 0xe3, 0x2c, 0xee, 0x4f, 0xf3, 0x7f, 0x2d, 0xb3, 0x79, 0xd6,
    0xb1, 0xb7, 0xee, 0x6b, 0x96, 0x5c, 0x09, 0xb6, 0xf4, 0x84, 0x1c, 0x66, 0x5b, 0xaf, 0x18, 0x27, 0x2d, 0x99, 0xe8, 0x3d,
    0xf7, 0x3b, 0x8d, 0xbd, 0x21, 0x07, 0x79, 0xf8, 0x5d, 0xeb, 0xde, 0x8e, 0x8c, 0x4a, 0x69, 0xb8, 0xc2, 0x6f, 0xc9, 0x0e,
    0xf6, 0x4b, 0xb7, 0xde, 0x35, 0xfe, 0x5b, 0xe6, 0xff, 0xbc, 0x69, 0xfc, 0xef, 0x37, 0xdf, 0xef, 0xfa, 0xf7, 0x9f, 0xb5,
    0xce, 0xff, 0xf7, 0xda, 0x3a, 0x33, 0x83, 0x7f, 0x7c, 0xbf, 0x6d, 0x5d, 0xa5, 0xcf, 0xfe, 0xfb, 0x8e, 0xaf, 0x11, 0xff,
    0x77, 0x9e, 0x27, 0xeb, 0xf1, 0xff, 0xf9, 0x02, 0xfb, 0x9d, 0xd2, 0x1d, 0x9d, 0xb3, 0xf8, 0xdf, 0x6f, 0xb9, 0x75, 0x66,
    0x65, 0xab, 0xea, 0xb3, 0xaa, 0x95, 0x95, 0x3e, 0xef, 0x1b, 0xff, 0x2d, 0xf9, 0xd2, 0xab, 0x5e, 0x27, 0x6f, 0xc3, 0x11,
    0x74, 0xd7, 0xf8, 0x3f, 0x7f, 0xf2, 0x50, 0x7f, 0x42, 0xf6, 0x8c, 0xad, 0xfb, 0x45, 0x77, 0xf0, 0x9e, 0x77, 0xec, 0xcf,
    0x8b, 0xff, 0x91, 0x0a, 0x85, 0xc7, 0xf7, 0x5d, 0xee, 0x70, 0x9d, 0xbc, 0xa2, 0x1e, 0xe2, 0x3d, 0xf6, 0x3b, 0x8b, 0xe6,
    0xa2, 0x7b, 0x3f, 0xc9, 0x71, 0x07, 0xff, 0x9e, 0x4f, 0x0d, 0x6a, 0xfd, 0x78, 0xf5, 0xf6, 0x67, 0xf5, 0xc6, 0x2b, 0xf6,
    0x5b, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0xa7, 0x95, 0x3c, 0x39, 0x59,
    0x05, 0xbc, 0x75, 0xd5, 0x2e, 0xfa, 0x55, 0xb5, 0x66, 0x6a, 0x26, 0x54, 0xc9, 0x7c, 0xb4, 0xf6, 0x66, 0xbf, 0xfc, 0x68,
    0xb6, 0xc1, 0x77, 0x86, 0xab, 0x56, 0xf3, 0xfd, 0x69, 0xbd, 0x78, 0xb5, 0xcf, 0x57, 0x6b, 0xa6, 0x8e, 0xd5, 0x8b, 0x3d,
    0x5b, 0x29, 0xfd, 0x59, 0x1c, 0xcf, 0x56, 0x55, 0x80, 0x3d, 0x7a, 0xe7, 0xf3, 0x7a, 0xbe, 0xd6, 0x03, 0x32, 0x1e, 0xfd,
    0xdf, 0xa1, 0x07, 0x65, 0x59, 0x5e, 0xb1, 0x72, 0x9f, 0x3f, 0xf4, 0x50, 0x9e, 0x94, 0x03, 0xb4, 0xad, 0x65, 0xdf, 0x6f,
    0xb5, 0xf5, 0xf1, 0x3e, 0xa7, 0xb1, 0xb2, 0xdf, 0xbd, 0xb6, 0x8e, 0xd4, 0xf3, 0x85, 0x96, 0x2b, 0xe2, 0xf3, 0xaa, 0xa8,
    0xaf, 0xb3, 0xb5, 0xe5, 0x68, 0xb7, 0x37, 0x39, 0x56, 0xf1, 0xcf, 0xac, 0x39, 0xff, 0x9d, 0x7a, 0x7d, 0x86, 0xda, 0x42,
    0xfc, 0x23, 0xfe, 0xbf, 0x5b, 0xaf, 0x17, 0xff, 0x7c, 0xdf, 0xfc, 0x7f, 0x1f, 0xaa, 0x17, 0xbf, 0xdd, 0x6a, 0xeb, 0xf8,
    0xb5, 0xd0, 0x7d, 0xb6, 0xde, 0xb5, 0x0a, 0x22, 0x70, 0xc5, 0x1d, 0xd8, 0xb1, 0x27, 0xb8, 0xc0, 0x6b, 0xe4, 0x60, 0x95,
    0xb8, 0x36, 0xfb, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd0, 0xe2, 0xdf, 0x7f, 0xda, 0x01, 0xc4, 0x3f,
    0xf0, 0xed, 0xe2, 0xff, 0x1f };

// Font glyphs rectangles data (on atlas)
static const Rectangle cyberFontRecs[189] = {
    { 4, 4, 4 , 14 },
    { 16, 4, 1 , 8 },
    { 25, 4, 4 , 3 },
    { 37, 4, 8 , 8 },
    { 53, 4, 8 , 9 },
    { 69, 4, 8 , 8 },
    { 85, 4, 8 , 8 },
    { 101, 4, 1 , 3 },
    { 110, 4, 4 , 9 },
    { 122, 4, 4 , 9 },
    { 134, 4, 5 , 6 },
    { 147, 4, 5 , 6 },
    { 160, 4, 2 , 2 },
    { 170, 4, 4 , 1 },
    { 182, 4, 1 , 1 },
    { 191, 4, 8 , 8 },
    { 207, 4, 8 , 8 },
    { 223, 4, 2 , 8 },
    { 233, 4, 8 , 8 },
    { 249, 4, 8 , 8 },
    { 265, 4, 8 , 8 },
    { 281, 4, 8 , 8 },
    { 297, 4, 8 , 8 },
    { 313, 4, 7 , 8 },
    { 328, 4, 8 , 8 },
    { 344, 4, 8 , 8 },
    { 360, 4, 1 , 4 },
    { 369, 4, 2 , 5 },
    { 379, 4, 4 , 8 },
    { 391, 4, 5 , 3 },
    { 404, 4, 4 , 8 },
    { 416, 4, 7 , 8 },
    { 431, 4, 8 , 8 },
    { 447, 4, 8 , 8 },
    { 463, 4, 8 , 8 },
    { 479, 4, 8 , 8 },
    { 495, 4, 8 , 8 },
    { 4, 26, 7 , 8 },
    { 19, 26, 7 , 8 },
    { 34, 26, 8 , 8 },
    { 50, 26, 8 , 8 },
    { 66, 26, 5 , 8 },
    { 79, 26, 7 , 8 },
    { 94, 26, 8 , 8 },
    { 110, 26, 7 , 8 },
    { 125, 26, 8 , 8 },
    { 141, 26, 8 , 8 },
    { 157, 26, 8 , 8 },
    { 173, 26, 8 , 8 },
    { 189, 26, 8 , 9 },
    { 205, 26, 8 , 8 },
    { 221, 26, 8 , 8 },
    { 237, 26, 8 , 8 },
    { 253, 26, 8 , 8 },
    { 269, 26, 8 , 8 },
    { 285, 26, 9 , 8 },
    { 302, 26, 8 , 8 },
    { 318, 26, 8 , 8 },
    { 334, 26, 8 , 8 },
    { 350, 26, 4 , 9 },
    { 362, 26, 8 , 8 },
    { 378, 26, 4 , 9 },
    { 390, 26, 4 , 3 },
    { 402, 26, 7 , 1 },
    { 417, 26, 2 , 3 },
    { 427, 26, 7 , 5 },
    { 442, 26, 7 , 8 },
    { 457, 26, 7 , 5 },
    { 472, 26, 7 , 8 },
    { 487, 26, 7 , 5 },
    { 4, 48, 4 , 8 },
    { 16, 48, 7 , 7 },
    { 31, 48, 7 , 8 },
    { 46, 48, 1 , 8 },
    { 55, 48, 3 , 10 },
    { 66, 48, 7 , 8 },
    { 81, 48, 4 , 8 },
    { 93, 48, 9 , 5 },
    { 110, 48, 7 , 5 },
    { 125, 48, 7 , 5 },
    { 140, 48, 7 , 7 },
    { 155, 48, 7 , 7 },
    { 170, 48, 5 , 5 },
    { 183, 48, 7 , 5 },
    { 198, 48, 5 , 8 },
    { 211, 48, 7 , 5 },
    { 226, 48, 7 , 5 },
    { 241, 48, 9 , 5 },
    { 258, 48, 7 , 5 },
    { 273, 48, 7 , 7 },
    { 288, 48, 7 , 5 },
    { 303, 48, 4 , 9 },
    { 315, 48, 1 , 9 },
    { 324, 48, 4 , 9 },
    { 336, 48, 8 , 2 },
    { 352, 48, 1 , 8 },
    { 361, 48, 7 , 8 },
    { 376, 48, 7 , 8 },
    { 391, 48, 8 , 9 },
    { 407, 48, 8 , 9 },
    { 423, 48, 8 , 10 },
    { 439, 48, 4 , 9 },
    { 451, 48, 7 , 8 },
    { 466, 48, 8 , 8 },
    { 482, 48, 7 , 6 },
    { 497, 48, 5 , 3 },
    { 4, 70, 5 , 3 },
    { 17, 70, 8 , 8 },
    { 33, 70, 0 , 0 },
    { 41, 70, 4 , 3 },
    { 53, 70, 8 , 6 },
    { 69, 70, 4 , 5 },
    { 81, 70, 4 , 5 },
    { 93, 70, 8 , 10 },
    { 109, 70, 7 , 7 },
    { 124, 70, 5 , 7 },
    { 137, 70, 1 , 1 },
    { 146, 70, 7 , 8 },
    { 161, 70, 2 , 5 },
    { 171, 70, 4 , 5 },
    { 183, 70, 5 , 3 },
    { 196, 70, 14 , 8 },
    { 218, 70, 13 , 5 },
    { 239, 70, 8 , 9 },
    { 255, 70, 7 , 8 },
    { 270, 70, 8 , 10 },
    { 286, 70, 8 , 10 },
    { 302, 70, 8 , 10 },
    { 318, 70, 8 , 10 },
    { 334, 70, 8 , 9 },
    { 350, 70, 8 , 12 },
    { 366, 70, 14 , 8 },
    { 388, 70, 8 , 10 },
    { 404, 70, 7 , 10 },
    { 419, 70, 7 , 10 },
    { 434, 70, 7 , 10 },
    { 449, 70, 7 , 9 },
    { 464, 70, 5 , 10 },
    { 477, 70, 5 , 10 },
    { 490, 70, 5 , 10 },
    { 4, 92, 5 , 9 },
    { 17, 92, 8 , 8 },
    { 33, 92, 8 , 10 },
    { 49, 92, 8 , 10 },
    { 65, 92, 8 , 10 },
    { 81, 92, 8 , 10 },
    { 97, 92, 8 , 10 },
    { 113, 92, 8 , 9 },
    { 129, 92, 4 , 4 },
    { 141, 92, 8 , 8 },
    { 157, 92, 8 , 10 },
    { 173, 92, 8 , 10 },
    { 189, 92, 8 , 10 },
    { 205, 92, 8 , 9 },
    { 221, 92, 8 , 10 },
    { 237, 92, 7 , 9 },
    { 252, 92, 7 , 9 },
    { 267, 92, 7 , 8 },
    { 282, 92, 7 , 8 },
    { 297, 92, 7 , 8 },
    { 312, 92, 7 , 8 },
    { 327, 92, 7 , 8 },
    { 342, 92, 7 , 9 },
    { 357, 92, 13 , 5 },
    { 378, 92, 7 , 7 },
    { 393, 92, 7 , 8 },
    { 408, 92, 7 , 8 },
    { 423, 92, 7 , 8 },
    { 438, 92, 7 , 8 },
    { 453, 92, 3 , 8 },
    { 464, 92, 2 , 8 },
    { 474, 92, 3 , 8 },
    { 485, 92, 3 , 8 },
    { 4, 114, 8 , 8 },
    { 20, 114, 7 , 8 },
    { 35, 114, 7 , 8 },
    { 50, 114, 7 , 8 },
    { 65, 114, 7 , 8 },
    { 80, 114, 7 , 8 },
    { 95, 114, 7 , 8 },
    { 110, 114, 5 , 6 },
    { 123, 114, 7 , 5 },
    { 138, 114, 7 , 8 },
    { 153, 114, 7 , 8 },
    { 168, 114, 7 , 8 },
    { 183, 114, 7 , 8 },
    { 198, 114, 7 , 10 },
    { 213, 114, 7 , 10 },
    { 228, 114, 7 , 10 },
};

// Font glyphs info data
// NOTE: No glyphs.image data provided
static const GlyphInfo cyberFontGlyphs[189] = {
    { 32, 0, 11, 4, { 0 }},
    { 33, 0, 3, 2, { 0 }},
    { 34, 0, 3, 4, { 0 }},
    { 35, 0, 3, 8, { 0 }},
    { 36, 0, 3, 8, { 0 }},
    { 37, 0, 3, 8, { 0 }},
    { 38, 0, 3, 8, { 0 }},
    { 39, 0, 3, 2, { 0 }},
    { 40, 0, 3, 4, { 0 }},
    { 41, 0, 3, 4, { 0 }},
    { 42, 0, 4, 6, { 0 }},
    { 43, 0, 4, 6, { 0 }},
    { 44, 0, 10, 3, { 0 }},
    { 45, 0, 7, 5, { 0 }},
    { 46, 0, 10, 2, { 0 }},
    { 47, 0, 3, 8, { 0 }},
    { 48, 0, 3, 8, { 0 }},
    { 49, 0, 3, 3, { 0 }},
    { 50, 0, 3, 8, { 0 }},
    { 51, 0, 3, 8, { 0 }},
    { 52, 0, 3, 8, { 0 }},
    { 53, 0, 3, 8, { 0 }},
    { 54, 0, 3, 8, { 0 }},
    { 55, 0, 3, 7, { 0 }},
    { 56, 0, 3, 8, { 0 }},
    { 57, 0, 3, 8, { 0 }},
    { 58, 0, 6, 2, { 0 }},
    { 59, 0, 6, 3, { 0 }},
    { 60, 0, 3, 5, { 0 }},
    { 61, 0, 6, 6, { 0 }},
    { 62, 0, 3, 5, { 0 }},
    { 63, 0, 3, 7, { 0 }},
    { 64, 0, 3, 8, { 0 }},
    { 65, 0, 3, 8, { 0 }},
    { 66, 0, 3, 8, { 0 }},
    { 67, 0, 3, 8, { 0 }},
    { 68, 0, 3, 8, { 0 }},
    { 69, 0, 3, 7, { 0 }},
    { 70, 0, 3, 7, { 0 }},
    { 71, 0, 3, 8, { 0 }},
    { 72, 0, 3, 8, { 0 }},
    { 73, 0, 3, 6, { 0 }},
    { 74, 0, 3, 7, { 0 }},
    { 75, 0, 3, 8, { 0 }},
    { 76, 0, 3, 7, { 0 }},
    { 77, 0, 3, 9, { 0 }},
    { 78, 0, 3, 8, { 0 }},
    { 79, 0, 3, 8, { 0 }},
    { 80, 0, 3, 8, { 0 }},
    { 81, 0, 3, 8, { 0 }},
    { 82, 0, 3, 8, { 0 }},
    { 83, 0, 3, 8, { 0 }},
    { 84, 0, 3, 8, { 0 }},
    { 85, 0, 3, 8, { 0 }},
    { 86, 0, 3, 8, { 0 }},
    { 87, 0, 3, 10, { 0 }},
    { 88, 0, 3, 8, { 0 }},
    { 89, 0, 3, 8, { 0 }},
    { 90, 0, 3, 8, { 0 }},
    { 91, 0, 3, 4, { 0 }},
    { 92, 0, 3, 8, { 0 }},
    { 93, 0, 3, 4, { 0 }},
    { 94, 0, 3, 4, { 0 }},
    { 95, 0, 11, 7, { 0 }},
    { 96, 0, 3, 3, { 0 }},
    { 97, 0, 6, 7, { 0 }},
    { 98, 0, 3, 7, { 0 }},
    { 99, 0, 6, 7, { 0 }},
    { 100, 0, 3, 7, { 0 }},
    { 101, 0, 6, 7, { 0 }},
    { 102, 0, 3, 5, { 0 }},
    { 103, 0, 6, 7, { 0 }},
    { 104, 0, 3, 7, { 0 }},
    { 105, 0, 3, 2, { 0 }},
    { 106, -2, 3, 2, { 0 }},
    { 107, 0, 3, 7, { 0 }},
    { 108, 0, 3, 4, { 0 }},
    { 109, 0, 6, 10, { 0 }},
    { 110, 0, 6, 7, { 0 }},
    { 111, 0, 6, 7, { 0 }},
    { 112, 0, 6, 7, { 0 }},
    { 113, 0, 6, 7, { 0 }},
    { 114, 0, 6, 6, { 0 }},
    { 115, 0, 6, 7, { 0 }},
    { 116, 0, 3, 6, { 0 }},
    { 117, 0, 6, 7, { 0 }},
    { 118, 0, 6, 7, { 0 }},
    { 119, 0, 6, 10, { 0 }},
    { 120, 0, 6, 7, { 0 }},
    { 121, 0, 6, 7, { 0 }},
    { 122, 0, 6, 7, { 0 }},
    { 123, 0, 3, 5, { 0 }},
    { 124, 0, 3, 2, { 0 }},
    { 125, 0, 3, 5, { 0 }},
    { 126, 0, 6, 8, { 0 }},
    { 161, 0, 3, 2, { 0 }},
    { 162, 0, 4, 7, { 0 }},
    { 163, 0, 3, 7, { 0 }},
    { 8364, 0, 3, 9, { 0 }},
    { 165, 0, 3, 8, { 0 }},
    { 352, 0, 1, 8, { 0 }},
    { 167, 0, 4, 5, { 0 }},
    { 353, 0, 3, 7, { 0 }},
    { 169, 0, 3, 9, { 0 }},
    { 170, 0, 3, 7, { 0 }},
    { 171, 0, 6, 6, { 0 }},
    { 172, 0, 7, 6, { 0 }},
    { 174, 0, 3, 9, { 0 }},
    { 175, 0, 11, 3, { 0 }},
    { 176, 0, 3, 4, { 0 }},
    { 177, 0, 6, 8, { 0 }},
    { 178, 0, 3, 4, { 0 }},
    { 179, 0, 3, 4, { 0 }},
    { 381, 0, 1, 8, { 0 }},
    { 181, 0, 6, 7, { 0 }},
    { 182, 0, 4, 6, { 0 }},
    { 183, 0, 7, 2, { 0 }},
    { 382, 0, 3, 7, { 0 }},
    { 185, 0, 3, 4, { 0 }},
    { 186, 0, 3, 5, { 0 }},
    { 187, 0, 6, 6, { 0 }},
    { 338, 0, 3, 14, { 0 }},
    { 339, 0, 6, 13, { 0 }},
    { 376, 0, 2, 8, { 0 }},
    { 191, 0, 3, 7, { 0 }},
    { 192, 0, 1, 8, { 0 }},
    { 193, 0, 1, 8, { 0 }},
    { 194, 0, 1, 8, { 0 }},
    { 195, 0, 1, 8, { 0 }},
    { 196, 0, 2, 8, { 0 }},
    { 197, 0, -1, 8, { 0 }},
    { 198, 0, 3, 14, { 0 }},
    { 199, 0, 3, 8, { 0 }},
    { 200, 0, 1, 7, { 0 }},
    { 201, 0, 1, 7, { 0 }},
    { 202, 0, 1, 7, { 0 }},
    { 203, 0, 2, 7, { 0 }},
    { 204, 0, 1, 6, { 0 }},
    { 205, 0, 1, 6, { 0 }},
    { 206, 0, 1, 6, { 0 }},
    { 207, 0, 2, 6, { 0 }},
    { 208, 0, 3, 9, { 0 }},
    { 209, 0, 1, 8, { 0 }},
    { 210, 0, 1, 8, { 0 }},
    { 211, 0, 1, 8, { 0 }},
    { 212, 0, 1, 8, { 0 }},
    { 213, 0, 1, 8, { 0 }},
    { 214, 0, 2, 8, { 0 }},
    { 215, 1, 6, 6, { 0 }},
    { 216, 0, 3, 8, { 0 }},
    { 217, 0, 1, 8, { 0 }},
    { 218, 0, 1, 8, { 0 }},
    { 219, 0, 1, 8, { 0 }},
    { 220, 0, 2, 8, { 0 }},
    { 221, 0, 1, 8, { 0 }},
    { 222, 0, 3, 7, { 0 }},
    { 223, 0, 3, 7, { 0 }},
    { 224, 0, 3, 7, { 0 }},
    { 225, 0, 3, 7, { 0 }},
    { 226, 0, 3, 7, { 0 }},
    { 227, 0, 3, 7, { 0 }},
    { 228, 0, 3, 7, { 0 }},
    { 229, 0, 2, 7, { 0 }},
    { 230, 0, 6, 13, { 0 }},
    { 231, 0, 6, 7, { 0 }},
    { 232, 0, 3, 7, { 0 }},
    { 233, 0, 3, 7, { 0 }},
    { 234, 0, 3, 7, { 0 }},
    { 235, 0, 3, 7, { 0 }},
    { 236, -1, 3, 2, { 0 }},
    { 237, 0, 3, 2, { 0 }},
    { 238, -1, 3, 2, { 0 }},
    { 239, -1, 3, 2, { 0 }},
    { 240, 0, 3, 8, { 0 }},
    { 241, 0, 3, 7, { 0 }},
    { 242, 0, 3, 7, { 0 }},
    { 243, 0, 3, 7, { 0 }},
    { 244, 0, 3, 7, { 0 }},
    { 245, 0, 3, 7, { 0 }},
    { 246, 0, 3, 7, { 0 }},
    { 247, 0, 4, 6, { 0 }},
    { 248, 0, 6, 7, { 0 }},
    { 249, 0, 3, 7, { 0 }},
    { 250, 0, 3, 7, { 0 }},
    { 251, 0, 3, 7, { 0 }},
    { 252, 0, 3, 7, { 0 }},
    { 253, 0, 3, 7, { 0 }},
    { 254, 0, 3, 7, { 0 }},
    { 255, 0, 3, 7, { 0 }},
};

// Style loading function: Cyber
static void GuiLoadStyleCyber(void)
{
    // Load style properties provided
    // NOTE: Default properties are propagated
    for (int i = 0; i < CYBER_STYLE_PROPS_COUNT; i++)
    {
        GuiSetStyle(cyberStyleProps[i].controlId, cyberStyleProps[i].propertyId, cyberStyleProps[i].propertyValue);
    }

    // Custom font loading
    // NOTE: Compressed font image data (DEFLATE), it requires DecompressData() function
    int cyberFontDataSize = 0;
    unsigned char *data = DecompressData(cyberFontData, CYBER_STYLE_FONT_ATLAS_COMP_SIZE, &cyberFontDataSize);
    Image imFont = { data, 512, 256, 1, 2 };

    Font font = { 0 };
    font.baseSize = 14;
    font.glyphCount = 189;

    // Load texture from image
    font.texture = LoadTextureFromImage(imFont);
    UnloadImage(imFont);  // Uncompressed image data can be unloaded from memory

    // Copy char recs data from global fontRecs
    // NOTE: Required to avoid issues if trying to free font
    font.recs = (Rectangle *)RAYGUI_MALLOC(font.glyphCount*sizeof(Rectangle));
    memcpy(font.recs, cyberFontRecs, font.glyphCount*sizeof(Rectangle));

    // Copy font char info data from global fontChars
    // NOTE: Required to avoid issues if trying to free font
    font.glyphs = (GlyphInfo *)RAYGUI_MALLOC(font.glyphCount*sizeof(GlyphInfo));
    memcpy(font.glyphs, cyberFontGlyphs, font.glyphCount*sizeof(GlyphInfo));

    GuiSetFont(font);

    // Setup a white rectangle on the font to be used on shapes drawing,
    // it makes possible to draw shapes and text (full UI) in a single draw call
    Rectangle fontWhiteRec = { 510, 254, 1, 1 };
    SetShapesTexture(font.texture, fontWhiteRec);

    //-----------------------------------------------------------------

    // TODO: Custom user style setup: Set specific properties here (if required)
    // i.e. Controls specific BORDER_WIDTH, TEXT_PADDING, TEXT_ALIGNMENT
}
