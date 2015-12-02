#include "findtextparams.h"

#include <QtGui>
#include "icdCreator.h"
#include "findtextparams.h"
#include "utils.h"
#include "DomModel.h"
#include "config.h"

#define SPLIT_SCOPE_CHAR '/'
#define ATTR_CHAR        '@'

FindTextParams::FindTextParams(const QString textToFind, const bool isCountingOnly, const bool isHiliteAll, const bool isMatchExact,
                               const bool isCaseSensitive, const bool isOnlyChildren, const EFindTarget findTarget,
                               const bool isCloseUnrelated, const bool isShowSize,
                               const QString &scope)
{
    mSize = 0 ;
    mIsCountingOnly = isCountingOnly ;
    mTextToFind = textToFind ;
    mIsHiliteAll = isHiliteAll ;
    mIsMatchExact = isMatchExact ;
    mIsCaseSensitive = isCaseSensitive ;
    mIsOnlyChildren = isOnlyChildren ;
    mFindTarget = findTarget ;
    mIsCloseUnrelated = isCloseUnrelated ;
    mIsShowSize = isShowSize ;
    mIsSearchAttribute = false;
    mIsScoped = false ;
    mOccurrences = 0 ;
    mScopes = scope.split(SPLIT_SCOPE_CHAR, QString::KeepEmptyParts);
    int scopeCount = mScopes.count();
    if((scopeCount > 0) && mScopes.at(scopeCount - 1).startsWith(ATTR_CHAR)) {
        mIsSearchAttribute = true ;
        mAttributeName = mScopes.at(scopeCount - 1);
        mAttributeName = mAttributeName.right(mAttributeName.length() - 1);
        mScopes.removeAt(scopeCount - 1);
    }
    scopeCount = mScopes.count();
    if((scopeCount > 0)) {
        mIsScoped = true;
        int scopeCount = mScopes.count();
        mScope = mScopes.at(scopeCount - 1);
        mScopes.removeAt(scopeCount - 1);
    }
}

FindTextParams::FindTextParams()
{
    mSize = 0 ;
    mTextToFind = "" ;
    mIsHiliteAll = false ;
    mIsMatchExact = false ;
    mIsCaseSensitive = false ;
    mIsOnlyChildren = false ;
    mFindTarget = FindTextParams::FIND_ALL ;
    mIsCloseUnrelated = false ;
    mIsSearchAttribute = false;
    mIsShowSize = false ;
    mAttributeName = "" ;
    mIsScoped = false ;
}

FindTextParams::~FindTextParams()
{
}

bool FindTextParams::checkParams(bool &isErrorShown)
{
    isErrorShown = false ;
    if((FIND_ATTRIBUTE_VALUE != mFindTarget) && mIsSearchAttribute) {
        Utils::error(tr("The scope is not legal for a search of an attribute value."));
        isErrorShown = true ;
        return false ;
    }
    return true;
}

bool FindTextParams::isTextMatched(const QString &textToExamine) const
{
    Qt::CaseSensitivity caseSensitivity =  mIsCaseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive ;
    if(mIsMatchExact) {
        return (0 == mTextToFind.compare(textToExamine, caseSensitivity));
    } else {
        return textToExamine.contains(mTextToFind, caseSensitivity);
    }
}


QStringList &FindTextParams::getScopes()
{
    return mScopes;
}
/*********************************************************
void FindTextParams::copyTo( FindTextParam &destination ) const
{
    destination.mTextToFind =  mTextToFind;
    destination.mIsHiliteAll =  mIsHiliteAll ;
    destination.mIsMatchExact = mIsMatchExact;
    destination.mIsCaseSensitive = mIsCaseSensitive;
    destination.mIsOnlyChildren = mIsOnlyChildren;
    destination.mFindTarget = mFindTarget ;
    destination.mIsSelToBookmarks = mIsSelToBookmarks ;
    destination.mIsCloseUnrelated =  mIsCloseUnrelated ;
}
********************************************************/
void FindTextParams::loadState()
{
    mTextToFind =  "";
    mIsHiliteAll =  Config::getBool(Config::KEY_SEARCH_HIGHLIGHALL, true);
    mIsMatchExact = Config::getBool(Config::KEY_SEARCH_MATCHEXACT, false);
    mIsCaseSensitive = Config::getBool(Config::KEY_SEARCH_CASEUNSITIVE, false);
    mIsOnlyChildren = Config::getBool(Config::KEY_SEARCH_ONLYCHILDREN, false);
    mFindTarget = (EFindTarget)Config::getInt(Config::KEY_SEARCH_FINDTARGET, 0);
    mIsCloseUnrelated =  Config::getBool(Config::KEY_SEARCH_CLOSEUNRELATED, true);
    mIsShowSize =  Config::getBool(Config::KEY_SEARCH_SHOWSIZE, true);
}

void FindTextParams::saveState() const
{
    Config::saveBool(Config::KEY_SEARCH_HIGHLIGHALL, mIsHiliteAll);
    Config::saveBool(Config::KEY_SEARCH_MATCHEXACT, mIsMatchExact);
    Config::saveBool(Config::KEY_SEARCH_CASEUNSITIVE, mIsCaseSensitive);
    Config::saveBool(Config::KEY_SEARCH_ONLYCHILDREN, mIsOnlyChildren);
    Config::saveInt(Config::KEY_SEARCH_FINDTARGET, mFindTarget);
    Config::saveBool(Config::KEY_SEARCH_CLOSEUNRELATED, mIsCloseUnrelated);
    Config::saveBool(Config::KEY_SEARCH_SHOWSIZE, mIsShowSize);
}

void FindTextParams::start()
{
    mOccurrences = 0 ;
    mSize = 0 ;
}

void FindTextParams::newOccurence(const int size)
{
    mOccurrences ++ ;
    mSize += size ;
}
