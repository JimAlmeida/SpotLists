#pragma once
#include <cpr/cpr.h>
#include "CURLDispatcher.h"
#include "CURLRequest.h"
#include "IHTTPRequest.h"
#include "SpotifyAPI.h"
#include "SpotifyFilter.h"
#include "SpotifyFlow.h"
#include "PlaylistElement.h"
#include "PlaylistElementGUI.h"
#include "Playlist.h"
#include "SoundLoader.h"
#include "MusicPlayer.h"
#include "SearchBar.h"
#include "PlaylistData.h"
#include "SearchPage.h"
#include "ContentPage.h"

namespace BETests {
    PlaylistElement FlowTest1(){
        /// <summary>
        /// Use case: User submits a query.
        /// Input: Artist name (string)
        /// Output (passing criteria): struct with the Artist Name, ID and its image URLs.
        /// </summary>
        SpotifyFlow info_flow;
        auto artists = info_flow.searchByArtist("Muse");
        return artists[2];
    }
    PlaylistElement FlowTest2() {
        /// <summary>
        /// Use case: User submits a query.
        /// Input: Track name (string)
        /// Output (passing criteria): Track Name, Track ID, Sample URL, Album Name, Album ID, Album Image URLs, Artist Name, Artist ID
        /// </summary>
        SpotifyFlow info_flow;
        auto tracks = info_flow.searchByTrack("The Blessing");
        return tracks[2];
    }
    PlaylistElement FlowTest3() {
        /// <summary>
        /// Use case: When the user selects an artist from the search results and needs to see its albums.
        /// Input: PlaylistElement object that came as a result from the search artist query.
        /// Output (passing criteria): Album Name, Album ID, Album Image URLs, Artist Name, Artist ID, Artist Image URLs, Album Artists, Album Artist IDs.
        /// </summary>
        SpotifyFlow info_flow;
        PlaylistElement artist = FlowTest1();
        auto albums = info_flow.searchAlbums(artist);
        return albums[0];
    }
    PlaylistElement FlowTest4() {
        /// <summary>
        /// Use case: When the user selects an album from the search results and needs to see its songs.
        /// Input: PlaylistElement object that came as a result from the search album query.
        /// Output (passing criteria): Track Name, Track ID, Sample URL, Track Artists, Track Artists ID, Album Name, Album ID, Album Image URLs, Artist Name, Artist ID, Artist Image URLs, Album Artists, Album Artist IDs.
        /// </summary>
        SpotifyFlow info_flow;
        PlaylistElement album = FlowTest3();
        auto tracks = info_flow.searchAlbumsTracks(album);
        return tracks[13];
    }
    PlaylistElement FlowTest5() {
        /// <summary>
        /// Use case: User submits an empty query.
        /// Input: Artist name (string)
        /// Output (passing criteria): Empty PlaylistElement with the exception of the Artist field that'll show Not Found.
        /// </summary>
        SpotifyFlow info_flow;
        auto artists = info_flow.searchByArtist("");
        if (artists.size()>0){ return artists[0]; }
        else {
            PlaylistElement pl;
            pl.artist = "NOT FOUND";
            return pl;
        }
        
    }
    PlaylistElement FlowTest6() {
        /// <summary>
        /// Use case: User submits an empty query.
        /// Input: Track name (string)
        /// Output (passing criteria): Empty PlaylistElement with the exception of the Track field that'll show Not Found.
        /// </summary>
        SpotifyFlow info_flow;
        auto tracks = info_flow.searchByTrack("");
        if (tracks.size() > 0) { return tracks[1]; }
        else {
            PlaylistElement pl;
            pl.track = "NOT FOUND";
            return pl;
        }
    }
    PlaylistElement FlowTest7() {
        /// <summary>
        /// Use case: User submits a garbage query.
        /// Input: Artist name (string)
        /// Output (passing criteria): Empty PlaylistElement with the exception of the Artist field that'll show Not Found.
        /// </summary>
        SpotifyFlow info_flow;
        auto artists = info_flow.searchByArtist("sdoahjdadsand jasncsjac");
        if (artists.size() > 0) { return artists[0]; }
        else {
            PlaylistElement pl;
            pl.artist = "NOT FOUND";
            return pl;
        }
    }
    PlaylistElement FlowTest8() {
        /// <summary>
        /// Use case: User submits a garbage query.
        /// Input: Track name (string)
        /// Output (passing criteria): Empty PlaylistElement with the exception of the Track field that'll show Not Found.
        /// </summary>
        SpotifyFlow info_flow;
        auto tracks = info_flow.searchByTrack("dhajdauhduhwdhwnddmklsd");
        if (tracks.size() > 0) { return tracks[1]; }
        else {
            PlaylistElement pl;
            pl.track = "NOT FOUND";
            return pl;
        }
    }
    PlaylistData FlowTest9() {
        /// <summary>
        /// Use case: User submits a query.
        /// Input: Track name (string)
        /// Output (passing criteria): Track Name, Track ID, Sample URL, Album Name, Album ID, Album Image URLs, Artist Name, Artist ID
        /// </summary>
        SpotifyFlow info_flow;
        auto artists = info_flow.searchByArtist("Muse");
        return PlaylistData(artists);
    }
    PlaylistData FlowTest10() {
        /// <summary>
        /// Use case: User submits a query.
        /// Input: Track name (string)
        /// Output (passing criteria): Track Name, Track ID, Sample URL, Album Name, Album ID, Album Image URLs, Artist Name, Artist ID
        /// </summary>
        SpotifyFlow info_flow;
        auto tracks = info_flow.searchByTrack("The Blessing");
        return PlaylistData(tracks);
    }
    void SaveDataTest() {
        //I'm checking equivalence through the debugger. In an automated test, I'd overload the == operator in the Playlist and PlaylistElement classes to handle the equality
        //of the Playlist objects, because of time constraints, I won't engage in this approach.
        SpotifyFlow info_flow;
        //Playlist artists(info_flow.searchByArtist("Muse"));
        //Playlist::savePlaylist("searchMuse.playlist", artists);
        //Playlist artists_loaded = Playlist::readPlaylist("searchMuse.playlist");
    }
    void SaveDataTest2() {
        //I'm checking equivalence through the debugger. In an automated test, I'd overload the == operator in the Playlist and PlaylistElement classes to handle the equality
        //of the Playlist objects, because of time constraints, I won't engage in this approach.
        SpotifyFlow info_flow;
        //Playlist tracks(info_flow.searchByTrack("The Blessing"));
        //Playlist::savePlaylist("searchTheBlessing.txt", tracks);
        //Playlist tracks_loaded = Playlist::readPlaylist("searchTheBlessing.txt");
    }
}

