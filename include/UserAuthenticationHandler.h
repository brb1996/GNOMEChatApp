#include <gtk/gtk.h>
#include "StructDef.h"

void loginData (GtkButton *object, gpointer user_data);


//Called when the Login Button is pressed to perform authentication

void loginData (GtkButton *object, gpointer user_data)
{
    struct user_login_details *auth_details = user_data;
    const gchar *login_username, *login_password;
    login_username = gtk_entry_get_text(GTK_ENTRY((GtkWidget *) auth_details->username));
    login_password = gtk_entry_get_text(GTK_ENTRY((GtkWidget *) auth_details->password));
    g_print ("username: %s\n", login_username);
    g_print ("password: %s\n", login_password);

}

