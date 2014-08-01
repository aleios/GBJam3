#pragma once
#ifndef MODSTREAM_HPP
#define MODSTREAM_HPP

#include <string>
#include <vector>

#include <SFML/Audio/SoundStream.hpp>

#ifndef _WIN32
#include <libmodplug/modplug.h>
#else
#include <modplug.h>
#endif

class ModStream
    : public sf::SoundStream
{
public:
    ModStream();
    ~ModStream();

    bool load(const std::string& filename);
    void unload();
private:
    virtual bool onGetData(Chunk& data);
    virtual void onSeek(sf::Time timeOffset);

    std::vector<sf::Int16> m_samples;
    std::size_t m_currentSample;

    ModPlugFile* m_file{ nullptr };
    static const unsigned int CHUNK_SIZE{ 4096 };
};

#endif