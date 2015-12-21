#-------------------------------------------------
#
# Project created by QtCreator 2015-03-23T15:20:08
#
#-------------------------------------------------

QT       += core gui
QT       += core xml svg network
QT       += xmlpatterns

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ICD_Creator
TEMPLATE = app

DEFINES += LIBQXMLEDIT_LIBRARY

RC_FILE = icdCreator.rc

SOURCES += main.cpp\
        mainwindow.cpp \
    domitem.cpp \
    dommodel.cpp \
    qitemaction.cpp \
    nodetablewidget.cpp \
    icdtreeview.cpp \
    style.cpp \
    paintinfo.cpp \
    config.cpp \
    utils.cpp \
    findtextparams.cpp \
    documenttype.cpp \
    edittextnode.cpp \
    editelement.cpp \
    undo/undobasechangeelement.cpp \
    undo/undocommand.cpp \
    undo/undodeletecommand.cpp \
    undo/undoeditcommand.cpp \
    undo/undoinsertcommand.cpp \
    undo/undomanager.cpp \
    undo/undomovedowncommand.cpp \
    undo/undomoveupcommand.cpp \
    xsaxhandler.cpp \
    xmlutils.cpp \
    xsdeditor/navigationtree.cpp \
    xsdeditor/XAnnotation.cpp \
    xsdeditor/XFactory.cpp \
    xsdeditor/XSCContent.cpp \
    xsdeditor/XSchemaAttribute.cpp \
    xsdeditor/XSchemaChoice.cpp \
    xsdeditor/XSchemaElement.cpp \
    xsdeditor/xschemaloader.cpp \
    xsdeditor/XSchemaObject.cpp \
    xsdeditor/XSchemaTopLevel.cpp \
    xsdeditor/xsdcontroller.cpp \
    xsdeditor/XsdException.cpp \
    xsdeditor/xsdgraphiccontext.cpp \
    xsdeditor/xsdplugin.cpp \
    xsdeditor/XSDScene.cpp \
    xsdeditor/XSDSchema.cpp \
    xsdeditor/XSDSchemaSequence.cpp \
    xsdeditor/xsdsctypes.cpp \
    xsdeditor/xsdwindow.cpp \
    xmleditglobals.cpp \
    xmleditwidget.cpp \
    qxmleditdata.cpp \
    editcomment.cpp \
    editprocessinginstruction.cpp \
    stylepersistence.cpp \
    schemavalidator.cpp \
    xsdeditor/items/graphicitems.cpp \
    xsdeditor/items/XSchemaBaseItems.cpp \
    xsdeditor/items/XSchemaCompositeItems.cpp \
    xsdeditor/items/XSchemaDerivedItems.cpp \
    xsdeditor/validator/schemasearchcontext.cpp \
    xsdeditor/validator/xcollect.cpp \
    xsdeditor/validator/xelementcontent.cpp \
    xsdeditor/validator/xsingleelementcontent.cpp \
    xsdeditor/validator/xvalidationcontext.cpp \
    xsdeditor/widgets/elementeditor.cpp \
    xsdeditor/widgets/widgetutility.cpp \
    xsdeditor/widgets/xsdattributeeditor.cpp \
    xsdeditor/widgets/xsdchoiceeditor.cpp \
    xsdeditor/widgets/xsdgenericeditor.cpp \
    xsdeditor/widgets/xsdrooteditor.cpp \
    xsdeditor/widgets/xsdsequenceeditor.cpp \
    xmleditwidgetprivate.cpp \
    navigationbox.cpp \
    validatormessagehandler.cpp \
    validationresults.cpp \
    texteditutils.cpp \
    alloweditemsinsert.cpp \
    searchinfiles.cpp \
    scansax.cpp \
    aboutdialog.cpp \
    AboutData.cpp \
    balsamiqsrc/balsamiqbasedialog.cpp \
    balsamiqsrc/balsamiqcontrol.cpp \
    balsamiqsrc/balsamiqplugin.cpp \
    balsamiqsrc/balsamiqproxy.cpp \
    balsamiqsrc/balsamiqtree.cpp \
    balsamiqsrc/balsamiqwork.cpp \
    compare.cpp \
    preferreddirs.cpp \
    config/configurationgeneraloptions.cpp \
    config/configurestyle.cpp \
    config/configvalidation.cpp \
    configurationdialog.cpp \
    services/loghandler.cpp \
    snippet.cpp \
    snippethandler.cpp \
    editsnippet.cpp \
    test.cpp \
    schemachooser.cpp \
    recodericdwizard.cpp \
    icdWizard/welcomepage.cpp \
    icdWizard/icdheaderpage.cpp \
    icdWizard/icdsubstationpage.cpp \
    icdWizard/icdcommunicationpage.cpp \
    icdWizard/icdiedservicespage.cpp \
    icdWizard/icdiedaccesspointpage.cpp \
    icdWizard/icddatatypetemplatepage.cpp \
    icdWizard/icddatatypetemplatenew.cpp \
    datatypemodel.cpp \
    datatypeitem.cpp \
    newtemplatelnodemodel.cpp \
    ipaddredit.cpp \
    ippartlineedit.cpp

