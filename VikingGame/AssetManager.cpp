#include "stdafx.h"
#include "AssetManager.h"

sf::Texture* AssetManager::GetTexture(std::string filename)
{
    if (mTextureStore.find(filename) == mTextureStore.end())
    {
        sf::Texture texture;
        texture.loadFromFile(filename);
        mTextureStore[filename] = texture;
    }
    return &mTextureStore[filename];
}

sf::Font* AssetManager::GetFont(std::string filename)
{
    if (mFontStore.find(filename) == mFontStore.end())
    {
        sf::Font font;
        font.loadFromFile(filename);
        mFontStore[filename] = font;
    }
    return &mFontStore[filename];
}


AssetManager* AssetManager::mrefInstance = nullptr;