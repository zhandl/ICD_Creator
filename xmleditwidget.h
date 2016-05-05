#ifndef XMLEDITWIDGET_H
#define XMLEDITWIDGET_H

#include "global.h"

#include <QWidget>
#include <QDomDocument>

#include "icdCreator.h"
#include "xmleditglobals.h"

#include "qxmleditdata.h"
#include "navigation.h"
#include "dommodel.h"

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QtGui/QMovie>

class XSDSchema;
class DomItem;
class XSchemaLoader;
class PaintInfo;

class XmlEditWidgetPrivate;

class LIBQXMLEDITSHARED_EXPORT XmlEditWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled)
    Q_PROPERTY(bool encodingLabelVisible READ isEncodingLabelVisible WRITE setEncodingLabelVisible)
    Q_PROPERTY(bool viewAsXSDButtonVisible READ isViewAsXSDButtonVisible WRITE setViewAsXSDButtonVisible)
    Q_PROPERTY(bool moveButtonsVisible READ areMoveButtonsVisible WRITE setMoveButtonsVisible)
    Q_PROPERTY(ulong versionNumber READ versionNumber)

    friend class XmlEditWidgetPrivate;

private:
    XmlEditWidgetPrivate *d;

public:
    explicit XmlEditWidget(QWidget *parent = 0);
    ~XmlEditWidget();

    bool isReady();

    ulong versionNumber();
    XmlEditWidgetPrivate *getPrivate();

    bool editItem(QTreeWidgetItem *item);

    bool init();
    void setData(QApplication *newApplication, QXmlEditData *newData, const bool newIsSlave);

    DomItem *getSelectedItem();
    void deleteSchema();

    void display();
    void repaint();
    void resetTree();
    void computeSelectionState();

    PaintInfo *getPaintInfo();

    void doLoadFileXplore(const QString &filePath);
//    void openProva();
    QString getContentAsText();
    qxmledit::EDisplayMode displayMode();

    bool isCDATA();
    void setCDATA(const bool isCData);
    void doNew();

    DomModel *getModel();

    void autoLoadValidation();

    void error(const QString& message);
    void warning(const QString& message);
    void message(const QString& message);
    bool askYN(const QString & message);

    QTreeWidget *getMainTreeWidget();
    void addChild();
    void addBrother();

    void editAttribute();
    void addText();
    void addPrivate();

    void addSubstation();
    void addCommunication();
    void addIED();
    void addDataTypeTemplates();

    void addHistory();
    void addHitem();

    void addSubNetwork();
    void addBitRate();
    void addConnectedAP();
    void addAddress();
    void addGSE();
    void addSMV();
    void addPhysconn();
    void addP();
    void addMinTime();
    void addMaxTime();

    void addServices();
    void addAccessPoint();
    void addServer();
    void addServerAt();
    void addGOOSESecurity();
    void addSMVSecurity();
    void addSubject();
    void addIssuerName();
    void addAuthentication();
    void addLDevice();
    void addAssociation();

    void addLN0();
    void addLN();
    void addAccessControl();
    void addDataSet();
    void addReportControl();
    void addLogControl();
    void addInputs();
    void addLog();
    void addGSEControl();
    void addSMVControl();
    void addSettingControl();
    void addSCLControl();

    void addPowerTransformer();
    void addGeneralEquipment();
    void addLNode();
    void addVoltageLevel();
    void addFunction();
    void addTransformerWinding();
    void addVoltage();
    void addBay();
    void addSubFunction();
    void addTapChanger();
    void addTerminal();
    void addSubEquipment();
    void addConductingEquipment();
    void addConnectivityNode();
    void addFCDA();
    void addTrgOps();
    void addOptFields();
    void addRptEnabled();
    void addSDI();
    void addDAI();
    void addExtRef();
    void addIEDName();
    void addSmvOpts();
    void addVal();
    void addLNodeType();
    void addDOType();
    void addDAType();
    void addEnumType();
    void addDO();
    void addSDO();
    void addDA();
    void addBDA();
    void addEnumVal();

//    void addLNode();
//    void addLN0();
//    void addDataSet();

    void errorNoRule();
    void setClipBoardItem(DomItem *pItem);
    void cleanClipBoard();
    DomItem *getClipBoardItem() const;

    bool isActionMode();
    bool isActionNoScanMode();
    void setDisplayMode(const qxmledit::EDisplayMode value);

    void setDocument(QDomDocument &document, const QString &filePath, const bool isSetState);
    void loadText(const QString &text, const bool isChangeState = true, const bool isAskForReview = false);
    void insertSnippet(DomModel *newModel);
    void insertAllowedItem(DomItem *item);
    void validateWithFile(const QString &filePath);
    XSDSchema *schema();
    bool isUndoPossible();
    bool isRedoPossible();
    void undo();
    void redo();


