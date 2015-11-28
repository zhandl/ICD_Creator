#ifndef PAINTINFO_H
#define PAINTINFO_H

#include "global.h"
#include "style.h"

class LIBQXMLEDITSHARED_EXPORT PaintInfo
{
private:
    bool isChanged;

    bool isOneAttrPerLine;
    bool isIndexPerChild;
    bool isCompactView;
    bool isShowAttributesLength;
    bool isUseFixedLengthFont;
    bool isShowUnBase64;
    int  zoomFactor;
    VStyle *_currentStyle;
    bool isShowElementTextLength;
    bool isShowElementSize;
    bool isExplore;
    bool isAttributesHTML;
    bool isHideView;

    void internalSetZoom(const int newValue);
    void recalcColumns();

public:
    PaintInfo();
    ~PaintInfo();

    void loadState();
    bool saveState();

    void setIndexPerChild(const bool newValue);
    void setOneAttrPerLine(const bool newValue);
    void setCompactView(const bool newValue);
    bool oneAttrPerLine() const;
    bool indexPerChild() const;
    bool compactView() const;
    bool showUnBase64() const;
    VStyle *currentStyle() const;
    int  zoom() const;
    bool showItemTextLength() const;
    bool showItemSize() const;
    bool exploreMode() const;
    bool attributesHTML() const;
    bool hideView() const;

    bool showAttributesLength() const;
    void setShowAttributesLength(const bool newValue);
    bool userFixedLengthFont() const;
    void setUserFixedLengthFont(const bool newValue);
    void setCurrentStyle(VStyle *newStyle);
    void setShowUnBase64(const bool newValue);
    void setZoom(const int newValue);
    void setShowItemTextLength(const bool newValue);
    void setShowItemSize(const bool newValue);
    void setExploreMode(const bool isExplore);
    void setAttributesHTML(const bool value);
    void setHideView(const bool value);

    bool zoomIn();
    bool zoomOut();

    bool canZoomOut();
    bool canZoomIn();

    int columnForTag;
    int columnForAttributes;
    int columnForText;
    int columnForDecodedText;
    int columnForChildren;
    int columnForSize;

};

#endif // PAINTINFO_H
