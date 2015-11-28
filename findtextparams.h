#ifndef FINDTEXTPARAMS_H
#define FINDTEXTPARAMS_H

#include "global.h"
#include <QApplication>
#include <QStringList>


class LIBQXMLEDITSHARED_EXPORT FindTextParams
{
    Q_DECLARE_TR_FUNCTIONS(FindTextParams)

public:
    enum EFindTarget {
        FIND_ALL,
        FIND_TAG,
        FIND_ATTRIBUTE_NAME,
        FIND_ATTRIBUTE_VALUE,
        FIND_TEXT

    };

private:

    bool        mIsCountingOnly;
    QString   mTextToFind;
    bool      mIsHiliteAll;
    bool      mIsMatchExact;
    bool      mIsCaseSensitive;
    bool      mIsOnlyChildren;
    EFindTarget mFindTarget;
    bool      mIsSelToBookmarks;
    bool      mIsCloseUnrelated;
    QStringList mScopes;
    bool      mIsSearchAttribute;
    QString   mAttributeName;
    QString   mScope;
    bool      mIsScoped ;
    bool      mIsShowSize ;
    int       mOccurrences;
    int       mSize; // size of result

public:
    FindTextParams();
    FindTextParams(const QString textToFind, const bool isCountingOnly, const bool isHiliteAll, const bool isMatchExact, const bool isCaseSensitive,
                   const bool isOnlyChildren, const EFindTarget findTarget, const bool isSelToBookmarks,
                   const bool isCloseUnrelated, const bool isShowSize, const QString &scope);
    ~FindTextParams();

    bool checkParams(bool &isErrorShown);

    void saveState() const;
    void loadState();

    const QString &getTextToFind() const {
        return mTextToFind;
    }

    bool isCountingOnly() const {
        return mIsCountingOnly ;
    }

    bool isTextMatched(const QString &textToExamine) const ;

    bool isLookOnlyChildren() const {
        return mIsOnlyChildren ;
    }
    bool isHiliteAll() const {
        return mIsHiliteAll;
    }
    EFindTarget getFindTarget() const {
        return mFindTarget;
    }
    bool isSelToBookmarks() const {
        return mIsSelToBookmarks;
    }
    bool isCloseUnrelated() const {
        return mIsCloseUnrelated;
    }
    bool isCaseSensitive() const {
        return mIsCaseSensitive;
    }
    bool isIsMatchExact() const {
        return mIsMatchExact;
    }
    bool isSearchInAttribute() const {
        return mIsSearchAttribute;
    }
    bool isSearchWithScope() const {
        return mIsScoped ;
    }
    const QString &attributeName() const {
        return mAttributeName;
    }

    const QString &mainScope() const {
        return mScope;
    }

    int getOccurrences() const {
        return mOccurrences;
    }

    bool isShowSize() const {
        return mIsShowSize;
    }

    int size() const {
        return mSize;
    }

    QStringList &getScopes();

    void start();

    void newOccurence(const int size);
};


#endif // FINDTEXTPARAMS_H
