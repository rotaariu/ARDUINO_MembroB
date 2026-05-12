#pragma once
#include <QObject>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>
#include <QtQml/qqmlregistration.h>

class MusicProvider : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString title     READ title     NOTIFY trackChanged)
    Q_PROPERTY(QString artist    READ artist    NOTIFY trackChanged)
    Q_PROPERTY(QString album     READ album     NOTIFY trackChanged)
    Q_PROPERTY(QString coverUrl  READ coverUrl  NOTIFY trackChanged)
    Q_PROPERTY(int     progressMs READ progressMs NOTIFY progressChanged)
    Q_PROPERTY(int     durationMs READ durationMs NOTIFY trackChanged)
    Q_PROPERTY(QStringList lyrics READ lyrics   NOTIFY lyricsChanged)
    Q_PROPERTY(int     currentLyricIndex READ currentLyricIndex NOTIFY progressChanged)

public:
    explicit MusicProvider(QObject* parent = nullptr);

    QString     title()            const { return m_title; }
    QString     artist()           const { return m_artist; }
    QString     album()            const { return m_album; }
    QString     coverUrl()         const { return m_coverUrl; }
    int         progressMs()       const { return m_progressMs; }
    int         durationMs()       const { return m_durationMs; }
    QStringList lyrics()           const { return m_lyricsText; }
    int         currentLyricIndex() const { return m_currentLyricIndex; }

    Q_INVOKABLE void setSpotifyToken(const QString& token);

signals:
    void trackChanged();
    void progressChanged();
    void lyricsChanged();

private slots:
    void pollSpotify();
    void onSpotifyReply(QNetworkReply* reply);
    void fetchLyrics();
    void onLyricsReply(QNetworkReply* reply);

private:
    void updateCurrentLyric();
    void parseSpotifyResponse(const QByteArray& data);
    void parseLrcLyrics(const QString& lrc);

    QTimer*               m_pollTimer;
    QNetworkAccessManager m_nam;

    QString     m_title;
    QString     m_artist;
    QString     m_album;
    QString     m_coverUrl;
    int         m_progressMs  = 0;
    int         m_durationMs  = 0;
    QString     m_spotifyToken;
    QString     m_lastTrackId;

    // Lyrics: lista di {time_ms, text}
    QList<QPair<int, QString>> m_lyricsSync;
    QStringList                m_lyricsText;
    int                        m_currentLyricIndex = 0;
};