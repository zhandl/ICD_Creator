#ifndef XMLEDITWIDGETPRIVATE_H
#define XMLEDITWIDGETPRIVATE_H

#include "xmleditwidget.h"

class XElementContent;

class XmlEditWidgetPrivate : public QObject
{
    Q_OBJECT
    friend class XmlEditWidget;

    XmlEditWidget *p;
    bool    started;
    bool    internalStateOk;
    DomModel *model;
    PaintInfo paintInfo;
    QApplication *application;
    QXmlEditData *_appData;
    QXmlEditData _defaultData;
    QMenu *styleMenu;
    QMenu *copyMenu;
    QActionGroup styleActionGroup;
    bool isSlave;
    int mainFontSize;

    qxmledit::EDisplayMode _displayMode;
//    QAttributeDelegate *attrDelegate;
    XSDSchema *_schemaRoot;
    DomItem *clipBoardItem;
    DomModel *newModel();
public:
    XmlEditWidgetPrivate(XmlEditWidget *theOwner);
    ~XmlEditWidgetPrivate();

    bool isReady();
    void secondStepConstructor();
    void deleteSchema();
    void showControls(const bool how);
    void loadSearchSettings();
    VStyle* loadStyleMenu();
    void resetStyleMenu();
    void deleteModel();
//    bool setUpDelegates();
    void startUIState();
    void setNewStyle(VStyle *newStyle);
    void setClipBoardActoinsState();
    void buildCopyMenu();
    void resetCopyMenu();
    void setDataColumnTitle(const bool isCompactView);
    void calcColumnState();
    QTreeWidgetItem *getSelItem();

    void moveUp();
    void moveDown();
    void deleteItem();
    void editItem();

    void findTextOperation(const bool isFindOrCount);

    void updateSearchUI(const FindTextParams &lastSearch);
    void saveSearchSettings(const FindTextParams &search);
    void decodeXsdInsertError(const DomModel::EInsSchemaRefInfo error);

    QAction *createStyleAction(QMenu *menu, const QString &label, const QString &tag, const QString &tooltip);
    QAction *createAnAction(QMenu *menu, const QString &label, const QString &tag, const QString &tooltip);

    void cleanClipBoard();

    ulong versionNumber();

    bool editItem(QTreeWidgetItem *item);

    bool init();
    void setData(QApplication *newApplication, QXmlEditData *newData, const bool newIsSlave);

    DomItem *getSelectedItem();

    void display();
    void repaint();
    void resetTree();
    void computeSelectionState();

    bool finishSetUpUi();

    PaintInfo *getPaintInfo();

    void doLoadFileXplore(const QString &filePath);
    void openProva();
    QString getContentAsText();
    qxmledit::EDisplayMode displayMode();

    bool isCDATA();
    void setCDATA(const bool isCData);
    void doNew();

    DomModel *getModel();

    void autoLoadValidation();

    void error(const QString &message);
    void warning(const QString &message);
    void message(const QString &message);
    bool askYN(const QString &message);

    QTreeWidget *getMainTreeWidget();
    void addChild();
    void addBrother();

    void errorNoRule();
    void setClipBoardItem(DomItem *pItem);
    DomItem *getClipBoardItem() const;

    bool isActionMode();
    bool isActionNoScanMode();
    void setDisplayMode(const qxmledit::EDisplayMode value);

    void setDocument(QDomDocument &document, const QString &filePath, const bool isSetState);
    void setNavigationDataAndEnable(const int minFragment, const int maxFragment);
    void showNavigationBox();
    void loadText(const QString &text, const bool isChangeState = true, const bool isAskForReview = false);
    void insertSnippet(DomModel *newModel);
    void insertAllowedItems(DomItem *item);
    void validateWithFile(const QString &filePath);
    XSDSchema *schema();
    bool isExpandTreeOnLoad();
    bool isUndoPossible();
    bool isRedoPossible();
    void undo();
    void redo();
    void notifyUndo();
    void setCurrentItem(DomItem *newSelection);

