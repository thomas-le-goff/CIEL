#pragma once

#include "raylib.h"
#include <string>
#include <map>
#include <vector>
#include <array>
#include <stdexcept>

struct Part
{
    std::string partId;
    uint maxVariants;

    std::string getTextureFilename(uint variantIndex);
};

class PartManager
{
private:
    std::map<std::string, std::vector<Texture2D>> parts;

public:
    PartManager(std::vector<Part> pParts);
    ~PartManager();
    Texture2D getPartTexture(std::string partId, uint partVariant);
};
