#include <gtk/gtk.h>
#include "UserAuthenticationHandler.h"
#include "StructDef.h"
#include "PasswordResetHandler.h"
#include "NewUserSignupHandler.h"


GtkWidget *passwordResetWindow;
GtkWidget *loginWindow;
GtkWidget *signupWindow;
GtkWidget *userNameTextEntry;
GtkWidget *passwordEntry;
GtkWidget *loginButton;
GtkWidget *user_email_address;
GtkWidget *user_new_password;
GtkWidget *resetPasswordSubmitButton;
GtkWidget *userSignupRegisterButton;
GtkBuilder *builder;

int argc; char *argv[] = {};

int main(int argc, char *argv[])
{
    struct user_login_details auth_details;
    
    //initialize gtk  
    gtk_init(&argc, &argv);

    builder = gtk_builder_new();

    //build gtk app from an external glade file generated using glade tool
    gtk_builder_add_from_file (builder, "Login_Window.glade", NULL);

    //Get the Login button widget using the corresponding object from the glade file
    loginButton =  GTK_WIDGET(gtk_builder_get_object(builder, "Loginform"));

    //Get username entered in the text field by the user
    userNameTextEntry = GTK_WIDGET(gtk_builder_get_object(builder, "username_text"));

    //Assign members of the structure to the appropriate values
    auth_details.username = userNameTextEntry;
    
    //Get password entered in the password field by the user
    passwordEntry =  GTK_WIDGET(gtk_builder_get_object(builder, "password_text"));

    //Assign members of the structure to the appropriate values
    auth_details.password = passwordEntry;

    //Callback function for Login Button press is called passing the username and password entered
    g_signal_connect(G_OBJECT(loginButton), "clicked", G_CALLBACK(loginData), (gpointer*)&auth_details);

    //initialize window widget using the corresponding object from the glade file
    loginWindow = GTK_WIDGET(gtk_builder_get_object(builder, "Login"));
    gtk_builder_connect_signals(builder, NULL);

    //On window close event, close the gtk loop and quit
    g_signal_connect (G_OBJECT (loginWindow), "destroy", G_CALLBACK (gtk_main_quit), NULL);
    g_object_unref(builder);

    //function to display the window as designed   
    gtk_widget_show(loginWindow);               

    //give control to gtk for running the application until gtk_main_quit() is called
    gtk_main();
    return 0;
}

// called when signup link is clicked

int open_Signup_Form(GtkWidget *widget, gpointer data)
{
      struct user_signup_details new_user_registration;

     gtk_widget_destroy(GTK_WIDGET(loginWindow));
     gtk_main_quit();
     
     sleep(0.5);

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "SignUp.glade", NULL);

    signupWindow = GTK_WIDGET(gtk_builder_get_object(builder, "signUp"));
    gtk_builder_connect_signals(builder, NULL);

    //Get the User registration button widget using the corresponding object from the glade file
    userSignupRegisterButton = GTK_WIDGET(gtk_builder_get_object(builder, "Register"));
    
    //Get username entered in the text field by the user
    userNameTextEntry = GTK_WIDGET(gtk_builder_get_object(builder, "name_text"));
    new_user_registration.signupUsername = userNameTextEntry;

    //Get EmailID entered in the text field by the user
    user_email_address = GTK_WIDGET(gtk_builder_get_object(builder, "email_text"));
    new_user_registration.signupEmailID = user_email_address;
    
    //Get new password entered in the password field by the user
    user_new_password = GTK_WIDGET(gtk_builder_get_object(builder, "set_password_text"));
    new_user_registration.signupPassword = user_new_password;

    //Callback function for new user signup registration button press is called passing the emailID and new password entered
    g_signal_connect(G_OBJECT(userSignupRegisterButton), "clicked", G_CALLBACK(newUserRegistration), (gpointer*)&new_user_registration);
    
    g_signal_connect (G_OBJECT (signupWindow), "destroy", G_CALLBACK (gtk_main_quit), NULL);    
    g_object_unref(builder);

    gtk_widget_show(signupWindow);
    gtk_main();

    return 0;
     
}

