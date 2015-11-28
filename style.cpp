#include "style.h"
#include <QDir>


StyleEntry::StyleEntry(const QString &newId)
{
    inited = false;
    _font = NULL ;
    _brush = NULL;
    _id = newId ;
    _useColor = false ;
    _bold = false;
    _italic = false;
    _fontSize = 0;
    _fontFamily = "";
    _originalFontSize = 0;
}

StyleEntry::~StyleEntry()
{
    deactivate();
}

const QString &StyleEntry::id()
{
    return _id ;
}

QColor StyleEntry::color()
{
    return _color;
}

QFont *StyleEntry::font()
{
    return _font ;
}

const QBrush &StyleEntry::brush()
{
    return *_brush;
}

void StyleEntry::setBold(const bool isBold)
{
    _bold = isBold ;
}

void StyleEntry::setItalic(const bool isItalic)
{
    _italic = isItalic ;
}

void StyleEntry::setFontSize(const bool newSize)
{
    _fontSize = newSize ;
}

void StyleEntry::setFontFamily(const QString & newFamily)
{
    _fontFamily = newFamily;
}

void StyleEntry::setColor(const QString &newColor)
{
    if(!newColor.isEmpty()) {
        bool ok ;
        uint val = newColor.toUInt(&ok, 16) ;
        if(ok) {
            _color = QColor((val >> 16) & 0x00FF, (val >> 8) & 0x00FF, val & 0x00FF);
            _useColor = true;
        }
    }
}

void StyleEntry::setZoom(const int zoom)
{
    if(NULL != _font) {
        _font->setPointSize(VStyle::getZoomFontSize(_originalFontSize, zoom));
    }
}

bool StyleEntry::isColor()
{
    return _useColor ;
}

bool StyleEntry::activate(const QFont &baseFont, const int zoom)
{
    bool isOk = true ;
    if(!inited) {
        if(!_fontFamily.isEmpty() && (_fontSize != 0)) {
            _font = new QFont(_fontFamily, _fontSize);
            if(NULL == _font) {
                isOk = false;
            }
        } else if(_bold || _italic) {
            _font = new QFont(baseFont);
            if(NULL == _font) {
                isOk = false;
            }
        }
        if(NULL != _font) {
            if(_italic) {
                _font->setItalic(true);
            }
            if(_bold) {
                _font->setBold(true);
            }
        }
        //---- brush
        if(_useColor) {
            _brush = new QBrush(_color);
            if(NULL == _brush)  {
                isOk = false;
            }
        }
        inited = true ;
        if(NULL != _font) {
            _originalFontSize = _font->pointSize();
        }
    }
    setZoom(zoom);
    return isOk ;
}

void StyleEntry::deactivate()
{
    if(inited) {
        if(_font != NULL) {
            delete _font;
            _font = NULL;
        }
        if(NULL != _brush) {
            delete _brush ;
            _brush = NULL ;
        }
        inited = false;
    }
}

//----------------------------------------------------------------

TokenEntry::TokenEntry(const QString &newKeyword, StyleEntry *newStyle)
{
    _keyword = newKeyword ;
    _style = newStyle ;
}

TokenEntry::~TokenEntry()
{
}

const QString &TokenEntry::keyword()
{
    return _keyword ;
}

StyleEntry *TokenEntry::style()
{
    return _style;
}

void TokenEntry::setStyle(StyleEntry * newStyle)
{
    _style = newStyle;
}

//----------------------------------------------------------------

IdEntry::IdEntry(const QString &value, const bool isAlpha)
{
    _value = value ;
    _isAlpha = isAlpha;
}

IdEntry::~IdEntry()
{
}

bool IdEntry::isAlpha() const
{
    return _isAlpha;
}

const QString &IdEntry::value() const
{
    return _value;
}

//----------------------------------------------------------------

QFont VStyle::_defaultFont("Sans Serif");
QBrush VStyle::_defaultBrush;
bool VStyle::globalInitFlag = false;
int  VStyle::_defaultFontSize = 0;

VStyle::VStyle(const QString &newName, const QString &newDescription)
{
    _inited = false;
    _name = newName;
    _description = newDescription ;
}


VStyle::~VStyle()
{
    foreach(StyleEntry * entry, _styles.values()) {
        delete entry;
    }
    foreach(TokenEntry * entry, _keywords.values()) {
        delete entry;
    }
    foreach(IdEntry * entry, _elementIds.values()) {
        delete entry;
    }
}

bool VStyle::addId(const QString &newId, const bool isAlpha)
{
    IdEntry * entry = new IdEntry(newId, isAlpha) ;
    if(NULL != entry) {
        if(_elementIds.value(newId, NULL) != NULL) {
            return false;
        }
        _elementIds.insert(newId, entry) ;
        return true;
    }
    return false ;
}

const QString &VStyle::name() const
{
    return _name;
}

bool VStyle::addToken(TokenEntry *tk)
{
    if(_keywords.value(tk->keyword(), NULL) != NULL) {
        return false;
    }
    _keywords.insert(tk->keyword(), tk);
    return true;
}

bool VStyle::addEntry(StyleEntry* entry)
{
    if(_styles.value(entry->id(), NULL) != NULL) {
        return false;
    }
    _styles.insert(entry->id(), entry);
    return true;
}

StyleEntry* VStyle::getStyleOfKeyword(const QString &kw)
{
    TokenEntry *tk = _keywords.value(kw, NULL);
    if(NULL != tk) {
        return tk->style();
    }
    return NULL ;
}

StyleEntry* VStyle::getStyleEntry(const QString &key)
{
    return _styles.value(key, NULL);
}

IdEntry* VStyle::getIdEntry(const QString &key)
{
    return _elementIds.value(key, NULL);
}

void VStyle::globalActivate(const QFont &baseFont, const QBrush &baseBrush)
{
    globalInitFlag = true;
    _defaultFont = baseFont ;
    _defaultFontSize = baseFont.pointSize();
    _defaultBrush = baseBrush ;
}

void VStyle::changeDefaultBrush(const QBrush &baseBrush)
{
    _defaultBrush = baseBrush ;
}

bool VStyle::activate(const QFont &baseFont, const int zoom)
{
    bool isOk = true ;
    if(!_inited) {
        _inited = true;
    }
    foreach(StyleEntry * entry, _styles.values()) {
        if(!entry->activate(baseFont, zoom)) {
            isOk = false ;
        }
    }
    return isOk ;
}

void VStyle::deactivate()
{
    foreach(StyleEntry * entry, _styles.values()) {
        entry->deactivate();
    }
}

const QFont &VStyle::defaultFont()
{
    return _defaultFont;
}

const QBrush &VStyle::defaultBrush()
{
    return _defaultBrush;
}

void VStyle::setZoom(const int zoom)
{
    int newSize = getZoomFontSize(_defaultFontSize, zoom);
    if(0 == newSize) {
        return ;
    }
    _defaultFont.setPointSize(newSize);
    // gestisce lo stile nei figli
    foreach(StyleEntry * entry, _styles.values()) {
        entry->setZoom(zoom);
    }
}

int VStyle::getZoomFontSize(const int size, const int zoom)
{
    if(zoom <= 1) {
        return size ;
    }
    int newSize = ((zoom + 1) * size) / 2;
    return newSize ;
}
