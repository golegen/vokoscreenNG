#include "QvkSystray.h"

QvkSystray::QvkSystray( Ui_MainWindow *ui_mainwindow )
{
    ui = ui_mainwindow;
}


QvkSystray::~QvkSystray()
{
}


void QvkSystray::init()
{
    QAction *titleAction = new QAction( this );
    titleAction->setText( "vokoscreen" );
    titleAction->setEnabled( false );

    startAction = new QAction( this );
    startAction->setIcon( QIcon::fromTheme( "media-playback-start", ui->pushButtonStart->style()->standardIcon( QStyle::SP_MediaPlay ) ) );
    startAction->setText( tr( "Start" ) );
    startAction->setData( "Start" );

    stopAction = new QAction( this );
    stopAction->setIcon( QIcon::fromTheme( "media-playback-stop" , ui->pushButtonStart->style()->standardIcon( QStyle::SP_MediaStop ) ) );
    stopAction->setText( tr( "Stop" ) );
    stopAction->setData( "Stop" );
    stopAction->setEnabled( false );

    pauseAction = new QAction( this );
    pauseAction->setIcon( QIcon::fromTheme( "media-playback-pause", ui->pushButtonStart->style()->standardIcon( QStyle::SP_MediaPause ) ) );
    pauseAction->setText( tr( "Pause" ) );
    pauseAction->setData( "Pause" );
    pauseAction->setEnabled( false );

    continueAction = new QAction( this );
    continueAction->setIcon( QIcon::fromTheme( "media-playback-start", ui->pushButtonStart->style()->standardIcon( QStyle::SP_MediaPlay ) ) );
    continueAction->setText( tr( "Continue" ) );
    continueAction->setData( "Continue" );
    continueAction->setEnabled( false );

    hideAction = new QAction( this );
    hideAction->setIcon( QIcon::fromTheme( "video-display", QIcon( ":/pictures/systray.png" ) ) );
    hideAction->setText( tr( "Hide window" ) );
    hideAction->setData( "Hide" );

    exitAction = new QAction( this );
    exitAction->setIcon( QIcon::fromTheme( "application-exit", ui->pushButtonStart->style()->standardIcon( QStyle::SP_DialogCloseButton ) ) );
    exitAction->setText( tr( "Exit" ) );
    exitAction->setData( "Exit" );

    connect( ui->pushButtonStart, SIGNAL( clicked( bool ) ), startAction,    SLOT( setEnabled( bool ) ) );
    connect( ui->pushButtonStart, SIGNAL( clicked( bool ) ), stopAction,     SLOT( setDisabled( bool ) ) );
    connect( ui->pushButtonStart, SIGNAL( clicked( bool ) ), pauseAction,    SLOT( setDisabled( bool ) ) );
    connect( ui->pushButtonStart, SIGNAL( clicked( bool ) ), continueAction, SLOT( setEnabled( bool ) ) );

    connect( ui->pushButtonStop, SIGNAL( clicked( bool ) ), startAction,    SLOT( setDisabled( bool ) ) );
    connect( ui->pushButtonStop, SIGNAL( clicked( bool ) ), stopAction,     SLOT( setEnabled( bool ) ) );
    connect( ui->pushButtonStop, SIGNAL( clicked( bool ) ), pauseAction,    SLOT( setEnabled( bool ) ) );
    connect( ui->pushButtonStop, SIGNAL( clicked( bool ) ), continueAction, SLOT( setEnabled( bool ) ) );

    connect( ui->pushButtonPause, SIGNAL( clicked( bool ) ), startAction,    SLOT( setEnabled( bool ) ) );
    connect( ui->pushButtonPause, SIGNAL( clicked( bool ) ), stopAction,     SLOT( setEnabled( bool ) ) );
    connect( ui->pushButtonPause, SIGNAL( clicked( bool ) ), pauseAction,    SLOT( setEnabled( bool ) ) );
    connect( ui->pushButtonPause, SIGNAL( clicked( bool ) ), continueAction, SLOT( setDisabled( bool ) ) );

    connect( ui->pushButtonContinue, SIGNAL( clicked( bool ) ), startAction,    SLOT( setEnabled( bool ) ) );
    connect( ui->pushButtonContinue, SIGNAL( clicked( bool ) ), stopAction,     SLOT( setDisabled( bool ) ) );
    connect( ui->pushButtonContinue, SIGNAL( clicked( bool ) ), pauseAction,    SLOT( setDisabled( bool ) ) );
    connect( ui->pushButtonContinue, SIGNAL( clicked( bool ) ), continueAction, SLOT( setEnabled( bool ) ) );

    connect( startAction,    SIGNAL( triggered( bool ) ), ui->pushButtonStart,    SLOT( click() ) );
    connect( stopAction,     SIGNAL( triggered( bool ) ), ui->pushButtonStop,     SLOT( click() ) );
    connect( pauseAction,    SIGNAL( triggered( bool ) ), ui->pushButtonPause,    SLOT( click() ) );
    connect( continueAction, SIGNAL( triggered( bool ) ), ui->pushButtonContinue, SLOT( click() ) );

    menu = new QMenu();
    menu->addAction( titleAction );
    menu->addSeparator();
    menu->addAction( startAction );
    menu->addAction( stopAction );
    menu->addAction( pauseAction );
    menu->addAction( continueAction );
    menu->addSeparator();
    menu->addAction( hideAction );
    menu->addSeparator();
    menu->addAction( exitAction );

    setIcon( QIcon( ":/pictures/systray.png" ) );
    setContextMenu ( menu );
    setToolTip( "vokoscreen" );
    show();

    connect( exitAction, SIGNAL( triggered( bool ) ), this, SLOT( slot_hide() ) );
}


void QvkSystray::slot_hide()
{
    hide();
    emit signal_SystemtrayIsClose();
}


void QvkSystray::slot_closeSystray()
{
    hide();
}
