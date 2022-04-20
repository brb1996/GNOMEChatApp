#ifndef STRUCTDEF_H
#define STRUCTDEF_H

//Structure defined with members that help in authenticating user during login 

struct user_login_details
{
    GtkWidget *username;
    GtkWidget *password;
};

//Structure defined with members that help in registering a new user

struct user_signup_details
{
    GtkWidget *signupUsername;
    GtkWidget *signupPassword;
    GtkWidget *signupEmailID;
};

//Structure defined with members that help in resetting user password

struct password_reset_details
{
    GtkWidget *userEmailID;
    GtkWidget *newPassword;
};


#endif