HEADERS  += mainwindow.h \
    domitem.h \
    dommodel.h \
    qitemaction.h \
    nodetablewidget.h \
    icdtreeview.h \
    icdCreator.h \
    global.h \
    paintinfo.h \
    style.h \
    config.h \
    utils.h \
    findtextparams.h \
    documenttype.h \
    edittextnode.h \
    editelement.h \
    undo/undobasechangeelement.h \
    undo/undocommand.h \
    undo/undodeletecommand.h \
    undo/undoeditcommand.h \
    undo/undoinsertcommand.h \
    undo/undomanager.h \
    undo/undomovedowncommand.h \
    undo/undomoveupcommand.h \
    xsaxhandler.h \
    xmlutils.h \
    xsdeditor/navigationtree.h \
    xsdeditor/xproperties.h \
    xsdeditor/xschema.h \
    xsdeditor/XSchemaIOContants.h \
    xsdeditor/xschemaloader.h \
    xsdeditor/xsdcontent.h \
    xsdeditor/xsdcontroller.h \
    xsdeditor/xsddefinitions.h \
    xsdeditor/xsdgraphiccontext.h \
    xsdeditor/xsdparseutils.h \
    xsdeditor/xsdplugin.h \
    xsdeditor/xsdsctypes.h \
    xsdeditor/xsdtypes.h \
    xsdeditor/xsdwindow.h \
    xsdeditor/xtypes.h \
    xmleditglobals.h \
    plugin.h \
    xmleditwidget.h \
    qxmleditdata.h \
    qxmledit.h \
    navigation.h \
    editcomment.h \
    editprocessinginstruction.h \
    stylepersistence.h \
    schemavalidator.h \
    SchemaInterface.h \
    xsdeditor/items/xgraphicsitems.h \
    xsdeditor/validator/schemasearchcontext.h \
    xsdeditor/validator/xelementcontent.h \
    xsdeditor/validator/xsingleelementcontent.h \
    xsdeditor/validator/xvalidationcontext.h \
    xsdeditor/widgets/elementeditor.h \
    xsdeditor/widgets/WidgetUtility.h \
    xsdeditor/widgets/XEditorInterface.h \
    xsdeditor/widgets/xsdattributeeditor.h \
    xsdeditor/widgets/xsdchoiceeditor.h \
    xsdeditor/widgets/xsdgenericeditor.h \
    xsdeditor/widgets/xsdrooteditor.h \
    xsdeditor/widgets/xsdsequenceeditor.h \
    xmleditwidgetprivate.h \
    navigationbox.h \
    validatormessagehandler.h \
    validationresults.h \
    texteditutils.h \
    alloweditemsinsert.h \
    searchinfiles.h \
    scansax.h \
    aboutdialog.h \
    authorinfo.h \
    balsamiqsrc/balsamiqbasedialog.h \
    balsamiqsrc/balsamiqcontrol.h \
    balsamiqsrc/balsamiqplugin.h \
    balsamiqsrc/balsamiqproxy.h \
    balsamiqsrc/balsamiqtree.h \
    balsamiqsrc/balsamiqwork.h \
    compare.h \
    preferreddirs.h \
    config/configurationgeneraloptions.h \
    config/configurestyle.h \
    config/configvalidation.h \
    configurationdialog.h \
    log.h \
    StartParams.h \
    services/loghandler.h \
    snippet.h \
    snippet_interface.h \
    snippethandler.h \
    editsnippet.h \
    test.h \
    schemachooser.h \
    recodericdwizard.h \
    icdWizard/welcomepage.h \
    icdWizard/icdheaderpage.h \
    icdWizard/icdsubstationpage.h \
    icdWizard/icdcommunicationpage.h \
    icdWizard/icdiedservicespage.h \
    icdWizard/icdiedaccesspointpage.h \
    icdWizard/icddatatypetemplatepage.h \
    icdWizard/icddatatypetemplatenew.h \
    datatypemodel.h \
    datatypeitem.h \
    newtemplatelnodemodel.h \
    ipaddredit.h \
    ippartlineedit.h

FORMS += \
    xsdeditor/xsdwindow.ui \
    xsdeditor/widgets/elementeditor.ui \
    xsdeditor/widgets/xsdattributeeditor.ui \
    xsdeditor/widgets/xsdchoiceeditor.ui \
    xsdeditor/widgets/xsdgenericeditor.ui \
    xsdeditor/widgets/xsdrooteditor.ui \
    xsdeditor/widgets/xsdsequenceeditor.ui \
    icdHeaderPage.ui \
    icdSubstationPage.ui \
    icdCommunicationPage.ui \
    icdIedServicesPage.ui \
    icdDataTypeTemplate.ui \
    icdDataTypeTemplateNewPage.ui

RESOURCES += \
    icdcreator.qrc
