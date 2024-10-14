/*
 * Created by french on 3/14/24.
*/
#include "view_utils.h"

static void vu_set_widget_text(GtkWidget *destination, const char *display_string)
{
   if (GTK_IS_ENTRY(destination))
      gtk_entry_set_text(GTK_ENTRY(destination), display_string);
   else if (GTK_IS_LABEL(destination))
      gtk_label_set_label(GTK_LABEL(destination), display_string);
   else if (GTK_IS_BUTTON(destination))
      gtk_button_set_label(GTK_BUTTON(destination), display_string);
}

void vu_set_float_widget_text(GtkWidget *destination, const char *float_format, float value)
{
   char display_string[32];

   snprintf(display_string, sizeof(display_string), float_format, value);
   vu_set_widget_text(destination, display_string);
}

void vu_set_double_widget_text(GtkWidget *destination, const char *double_format, double value)
{
   char display_string[32];

   snprintf(display_string, sizeof(display_string), double_format, value);
   vu_set_widget_text(destination, display_string);
}

void vu_clear_float_widget_text(GtkWidget *destination, const char *float_format, float *default_value)
{
   char display_string[32];
   if (default_value != NULL) /* We might have 0 defaults, so explicit NULL check, not just defined check*/
   {
      snprintf(display_string, sizeof(display_string), float_format, default_value);
   }
   else
   {
      display_string[0] = '\0';
   }
   vu_set_widget_text(destination, display_string);
}

void vu_clear_double_widget_text(GtkWidget *destination, const char *double_format, double *default_value)
{
   char display_string[32];
   if (default_value != NULL) /* We might have 0 defaults, so explicit NULL check, not just defined check*/
   {
      snprintf(display_string, sizeof(display_string), double_format, default_value);
   }
   else
   {
      display_string[0] = '\0';
   }
   vu_set_widget_text(destination, display_string);
}

void vu_set_time_widget_text(GtkWidget *destination, const char *datetime_format, struct tm *source)
{
   char display_string[32];
   if (source != NULL){
      strftime(display_string, sizeof(display_string), datetime_format, source);
   } else {
      display_string[0] = '\0';
   }
   vu_set_widget_text(destination, display_string);
}

void vu_clear_time_widget_text(GtkWidget *destination, const char *with_format, const char *default_value)
{
   char display_string[32];
   if (default_value != NULL) /* We might have 0 defaults, so explicit NULL check, not just defined check*/
   {
      snprintf(display_string, sizeof(display_string), with_format, default_value);
   }
   else
   {
      display_string[0] = '\0';
   }
   vu_set_widget_text(destination, display_string);
}
