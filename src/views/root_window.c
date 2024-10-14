/**
 * @brief The implementation
 */
#include <glib-2.0/glib.h>
#include "root_window.h"
#include "interfaces/app_interface.h"
#include "utils/sys_interface.h"
#include "utils/logging.h"

#include "composites/one_button_acknowledge.h"
#include "composites/two_button_popup_overlay.h"

static const char *MSG_OUT_CURSOR_NAME = "msgOutCursor";
static GtkTextMark *msgOutCursor;
static char timestamp[20];  // not sure why it felt better to allocate the memory once

void on_main_wnd_close_clicked(__attribute__((unused)) GtkWidget *srcWidget,
                                __attribute__((unused)) gpointer uData) {
   gtk_main_quit();
}

gboolean on_main_wnd_delete_event(__attribute__((unused)) GtkWidget *srcWidget,
                                    __attribute__((unused)) GdkEvent *event,
                                    __attribute__((unused)) gpointer uData) {
   gtk_main_quit();
   return FALSE;
}


void temp_callback(GtkResponseType prompt_response)
{
   logging_llprintf(LOGLEVEL_DEBUG, "%s", __func__);

   if (prompt_response == GTK_RESPONSE_ACCEPT)
   {
      logging_llprintf(LOGLEVEL_DEBUG, "%s: USER ACCEPTED", __func__);
   }
   else if (prompt_response == GTK_RESPONSE_REJECT)
   {
      logging_llprintf(LOGLEVEL_DEBUG, "%s: USER REJECTED", __func__);
   }
   else
   {
      logging_llprintf(LOGLEVEL_DEBUG, "%s: UNKNOWN RESPONSE", __func__);
   }
}

static gboolean toggle_popup = true;

void on_do_something_button_clicked(__attribute__((unused)) GtkButton *button, __attribute__((unused)) gpointer *user_data)
{
   app_widget_ref_struct *wdgts = (app_widget_ref_struct *) user_data;
   gchar text_entered_by_user[2047];
   gchar build_a_msg_out[2048];

   gboolean use_entered_text = (gtk_entry_buffer_get_length(gtk_entry_get_buffer(GTK_ENTRY(wdgts->w_say_something_entry))) > 0);

   if (use_entered_text){
      snprintf(text_entered_by_user, sizeof(text_entered_by_user), "%s",
               gtk_entry_get_text(GTK_ENTRY(wdgts->w_say_something_entry)));
      print_log_level_msgout(LOGLEVEL_INFO, "%s", gtk_entry_get_text(GTK_ENTRY(wdgts->w_say_something_entry)));
   } else {
      print_log_level_msgout(LOGLEVEL_INFO, "nothing to say?");
   }

   snprintf(build_a_msg_out, sizeof(build_a_msg_out), "%s\n",
            use_entered_text ? text_entered_by_user : "Nothing to do...\n");
   GtkWidget *popup;
   if (toggle_popup)
   {
      popup = two_button_popup_new("Turn it up to 11!", build_a_msg_out,
                             "Rock on!", "That's a nope!",
                             (TwoButtonResponseCallback_T)temp_callback);

   }
   else
   {
      popup = one_button_acknowledge_new("Turn it up to 2!", build_a_msg_out,
                                   "Rock on!",
                                   (OneButtonResponseCallback_T )temp_callback);

   }
   gtk_overlay_add_overlay(GTK_OVERLAY(wdgts->w_home_page_overlay), popup);
   gtk_widget_show_all(popup);
   toggle_popup ^= TRUE;

}


void on_timestamp_selection_combobox_changed(__attribute__((unused)) GtkComboBox *comboBox, __attribute__((unused)) gpointer user_data)
{
   GtkTreeIter tIter;
   GValue current_selection = {0};

   if (gtk_combo_box_get_active_iter(comboBox, &tIter))
   {
      GtkTreeModel *model = gtk_combo_box_get_model(comboBox);
      gtk_tree_model_get_value(model, &tIter, 0, &current_selection);
   }

   logging_llprintf(LOGLEVEL_DEBUG, "%s",
                    g_value_get_string(&current_selection) != NULL ? g_value_get_string(&current_selection) : "selection changed, but we didn't get a good reference for it");
}

void on_basic_items_combo_changed(__attribute__((unused)) GtkComboBox *comboBox, __attribute__((unused)) gpointer user_data)
{
   GtkTreeIter tIter;
   GValue current_selection = {0};

   if (gtk_combo_box_get_active_iter(comboBox, &tIter))
   {
      GtkTreeModel *model = gtk_combo_box_get_model(comboBox);
      gtk_tree_model_get_value(model, &tIter, 0, &current_selection);
   }

   logging_llprintf(LOGLEVEL_DEBUG, "%s",
                    g_value_get_string(&current_selection) != NULL ? g_value_get_string(&current_selection) : "selection changed, but we didn't get a good reference for it");
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void set_msgout_buffer(const char *msgout)
{
   if (get_app_state() == APP_STATE_SUCCESS)
   {  /* Let's not use the MsgOut widget before it's been built */
      GtkTextBuffer  *tvBuff  =  gtk_text_view_get_buffer(GTK_TEXT_VIEW(g_app_widget_refs->w_msg_out_textview));
      GtkTextIter    endIter;
      gtk_text_buffer_get_end_iter(tvBuff, &endIter);

      if (!gtk_text_buffer_get_mark(tvBuff, MSG_OUT_CURSOR_NAME))
      {
         msgOutCursor = gtk_text_mark_new(MSG_OUT_CURSOR_NAME, FALSE);
         gtk_text_buffer_add_mark(tvBuff, msgOutCursor, &endIter);
      }

      gtk_text_buffer_insert(tvBuff, &endIter, msgout, -1);

      // This keeps the latest msgout in view, BUT if you were scrolling up and a new msgout was posted, it will
      // autoscroll to the insertion.  It would be better to only auto-scroll the msgout if the user is not looking
      // at previous messages
      gtk_text_view_scroll_to_mark(GTK_TEXT_VIEW(g_app_widget_refs->w_msg_out_textview), msgOutCursor, 0.0, TRUE, 0.0, 0.0);
   }
}

void print_log_level_msgout(LOGLEVEL loglevel, const char *_format, ...)
{
   if (loglevel >= get_app_log_level()) {
      bool use_ts = get_app_log_w_timestamp_flag();

      // We're not going to "flag" out the timestamp in the memory sizing here, because... who cares if it's too big?
      char ll_msg_out[LOGGING_MAX_MSG_LENGTH + sizeof(timestamp) + (2*sizeof(':')) + sizeof(get_log_level_str(loglevel))];
      char line_out[LOGGING_MAX_MSG_LENGTH];

      va_list arg;
      va_start(arg, _format);
      vsnprintf(line_out, sizeof (line_out), _format, arg);
      va_end(arg);

      if (use_ts)
         get_timestamp(timestamp, sizeof(timestamp));

      snprintf(ll_msg_out, sizeof (ll_msg_out), "%s%s%s:%s\n",
               use_ts ? timestamp:"", use_ts?":":"", get_log_level_str(loglevel), line_out);

      logging_llprintf(loglevel, "%s", line_out);
      set_msgout_buffer(ll_msg_out);
   }
}
