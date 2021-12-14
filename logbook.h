/** @file logbook.h
 *  @brief logbook header file
 *
 *  header file containing functions and variables used the logbook widget
 *
 *  @author patrick mccormick
 *  @bug no known bugs
 */

#ifndef LOGBOOK_H
#define LOGBOOK_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QDomElement>


namespace Ui {
class logbook;
}

class logbook : public QDialog
{
    Q_OBJECT

public:
    /** @brief [event] UI creation
     *
     *  constructs logbook widget
     *
     *  @param parent   the new parent to become a window
     *
     *  @return void
     */
    explicit logbook(QWidget *parent = nullptr);


    /** @brief [virtual] destroys widget
     *
     *  widget is destroyed if it is currently open
     *
     *  @return void
     */
    ~logbook();

private slots:

    /** @brief [signal] load XML file
     *
     *  when button is pressed, user is prompted to select an XML file to load into the table widget
     *
     *  @return void
     */
    void on_pushButton_2_clicked();


    /** @brief [signal] add entry
     *
     *  when button is pressed, user input from text boxes is entered into table widget
     *
     *  @return void
     */
    void on_pushButton_4_clicked();


    /** @brief [signal] delete entry
     *
     *  when button is pressed, the selected row of data from the table widget is deleted
     *
     *  @return void
     */
    void on_pushButton_5_clicked();


    /** @brief [signal] save file
     *
     *  when button is pressed, user is prompted to save the data contained in the table widget
     *
     *  @return void
     */
    void on_pushButton_6_clicked();

private:
    Ui::logbook *ui;

    /** @brief [signal] load XML file
     *
     *  @param  root    XML root
     *  @param  tag     XML tag
     *  @param  att     XML attribute
     *
     *  when button is pressed, user is prompted to select an XML file to load into the table widget
     *
     *  @return void
     */
    void loadFile(QDomElement root, QString tag, QString att);

};

// LO1. Design and implement a class
class User
{
// LO2a. Include comments describing the visibility inheritance model
// The following members are public, which means that any class can access and use them
public:
    QString lastName{};
    QString firstName{};
    int licenseNumber{};

    User(int m_licenseNumber) : licenseNumber{m_licenseNumber}
    {
    }
    // LO1b. Overload a constructor
    // LO1c. Utilize an initialization list
    User(QString m_lastName, QString m_firstName)
        :lastName{m_lastName}, firstName{m_firstName}
    {
    }
};

class Pilot : public User
{

public:
    // LO2. Use subclassing to design simple class hierarchies that allow code to be reused for distinct subclasses.
    // LO5. Explain the relationship between object-oriented inheritance (code-sharing and overriding) and subtyping (the idea of a subtype being usable in a context that expects
    // the supertype): Subtyping refers to the compatibility of interfaces whereas inheritance refers to reuse of implementations.
    Pilot(QString lastName, QString firstName) : User(lastName, firstName)
    {
    }
};

#endif // LOGBOOK_H
