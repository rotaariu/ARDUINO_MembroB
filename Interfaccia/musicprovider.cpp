#include "musicprovider.h"
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include <QUrlQuery>

MusicProvider::MusicProvider(QObject* parent) : QObject(parent) {
    m_pollTimer = new QTimer(this);
    m_pollTimer->setInterval(1000); // ogni secondo
    connect(m_pollTimer, &QTimer::timeout, this, &MusicProvider::pollSpotify);
    m_pollTimer->start();

    connect(&m_nam, &QNetworkAccessManager::finished,
            this,   &MusicProvider::onSpotifyReply);
}

void MusicProvider::setSpotifyToken(const QString& token) {
    m_spotifyToken = token;
}

void MusicProvider::pollSpotify() {
    if (m_spotifyToken.isEmpty()) return;

    QNetworkRequest req(QUrl("https://api.spotify.com/v1/me/player/currently-playing"));
    req.setRawHeader("Authorization", ("Bearer " + m_spotifyToken).toUtf8());
    m_nam.get(req);
}

void MusicProvider::onSpotifyReply(QNetworkReply* reply) {
    reply->deleteLater();

    if (reply->error() != QNetworkReply::NoError) return;
    if (reply->url().host() != "api.spotify.com") return; // ignora risposte lyrics

    QByteArray data = reply->readAll();
    if (data.isEmpty()) return;

    parseSpotifyResponse(data);
}

void MusicProvider::parseSpotifyResponse(const QByteArray& data) {
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject root  = doc.object();

    if (!root["is_playing"].toBool()) return;

    QJsonObject item   = root["item"].toObject();
    QString trackId    = item["id"].toString();
    m_progressMs       = root["progress_ms"].toInt();
    m_durationMs       = item["duration_ms"].toInt();

    emit progressChanged();

    // Se la traccia è cambiata, aggiorna tutto
    if (trackId != m_lastTrackId) {
        m_lastTrackId = trackId;
        m_title       = item["name"].toString();
        m_artist      = item["artists"].toArray()[0].toObject()["name"].toString();
        m_album       = item["album"].toObject()["name"].toString();

        QJsonArray images = item["album"].toObject()["images"].toArray();
        if (!images.isEmpty())
            m_coverUrl = images[0].toObject()["url"].toString();

        emit trackChanged();
        fetchLyrics(); // scarica le lyrics per la nuova traccia
    }

    updateCurrentLyric();
}

void MusicProvider::fetchLyrics() {
    // LRCLIB - gratuita, no API key
    QUrl url("https://lrclib.net/api/get");
    QUrlQuery query;
    query.addQueryItem("artist_name", m_artist);
    query.addQueryItem("track_name",  m_title);
    url.setQuery(query);

    QNetworkRequest req(url);
    req.setRawHeader("User-Agent", "Q9Visualizer/1.0 (contact@example.com)");
    req.setRawHeader("Accept", "application/json");
    req.setAttribute(QNetworkRequest::RedirectPolicyAttribute,
                     QNetworkRequest::NoLessSafeRedirectPolicy);

    QNetworkAccessManager* lyricsNam = new QNetworkAccessManager(this);
    connect(lyricsNam, &QNetworkAccessManager::finished,
            this,      &MusicProvider::onLyricsReply);
    lyricsNam->get(req);
}

void MusicProvider::onLyricsReply(QNetworkReply* reply) {
    reply->deleteLater();
    sender()->deleteLater(); // pulisce il QNetworkAccessManager temporaneo

    if (reply->error() != QNetworkReply::NoError) return;

    QJsonDocument doc  = QJsonDocument::fromJson(reply->readAll());
    QString syncedLyric = doc.object()["syncedLyrics"].toString();

    if (!syncedLyric.isEmpty())
        parseLrcLyrics(syncedLyric);
}

void MusicProvider::parseLrcLyrics(const QString& lrc) {
    // Formato LRC: [mm:ss.xx] testo
    m_lyricsSync.clear();
    m_lyricsText.clear();

    for (const QString& line : lrc.split('\n')) {
        QRegularExpression re(R"(\[(\d+):(\d+\.\d+)\]\s*(.*))");
        auto match = re.match(line);
        if (!match.hasMatch()) continue;

        int    minutes = match.captured(1).toInt();
        double seconds = match.captured(2).toDouble();
        QString text   = match.captured(3);
        int    timeMs  = static_cast<int>((minutes * 60 + seconds) * 1000);

        m_lyricsSync.append({timeMs, text});
        m_lyricsText.append(text);
    }

    emit lyricsChanged();
}

void MusicProvider::updateCurrentLyric() {
    if (m_lyricsSync.isEmpty()) return;

    int idx = 0;
    for (int i = m_lyricsSync.size() - 1; i >= 0; --i) {
        if (m_progressMs >= m_lyricsSync[i].first) {
            idx = i;
            break;
        }
    }

    if (idx != m_currentLyricIndex) {
        m_currentLyricIndex = idx;
        emit progressChanged();
    }
}