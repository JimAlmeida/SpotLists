#include "SoundLoader.h"

QMediaPlayer* SoundLoader::loadSongFromURL(std::string url)
{
    QMediaPlayer* player = new QMediaPlayer();
    if (!url.empty()) {
        player->setMedia(QUrl(url.c_str()));  
    }
    return player;
}