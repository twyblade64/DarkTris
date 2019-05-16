#ifndef HEX_RESOURCE_LOADER_H_
#define HEX_RESOURCE_LOADER_H_

#include <map>
#include <memory>
#include <string>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class ResourceLoader {
    public:
        ResourceLoader();
    public:
        sf::Texture* LoadTexture(int id, const std::string& filename);
        sf::Texture* GetTexture(int id);
        bool CheckTexture(int id);
        void UnloadTexture(int id);

        sf::Font* LoadFont(int id, const std::string& filename);
        sf::Font* GetFont(int id);
        bool CheckFont(int id);
        void UnloadFont(int id);

        sf::SoundBuffer* LoadSound(int id, const std::string& filename);
        sf::SoundBuffer* GetSound(int id);
        bool CheckSound(int id);
        void UnloadSound(int id);

        void UnloadAll();
    private:
        std::map<int, std::unique_ptr<sf::Texture>> mTextureMap;
        std::map<int, std::unique_ptr<sf::Font>> mFontMap;
        std::map<int, std::unique_ptr<sf::SoundBuffer>> mSoundMap;
};

#endif // HEX_RESOURCE_LOADER_H_
