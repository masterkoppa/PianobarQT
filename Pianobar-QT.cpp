#include "Pianobar-QT.h"




Pianobar_QT::Pianobar_QT(QWidget* parent) : QWidget(parent)
{
    QGridLayout* layout = new QGridLayout(this);
    
    QLabel* title = new QLabel("Welcome to PianobarQT", this);
    QFont titleFont;
    titleFont.setPointSize(20);
    titleFont.setUnderline(true);
    titleFont.setBold(true);
    
    title->setFont(titleFont);
    
    layout->addWidget(title, 0, 0, 1, 2);
    
    QLabel* userNameLabel = new QLabel("Username", this);
    
    layout->addWidget(userNameLabel, 1, 0);
    
    userName = new QLineEdit(this);
    
    layout->addWidget(userName, 1, 1);
    
    QLabel* passwordLabel = new QLabel("Password", this);
    
    layout->addWidget(passwordLabel, 2, 0);
    
    passwordField = new QLineEdit(this);
    passwordField->setEchoMode(QLineEdit::Password);
    
    layout->addWidget(passwordField, 2, 1);
    
    ok = new QPushButton("Ok", this);
    QPushButton* cancel = new QPushButton("Cancel", this);
    
    QHBoxLayout* hbox = new QHBoxLayout();
    
    hbox->addWidget(ok, 1, Qt::AlignRight);
    hbox->addWidget(cancel, 1, Qt::AlignRight);
    
    layout->addLayout(hbox, 3, 1);
    
    setLayout(layout);
    
    connect(cancel, SIGNAL(clicked(bool)), SLOT(cancelPressed()));
    connect(ok, SIGNAL(clicked(bool)), SLOT(logIn()));
    
}
void Pianobar_QT::logIn(){
    
    QString username = userName->text();
    QString password = passwordField->text();
    
    if(username.isEmpty() || password.isEmpty()){
       if(username.isEmpty()){
	userName->setStyleSheet("background: red");
       }else{
	userName->setStyleSheet("background: white");
       }
       if(password.isEmpty()){
	passwordField->setStyleSheet("background: red");
       }else{
	passwordField->setStyleSheet("background: white");
       }
       
      return;
    }
        
    piano.PianoInitialize(&ph, &wh);
    
    //Copy the data to avoid overwriting... dam you memory
    char* user = strdup(username.toAscii().data());
    char* pass = strdup(password.toAscii().data());
        
    if(!piano.PianoLogin(&ph, &wh, user, pass)){
      //TODO: Tell the user in a nicer way that the login failed
      userName->setStyleSheet("background: red");
      passwordField->setStyleSheet("background: red");
      return;
    }
    
    //Memory needs to be freed, plus it's sensitive information
    free(user);
    free(pass);
    
    Pianobar_QT_MainWindow mainWindow;
    
    mainWindow.resize(500, 500);
    mainWindow.setHandlers(ph, wh);
    mainWindow.show();
    
    //this->close();
    
    //Make sure that there are no double logins
    ok->disconnect(SIGNAL(clicked(bool)));
}

void Pianobar_QT::cancelPressed()
{
  //We are out of here
  exit(0);
}



#include "Pianobar-QT.moc"