    //------------------------------------
    void setMoveButtonsVisible(bool isShow);
    bool areMoveButtonsVisible();
    // Show/Hide ViewAsXsd
    void setViewAsXSDButtonVisible(bool isShow);
    bool isViewAsXSDButtonVisible();
    // Show/Hide encoding label at the top of the right layout
    void setEncodingLabelVisible(bool isShow);
    bool isEncodingLabelVisible();
    // Show/Hide doc type label
    void setDocTypeVisible(bool isShow);
    bool isDocTypeVisible();
    //
    void resizeTreeColumns();
    void onAddBrother();
    void onDeleteItem();
    void onMoveUp();
    void onMoveDown();
    void onActionPaste();
    void onActionCopy();
    void onActionCut();
    void onActionExpandAll();
    void onActionShowAttrLine(const bool state);
    void onActionAppendComment();
    void onActionAddComment();
    void onActionAppendProcessingInstruction();
    void onActionAddProcessingInstruction();
    void onActionResizeToContents();
    void onActionAddChildElement();
    void onActionAppendChildElement();
    void onActionEdit();
    void onActionFind();
    void onActionDelete();
    void onActionMoveUp();
    void onActionMoveDown();
    void onActionGoToParent();
    void onActionGoToPreviousBrother();
    void onActionGoToNextBrother();
    void onActionClearBookmarks();
    void onActionToggleBookmark();
    void onActionGotoNextBookmark();
    void onActionGotoPreviousBookmark();
    void onActionShowChildIndex(const bool isChecked);
    void onActionCloseThisAllBrothers();
    void onActionNewFromClipboard();
    void onActionCompactView(const bool isChecked);
    void onActionHideBrothers();
    void onActionFixedSizeAttributes(const bool isChecked);
    void onActionShowAttributesLength(const bool isChecked);
//    void onActionShowCurrentElementTextBase64(const bool isChecked);
//    void onActionShowBase64(const bool isChecked);
    void onActionZoomIn();
    void onActionZoomOut();
    void onActionCopyPathToClipboard();
    void onActionValidate();
    void onActionValidateFile();
    void onActionValidateNewFile();
    void onActionInsertSnippet();
    void onActionShowElementTextLength(const bool isChecked);
    void onActionShowElementSize(const bool isChecked);
    void onActionDeleteBookmarked();
    void onActionCleanBookmarkedContent();
    void onActionHideView(const bool isChecked);
    void onActionViewAsXsd();
    void onActionAllowedSchemaElements();
    void onActionNewUsingXMLSchema(const QString &schemaURL);
    void onActionTransformInComment();
    void onActionExtractElementsFromComment();
    void onActionInsertNoNamespaceSchemaReferenceAttributes();
    void onActionInsertSchemaReferenceAttributes();
    DomItem* onActionHideLeafChildren();
    void onActionHideAllLeafChildren();
    DomItem* onActionShowLeafChildren();
    void onActionShowAllLeafChildren();
    bool isValidXsd();
    void loadSchema(const QString &schemaURL);

    bool findAllowedItemsElement(XElementContent *content, DomItem *element, bool &startAsRoot);

private slots:
    void schemaLoadComplete(XSchemaLoader *loader, XSDSchema *schema, const bool isError);
    void modelIsModified();
    void modelUndoChanged();
    void findText();
    void countTextOccurrences();
    void clearSearchText();
    void searchTextChanged(const QString & text);
    void elementDoubleClicked(QTreeWidgetItem * item, int column) ;
    void on_treeWidget_itemSelectionChanged();
    void on_viewAsXsdCmd_clicked();
    void treeContextMenu(const QPoint& position);
    void onStyleChanged();
    void onCopySpecial();
    void navigateToPage(const int page);
    void docTypeChanged(const QString &docType);

    // buttons of the user interface
    void on_ok_clicked();
    void on_cancel_clicked();
    void on_moveUp_clicked();
    void on_moveDown_clicked();
    void on_addChild_clicked();
    void on_addBrother_clicked();
    void on_editItem_clicked();
    void on_deleteItem_clicked();
    void on_closeSearchPanel_clicked();

};

#endif // XMLEDITWIDGETPRIVATE_H
