#include "part.hpp"

std::string Part::getTextureFilename(uint variantIndex)
{
    return partId + "_" + std::to_string(variantIndex + 1) + ".png";
}

PartManager::PartManager(std::vector<Part> pParts) : parts{}
{
    for (auto &&p : pParts)
    {
        Texture2D texture = LoadTexture(p.getTextureFilename(1).c_str());
        if (texture.id == 0)
            throw std::runtime_error("Failed to load texture: " + p.getTextureFilename(1));
        this->parts[p.partId].push_back(texture);
    }
}

PartManager::~PartManager()
{
    for (const auto &[_, variants] : this->parts)
    {
        for (const auto &v : variants)
        {
            UnloadTexture(v);
        }
    }
}

Texture2D PartManager::getPartTexture(std::string partId, uint partVariant)
{
    try
    {
        const auto &variants = this->parts.at(partId);

        if (variants.empty())
        {
            throw std::runtime_error("No variants for part: " + partId);
        }

        return variants[partVariant % variants.size()];
    }
    catch (std::out_of_range ex)
    {
        throw std::runtime_error("Part: " + partId + " doesn't exist.");
    }
}
