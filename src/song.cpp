#include "Song.h"
#include <sstream>
#include <iomanip>

Song::Song(const std::string& title,
           const std::string& artist,
           const std::string& album,
           const std::string& genre,
           int year,
           int durationSec,
           const std::string& filePath)
    : title_(title),
      artist_(artist),
      album_(album),
      genre_(genre),
      year_(year),
      durationSec_(durationSec),
      filePath_(filePath) {}

const std::string& Song::getTitle() const { return title_; }
const std::string& Song::getArtist() const { return artist_; }
const std::string& Song::getAlbum() const { return album_; }
const std::string& Song::getGenre() const { return genre_; }
int Song::getYear() const { return year_; }
int Song::getDurationSec() const { return durationSec_; }
const std::string& Song::getFilePath() const { return filePath_; }

std::string Song::getFormattedDuration() const {
    int min = durationSec_ / 60;
    int sec = durationSec_ % 60;

    std::ostringstream out;
    out << std::setw(2) << std::setfill('0') << min
        << ":"
        << std::setw(2) << std::setfill('0') << sec;
    return out.str();
}

bool Song::isValid() const {
    return !title_.empty()
        && !artist_.empty()
        && durationSec_ > 0
        && !filePath_.empty();
}