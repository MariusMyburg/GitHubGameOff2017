#pragma once
#include "SFML\Graphics.hpp"
#include <map>

class AssetManager
{
public:    
    ~AssetManager() { };
        
    sf::Texture* GetTexture(std::string filename);
    sf::Font* GetFont(std::string filename);

    static AssetManager* Instance()
    {
        if (mrefInstance == nullptr)
        {
            mrefInstance = new AssetManager();
        }
        return mrefInstance;
    }

private:
    AssetManager() 
    { 
        mrefInstance = this;
    };

    static AssetManager* mrefInstance;
    std::map<std::string, sf::Texture> mTextureStore;
    std::map<std::string, sf::Font> mFontStore;
};