namespace GUITests {
    PlaylistElementGUI* PlayElement1() {
        PlaylistElement artist = BETests::FlowTest1();
        PlaylistElementGUI* widget = new PlaylistElementGUI(artist);
        return widget;
    }
    PlaylistElementGUI* PlayElement2() {
        PlaylistElement track = BETests::FlowTest2();
        PlaylistElementGUI* widget = new PlaylistElementGUI(track);
        return widget;
    }
    QMediaPlayer* AudioPlayer() {
        return SoundLoader::loadSongFromURL("https://p.scdn.co/mp3-preview/beda634f6584de6b3a9d4de9d0379a3e737904ed?cid=62a214e649dc461cb84f70416171ad54");
    }
    MusicPlayer* AudioWidget() {
        PlaylistElement track = BETests::FlowTest2();
        MusicPlayer* player = new MusicPlayer(track);
        return player;
    }
    TopBar* SearchWidget() {
        return new TopBar();
    }
    Playlist* PlaylistArray() {
        Playlist* my_playlist = new Playlist();
        my_playlist->loadData(BETests::FlowTest10());
        my_playlist->setMinimumSize(my_playlist->sizeHint());
        my_playlist->buildGridLayout(4);
        return my_playlist;
    }
    Playlist* PlaylistArray2() {
        Playlist* my_playlist = new Playlist();
        my_playlist->loadData(BETests::FlowTest9());
        my_playlist->setMinimumSize(my_playlist->sizeHint());
        my_playlist->buildListLayout();
        return my_playlist;
    }
    SearchPage* searchPage() {
        SearchPage* page = new SearchPage();
        page->loadData(BETests::FlowTest9(), BETests::FlowTest10());
        page->setMinimumSize(page->sizeHint());
        return page;
    }
    SearchPage* searchPage2() {
        SearchPage* page = new SearchPage(BETests::FlowTest9(), BETests::FlowTest10());
        page->setMinimumSize(page->sizeHint());
        return page;
    }
    ContentPage* trackPage() {
        ContentPage* page = new ContentPage(ContentType::TRACK);
        page->loadData(ContentType::TRACK, BETests::FlowTest10());
        page->setMinimumSize(page->sizeHint());
        return page;
    }
    ContentPage* artistPage() {
        ContentPage* page = new ContentPage(ContentType::ALBUM);
        page->loadData(ContentType::ALBUM, BETests::FlowTest9());
        page->setMinimumSize(page->sizeHint());
        return page;
    }
}
