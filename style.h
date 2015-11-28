#ifndef STYLE_H
#define STYLE_H

#include "global.h"
#include "icdCreator.h"

class StyleEntry
{
    bool inited;
    QFont *_font;
    QBrush *_brush;
    QString _id;
    QColor _color;
    bool _useColor;
    QString _fontFamily;
    int _fontSize;
    bool _bold;
    bool _italic;
    int _originalFontSize;
public:

    const QString &id();
    QColor color();
    const QBrush &brush();
    bool isColor();
    QFont *font();

    StyleEntry(const QString &id);
    ~StyleEntry();

    void setBold(const bool isBold);
    void setItalic(const bool isItalic);
    void setFontSize(const bool newSize);
    void setFontFamily(const QString &newFamily);
    void setColor(const QString &newColor);
    void setZoom(const int zoom);

    void deactivate();
    bool activate(const QFont &baseFont, const int zoom);
};

class TokenEntry
{
    QString _keyword;
    StyleEntry *_style;

public:
    const QString &keyword();
    StyleEntry *style();
    void setStyle(StyleEntry *style);

    TokenEntry(const QString &newKeyword, StyleEntry *entry);
    ~TokenEntry();
};

class IdEntry
{
    QString _value;
    bool _isAlpha;

public:
    IdEntry(const QString &newValue, const bool newIsAlpha);
    ~IdEntry();

    bool isAlpha() const;
    const QString &value() const;
};

class LIBQXMLEDITSHARED_EXPORT VStyle
{
public:
    static bool globalInitFlag;
private:
    bool        _inited;
    QString     _name;
    QString     _description;
    QMap<QString, TokenEntry*>  _keywords;
    QMap<QString, StyleEntry*>  _styles;
    QMap<QString, IdEntry*>     _elementIds;

    static QFont _defaultFont;
    static int   _defaultFontSize;
    static QBrush _defaultBrush;
public:
    const QString &name() const;
    bool addId(const QString &newId, const bool isAlpha);
    bool addToken(TokenEntry *tk);
    bool addEntry(StyleEntry *entry);
    StyleEntry* getStyleOfKeyword(const QString &kw);
    StyleEntry* getStyleEntry(const QString &key);
    IdEntry* getIdEntry(const QString &key);

    VStyle(const QString &newName, const QString &newDescription);
    ~VStyle();

    bool activate(const QFont &baseFont, const int zoom);
    void deactivate();

    static void globalActivate(const QFont &baseFont, const QBrush &baseBrush);
    static void changeDefaultBrush(const QBrush &baseBrush);
    static const QFont &defaultFont();
    static const QBrush &defaultBrush();
    static int getZoomFontSize(const int size, const int zoom);
    void setZoom(const int zoom);
};

#endif // STYLE_H
