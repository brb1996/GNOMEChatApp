#include <gtk/gtk.h>
#include "StructDef.h"

void resetPassword (GtkButton *object, gpointer password_reset_data);


//Called when the Login Button is pressed to perform authentication

void resetPassword (GtkButton *object, gpointer password_reset_data)
{
    struct password_reset_details *new_password_details = password_reset_data;
    const gchar *user_emailId, *new_user_password;
    user_emailId = gtk_entry_get_text(GTK_ENTRY((GtkWidget *) new_password_details->userEmailID));
    new_user_password = gtk_entry_get_text(GTK_ENTRY((GtkWidget *) new_password_details->newPassword));
    g_print ("emailId: %s\n", user_emailId);
    g_print ("new password: %s\n", new_user_password);

}

