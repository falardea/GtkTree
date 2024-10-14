/**
 * @brief The implementation
 */
#include <gtk/gtk.h>
#include "app_globals.h"
#include "ui_builder.h"
#include "utils/logging.h"
#include "views/composites/temp/view_samples.h"
#include "views/composites/temp/model_samples.h"
#include "views/composites/temp/basic_combo_box.h"

#define GET_WIDGET(wdgt)   appWidgetsT->w_##wdgt = GTK_WIDGET(gtk_builder_get_object(builder, #wdgt))
#define GET_OBJECT(wdgt)   appWidgetsT->g_##wdgt = G_OBJECT(gtk_builder_get_object(builder, #wdgt))

#define GET_WDGT_AND_BIND_SENS2ACTIVE(wdgt, wdgt_sensitive_to) \
            appWidgetsT->w_##wdgt = GTK_WIDGET(gtk_builder_get_object(builder, #wdgt)); \
            g_object_bind_property( appWidgetsT->w_##wdgt_sensitive_to, "active", \
            appWidgetsT->w_##wdgt , "sensitive", \
            G_BINDING_DEFAULT);

app_widget_ref_struct *app_builder(void) {
   GtkBuilder *builder;

   app_widget_ref_struct *appWidgetsT = g_slice_new(app_widget_ref_struct);

   builder = gtk_builder_new();

   if (gtk_builder_add_from_resource(builder, "/resource_path/resources/gtk_tree.glade", NULL) == 0) {
      logging_llprintf(LOGLEVEL_ERROR, "failed to load glade resource");
      return NULL;
   }

   GET_WIDGET(msg_out_textview);
   GET_WIDGET(say_something_entry);
   GET_WIDGET(do_something_button);
   GET_WIDGET(home_page_overlay);

   GET_WIDGET(basic_items_combo);
   GET_WIDGET(timestamp_selection_combobox);

   GET_WIDGET(brand_logo);

   GET_WIDGET(trvwSamplesTable);
   GET_OBJECT(trslctnSelectedSample);

   GET_WIDGET(tbtnEditSelection);
   GET_WIDGET(tbtnCreateRow);
   GET_WIDGET(tbtnDeleteRow);

   GET_WIDGET(ppvrAreYouSure);
   GET_WIDGET(lblPopoverAreYouSureMsg);
   GET_WIDGET(btnAreYouSureConfirm);
   GET_WIDGET(btnAreYouSureCancel);

   // GET_WIDGET(editSampleDateTime);
   GET_WDGT_AND_BIND_SENS2ACTIVE(editSampleDateTime, tbtnEditSelection);
   GET_WDGT_AND_BIND_SENS2ACTIVE(entrySampleHour, tbtnEditSelection);
   GET_WDGT_AND_BIND_SENS2ACTIVE(entrySampleMinute, tbtnEditSelection);
   GET_WDGT_AND_BIND_SENS2ACTIVE(entryMeasurement1, tbtnEditSelection);
   GET_WDGT_AND_BIND_SENS2ACTIVE(entryMeasurement2, tbtnEditSelection);
   GET_WDGT_AND_BIND_SENS2ACTIVE(entryMeasurement3, tbtnEditSelection);
   GET_WDGT_AND_BIND_SENS2ACTIVE(entryMeasurement4, tbtnEditSelection);

   GET_WDGT_AND_BIND_SENS2ACTIVE(entryCalculationA, tbtnEditSelection);
   GET_WDGT_AND_BIND_SENS2ACTIVE(entryCalculationB, tbtnEditSelection);

   GET_WDGT_AND_BIND_SENS2ACTIVE(btnChangeRow, tbtnEditSelection);
   GET_WDGT_AND_BIND_SENS2ACTIVE(btnCancelRowChange, tbtnEditSelection);

   GET_WDGT_AND_BIND_SENS2ACTIVE(lblSampleDate, tbtnEditSelection);

   // Datepicker
   GET_WIDGET(ppvrDatepicker);
   GET_WIDGET(popCalendar);
   GET_WIDGET(popDone);
   GET_WIDGET(popCancel);

   // set up the table column definitions
   build_samples_view(appWidgetsT->w_trvwSamplesTable);
   // build, and possibly populate from <...>, a model of the data to bind to the table as its "TreeModel"
   gtk_tree_view_set_model(GTK_TREE_VIEW(appWidgetsT->w_trvwSamplesTable), get_samples_reference());
   gtk_combo_box_set_model(GTK_COMBO_BOX(appWidgetsT->w_timestamp_selection_combobox), GTK_TREE_MODEL(get_samples_reference()));
   gtk_combo_box_set_active(GTK_COMBO_BOX(appWidgetsT->w_timestamp_selection_combobox), 0);

   build_basic_combo_box(appWidgetsT);

   gtk_builder_connect_signals(builder, appWidgetsT);

   g_object_unref(builder);
   return appWidgetsT;
}
