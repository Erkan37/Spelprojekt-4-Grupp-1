#pragma once
struct TileSetLayerProperties
{
    TileSetLayerProperties();

    std::string mySpritePath[3];

    int myQuadLengthX;
    int myQuadLengthY;

    float mySpriteSizeX;
    float mySpriteSizeY;

    float myRectQuadX;
    float myRectQuadY;

    int myImageSizeX;
    int myImageSizeY;
};

