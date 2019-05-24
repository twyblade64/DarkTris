#include "ResourceLoader.hpp"

ResourceLoader::ResourceLoader() {}

sf::Texture* ResourceLoader::LoadTexture(int id, const std::string& filename) {
    if (CheckTexture(id)) return GetTexture(id);

    std::unique_ptr<sf::Texture> ptr = std::unique_ptr<sf::Texture>(new sf::Texture());
    if (ptr->loadFromFile(filename))
        mTextureMap[id] = std::move(ptr);
    else
        mTextureMap[id] = nullptr;

    return mTextureMap[id].get();
}

sf::Texture* ResourceLoader::GetTexture(int id) {
    return mTextureMap[id].get();
}

bool ResourceLoader::CheckTexture(int id) {
    return mTextureMap[id] != nullptr;
}

void ResourceLoader::UnloadTexture(int id) {
    mTextureMap[id] = nullptr;
}


sf::Font* ResourceLoader::LoadFont(int id, const std::string& filename) {
    if (CheckFont(id)) return GetFont(id);

    std::unique_ptr<sf::Font> ptr = std::unique_ptr<sf::Font>(new sf::Font());
    if (ptr->loadFromFile(filename))
        mFontMap[id] = std::move(ptr);
    else
        mFontMap[id] = nullptr;

    return mFontMap[id].get();
}

sf::Font* ResourceLoader::GetFont(int id) {
    return mFontMap[id].get();
}

bool ResourceLoader::CheckFont(int id) {
    return mFontMap[id] != nullptr;
}

void ResourceLoader::UnloadFont(int id) {
    mFontMap[id] = nullptr;
}


sf::SoundBuffer* ResourceLoader::LoadSound(int id, const std::string& filename) {
    std::unique_ptr<sf::SoundBuffer> ptr = std::unique_ptr<sf::SoundBuffer>(new sf::SoundBuffer());
    if (ptr->loadFromFile(filename))
        mSoundMap[id] = std::move(ptr);
    else
        mSoundMap[id] = nullptr;
    return mSoundMap[id].get();
}

sf::SoundBuffer* ResourceLoader::GetSound(int id) {
    return mSoundMap[id].get();
}

bool ResourceLoader::CheckSound(int id) {
    return mSoundMap[id] != nullptr;
}

void ResourceLoader::UnloadSound(int id) {
    mSoundMap[id] = nullptr;
}

void ResourceLoader::UnloadAll() {
    mTextureMap.clear();
    mFontMap.clear();
    mSoundMap.clear();
}