private:
    //-------- UI
    QVBoxLayout *verticalLayout_2;
    QGroupBox *searchGroup;
    QVBoxLayout *ricercaLayout;
    QHBoxLayout *searchTop;
    QPushButton *closeSearchPanel;
    QLabel *label_2;
    QLineEdit *searchEditBox;
    QToolButton *clearText;
    QPushButton *findButton;
    QPushButton *counting;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QComboBox *searchLocation;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelScope;
    QLineEdit *searchScope;
    QHBoxLayout *searchBottom;
    QSpacerItem *horizontalSpacer;
    QCheckBox *closeUnrelated;
    QCheckBox *isMatchExactValue;
    QCheckBox *isCaseSensitive;
    QCheckBox *isHiglightAll;
    QCheckBox *isOnlyChildren;
    QCheckBox *showSize;
    QHBoxLayout *searchResultsLayout;
    QLabel *searchResult;
    QLabel *occNumber;
    QLabel *lblSize;
    QLabel *sizeOfSearch;
    QSpacerItem *horizontalSpacer_3;
    QCheckBox *cdataElement;
//    QHBoxLayout *mainLayout;
    QGridLayout *mainLayout;
    QTreeWidget *treeWidget;
    QVBoxLayout *verticalLayout;
    QLabel *docTypeLabel;
    QLabel *encoding;
    QPushButton *ok;
    QPushButton *cancel;
    QPushButton *addChildButton;
    QPushButton *addBrotherButton;
    QPushButton *editItemButton;
    QPushButton *deleteItem;
    QPushButton *moveUpButton;
    QPushButton *moveDownButton;
    QPushButton *viewAsXsdCmd;
    QPushButton *testPrev;
    QPushButton *testNext;
    QHBoxLayout *parentNav;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLowLayout;
    QToolButton *styleButton;
    QToolButton *copySpecial;

    QLabel *loading;
    QMovie *movie;

    void setupUi();
    void retranslateUi();

    //------- emit signals
    void emitReevalueSelectionState();
    void emitDocumentIsModified(const bool isModified);
    void emitTreeContextMenuRequested(const QPoint &);
    void emitSignalSetClipBoardActionsState(const bool isAction);
    void emitOkClicked();
    void emitCancelClicked();
    void emitEnableZoom();
    void emitViewAsXsdRequested();
    void emitSchemaLabelChanged(const QString &newLabel);
    void emitShowStatusMessage(const QString &message, const bool isLongTimeout);
    void emitDataReadyMessage(const QString &newLabel);
    void emitLoadCurrentPage(const int page);

protected:
    virtual void changeEvent(QEvent *e);
    virtual bool eventFilter(QObject *obj, QEvent *event);
public:
    void setMoveButtonsVisible(bool isShow);
    bool areMoveButtonsVisible();

    void setViewAsXSDButtonVisible(bool isShow);
    bool isViewAsXSDButtonVisible();

    void setEncodingLabelVisible(bool isShow);
    bool isEncodingLabelVisible();

    void setDocTypeVisible(bool isShow);
    bool isDocTypeVisible();

    void resizeTreeColumns();
    void onAddBrother();
    void onDeleteItem();
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
    void onActionAddChildItem();
    void onActionAppendChildItem();
    void onActionEdit();
    void onActionFind();
    void onActionDelete();
    void onActionMoveUp();
    void onActionMoveDown();
    void onActionGoToParent();
    void onActionGoToPreviousBrother();
    void onActionGoToNextBrother();
    void onActionShowChildIndex(const bool isChecked);
    void onActionCloseThisAllBrothers();
    void onActionNewFromClipboard();
    void onActionCompactView(const bool isChecked);
    void onActionHideBrothers();
    void onActionFixedSizeAttributes(const bool isChecked);
    void onActionShowAttributesLength(const bool isChecked);
//    void onActionShowCurrentItemTextBase64(const bool isChecked);
//    void onActionShowBase64(const bool isChecked);
    void onActionZoomIn();
    void onActionZoomOut();
    void onActionCopyPathToClipboard();
    void onActionValidate();
    void onActionValidateFile();
    void onActionValidateNewFile();
    void onActionInsertSnippet();
    void onActionShowItemTextLength(const bool isChecked);
    void onActionShowItemSize(const bool isChecked);
    void onActionHideView(const bool isChecked);
    void onActionViewAsXsd();
    void onActionAllowedSchemaItems();
    void onActionNewUsingXMLSchema(const QString &schemaURL);
    void onActionTransformInComment();
    void onActionExtractItemsFromComment();
    void onActionInsertSchemaReferenceAttributes();
    void onActionInsertNoNamespaceSchemaReferenceAttributes();
    DomItem *onActionHideLeafChildren();
    void onActionHideAllLeafChildren();
    DomItem *onActionShowLeafChildren();
    void onActionShowAllLeafChildren();
    bool isValidXsd();
    void loadSchema(const QString &schemaURL);
    void setCurrentItem(DomItem *newSelection);

    void setModelLoadingLabel();
    void setModelCompleted();


signals:
    void reevaluateSelectionState();
    void documentIsModified(const bool isModified);
    void treeContextMenuRequested(const QPoint &);
    void signalSetClipBoardActionsState(const bool isAction);
    void okClicked();
    void cancelClicked();
    void enableZoom();
    void viewAsXsdRequested();
    void schemaLabelChanged(const QString &newLabel);
    void showStatusMessage(const QString &message, const bool isLongTimeout);
    void dataReadyMessage(const QString &newLabel);
    void loadCurrentPage(const int page);
    void undoStateUpdated(const bool undoPossible, const bool redoPossible);

};

#endif // XMLEDITWIDGET_H