// called when forgot Password link is clicked

int open_Forgot_Password(GtkWidget *widget, gpointer data)
{
     
     struct password_reset_details new_password_details;

     gtk_widget_destroy(GTK_WIDGET(loginWindow));
     gtk_main_quit();

     sleep(0.5);

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "set_new_password.glade", NULL);
    
    passwordResetWindow = GTK_WIDGET(gtk_builder_get_object(builder, "setPassword"));
    gtk_builder_connect_signals(builder, NULL);

    //Get the Reset Password Submit button widget using the corresponding object from the glade file
    resetPasswordSubmitButton = GTK_WIDGET(gtk_builder_get_object(builder, "submit"));

    //Get EmailID entered in the text field by the user
    user_email_address = GTK_WIDGET(gtk_builder_get_object(builder, "emailID_text"));
    new_password_details.userEmailID = user_email_address;

    //Get new password entered in the password field by the user
    user_new_password = GTK_WIDGET(gtk_builder_get_object(builder, "newpassword_text"));
    new_password_details.newPassword = user_new_password;

    //Callback function for reset password submit button press is called passing the emailID and new password entered
    g_signal_connect(G_OBJECT(resetPasswordSubmitButton), "clicked", G_CALLBACK(resetPassword), (gpointer*)&new_password_details);

    g_signal_connect (G_OBJECT (passwordResetWindow), "destroy", G_CALLBACK (gtk_main_quit), NULL);
    g_object_unref(builder);

    gtk_widget_show(passwordResetWindow);
    gtk_main();

    return 0;
}

// called when home button is clicked to redirect back to login page from signUp page

int login_Page_Redirect_signUp(GtkWidget *widget, gpointer data)
{
     gtk_widget_destroy(GTK_WIDGET(signupWindow));
     gtk_main_quit();

     sleep(0.5);

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();

    //build gtk app from an external glade file generated using glade tool
   
      gtk_builder_add_from_file (builder, "Login_Window.glade", NULL);
    
    //initialize window widget using the corresponding object from the glade file
   
      loginWindow = GTK_WIDGET(gtk_builder_get_object(builder, "Login"));
      gtk_builder_connect_signals(builder, NULL);
    
    //On window close event, close the gtk loop and quit
      g_signal_connect (G_OBJECT (loginWindow), "destroy", G_CALLBACK (gtk_main_quit), NULL);
      g_object_unref(builder);
    
    //function to display the window as designed
      gtk_widget_show(loginWindow);
    
    //give control to gtk for running the application until gtk_main_quit() is called
      gtk_main();
    
      return 0;

}

// called when home button is clicked to redirect back to login page from ResetPassword page

int login_Page_Redirect_passwordReset(GtkWidget *widget, gpointer data)
{
      gtk_widget_destroy(GTK_WIDGET(passwordResetWindow));
      gtk_main_quit();

      sleep(0.5);

     gtk_init(&argc, &argv);

     builder = gtk_builder_new();

   //build gtk app from an external glade file generated using glade tool

     gtk_builder_add_from_file (builder, "Login_Window.glade", NULL);

   //initialize window widget using the corresponding object from the glade file

      loginWindow = GTK_WIDGET(gtk_builder_get_object(builder, "Login"));
      gtk_builder_connect_signals(builder, NULL);

    //On window close event, close the gtk loop and quit
      g_signal_connect (G_OBJECT (loginWindow), "destroy", G_CALLBACK (gtk_main_quit), NULL);
      g_object_unref(builder);

    //function to display the window as designed
       gtk_widget_show(loginWindow);

    //give control to gtk for running the application until gtk_main_quit() is called
     gtk_main();

      return 0;

}

    
