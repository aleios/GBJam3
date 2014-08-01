#include "modstream.hpp"
#include <fstream>
#include <iostream>

ModStream::ModStream()
{
    m_samples.resize(CHUNK_SIZE, 0);
}

ModStream::~ModStream()
{
    unload();
}

bool ModStream::load(const std::string& filename)
{
    ModPlug_Settings settings;
    ModPlug_GetSettings(&settings);
    settings.mFlags |= MODPLUG_ENABLE_OVERSAMPLING;
    settings.mChannels = 2;
    settings.mBits = 16;
    settings.mFrequency = 48000;
    settings.mResamplingMode = MODPLUG_RESAMPLE_FIR;
    settings.mLoopCount = 1;
    ModPlug_SetSettings(&settings);

    std::vector<char> data;
    std::ifstream modFile(filename.c_str(), std::ifstream::in | std::ifstream::binary);

    // Find file size.
    modFile.seekg(0, std::ifstream::end);
    std::streamoff bufferSize = modFile.tellg();
    modFile.seekg(0, std::ios::beg);
    //std::cout << "Buffer Size: " << bufferSize << "\n";
    data.resize(bufferSize);
    modFile.read(&data[0], bufferSize);

    // Load mod into modplug.
    m_file = ModPlug_Load(&data[0], bufferSize);

    // Initialize the stream.
    initialize(2, 48000);

    return true;
}

void ModStream::unload()
{
    if (getStatus() != sf::SoundStream::Stopped)
        stop();

    if (m_file != nullptr)
        ModPlug_Unload(m_file);

    m_samples.clear();
    m_samples.resize(CHUNK_SIZE, 0);
}

bool ModStream::onGetData(Chunk& data)
{
    if (m_samples.size() > 0 && m_file != nullptr)
    {
        // Read new chunks.
        int read = ModPlug_Read(m_file, reinterpret_cast<void*>(&m_samples[0]), CHUNK_SIZE);

        // No more data. File ended.
        if (read == 0)
            return false;

        data.sampleCount = static_cast<size_t>(read / 2);
        data.samples = &m_samples[0];
        return true;
    }
    return false;
}

void ModStream::onSeek(sf::Time timeOffset)
{
    ModPlug_Seek(m_file, timeOffset.asMilliseconds());
}
