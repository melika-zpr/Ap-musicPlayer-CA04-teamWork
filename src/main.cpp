#include <iostream>
#include <vector>

#include "MusicLibrary.h"
#include "CsvLoader.h"

using namespace std;

int main()
{
    MusicLibrary library;
    CsvLoader loader;

    vector<string> errors;

    bool success = loader.load("Data/library.csv", library, errors);

    if (!success)
    {
        cout << "Failed to load CSV." << endl;
    }

    cout << "Songs Loaded: " << library.size() << endl << endl;

    for (Song* song : library.getSongs())
    {
        cout << "-----------------------------" << endl;
        cout << "Title    : " << song->getTitle() << endl;
        cout << "Artist   : " << song->getArtist() << endl;
        cout << "Album    : " << song->getAlbum() << endl;
        cout << "Genre    : " << song->getGenre() << endl;
        cout << "Year     : " << song->getYear() << endl;
        cout << "Duration : " << song->getFormattedDuration() << endl;
        cout << "Path     : " << song->getFilePath() << endl;
    }

    if (!errors.empty())
    {
        cout << endl;
        cout << "========== Errors ==========" << endl;

        for (const string& error : errors)
        {
            cout << error << endl;
        }
    }

    return 0;
}