#include <gtk/gtk.h>
#include "StructDef.h"

void newUserRegistration (GtkButton *object, gpointer new_user_signup_details);


//Called when the Signup button is pressed to register a new user

void newUserRegistration (GtkButton *object, gpointer new_user_signup_details)
{
    struct user_signup_details *new_user_registration = new_user_signup_details;
    const gchar *new_username, *user_emailId, *new_user_password;
    new_username =   gtk_entry_get_text(GTK_ENTRY((GtkWidget *) new_user_registration->signupUsername));
    user_emailId = gtk_entry_get_text(GTK_ENTRY((GtkWidget *) new_user_registration->signupEmailID));
    new_user_password = gtk_entry_get_text(GTK_ENTRY((GtkWidget *) new_user_registration->signupPassword));
    g_print ("emailId: %s\n", user_emailId);
    g_print ("new password: %s\n", new_user_password);
    g_print ("new username: %s\n", new_username);

}
                        
